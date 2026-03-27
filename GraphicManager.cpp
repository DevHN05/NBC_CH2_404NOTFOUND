#include "GraphicManager.h"

using namespace std;

void GraphicManager::initialize_assets()
{
    AsciiAssets["PLAYER"] = {
    "   ____   ", // 1
    "  |    |  ", // 2
    "  (^_^)   ", // 3
    "  <)  (>  ", // 4
    "  --||--  ", // 5
    "    ||    ", // 6
    "   /  \\   ", // 7
    "  /|  |\\  ", // 8
    " | |  | | ", // 9
    " | |  | | ", // 10
    " | |  | | ", // 11
    " | |  | | ", // 12
    " | |  | | ", // 13
    " |/____\\| ", // 14
    };
}

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
    SMALL_RECT rect = { 0, 0, (short)(Width - 1), (short)(Height - 1) };
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
    int StartX = 25, StartY = 10;

    GoSpace(StartX, StartY);     cout << "o  o  o-o  o  o   o   o      o    o--o                  o  ";
    GoSpace(StartX, StartY + 1); cout << "|  | o  /o |  |   |\\  |      |    |                     |  ";
    GoSpace(StartX, StartY + 2); cout << "o--O | / | o--O   | \\ | o-o -o-   O-o  o-o o  o o-o   o-O  ";
    GoSpace(StartX, StartY + 3); cout << "   | o/  o    |   |  \\| | |  |    |    | | |  | |  | |  |  ";
    GoSpace(StartX, StartY + 4); cout << "   o  o-o     o   o   o o-o  o    o    o-o o--o o  o  o-o  ";

    GoSpace(41, StartY + 7); cout << "[ PROJECT : 404 NOT FOUND ]";

    GoSpace(38, StartY + 9); cout << "ENTER YOUR NICKNAME: ";
    string InputName;
    cin >> InputName;

    //Gotoxy(35, start_y + 11); cout << ">> CONNECTION ESTABLISHED: " << input_name;
    GoSpace(42, StartY + 13); cout << "[Press Enter to Start]";

    cin.ignore(100, '\n');
    cin.get();

    return InputName;
}

void GraphicManager::DrawAsciiArt(const string& name, int x, int y)
{
    if (AsciiAssets.find(name) == AsciiAssets.end()) return;

    int lineOffset = 0;
    for (const string& line : AsciiAssets[name]) {
        GoSpace(x, y + lineOffset++);
        cout << line;
    }
}
