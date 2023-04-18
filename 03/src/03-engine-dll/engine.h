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

private:
    static void setup_key(SDL_Keycode key, KeyType type);
    static int  get_key(SDL_Keycode key);

public:
    static bool key_pressed(KeyType key);
    static bool any_key_pressed();
    static int  init(BaseGame* inst);
};