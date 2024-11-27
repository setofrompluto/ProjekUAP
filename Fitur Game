#include <ncurses/curses.h>
#include <string>
using namespace std;

int main() {
    initscr(); 
    noecho();  
    cbreak();
    string username;

    clear();
    printw("Masukkan username: ");
    username.clear();
    char v;
        
    while ((v = getch()) != '\n') {
    	username += v;
    	printw("%c", v);
    }

    clear();
    printw("Selamat datang, %s!\n", username.c_str());
    refresh();
    getch();

    endwin();
    return 0;
}
