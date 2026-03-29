#include "GraphicManager.h"
#include "PlayerManager.h"
#include "Inventory.h"
#include "ItemManager.h"
#include <windows.h>

using namespace std;

void GraphicManager::InitializeAssets()
{
    AsciiAssets["PLAYER"] =
    {
        "             .---.          .---.          ",
        "            |     \\        /     |         ",
        "             \\     \\  __  /     /          ",
        "              '---  [ ^_^ ]  ---'          ",
        "       ________/           \\               ",
        "   ---'                     '---.          ",
        "  /      SYSTEM      ONLINE      \\         ",
        " /   .-------------------------.  \\        ",
        "|   /                           \\  |   _   ",
        "|  |        (  Tail  )           | |  / )  ",
        "|  |         \\      /            | | / /   ",
        "'--'          '----'             '--' /    ",
        "             /__|__|__\\               '     ", // 13. 지지대 (13줄 제한)
    };
    //Monster
    AsciiAssets["파수꾼 :: 테스트 봇"] =
    {
        "        .-----------.          ",
        "     .-'             '-.       ",
        "   /     .---------.     \\     ",
        "  |     /   [X_X]   \\     |    ",
        " /     |    ERROR    |     \\   ",
        "|      \\____________/      |   ",
        "|   .-------------------.   |   ",
        "\\  /                     \\  /   ",
        " '|      01011010110      |'    ",
        "  \\      ___________      /     ",
        "   '----/           \\----'      ",
        "       '-------------'          ",
    };
    AsciiAssets["파수꾼 :: 시스템 보안 봇"] =
    {
        "        .=====.           ",
        "    .---'-----'---.       ",
        "   /  [|[ (O) ]|]  \\      ",
        "  /   '-----------'   \\     ",
        " /   .-------------.   \\    ",
        "|   /  > SECURED <  \\   |   ",
        "|  |   [SYSTEM OK]   |  |   ",
        "|   \\_____________/   |   ",
        " \\__       ||       __/    ",
        "  | |======||======| |     ",
        "  | |      ||      | |     ",
        "  '='      ''      '='     ",
    };
    AsciiAssets["방랑자 :: delete ptr;"] =
    {
        "     .-----.           ",
        "   _/__|___\\___        ",
        "  /   _____     \\      ",
        " |   / ^_^ \\     |     ",
        " |  |  [???]  |  |     ",
        "  \\  \\_______/  /     ",
        "  /\\__  ~  __ /\\      ",
        " / | [del_ptr] | \\     ",
        "/__|_ _ _ _ _ _|_\\    ",
        "     |   |             ",
        "    _|_ _|_            ",
        " ..null..0x00..*..     ",
    };
    AsciiAssets["분쇄자 :: Break"] =
    {
        "     ._____________.       ",
        "     |=============|       ",
        "  .--|_____________|--.    ",
        " /   ||_///___\\\\\_||    \\",
        "|    || > [BREAK] < ||  |",
        " \\   ||_\\\\\\___///_||   /",
        "  '--|_____________|--'    ",
        "     |=============|       ",
        "    / _____   _____ \\      ",
        "   < [#####] [#####] >     ",
        "    \\_@@@@@___@@@@@_/      ",
        "     '-----' '-----'       ",
    };
    AsciiAssets["침략자 :: 2147483648"] =
    {
        "       .-------------.        ",
        "    .-'  _   _   _   '-.      ",
        "   /   ((_)) ((_)) ((_)) \\    ",
        "|  < F U L L > [OVERFLOW] |  ",
        "\\   ((_)) ((_)) ((_))   /    ",
        " '--._______     _______.-'   ",
        "    /       \\___/       \\     ",
        "   /  /\\  /\\  |  /\\  /\\  \\    ",
        "  |  |##||##| | |##||##|  |   ",
        "  |  |##||##| | |##||##|  |   ",
        "   \\  \\/  \\/  |  \\/  \\/  /    ",
        "    '-------------------'     ",
    };
    AsciiAssets["암살자 :: 세미콜론"] =
    {
        "    ._____.      ",
        "   / _____ \\     ",
        "  | / ^_^ \\ |    ",
        "  || [!!!] ||    ",
        "  \\_\\_____/_/    ",
        "  /\\\\_   _//\\    ",
        " /  \\\\_|_//  \\   ",
        "|_| [CORE] |_|   ",
        "| |  _|_|  | |   ",
        "| / /|||\\ \\ |   ",
        "|___|||||___|    ",
        "    '---'        ",
    };
    AsciiAssets["BRIDGE"] =
    {
        "    ._____________.       ",
        "   /  __________  \\      ",
        "  I  I [ LOG ] I  I     ",
        "  I_ I [BRIDGE] I _I     ",
        " /__\\___________/__\\    ",
        "[===================]   ",
        "[===================]   ",
        "[===================]   ",
        " \\__/[~~~~~~~~~]\\__/    ",
        "    I ~ ~ ~ ~ ~ I       ",
        "    I___________I       ",
        "        '-----'           ",
    };
    AsciiAssets["FOREST"] =
    {
        "       .  .  ..  .  .       ",
        "    . (  ) (  ) (  ) .      ",
        "   . /\\  /\\  /\\  /\\  .",
        "  . //\\\\//\\\\//\\\\//\\\\ .",
        " . ///\\\\\\///\\\\\\///\\\\\\ .",
        "|  < F O R E S T >  |      ",
        " \\  ///\\\\\\///\\\\\\///  /",
        "  | ||||||||||||||| |      ",
        "  | ||||[S O S]|||| |      ",
        "  /_\\\\\\\\\\\\_\\\\\\\\\\\\_\\\\\\_\\",
        " (____ whispers ____)      ",
        "  '---------------'        ",
    };
    AsciiAssets["DATANOISE"] =
    {
        "     ._________________.     ",
        "  .--| 01101  10110   |--.  ",
        " /   |#@$!%&*&%!$@#&@#|   \\ ",
        "|    | D A T A N O I S E |   | ",
        " \\   | 10110  01101   |   /  ",
        "  '--|__#&@!%$*&@#&__ |--'  ",
        "      |  ||  ||  ||  |       ",
        "      | _||_ || _||_ |       ",
        "     <[0101][1010][01]>      ",
        "      \\_  _  _  _  _/        ",
        "        '*'@#&!%$*@#*'        ",
        "         '---------'         ",
    };
    AsciiAssets["GRAVITY"] =
    {
        "    .^^^^^^^^^^^^^^^^^^^.    ",
        " .--| ^ ^ ^ [ANTI-G] ^ ^ |--.",
        "/   |  ^ /^ ^ ^ / ^ /^  |   \\",
        "|   | ^ / A V I T Y ^ ^ |   |",
        "\\   |  ^ / ^ G R ^ ^ /  |  / ",
        " '--|___^^^^^^^^^^^^^___|--' ",
        "     |  ||  ||  ||  |        ",
        "     | _||_ || _||_ |        ",
        "    <[^^^^][^^^^][^^]>       ",
        "     \\_  _  _  _  _/         ",
        "       'v'v'v'v'v'v'         ",
        "        '---------'          ",
    };
    AsciiAssets["CLIFF"] =
    {
        "   ___  [CLIFF]  ___   ___   ",
        "  /   \\_________/   \\ /   \\  ",
        " |::::|_________|::::|:::::| ",
        " |:::::::::::::::::::::::::| ",
        " |:::::::::::::::::::::::::| ",
        " |:::::::::::::::::::::::::| ",
        " |:::::::::::::::::::::::::| ",
        " |:::::::::::::::::::::::::| ",
        " |:::::::::::::::::::::::::| ",
        "  \\:::::::::::::::::::::::/  ",
        "   |:::::::::::::::::::::|   ",
        "   '---------------------'   ",
    };
    AsciiAssets["처형자 :: 가비지 컬렉션"] =
    {
        "     ._________________.    ",
        "  .-' \\               / '-.  ",
        " /   __\\_____________/__   \\ ",
        "|   / < [I N T A K E] > \\   | ",
        "|  |   (( _ _ _ _ _ ))   |  | ",
        "|   \\ <#$@!%*&#@$%> /   |   ",
        "|    '-------------'    |   ",
        "| [G A R B A G E   C O L.] |",
        "| [L E C T I O N  v1.0] |   ",
        "| ::::::::::::::::::::::|   ",
        " \\_____________________/    ",
        "    '---------------'       ",
    };
    AsciiAssets["소거자 :: 언디클레어드"] =
    {
        "      .----------.             ",
        "   .-'            '-.          ",
        "  /   < >      < >   \\         ",
        " |           __           |    ",
        "/       .---'  '---.       \\   ",
        "       / [UNDECLARED] \\       |  ",
        "      |  <404 ERROR>  |      |  ",
        "\\      \\_____________/      /   ",
        " '--._______    _______.--'    ", //
        "    /  /\\  /\\  /\\  /\\  \\       ",
        "   (  (__)(__)(__)(__)  )      ", //
        "    '------------------'       ", //
    };
    AsciiAssets["투영자 :: 댕글링 포인터"] =
    {
        "           .-------------------.  ",
        "        .-'   (@#$%%**%%$#@)    '-.  ",
        "     .-'   (#####@@####@@#####)    '-.  ",
        "   /   (#####(@*VOID*@)#####)         \\        ",
        " /_____(#####(@XXXXXX@)#####)___________\\",
        "|_______( [X] 0xDEADBEEF [X] )____________|",
        " \\~~~~~(#####@@####@@#####)~~~~~/~~~~~  /",
        "   \\   (#####@@####@@#####)   /       /",
        "     '-.   (#####@@####@@#####)   .-' ",
        "        '-.   (@#$%%**%%$#@)   .-'   ",
        "           '-------------------'   ",
        "          [ FATAL EXCEPTION ]      ",
    };
    AsciiAssets["BROKENACTOR"] =
    {
        "     _______________________  ",
        "    /                      /| ",
        "   /      [LOADING...]    / | ",
        "  /______________________/  | ",
        " |  ____________________  |  |",
        " | | [X] BROKEN_CUBE [X]| |  |",
        " | |  0xDEADBEEF / NAN  | | / ",
        " | |____________________| |/  ",
        " |  ::::::::::::::::::::  |   ",
        " |__#%&@!$*&%#@!$*&%#@!$__|   ",
        "[SYSTEM_HALT] [SEGFAULT]      ",
        " '----------------------'     ",
    };
    AsciiAssets["UNINITARRAY"] =
    {
        "         _______________________           ",
        "        /                      /|          ",
        "       /   < > [MIMIC] < >    / |          ",
        "      /______________________/  |          ",
        "     |  ____________________  |  |         ",
        "     | |  V V V V V V V V V | |  |         ",
        "     | | [X] UNINITARRAY [X]| | /          ",
        "     | |  A A A A A A A A A | |/           ",
        "     | |____________________| |            ",
        "     |  ::::::::::::::::::::  |            ",
        "    [ G N A W ] [ S E G F A U L T ]       ",
        "     '----------------------'              ",
    };
    //NPC
    AsciiAssets["SHOPKEEPER"] =
    {
        "      ╔══════════════════════╗      ", // 1. 상점 간판 상단
        "      ║   💰 MYSTERY SHOP 💰 ║      ", // 2. 유니코드 아이콘 활용
        "      ╚══════════╦═══════════╝      ", // 3. 간판 하단 연결
        "   __________   _║_     __________   ", // 4. 지붕 및 천장 구조
        "  /          \\ ( ●_● ) /          \\  ", // 5. 상점 주인 (안경 쓴 현자 느낌)
        " |    [⚔️]    |   /█\\  |    [🧪]   | ", // 6. 좌우 진열대 (검과 포션)
        " |    [🛡️]    | _/   \\_|    [📜]   | ", // 7. 좌우 진열대 (방패와 주문서)
        " 🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱 ", // 8. 카운터 뒷배경 벽돌
        " ╔════════════════════════════════╗ ", // 9. 메인 카운터 상단
        " ║ 📂 [Buy] 📂 [Sell]  📂[Exit]   ║ ", // 10. 상점 UI 메뉴 버튼 느낌
        " ╠════════════════════════════════╣ ", // 11. 카운터 중간 구분선
        " ║  Welcome! What do you need?    ║ ", // 12. 주인의 대사 텍스트
        " ║  [ G: 1,250 ]        [ W: 45 ] ║ ", // 13. 소지금 및 무게 정보
        " ╚════════════════════════════════╝ ", // 14. 카운터 하단 마감
        "   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   ", // 15. 바닥 그림자/질감 (15줄)
    };
}

