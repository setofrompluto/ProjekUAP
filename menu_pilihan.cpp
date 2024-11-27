#include <cstring>
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
using namespace std;

int main()
{

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    const char *pilihan[] = {
        "Start",
        "Settings",
        "About",
        "Exit"};

    int j = 133;
    for (int i = 0; i < COLS; i++)
    {
        mvprintw(1, i, "=");
        mvprintw(31, j--, "=");
        Sleep(100);
        refresh();
    }

    int terpilih = 0;
    bool berjalan = true, setting = false;
    while (berjalan)
    {

        /*
        Ini berfungsi untuk memperbarui baris dan kolom
        sesuai dengan ukuran terminal. Jadi ini berguna
        kalo misal awalnya terminalnya kecil terus mau di maximize.
        Dengan begitu, tulisan yang keluar ga akan ancur berantakan.
        */
        resize_term(LINES, COLS);

        clear();

        for (int a = 0; a < COLS; a++)
        {
            mvprintw(1, a, "=");
            mvprintw(31, a, "=");
        }

        for (int i = 0; i < 4; i++)
        {
            if (i == terpilih)
            {
                attron(A_REVERSE);
                attron(A_BOLD);
                mvprintw(i + LINES / 2 + 1, (COLS - strlen(pilihan[i])) / 2, pilihan[i]);
                attroff(A_REVERSE);
                attroff(A_BOLD);
            }
            else
            {
                mvprintw(i + LINES / 2 + 1, (COLS - strlen(pilihan[i])) / 2, pilihan[i]);
            }

            // Apa fungsi strlen? Dia berfungsi untuk menghitung panjang
            // dari sebuah string. Misal strlen(pilihan[0]). Nah disini
            // kalo dia di cout, dia bakal cout angka 5 karena Start itu
            // memiliki 5 huruf. strlen juga membaca spasi.
            //////////////////////////////////////////////////////

            if (terpilih == 0)
            {
                mvprintw(LINES / 2 + 6, (COLS - strlen("Memulai game")) / 2, "Memulai game");
            }
            else if (terpilih == 1)
            {
                mvprintw(LINES / 2 + 6, (COLS - strlen("Pengaturan game ini")) / 2, "Pengaturan game ini");
            }
            else if (terpilih == 2)
            {
                mvprintw(LINES / 2 + 6, (COLS - strlen("Siapa aja sih yang buat?")) / 2, "Siapa aja sih yang buat?");
            }
            else if (terpilih == 3)
            {
                mvprintw(LINES / 2 + 6, (COLS - strlen("Keluar dari game?")) / 2, "Keluar dari game?");
                refresh();
            }
        }

        refresh();

        // Ini bagian untuk naik turun di menu pilihan
        // dimana kondisi yang dibaca adalah
        // KEY_UP (panah naik) dan KEY_DOWN (panah turun).
        bool status_suara = true;
        int ch = getch();

        switch (ch)
        {

        // Kalo naik, "terpilih" yang awalnya 0 (berarti ada di pilihan "Start")
        // bakal turun ke bawah, karena 0 - 1 = -1 lalu -1 + 4 = 3 dan 3 % 4 = 3.
        // Jadi si "terpilih" akan pindah langsung ke pilihan terakhir, yaitu "Exit"
        // Kenapa 3 dan bukannya 4? Karena dalam array indeks elemen pertamanya adalah 0.
        case KEY_UP:
            if (status_suara = true)
            {
                Beep(600, 200);
            }
            else
            {
                Beep(0, 0);
            }
            terpilih = (terpilih - 1 + 4) % 4;
            break;

        // Disini sama, cuman "terpilih" yang awalnya 0 ditambah bukan dikurang.
        // Jadi 0 + 1 = 1 lalu 1 % 4 = 1. Dengan begini, si "terpilih" akan
        // pindah ke pilihan 1, yaitu "Options".
        // Nilai "terpilih" akan tetap, selama tombol naik maupun turun belum ditekan.
        // Fungsi modulus 4 adalah untuk menjaga agar "terpilih" tetap berada dalam rentang angka 4 (cmiiw).
        case KEY_DOWN:
            if (status_suara = true)
            {
                Beep(600, 200);
            }
            else
            {
                Beep(0, 0);
            }
            terpilih = (terpilih + 1) % 4;
            break;

        case 10:
            if (terpilih == 2)
            {
                mvprintw(LINES / 2 + 7, COLS / 2 - 20, "                Kelompok 8");
                mvprintw(LINES / 2 + 8, COLS / 2 - 20, "Dimas Seto Aji             (2417051052)");
                mvprintw(LINES / 2 + 9, COLS / 2 - 20, "Viandra Thridya Agsatri    (2417051008)");
                mvprintw(LINES / 2 + 10, COLS / 2 - 20, "FX Novryandhika Widyanto   (2457051013)");
                refresh();
                getch();
            }
            else if (terpilih == 3)
            {
                mvprintw(LINES / 2 + 6, (COLS - strlen("Keluar dari game...")) / 2, "Keluar dari game...");
                refresh();
                sleep(3);
                berjalan = false;
            }
            else if (terpilih == 1)
            {
                clear();
                bool keMenuUtama = false;
                int pilihanSettings = 0;
                const char *pengaturan[] = {"Sound: ON", "Sound: OFF", "Back"};
                do
                {
                    for (int a = 0; a < COLS; a++)
                    {
                        mvprintw(1, a, "=");
                        mvprintw(31, a, "=");
                    }
                    for (int sc = 0; sc < 3; sc++)
                    {
                        if (sc == pilihanSettings)
                        {
                            attron(A_REVERSE);
                            attron(A_BOLD);
                            mvprintw(sc + LINES / 2 + 1, (COLS - strlen(pengaturan[sc])) / 2, pengaturan[sc]);
                            attroff(A_REVERSE);
                            attroff(A_BOLD);
                        }
                        else
                        {
                            mvprintw(sc + LINES / 2 + 1, (COLS - strlen(pengaturan[sc])) / 2, pengaturan[sc]);
                        }
                    }
                    int tombolSettings = getch();

                    switch (tombolSettings)
                    {
                    case KEY_UP:
                        pilihanSettings = (pilihanSettings - 1 + 3) % 3;
                        break;

                    case KEY_DOWN:
                        pilihanSettings = (pilihanSettings + 1) % 3;
                        break;

                    case 10:
                        if (pilihanSettings == 0)
                        {
                            status_suara = true;
                            mvprintw(LINES / 2 + 5, (COLS - strlen("Sound turned ON")) / 2, "Sound turned ON");
                            getch();
                        }
                        else if (pilihanSettings == 1)
                        {
                            status_suara = false;
                            mvprintw(LINES / 2 + 5, (COLS - strlen("Sound turned OFF")) / 2, "Sound turned OFF");
                            getch();
                        }
                        else if (pilihanSettings == 2)
                        {
                            mvprintw(LINES / 2 + 5, (COLS - strlen("Kembali ke menu utama")) / 2, "Kembali ke menu utama");
                            refresh();
                            getch();
                            keMenuUtama = true;
                        }
                        break;
                    }

                } while (!keMenuUtama);
                refresh();
                break;
            }
            break;
        }
    }
    endwin();
    return 0;
}
