#include "SDL3/SDL.h"
#include <vector>

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

class Engine
{
    static std::vector<Key> keys;
    static const char*      keyNames[10];

public:
    static const char* get_key(SDL_Keycode key);
    static void        setup_key(SDL_Keycode key, KeyType type);
};
