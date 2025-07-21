#include "gameApp.h"
int main()
{
    gameApp game("my 2D game engine", 640, 480, 60);

    if (game.Init())
    {
        game.Run();
    }

    return 0;
}