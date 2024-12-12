#include <cstring>
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

int aste_x, aste_y, aste_x2, aste_y2;
int terpilih = 0;

void asteroid()
{
    mvprintw(aste_y, aste_x, "            ");
    mvprintw(aste_y + 1, aste_x, "              ");
    mvprintw(aste_y + 2, aste_x, "            ");

    mvprintw(aste_y2, aste_x2, "            ");
    mvprintw(aste_y2 + 1, aste_x2, "              ");
    mvprintw(aste_y2 + 2, aste_x2, "            ");

    aste_x--;
    aste_x2--;

    if (aste_x <= 0)
    {
        aste_x = COLS - 3;
        aste_y = rand() % LINES;
    }

    if (aste_x2 <= 0)
    {
        aste_x2 = COLS - 3;
        aste_y2 = rand() % LINES;
    }

    if (aste_y < LINES - 3)
    {
        mvprintw(aste_y, aste_x,     " (0000)))))");
        mvprintw(aste_y + 1, aste_x, "(000000))))))");
        mvprintw(aste_y + 2, aste_x, " (0000)))))");
    }

    if (aste_y2 < LINES - 3)
    {
        mvprintw(aste_y2, aste_x2,     " (0000)))))");
        mvprintw(aste_y2 + 1, aste_x2, "(000000))))))");
        mvprintw(aste_y2 + 2, aste_x2, " (0000)))))");
    }
    Sleep(10);
}


bool tabrakan(int y, int x)
{
    bool tabrakan_diX = (aste_x <= x + 9 && aste_x + 3 >= x);
    bool tabrakan_diY = (aste_y >= y && aste_y <= y + 2);

    bool tabrakan_diX2 = (aste_x2 <= x + 9 && aste_x2 + 3 >= x);
    bool tabrakan_diY2 = (aste_y2 >= y && aste_y2 <= y + 2);

    return (tabrakan_diX && tabrakan_diY) || (tabrakan_diX2 && tabrakan_diY2);
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

    int skor = 0;
    int kontrol_asteroid = 0;

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
            skor++;
        }

        if (tabrakan(y, x))
        {
            clear();
            mvprintw(LINES / 2, (COLS - strlen("GAME OVER")) / 2, "GAME OVER");
            mvprintw(LINES / 2 + 1, (COLS - strlen("SESIMPEL ITU")) / 2, "SESIMPEL ITU");
            mvprintw(LINES / 2 + 2, (COLS - strlen("SKORMU: %d")) / 2, "SKORMU: %d", skor);
            refresh();
            Sleep(6000); 
            break;
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

void popUp()
{
    if (terpilih == 0)
    {
        mvprintw(LINES - 8, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 7, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 6, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 5, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 4, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 3, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 2, COLS / 2 - 20, "                                        ");
        mvprintw(LINES / 2 + 9, COLS / 2,  "                             ");
        mvprintw(LINES / 2 + 9, (COLS - strlen("Memulai game")) / 2, "Memulai game");
    }
    else if (terpilih == 1)
    {
        mvprintw(LINES - 8, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 7, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 6, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 5, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 4, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 3, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 2, COLS / 2 - 20, "                                        ");
        mvprintw(LINES / 2 + 9, COLS / 2,  "                             ");
        mvprintw(LINES / 2 + 9, (COLS - strlen("Skor mu berapa ya?")) / 2, "Skor mu berapa ya?");
    }
    else if (terpilih == 2)
    {
        mvprintw(LINES - 8, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 7, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 6, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 5, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 4, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 3, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 2, COLS / 2 - 20, "                                        ");
        mvprintw(LINES / 2 + 9, COLS / 2,  "                             ");
        mvprintw(LINES / 2 + 9, (COLS - strlen("Para kontributor keren")) / 2, "Para kontributor keren");
    }
    else if (terpilih == 3)
    {
        mvprintw(LINES - 8, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 7, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 6, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 5, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 4, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 3, COLS / 2 - 20, "                                        ");
        mvprintw(LINES - 2, COLS / 2 - 20, "                                        ");
        mvprintw(LINES / 2 + 9, COLS / 2,  "                             ");
        mvprintw(LINES / 2 + 9, (COLS - strlen("Keluar dari game?")) / 2, "Keluar dari game?");
    }
    refresh();
}

void menuScreen()
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    const char *nama[] = {
        "   __  _  _  ___  ____ ",
        "  (  )( )( )/ __)(_  _)",
        " __)(  )()( \\__ \\  )(  ",
        "(___/  \\__/ (___/ (__) ",
        " ___    __   ___    __  ___ "
        "(   \\  /  \\ (   \\  / _)(  _)",
        ") ) )( () ) ) ) )( (/\\ ) _)",
        "(___/  \\__/ (___/  \\__/(___)",

    };

    int cols_garis = COLS;
    for (int i = 0; i < cols_garis; i++)
    {
        mvprintw(1, i, "=");
        mvprintw(LINES - 1, i, "=");
        Sleep(10);
        refresh();
    }

    int terpilih = 0;

    for (int a = 0; a < COLS; a++)
    {
        mvprintw(1, a, "=");
        mvprintw(LINES - 1, a, "=");
    }

    mvprintw(LINES - LINES + 5, (COLS - strlen("   __  _  _  ___  ____ ")) / 2, "   __  _  _  ___  ____ ");
    mvprintw(LINES - LINES + 6, (COLS - strlen("  (  )( )( )/ __)(_  _)")) / 2, "  (  )( )( )/ __)(_  _)");
    mvprintw(LINES - LINES + 7, (COLS - strlen(" __)(  )()( \\__ \\  )(  ")) / 2, " __)(  )()( \\__ \\  )(  ");
    mvprintw(LINES - LINES + 8, (COLS - strlen("(___/  \\__/ (___/ (__) ")) / 2, "(___/  \\__/ (___/ (__) ");
    mvprintw(LINES - LINES + 9, (COLS - strlen("___    __   ___    __  ___ ")) / 2, "___    __   ___    __  ___ ");
    mvprintw(LINES - LINES + 10, (COLS - strlen("(   \\  /  \\ (   \\  / _)(  _)")) / 2, "(   \\  /  \\ (   \\  / _)(  _)");
    mvprintw(LINES - LINES + 11, (COLS - strlen(" ) ) )( () ) ) ) )( (/\\ ) _)")) / 2, " ) ) )( () ) ) ) )( (/\\ ) _)");
    mvprintw(LINES - LINES + 12, (COLS - strlen("(___/  \\__/ (___/  \\__/(___)")) / 2, "(___/  \\__/ (___/  \\__/(___)");
    refresh();
}

