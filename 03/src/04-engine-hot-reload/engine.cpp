#include "engine.h"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <thread>

std::vector<Key>     Engine::keys;
std::vector<KeyType> Engine::activeKeys;
BaseGame*            Engine::game;

void Engine::setup_key(SDL_Keycode key, KeyType type)
{
    for (int i = 0; i < keys.size(); i++)
        if (keys[i].code == key)
        {
            keys[i].type = type;
            return;
        }
    Key* k  = new Key();
    k->code = key;
    k->type = type;
    keys.push_back(*k);
}

int Engine::get_key(SDL_Keycode key)
{
    for (int i = 0; i < keys.size(); i++)
        if (keys[i].code == key)
            return (int)keys[i].type;
    return -1;
}

bool Engine::key_pressed(KeyType key)
{
    for (int i = 0; i < activeKeys.size(); i++)
        if (activeKeys[i] == key)
            return true;
    return false;
}

void sdl_die(const char* message)
{
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

bool Engine::any_key_pressed()
{
    return activeKeys.size() > 0;
}

int Engine::init()
{
    void*       game_handle = NULL;
    const char* filepath    = "lib/libproj-04.dylib";
    Engine::reload_game(filepath, "lib/tmp.dylib", game_handle);
    auto last_write = std::filesystem::last_write_time(filepath);

    Engine::setup_key(SDLK_w, KeyType::UP);
    Engine::setup_key(SDLK_s, KeyType::DOWN);
    Engine::setup_key(SDLK_a, KeyType::LEFT);
    Engine::setup_key(SDLK_d, KeyType::RIGHT);
    Engine::setup_key(SDLK_q, KeyType::JB0);
    Engine::setup_key(SDLK_e, KeyType::JB1);
    Engine::setup_key(SDLK_r, KeyType::JB2);
    Engine::setup_key(SDLK_f, KeyType::JB3);
    Engine::setup_key(SDLK_RETURN, KeyType::START);
    Engine::setup_key(SDLK_ESCAPE, KeyType::MENU);
    const int     SCREEN_WIDTH  = 960;
    const int     SCREEN_HEIGHT = 540;
    SDL_Window*   window        = NULL;
    SDL_GLContext maincontext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_die("Couldn't initialize SDL");

    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL);

    window = SDL_CreateWindow("Window",
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

    if (window == NULL)
        sdl_die("Couldn't set video mode");

    SDL_Event event;

    bool        done = false;
    SDL_Keycode lastCode;

    while (!done)
    {
        auto current_write_time = std::filesystem::last_write_time(filepath);

        if (current_write_time != last_write)
        {
            std::filesystem::file_time_type next_write_time;
            // wait while library file finish to changing
            for (;;)
            {
                using namespace std::chrono;
                std::this_thread::sleep_for(milliseconds(100));
                next_write_time = std::filesystem::last_write_time(filepath);
                if (next_write_time != current_write_time)
                {
                    current_write_time = next_write_time;
                }
                else
                {
                    break;
                }
            }
            Engine::reload_game(filepath, "lib/tmp.dylib", game_handle);

            if (game == nullptr)
            {
                std::cerr << "next attempt to reload game..." << std::endl;
                continue;
            }

            last_write = next_write_time;
        }
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                event.window.windowID == SDL_GetWindowID(window))
                done = true;
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                int key = Engine::get_key(event.key.keysym.sym);
                if (key != -1)
                    activeKeys.push_back((KeyType)key);
            }
        }
        if (game != NULL)
        {
            game->update();
        }
        activeKeys.clear();
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}

void Engine::reload_game(const char* library_name,
                         const char* tmp_library_name,
                         void*&      old_handle)
{
    system("clear");

    if (game != NULL)
    {
        std::cout << "\nreloading game" << std::endl;
        SDL_UnloadObject(old_handle);
    }

    void* game_handle = SDL_LoadObject(library_name);

    if (game_handle == nullptr)
    {
        std::cerr << "error: failed to load: [" << tmp_library_name << "] "
                  << SDL_GetError() << std::endl;
        return;
    }

    old_handle = game_handle;

    SDL_FunctionPointer create_game_func_ptr =
        SDL_LoadFunction(game_handle, "create_game");

    if (create_game_func_ptr == nullptr)
    {
        std::cerr << "error: no function [create_game] in " << tmp_library_name
                  << " " << SDL_GetError() << std::endl;
        return;
    }

    using create_game_ptr = decltype(&create_game);

    auto create_game_func =
        reinterpret_cast<create_game_ptr>(create_game_func_ptr);

    BaseGame* gameLoaded = create_game_func();

    if (gameLoaded == nullptr)
    {
        std::cerr << "error: func [create_game] returned: nullptr" << std::endl;
        return;
    }
    game = gameLoaded;

    if (game != NULL)
        game->load();
}