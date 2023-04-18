#include "engine.h"
#include <iostream>
#include <string>

using namespace std;
vector<Key>     Engine::keys;
vector<KeyType> Engine::activeKeys;

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

int Engine::init(BaseGame* inst)
{
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

    window = SDL_CreateWindow(
        "Window", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    if (window == NULL)
        sdl_die("Couldn't set video mode");

    SDL_Event event;

    bool        done = false;
    SDL_Keycode lastCode;
    if (inst != NULL)
        inst->load();

    while (!done)
    {
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
        if (inst != NULL)
            inst->update();
        activeKeys.clear();
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}