#include "GraphicManager.h"

#include "PlayerManager.h"

using namespace std;

void GraphicManager::initialize_assets()
{
    AsciiAssets["PLAYER"] =
    {
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
    HANDLE HOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Coord = { (short)X, (short)Y };
    SetConsoleCursorPosition(HOut, Coord);
}

void GraphicManager::SetConsoleSize(int Width, int Height)
{
    HANDLE HOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD BufferSize = { (short)Width, (short)Height };
    SMALL_RECT WindowSize = { 0, 0, (short)(Width - 1), (short)(Height - 1) };
}

void GraphicManager::DrawLayout()
{
    system("cls");

    for (int i = 0; i < 120; i++)
    {
        GoSpace(i, 0); cout << "="; GoSpace(i, 18); cout << "=";
    }
    for (int i = 0; i <= 18; i++)
    {
        GoSpace(0, i); cout << "|"; GoSpace(119, i); cout << "|";
    }

    for (int i = 19; i < 28; i++) {
        GoSpace(0, i); cout << "|";
        GoSpace(76, i); cout << "|";
        GoSpace(119, i); cout << "|";
    }
    for (int i = 0; i < 120; i++)
    {
        GoSpace(i, 28); cout << "=";
    }

    GoSpace(2, 19); cout << "[ SYSTEM LOG ]";
    GoSpace(78, 19); cout << "[ STATUS & INVENTORY ]";

    int Line = 0;
    for (const string& Log : GameLogs)
    {
        GoSpace(2, 21 + Line++);
        cout << "> " << Log;
    }
}

void GraphicManager::DrawInventoryData(PlayerManager& Player)
{
    GoSpace(78, 21); cout << "- GOLD: " << Player.GetGold() << "G";
    GoSpace(78, 22); cout << "- ATK: " << Player.GetStrength();
    GoSpace(78, 24); cout << "[ Inventory ]";
    GoSpace(78, 25); cout << " 1. Recovery (HP)";
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

string GraphicManager::ShowTitle()
{
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

void GraphicManager::DrawAsciiArt(const string& Name, int X, int Y)
{
    if (AsciiAssets.find(Name) == AsciiAssets.end()) return;

    int LineOffset = 0;
    for (const string& Line : AsciiAssets[Name]) {
        GoSpace(X, Y + LineOffset++);
        cout << Line;
    }
}