void GraphicManager::GoSpace(int X, int Y) const
{
    COORD Coord = { static_cast<short>(X), static_cast<short>(Y) };
    SetConsoleCursorPosition(HOut, Coord);
}

void GraphicManager::SetConsoleSize(int Width, int Height) const
{
    if (HOut == INVALID_HANDLE_VALUE) return;

    COORD BufferSize = { static_cast<short>(Width), static_cast<short>(Height) };

    //창 크기 설정
    SMALL_RECT WindowSize = { 0, 0, static_cast<short>(Width - 1), static_cast<short>(Height - 1) };

    SMALL_RECT MinWindow = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(HOut, TRUE, &MinWindow);

    SetConsoleScreenBufferSize(HOut, BufferSize);
    SetConsoleWindowInfo(HOut, TRUE, &WindowSize);
}

void GraphicManager::DrawLayout() const
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

    int Line = 0;
    for (const string& Log : GameLogs)
    {
        GoSpace(2, 21 + Line++);
        cout << "> " << Log;
    }
}

void GraphicManager::DrawLobbyStatus(PlayerManager& Player) const
{
    GoSpace(40, 8); cout << " [ " << Player.GetNickname() << " ]  Lv." << Player.GetLevel();
    GoSpace(5, 2);  cout << ">> FIELD: SYSTEM CORE";
    GoSpace(40, 9); cout << " HP:  [ ";
    int MaxHpBar = 20;
    int FilledHPGauge = (int)(Player.GetHealth() * MaxHpBar / Player.GetMaxHealth());
    FilledHPGauge = min(FilledHPGauge, MaxHpBar);

    for (int i = 0; i < MaxHpBar; i++)
    {
        if (i < FilledHPGauge)
            cout << "■";
        else
            cout << " ";
    }
    cout << " ] " << Player.GetHealth() << " / " << Player.GetMaxHealth();

    GoSpace(40, 10); cout << " EXP: [ ";
    int MaxExpBar = 20;
    int FilledExpGauge = (int)(Player.GetExperience() * MaxExpBar / Player.GetMaxExperience());
    FilledExpGauge = min(FilledExpGauge, MaxExpBar);

    for (int i = 0; i < MaxExpBar; i++)
    {
        if (i < FilledExpGauge)
            cout << "■";
        else
            cout << " ";
    }
    cout << " ] " << Player.GetExperience() << " / " << Player.GetMaxExperience();
}

