#include "gameApp.h"
int main()
{
    gameApp game("my 2D game engine", 800, 600, 60);

    if (game.Init())
    {
        game.Run();
    }

    return 0;
}