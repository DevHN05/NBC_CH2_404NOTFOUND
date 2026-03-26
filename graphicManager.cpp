#include "GraphicManager.h"

using namespace std;

void GraphicManager::GoSpace(int X, int Y) 
{
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (short)X, (short)Y };
    SetConsoleCursorPosition(h_out, coord);
}

void GraphicManager::SetConsoleSize(int Width, int Height) 
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (short)Width, (short)Height };
    SetConsoleScreenBufferSize(out, coord);
    SMALL_RECT rect = { 0, 0, (short)Width - 1, (short)Height - 1 };
    SetConsoleWindowInfo(out, TRUE, &rect);
}

void GraphicManager::DrawLayout() 
{
    system("cls");

    for (int i = 0; i < 110; i++) { GoSpace(i, 0); cout << "="; GoSpace(i, 18); cout << "="; }
    for (int i = 0; i <= 18; i++) { GoSpace(0, i); cout << "|"; GoSpace(109, i); cout << "|"; }

    for (int i = 19; i < 28; i++) {
        GoSpace(0, i); cout << "|";
        GoSpace(70, i); cout << "|";
        GoSpace(109, i); cout << "|";
    }
    for (int i = 0; i < 110; i++) { GoSpace(i, 28); cout << "="; }

    GoSpace(2, 19); cout << "[ SYSTEM LOG ]";
    GoSpace(72, 19); cout << "[ STATUS & INVENTORY ]";

    int line = 0;
    for (const string& log : GameLogs) {
        GoSpace(2, 21 + line++);
        cout << "> " << log;
    }
}

void GraphicManager::AddLog(const string& Log) 
{
    GameLogs.push_back(Log);
    if (GameLogs.size() > 7) GameLogs.pop_front();

    for (int i = 0; i < 7; i++)
    {
        GoSpace(2, 21 + i);
        cout << "                                                                 ";
        if (i < GameLogs.size()) {
            GoSpace(2, 21 + i);
            cout << "> " << GameLogs[i];
        }
    }
}

void GraphicManager::ClearLogs()
{
    GameLogs.clear();

    for (int i = 0; i < 7; i++) {

        GoSpace(2, 21 + i);


        cout << "                                                                 ";
    }

    GoSpace(0, 30);
}

string GraphicManager::ShowTitle() {

    system("cls");
    int start_x = 25, start_y = 10;

    GoSpace(start_x, start_y);     cout << "o  o  o-o  o  o o   o      o  o--o                  o  ";
    GoSpace(start_x, start_y + 1); cout << "|  | o  /o |  | |\\  |      |  |                     |  ";
    GoSpace(start_x, start_y + 2); cout << "o--O | / | o--O | \\ | o-o -o- O-o  o-o o  o o-o   o-O  ";
    GoSpace(start_x, start_y + 3); cout << "   | o/  o    | |  \\| | |  |  |    | | |  | |  | |  |  ";
    GoSpace(start_x, start_y + 4); cout << "   o  o-o     o o   o o-o  o  o    o-o o--o o  o  o-o  ";

    GoSpace(41, start_y + 7); cout << "[ PROJECT : 404 NOT FOUND ]";

    GoSpace(38, start_y + 9); cout << "ENTER YOUR NICKNAME: ";
    string input_name;
    cin >> input_name;

    //Gotoxy(35, start_y + 11); cout << ">> CONNECTION ESTABLISHED: " << input_name;
    GoSpace(38, start_y + 13); cout << "[Press Enter to Start]";

    cin.ignore(100, '\n'); 
    cin.get(); 

    return input_name;
}