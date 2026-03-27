#include "GraphicManager.h"
#include "PlayerManager.h"
#include <windows.h>

using namespace std;

void GraphicManager::InitializeAssets()
{
    AsciiAssets["PLAYER"] =
    {
        "             .---.          .---.          ", // 1. 귀/뿔 부분
        "            |     \\        /     |         ", // 2. 귀의 실루엣
        "             \\     \\  __  /     /          ", // 3. 머리 뒷라인
        "              '---  [ ^_^ ]  ---'          ", // 4. 살짝 돌아본 얼굴
        "       ________/           \\               ", // 5. 목에서 등으로 이어지는 선
        "   ---'                     '---.          ", // 6. 넓은 등 근육
        "  /      SYSTEM      ONLINE      \\         ", // 7. 등 위 시스템 텍스트
        " /   .-------------------------.  \\        ", // 8. 척추/장갑 라인
        "|   /                           \\  |   _   ", // 9. 뒷다리 허벅지 시작
        "|  |        (  Tail  )           | |  / )  ", // 10. 풍성한 꼬리 표현
        "|  |         \\      /            | | / /   ", // 11. 꼬리 2
        "'--'          '----'             '--' /    ", // 12. 뒷발 바닥
        "             /__|__|__\\               '     ", // 13. 지지대 (13줄 제한)
    };

    AsciiAssets["SLIME"] = {
        "        .-----------.        ", // 1. 상단 안테나/돌기
        "     .-'             '-.      ", // 2. 부드러운 상단 라인
        "   /     .---------.     \\     ", // 3. 내부 코어 보호막
        "  |     /   [X_X]   \\     |    ", // 4. 에러 발생한 코어 눈
        " /     |    ERROR    |     \\   ", // 5. 상태 메시지
        "|      \\____________/      |   ", // 6. 코어 하단부
        "|   .-------------------.   |   ", // 7. 내부 전선/회로 느낌
        "\\  /                     \\  /  ", // 8. 출렁이는 몸체 옆면
        " '|      01011010110      |'    ", // 9. 흘러나오는 데이터 코드
        "  \\      ___________      /     ", // 10. 바닥 접촉면 시작
        "   '----/           \\----'      ", // 11. 바닥에 퍼진 질감
        "       '-------------'          ", // 12. 마감 (12줄 제한)
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

void GraphicManager::HitShake(const string& TargetKey, int StartX, int StartY, int Force)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int Offsets[] = { -2 - Force, 2 + Force, -1- Force, 1 + Force, 0 };

    for (int Offset : Offsets)
    {
        if (Offset != 0)
            SetConsoleTextAttribute(hConsole, 0x0C);
        else
            SetConsoleTextAttribute(hConsole, 0x0F);

        int LineOffset = 0;
        for (const string& Line : AsciiAssets[TargetKey])
        {
            GoSpace(StartX + Offset, StartY + LineOffset++);
            cout << "  " << Line << "  ";
        }
        Sleep(50);
    }

    SetConsoleTextAttribute(hConsole, 0x0F);
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

void GraphicManager::DrawAsciiArt(const string& Player,const string& Monster)
{
    if (AsciiAssets.find(Player) == AsciiAssets.end()) return;
    if (AsciiAssets.find(Monster) == AsciiAssets.end()) return;

    if (AsciiAssets.count("PLAYER") > 0)
    {
        int StartX = 12;
        int StartY = 5;  // 기존보다 위로 올림
        int LineOffset = 0;
        for (const string& Line : AsciiAssets["PLAYER"])
        {
            GoSpace(StartX, StartY + LineOffset++);
            cout << Line;
        }
    }

    if (AsciiAssets.count(Monster) > 0)
    {
        int StartX = 74;
        int StartY = 1;
        int LineOffset = 0;
        for (const string& Line : AsciiAssets[Monster])
        {
            GoSpace(StartX, StartY + LineOffset++);
            cout << Line;
        }
    }
}