void GraphicManager::DrawInventoryData(PlayerManager& Player) const
{
    GoSpace(2, 19); cout << "[ SYSTEM LOG ]";

    GoSpace(78, 19); cout << "[ STATUS]";
    //oSpace(78, 20); cout << "- LV: " << Player.GetLevel();
    //GoSpace(78, 21); cout << "- EXP: " << Player.GetExperience() << " / " << Player.GetMaxExperience();
    GoSpace(78, 20); cout << "- ATK: " << Player.GetStrength();
    GoSpace(78, 21); cout << "- Dex: " << Player.GetDexterity();
    GoSpace(78, 22); cout << "- Int: " << Player.GetIntelligence();
    GoSpace(78, 23); cout << "- Lux: " << Player.GetLuck();

    GoSpace(94, 19); cout << "[ Inventory ]";
    GoSpace(94, 20); cout << "- GOLD: " << Player.GetGold() << " G";
    for (int i =0; i < Player.GetPlayerInventory().size(); ++i)
    {
        GoSpace(94, 21 + i); cout << "- " << Player.GetPlayerInventory()[i]->GetName();
    }
 }

void GraphicManager::AddLog(const string& Log)
{
    GameLogs.push_back(Log);
    if (GameLogs.size() > 7)
        GameLogs.pop_front();

    for (int i = 0; i < 7; i++)
    {
        GoSpace(2, 21 + i);
        cout << "                                                                          ";
        if (i < GameLogs.size())
        {
            GoSpace(2, 21 + i);
            cout << "> " << GameLogs[i];
        }
    }
}