void start()
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
    clear();
    endwin();
}


void menuPilihan()
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    const char *pilihan[] = {
        "Start",
        "Leaderboard",
        "Credits",
        "Exit"};

    bool berjalan = true;

    while (berjalan)
    {
        mvprintw(LINES - LINES + 5, (COLS - strlen("   __  _  _  ___  ____ ")) / 2, "   __  _  _  ___  ____ ");
        mvprintw(LINES - LINES + 6, (COLS - strlen("  (  )( )( )/ __)(_  _)")) / 2, "  (  )( )( )/ __)(_  _)");
        mvprintw(LINES - LINES + 7, (COLS - strlen(" __)(  )()( \\__ \\  )(  ")) / 2, " __)(  )()( \\__ \\  )(  ");
        mvprintw(LINES - LINES + 8, (COLS - strlen("(___/  \\__/ (___/ (__) ")) / 2, "(___/  \\__/ (___/ (__) ");
        mvprintw(LINES - LINES + 9, (COLS - strlen("___    __   ___    __  ___ ")) / 2, "___    __   ___    __  ___ ");
        mvprintw(LINES - LINES + 10, (COLS - strlen("(   \\  /  \\ (   \\  / _)(  _)")) / 2, "(   \\  /  \\ (   \\  / _)(  _)");
        mvprintw(LINES - LINES + 11, (COLS - strlen(" ) ) )( () ) ) ) )( (/\\ ) _)")) / 2, " ) ) )( () ) ) ) )( (/\\ ) _)");
        mvprintw(LINES - LINES + 12, (COLS - strlen("(___/  \\__/ (___/  \\__/(___)")) / 2, "(___/  \\__/ (___/  \\__/(___)");
        refresh();

        for (int i = 0; i < 4; i++)
        {
            if (i == terpilih)
            {
                attron(A_REVERSE);
                attron(A_BOLD);
                mvprintw(i + LINES / 2 + 3, (COLS - strlen(pilihan[i])) / 2, pilihan[i]);
                attroff(A_REVERSE);
                attroff(A_BOLD);
            }
            else
            {
                mvprintw(i + LINES / 2 + 3, (COLS - strlen(pilihan[i])) / 2, pilihan[i]);
            }

            popUp();
        }

        int ch = getch();

        switch (ch)
        {

        case KEY_UP:
            terpilih = (terpilih - 1 + 4) % 4;
            break;

        case KEY_DOWN:
            terpilih = (terpilih + 1) % 4;
            break;

        case 10:
            if (terpilih == 2)
            {
                mvprintw(LINES / 2 + 10, (COLS - strlen("Kelompok 8")) / 2, "Kelompok 8");
                mvprintw(LINES / 2 + 11, (COLS - strlen("Dimas Seto Aji             (2417051052)")) / 2, "Dimas Seto Aji             (2417051052)");
                mvprintw(LINES / 2 + 12, (COLS - strlen("Viandra Thridya Agsatri    (2417051008)")) / 2, "Viandra Thridya Agsatri    (2417051008)");
                mvprintw(LINES / 2 + 13, (COLS - strlen("FX Novryandhika Widyanto   (2457051013)")) / 2, "FX Novryandhika Widyanto   (2457051013)");
                refresh();
                getch();
            }
            else if (terpilih == 3)
            {
                mvprintw(LINES / 2 + 9, (COLS - strlen("Keluar dari game...")) / 2, "Keluar dari game...");
                refresh();
                Sleep(3000);
                berjalan = false;
            }
            else if (terpilih == 0)
            {
                start();
                break;
            }
        }
    }
}
int main()
{
    menuScreen();
    menuPilihan();
    endwin();
    return 0;
}