#include "app.h"
#include "SDL3/SDL.h"
#include "glad/glad.h"
#include <SDL3/SDL_opengl.h>
#include <iostream>

Vector3 Game::get_mouse_position()
{
    float x, y;
    SDL_GetMouseState(&x, &y);
    return Vector3(x, -y, 0.0f);
}

uint32_t last_tick_time = 0;

void sdl_die(const char* message)
{
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

int Engine::get_time()
{
    return SDL_GetTicks();
}

void Engine::start(Game* game)
{
    const int     SCREEN_WIDTH  = 800;
    const int     SCREEN_HEIGHT = 800;
    SDL_Window*   window        = NULL;
    SDL_GLContext maincontext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_die("Couldn't initialize SDL");
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#if defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    window = SDL_CreateWindow(
        "Engine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    if (window == NULL)
        sdl_die("Couldn't set video mode");

    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == NULL)
        sdl_die("Failed to create OpenGL context");
    printf("OpenGL loaded\n");

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    SDL_GL_SetSwapInterval(1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    SDL_Event event;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    bool done = false;

    game->init();

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            else if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                     event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        uint32_t tick_time = SDL_GetTicks();
        game->update((tick_time - last_tick_time) / 1000.0f);
        last_tick_time = tick_time;
        glClear(GL_COLOR_BUFFER_BIT);
        game->render();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}