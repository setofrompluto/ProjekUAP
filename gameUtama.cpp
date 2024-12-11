#include <ncurses/curses.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>
using namespace std; 

int aste_x, aste_y, aste_x2, aste_y2;

void asteroid()
{
    mvprintw(aste_y, aste_x, "            ");
    mvprintw(aste_y + 1, aste_x, "              ");
    mvprintw(aste_y + 2, aste_x, "            ");

    mvprintw(aste_y2, aste_x2, "            ");
    mvprintw(aste_y2 + 1, aste_x2, "              ");
    mvprintw(aste_y2 + 2, aste_x2, "            ");

    aste_x--, aste_x2--;
    if (aste_x <= 0)
    {
        aste_x = COLS - 3;
        aste_x2 = COLS - 3;
        aste_y = rand() % LINES;
        aste_y2 = rand() % LINES;
    }

    if (aste_y < LINES - 3 && aste_y2 < LINES - 3)
    {
        mvprintw(aste_y, aste_x,     " (0000)))))");
        mvprintw(aste_y + 1, aste_x, "(000000))))))");
        mvprintw(aste_y + 2, aste_x, " (0000)))))");

        mvprintw(aste_y2, aste_x2,     " (0000)))))");
        mvprintw(aste_y2 + 1, aste_x2, "(000000))))))");
        mvprintw(aste_y2 + 2, aste_x2, " (0000)))))");
        Sleep(10);
    }
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

    int kontrol_asteroid = 0;

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
                y = y - 1;
            break;

        case KEY_DOWN:
            if (y < LINES - 3)
                y = y + 1;
            break;

        case KEY_RIGHT:
            if (x < COLS - 10)
                x = x + 1;
            break;

        case KEY_LEFT:
            if (x > 0)
                x = x - 1;
            break;

        default:
            break;
        }

        mvprintw(old_y, old_x, eraser);
        mvprintw(old_y + 1, old_x, eraser);
        mvprintw(old_y + 2, old_x, eraser);

        mvprintw(y, x, plane1);
        mvprintw(y + 1, x, plane2);
        mvprintw(y + 2, x, plane3);

        kontrol_asteroid++;

        if (kontrol_asteroid >= 10)
        {
            asteroid();
            kontrol_asteroid = 0;
        }
    }
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
