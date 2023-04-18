#include "SDL3/SDL.h"
#include <vector>

#ifndef DYNDLL
#define DYNDLL
#endif

enum class KeyType
{
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3,
    JB0   = 4,
    JB1   = 5,
    JB2   = 6,
    JB3   = 7,
    START = 8,
    MENU  = 9
};

struct Key
{
    SDL_Keycode code;
    KeyType     type;
};

class BaseGame
{

public:
    virtual ~BaseGame()   = default;
    virtual void load()   = 0;
    virtual void update() = 0;
};

class Engine
{
    static std::vector<Key>     keys;
    static std::vector<KeyType> activeKeys;
    static BaseGame*            game;

private:
    static void setup_key(SDL_Keycode key, KeyType type);
    static int  get_key(SDL_Keycode key);
    static void reload_game(const char* library_name, void*& old_handle);

public:
    static bool key_pressed(KeyType key);
    static bool any_key_pressed();
    static int  init();
};

extern "C" DYNDLL BaseGame* create_game();