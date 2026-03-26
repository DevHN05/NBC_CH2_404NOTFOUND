#include "graphicManager.h"

using namespace std;

void graphicManager::go_space(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(hOut, coord);
}

void graphicManager::set_console_size(int width, int height) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (short)width, (short)height };
    SetConsoleScreenBufferSize(out, coord);
    SMALL_RECT rect = { 0, 0, (short)width - 1, (short)height - 1 };
    SetConsoleWindowInfo(out, TRUE, &rect);
}

void graphicManager::draw_layout() {
    system("cls");

    for (int i = 0; i < 110; i++) { go_space(i, 0); cout << "="; go_space(i, 18); cout << "="; }
    for (int i = 0; i <= 18; i++) { go_space(0, i); cout << "|"; go_space(109, i); cout << "|"; }

    for (int i = 19; i < 28; i++) {
        go_space(0, i); cout << "|";
        go_space(70, i); cout << "|";
        go_space(109, i); cout << "|";
    }
    for (int i = 0; i < 110; i++) { go_space(i, 28); cout << "="; }

    go_space(2, 19); cout << "[ SYSTEM LOG ]";
    go_space(72, 19); cout << "[ STATUS & INVENTORY ]";

    int line = 0;
    for (const string& log : gameLogs) {
        go_space(2, 21 + line++);
        cout << "> " << log;
    }
}

void graphicManager::add_log(const string& log) {
    gameLogs.push_back(log);
    if (gameLogs.size() > 7) gameLogs.pop_front();

    for (int i = 0; i < 7; i++)
    {
        go_space(2, 21 + i);
        cout << "                                                                 ";
        if (i < gameLogs.size()) {
            go_space(2, 21 + i);
            cout << "> " << gameLogs[i];
        }
    }
}

void graphicManager::clear_logs()
{
    gameLogs.clear();

    for (int i = 0; i < 7; i++) {

        go_space(2, 21 + i);


        cout << "                                                                 ";
    }

    go_space(0, 30);
}

string graphicManager::show_title() {
    system("cls");
    int startX = 25, startY = 10;

    go_space(startX, startY);     cout << "o  o  o-o  o  o o   o      o  o--o                  o  ";
    go_space(startX, startY + 1); cout << "|  | o  /o |  | |\\  |      |  |                     |  ";
    go_space(startX, startY + 2); cout << "o--O | / | o--O | \\ | o-o -o- O-o  o-o o  o o-o   o-O  ";
    go_space(startX, startY + 3); cout << "   | o/  o    | |  \\| | |  |  |    | | |  | |  | |  |  ";
    go_space(startX, startY + 4); cout << "   o  o-o     o o   o o-o  o  o    o-o o--o o  o  o-o  ";

    go_space(41, startY + 7); cout << "[ PROJECT : 404 NOT FOUND ]";

    go_space(38, startY + 9); cout << "ENTER YOUR NICKNAME: ";
    string inputName;
    cin >> inputName;

    //Gotoxy(35, startY + 11); cout << ">> CONNECTION ESTABLISHED: " << inputName;
    go_space(38, startY + 13); cout << "[Press Enter to Start]";

    cin.ignore(100, '\n'); 
    cin.get(); 

    return inputName;
}