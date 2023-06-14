#include "Game.h"

int main()
{
    srand(time(NULL));
    Game game;

    while (game.isRunning())
    {
        game.update();

        game.render();
    }
    return 0;
}