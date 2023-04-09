#include <SDL3/SDL_version.h>
#include <iostream>

void write(const char* head, const SDL_version& v)
{
    using namespace std;
    cout << head;
    cout << static_cast<int>(v.major) << '.';
    cout << static_cast<int>(v.minor) << '.';
    cout << static_cast<int>(v.patch) << endl;
}

int main()
{
    SDL_version ver = { 0, 0, 0 };

    SDL_GetVersion(&ver);
    write("linked: ", ver);

    SDL_VERSION(&ver)
    write("compiled: ", ver);

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}