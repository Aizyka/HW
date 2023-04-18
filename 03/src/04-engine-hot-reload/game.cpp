#include "engine.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

struct Line
{
    int pos;
    int diff;
};

class MyGame : public BaseGame
{
    vector<Line> lines;
    int          line_length_add = 2;
    int          area_width      = 20;
    int          lines_count     = 2;

public:
    void load() override
    {
        for (int i = 1; i <= lines_count; i++)
        {
            Line* ln = new Line();
            ln->pos  = i * 5;
            // ln->diff = 1;
            ln->diff = i % 2 == 0 ? 1 : -1;
            lines.push_back(*ln);
        }
    }

    void update() override
    {
        cout << "\r"
             << "[[";
        for (int i = 0; i < area_width; i++)
        {
            bool founded = false;
            for (int j = 0; j < lines.size(); j++)
            {
                if (i > lines[j].pos - line_length_add &&
                    i < lines[j].pos + line_length_add)
                {
                    founded = true;
                    break;
                }
            }
            if (founded)
                cout << "=";
            else
                cout << " ";
        }
        cout << "]]" << flush;
        for (int i = 0; i < lines.size(); i++)
        {
            for (int j = 0; j < lines.size(); j++)
            {
                if (i == j)
                    continue;
                if (lines[i].pos + lines[i].diff ==
                    lines[j].pos + lines[j].diff)
                {
                    lines[i].diff *= -1;
                    lines[j].diff *= -1;
                }
            }
            lines[i].pos += lines[i].diff;
            if (lines[i].pos + line_length_add >= area_width ||
                lines[i].pos - line_length_add <= 0)
                lines[i].diff *= -1;
        }
        using namespace std::chrono;
        std::this_thread::sleep_for(milliseconds(40));
    }
};

OM_DECLSPEC BaseGame* create_game()
{
    return new MyGame();
}