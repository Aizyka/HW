#pragma once
class Texture
{
    unsigned int program;

public:
    char* path;
    void  load();
    void  use();
};
