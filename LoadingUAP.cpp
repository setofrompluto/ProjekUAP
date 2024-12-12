#include <ncurses/ncurses.h>
#include <windows.h>
#include <iostream>
using namespace std;

void loading()
{
    initscr();

    int x = 0;
    while (x <= 100)
    {
        clear();
        mvprintw(LINES / 2, (COLS - strlen("Loading... %d%%")) / 2, "Loading... %d%%", x);
        refresh();
        Sleep(100);
        x += 1;
    }

    Sleep(110);
    clear();

    mvprintw(LINES / 2, (COLS - strlen("Press enter to CONTINUE!!!!!")) / 2, "Press enter to CONTINUE!!!!!");
    getch();
}