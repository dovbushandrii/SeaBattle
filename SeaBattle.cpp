#include <iostream>
#include <string>
#include <conio.h>
#include "SeaBattle.h"

using namespace std;

int main()
{
    /*char key = 0;
    while (key != 13)
    {
        key = _getch();
        cout << (int)key;
        if (key == 0 || key == -32)
        {
            key = _getch();
            cout << (int)key;
        }
    }*/
    SeaBattleGame game;
    game.startgame();

    return 0;
}

