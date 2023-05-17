#include "input.h"
#include <algorithm>
std::vector<KeyCode> Input::button;
std::vector<KeyCode> Input::buttonUp;
std::vector<KeyCode> Input::buttonDown;
std::vector<uint8_t> Input::mouseButton;
std::vector<uint8_t> Input::mouseButtonUp;
std::vector<uint8_t> Input::mouseButtonDown;

bool Input::GetKeyDown(KeyCode key)
{
    return std::find(buttonDown.begin(), buttonDown.end(), key) !=
           buttonDown.end();
}
bool Input::GetKey(KeyCode key)
{
    return std::find(button.begin(), button.end(), key) != button.end();
}
bool Input::GetKeyUp(KeyCode key)
{
    return std::find(buttonUp.begin(), buttonUp.end(), key) != buttonUp.end();
}
bool Input::GetMouseButtonDown(uint8_t mouse)
{
    return std::find(mouseButtonDown.begin(), mouseButtonDown.end(), mouse) !=
           mouseButtonDown.end();
}
bool Input::GetMouseButton(uint8_t mouse)
{
    return std::find(mouseButton.begin(), mouseButton.end(), mouse) !=
           mouseButton.end();
}
bool Input::GetMouseButtonUp(uint8_t mouse)
{
    return std::find(mouseButtonUp.begin(), mouseButtonUp.end(), mouse) !=
           mouseButtonUp.end();
}