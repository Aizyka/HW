#include "engine.h"
#include <iostream>
#include <string>

using namespace std;
const char* keyNames[10] = { "Up",
                             "Down",
                             "Left",
                             "Right",
                             "Joystick button 0",
                             "Joystick button 1",
                             "Joystick button 2",
                             "Joystick button 3",
                             "Start",
                             "Menu" };

class MyGame : public BaseGame
{
public:
    void load() override { cout << "loaded" << endl; }

    void update() override
    {
        if (Engine::any_key_pressed())
        {
            cout << "\nPressed buttons:\n" << endl;
            for (int i = 0; i < 10; i++)
            {
                if (Engine::key_pressed((KeyType)i))
                    cout << keyNames[i] << endl;
            }
        }
    }
};

int main()
{
    MyGame* game = new MyGame();
    Engine::init(static_cast<BaseGame*>(game));
    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}