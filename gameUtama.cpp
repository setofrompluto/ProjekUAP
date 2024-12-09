#include <ncurses/ncurses.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

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

int main()
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
            {
                y = y - 1;
            }
            else
            {
                y = y - 0;
            }
            break;

        case KEY_DOWN:
            if (y < LINES - 3)
            {
                y = y + 1;
            }
            else
            {
                y = y + 0;
            }
            break;

        case KEY_RIGHT:
            if (x < COLS - 10)
            {
                x = x + 1;
            }
            else
            {
                x = x + 0;
            }
            break;

        case KEY_LEFT:
            if (x > 0)
            {
                x = x - 1;
            }
            else
            {
                x = x - 0;
            }
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

        asteroid();
    }
    refresh();

    endwin();
    return 0;
}