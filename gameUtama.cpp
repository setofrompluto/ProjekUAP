#include <ncurses/curses.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>
using namespace std; 

int aste_x, aste_y;

void asteroid()
{
    mvprintw(aste_y, aste_x, "   ");

    aste_x--;
    if (aste_x < 0)
    {
        aste_x = COLS - 3;
        aste_y = rand() % LINES;
    }

    mvprintw(aste_y, aste_x, "000");
    refresh();
    Sleep(100);
}

void playGame()
{
    srand(time(0));

    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);

    const char plane1[] = ">==||+\\\\";
    const char plane2[] = "  >||++==>";
    const char plane3[] = ">==||+//";
    const char eraser[] = "          ";
    int y = 10, x = 20;

    int ch = getch();

    aste_x = COLS - 3;
    aste_y = rand() % LINES;

    while ((ch = getch()) != 'q')
    {
        int old_y = y;
        int old_x = x;

        switch (ch)
        {
        case KEY_UP:
            if (y > 0)
                y--;
            break;
        case KEY_DOWN:
            if (y < LINES - 3)
                y++;
            break;
        case KEY_RIGHT:
            if (x < COLS - 10)
                x++;
            break;
        case KEY_LEFT:
            if (x > 0)
                x--;
            break;
        }

        mvprintw(old_y, old_x, eraser);
        mvprintw(old_y + 1, old_x, eraser);
        mvprintw(old_y + 2, old_x, eraser);

        mvprintw(y, x, plane1);
        mvprintw(y + 1, x, plane2);
        mvprintw(y + 2, x, plane3);

        asteroid();
    }
    refresh();
    endwin();
}

string get_username()
{
    string username;
    mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Enter your username: ");
    echo();
    mvgetstr(LINES / 2, COLS / 2 - 5, &username[0]); 
    noecho();
    return username;
}

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(1);
    string username = get_username();
    clear(); 

    mvprintw(LINES / 2, COLS / 2 - 10, "Welcome, %s!", username.c_str());
    mvprintw(LINES / 2 + 1, COLS / 2 - 10, "Press any key to start the game...");
    refresh();
    getch(); 
    clear();
    playGame();

    endwin();
    return 0;
}