void GraphicManager::ClearLogs()
{
    GameLogs.clear();

    for (int i = 0; i < 8; i++)
    {
        GoSpace(2, 20 + i);

        cout << "                                                                          ";
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

string GraphicManager::ShowTitle() const
{
    system("cls");
    int StartX = 30, StartY = 12;

    GoSpace(0, 0);      cout <<"________________________________________________________________________________________________________________________",
    GoSpace(0, 1);      cout <<"|[ SYSTEM_TERMINAL_V4.04 ]                                                                     [ STATUS: 0xDEADC0DE ]  |" ,
    GoSpace(0, 2);      cout <<"|======================================================================================================================|",
    Sleep(50);
    const char* logs[] = {
        "| [CPU] [|||||||||||||||||||||||||||||||          ] 72% | [MEM] [■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□□] 92% | [TEMP] 42'C   |",
        "|----------------------------------------------------------------------------------------------------------------------|",
        "| [NET_LOG]                                                                                                            |",
        "| > TRACE: 127.0.0.1 ... OK                                                                                            |",
        "| > ADDR_RECURSIVE ... DETECTED                                                                                        |",
        "| > ERR: SEG_FAULT (0xDEADBEEF)                                                                                        |"
    };
    for(int i=0; i<6; i++) {
        GoSpace(0, 3+i); cout << logs[i];
        Sleep(50); // 0.05초 간격
    }
    GoSpace(0, 9);      cout <<"|                                                                                                                      |",
    GoSpace(0, 10);     cout <<"|                                                                                                                      |",
    GoSpace(0, 11);     cout <<"|                                                                                                                      |",
    GoSpace(0, 12);     cout <<"|                                                                                                                      |",
    GoSpace(0, 13);     cout <<"|                                                                                                                      |",
    GoSpace(0, 14);     cout <<"|                                                                                                                      |",
    GoSpace(0, 15);     cout <<"|                                                                                                                      |",
    GoSpace(0, 16);     cout <<"|                                                                                                                      |",
    GoSpace(0, 17);     cout <<"|                                                                                                                      |",
    GoSpace(0, 18);     cout <<"|                                                                                                                      |",
    GoSpace(0, 19);     cout <<"|                                                                                                                      |",
    GoSpace(0, 20);     cout <<"|                                                                                                                      |",
    GoSpace(0, 21);     cout <<"|                                                                                                                      |",
    GoSpace(0, 22);     cout <<"|                                                                                                                      |",
    GoSpace(0, 23);     cout <<"|                                                                                                                      |",
    GoSpace(0, 24);     cout <<"| [STORAGE]                                                                                                            |",
    GoSpace(0, 25);     cout <<"| SEC_A: [■■■■■■■□□] 70%                                                                                               |",
    GoSpace(0, 26);     cout <<"| SEC_B: [■■■□□□□□□] 30%                                                                                               |",
    GoSpace(0, 27);     cout <<"| SEC_C: [■■■■■■■■■] 100%                                                                                              |",
    GoSpace(0, 28);     cout <<"|                                                                                                                      |",
    GoSpace(0, 29);     cout <<"|______________________________________________________________________________________________________________________|",
    GoSpace(0, 30);     cout <<"| [CMD] : /START  /OPTIONS  /RECOVERY  /SHUTDOWN                                          [TERMINAL_READY]  _          |",
    GoSpace(0, 31);     cout <<"|______________________________________________________________________________________________________________________|";

    Sleep(300);
    GoSpace(StartX, StartY);     cout << "o  o  o-o  o  o   o   o      o    o--o                  o  ";
    Sleep(50);
    GoSpace(StartX, StartY + 1); cout << "|  | o  /o |  |   |\\  |      |    |                     |  ";
    Sleep(50);
    GoSpace(StartX, StartY + 2); cout << "o--O | / | o--O   | \\ | o-o -o-   O-o  o-o o  o o-o   o-O  ";
    GoSpace(StartX, StartY + 3); cout << "   | o/  o    |   |  \\| | |  |    |    | | |  | |  | |  |  ";
    GoSpace(StartX, StartY + 4); cout << "   o  o-o     o   o   o o-o  o    o    o-o o--o o  o  o-o  ";

    GoSpace(41, StartY + 7); cout << "[ PROJECT : 404 NOT FOUND ]";

    GoSpace(38, StartY + 9); cout << "ENTER YOUR NICKNAME: ";

    string InputName;
    while (true)
    {
        GoSpace(59, StartY + 9);

        getline(cin, InputName);

        if (InputName.empty())
        {
            continue;
        }

        break;
    }

    GoSpace(42, StartY + 13); cout << "[Press Enter to Start]";

    cin.ignore(100, '\n');
    //cin.get();

    return InputName;
}

void GraphicManager::DrawAsciiCombatArt(const string& Player,const string& Monster)
{
    if (AsciiAssets.find(Player) == AsciiAssets.end()) return;
    if (AsciiAssets.find(Monster) == AsciiAssets.end()) return;

    if (AsciiAssets.count("PLAYER") > 0)
    {
        int LineOffset = 0;
        for (const string& Line : AsciiAssets["PLAYER"])
        {
            int StartY = 5;
            int StartX = 12;
            GoSpace(StartX, StartY + LineOffset++);
            cout << Line;
        }
    }

    if (AsciiAssets.count(Monster) > 0)
    {
        int LineOffset = 0;
        for (const string& Line : AsciiAssets[Monster])
        {
            int StartY = 1;
            int StartX = 74;
            GoSpace(StartX, StartY + LineOffset++);
            cout << Line;
        }
    }
}

void GraphicManager::DrawAsciiArt(const string& Name, const int& X,const int& Y)
{
    if (AsciiAssets.find(Name) == AsciiAssets.end()) return;

    if (AsciiAssets.count(Name) > 0)
    {
        int LineOffset = 0;
        for (const string& Line : AsciiAssets[Name])
        {
            GoSpace(X, Y + LineOffset++);
            cout << Line;
        }
    }

}
