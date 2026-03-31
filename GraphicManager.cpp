#include "GraphicManager.h"
#include "PlayerManager.h"
#include "LoggerSystem.h"
#include "GameSystem.h"
#include "BaseMonster.h"
#include "Inventory.h"
#include "BaseItem.h"
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
        "  /   '-----------'  \\     ",
        " /   .-------------.  \\    ",
        "|   /  > SECURED <  \\  |   ",
        "|  |   [SYSTEM OK]   |  |   ",
        "|   \\_____________/    |   ",
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
        " / | [del_ptr] |\\     ",
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
        " /   ((_)) ((_)) ((_))   \\    ",
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
        "|    | D A T A N O I S E |  | ",
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
        "  /   \\_________/   \\ /   \\",
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
        "|  |   (( _ _ _ _ _ ))   |   | ",
        "|   \\ <#$@!%*&#@$%> /   |   |",
        "|    '-------------'     |   |",
        "| [G A R B A G E   C O L.]   |",
        "| [L E C T I O N  v1.0]  |   |",
        "| :::::::::::::::::::::: |   |",
        " \\_____________________/___/",
        "    '----------------------'",
    };
    AsciiAssets["소거자 :: 언디클레어드"] =
    {
        "      .----------.            ",
        "   .-'            '-.         ",
        "  /   < >      < >    \\      ",
        " |           __           |    ",
        "/       .---'  '---.       \\ ",
        "|      / [UNDECLARED] \\    |  ",
        "|      |  <404 ERROR> |     |  ",
        "\\     \\_____________/    /   ",
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
    AsciiAssets["INVENTORY"] =
    {
        "           .---.               ",
        "          /_____\\              ",
        "      ___|`^--^` |___          ",
        "     |   |---|---|   |         ",
        "     |   |---|---|   |         ",
        "  .--|   |   |   |   |--.      ",
        " /   |   |   |   |   |   \\     ",
        "|    /---------------\\    |    ",
        "|   /   ___________   \\   |    ",
        "|  |   /           \\   |  |    ",
        "|  |  |   [|||||]   |  |  |    ",
        "'__|  |             |  |__'    ",
        "   |  |  .-------.  |  |       ",
        "   |  |  |  Bag  |  |  |       ",
        "   |  |  '-------'  |  |       ",
        "   |  |_____________|  |       ",
        "   |                   |       ",
        "   \\   /^^^^^^^^^^^\\   /       ",
        "    \\_________________/        "
    };
    //Logo
    AsciiAssets["YOUDIED"] =
    {
        "▒█████ █████                       ▒██████████   ▒███              ▒█████",
        "▒▒███ ▒▒███                         ▒███▒▒▒▒███  ▒▒▒               ▒▒███ ",
        " ▒▒███▒███    ██████  █████ ████    ▒███   ▒▒███ ▒███   ██████   ███████ ",
        "  ▒▒█████    ███▒▒███▒▒███ ▒███     ▒███    ▒███ ▒███  ███▒▒███ ███▒▒███ ",
        "   ▒▒███    ▒███ ▒███ ▒███ ▒███     ▒███    ▒███ ▒███ ▒███████ ▒███ ▒███ ",
        "    ▒███    ▒███ ▒███ ▒███ ▒███     ▒███    ███  ▒███ ▒███▒▒   ▒███ ▒███ ",
        "   ▒█████   ▒▒██████  ▒▒████████   ▒██████████  ▒█████▒▒██████ ▒▒████████",
        "   ▒▒▒▒▒     ▒▒▒▒▒▒    ▒▒▒▒▒▒▒▒    ▒▒▒▒▒▒▒▒▒▒   ▒▒▒▒▒  ▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒ "
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

    // 1. 최소 크기 방어 (120x29 미만으로 작아지지 않게)
    int targetW = (Width > 120) ? Width : 120;
    int targetH = (Height > 29) ? Height : 29;

    // 2. 버퍼 크기 설정 (화면 너비)
    COORD bufferSize = { static_cast<short>(targetW), static_cast<short>(targetH) };

    // 3. 창 크기 설정 구역 (Small Rect)
    SMALL_RECT windowSize = { 0, 0, static_cast<short>(targetW - 1), static_cast<short>(targetH - 1) };

    // [중요] 창 크기를 먼저 아주 작게 만들었다가 키워야 오류가 안 납니다.
    SMALL_RECT minWindow = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(HOut, TRUE, &minWindow);

    // 버퍼 크기를 먼저 키우고
    SetConsoleScreenBufferSize(HOut, bufferSize);
    // 그 다음 창 크기를 키웁니다
    SetConsoleWindowInfo(HOut, TRUE, &windowSize);
}

void GraphicManager::UpdateWindowSize()
{
    CONSOLE_SCREEN_BUFFER_INFO Csbi;
    if (GetConsoleScreenBufferInfo(HOut, &Csbi))
    {
        int w = Csbi.srWindow.Right - Csbi.srWindow.Left + 1;
        int h = Csbi.srWindow.Bottom - Csbi.srWindow.Top + 1;

        this->CurrentWidth = (w > 120) ? w : 120;
        this->CurrentHeight = (h > 29) ? h : 29;

        this->OffsetX = this->CurrentWidth - 120;
        this->OffsetY = this->CurrentHeight - 29;

        this->MainBottom  = (this->CurrentHeight * 64) / 100;
        this->SplitColumn = (this->CurrentWidth * 63) / 100;
        this->RightEdge   = this->CurrentWidth - 1;
        this->BottomEdge  = this->CurrentHeight - 1;
    }
}

void GraphicManager::DrawLayout() const
{
    system("cls");

    for (int i = 0; i <= RightEdge; i++)
    {
        GoSpace(i, 0);          cout << "=";
        GoSpace(i, MainBottom); cout << "=";
    }
    for (int i = 0; i <= MainBottom; i++)
    {
        GoSpace(0, i);         cout << "|";
        GoSpace(RightEdge, i); cout << "|";
    }

    for (int i = MainBottom + 1; i < BottomEdge; i++)
    {
        GoSpace(0, i);           cout << "|";
        GoSpace(SplitColumn, i); cout << "|";
        GoSpace(RightEdge, i);   cout << "|";
    }

    for (int i = 0; i <= RightEdge; i++)
    {
        GoSpace(i, BottomEdge); cout << "=";
    }

    int line = 0;
    int logStartY = MainBottom + 2;

    for (const string& Log : GameLogs)
    {
        if (logStartY + line < BottomEdge)
        {
            GoSpace(2, logStartY + line++);
            cout << "> " << Log;
        }
    }
}

void GraphicManager::DrawCombatLayOut() const
{
    for (int y = 1; y < MainBottom; y++)
    {
        GoSpace(1, y);

        for (int x = 1; x < RightEdge; x++)
        {
            cout << " ";
        }
    }
}

void GraphicManager::DrawLobbyStatus(PlayerManager& Player) const
{
    int centerX = SplitColumn / 2 - 10;
    int centerY = MainBottom / 2;

    GoSpace(centerX, centerY); cout << " [ " << Player.GetNickname() << " ]  Lv." << Player.GetLevel();
    GoSpace(5, 2);  cout << ">> FIELD: SYSTEM CORE";

    // HP Bar
    GoSpace(centerX, centerY + 1); cout << " HP:  [ ";
    int MaxHpBar = 20;
    int FilledHPGauge = (int)(Player.GetHealth() * MaxHpBar / Player.GetMaxHealth());
    FilledHPGauge = min(FilledHPGauge, MaxHpBar);
    for (int i = 0; i < MaxHpBar; i++) cout << (i < FilledHPGauge ? "■" : " ");
    cout << " ] " << Player.GetHealth() << " / " << Player.GetMaxHealth();

    // EXP Bar
    GoSpace(centerX, centerY + 2); cout << " EXP: [ ";
    int MaxExpBar = 20;
    int FilledExpGauge = (int)(Player.GetExperience() * MaxExpBar / Player.GetMaxExperience());
    FilledExpGauge = min(FilledExpGauge, MaxExpBar);
    for (int i = 0; i < MaxExpBar; i++) cout << (i < FilledExpGauge ? "■" : " ");
    cout << " ] " << Player.GetExperience() << " / " << Player.GetMaxExperience();
}

void GraphicManager::DrawInventoryData(PlayerManager& Player) const
{
    //GoSpace(2, MainBottom + 1); cout << "[ SYSTEM LOG ]";

    int statusX = SplitColumn + 2;
    int startY = MainBottom + 1;

    GoSpace(statusX, startY); cout << "[ STATUS ]";
    GoSpace(statusX, startY + 1); cout << "- ATK: " << Player.GetStrength();
    GoSpace(statusX, startY + 2); cout << "- Dex: " << Player.GetDexterity();
    GoSpace(statusX, startY + 3); cout << "- Int: " << Player.GetIntelligence();
    GoSpace(statusX, startY + 4); cout << "- Lux: " << Player.GetLuck();

    int invX = statusX + 16;
    if (invX + 20 > RightEdge) invX = statusX;

    GoSpace(invX, startY); cout << "[ Inventory ]";
    GoSpace(invX, startY + 1); cout << "- GOLD: " << Player.GetGold() << " G";
    for (int i = 0; i < Player.GetPlayerInventory().size(); ++i)
    {
        if (startY + 2 + i < BottomEdge) {
            GoSpace(invX, startY + 2 + i);
            cout << "- " << Player.GetPlayerInventory()[i]->GetName();
        }
    }
 }

void GraphicManager::DrawGameOver(PlayerManager& Player)
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();
    DrawLayout();
    DrawInventoryData(Player);

    int targetX = (CurrentWidth / 2) - (72 / 2);

    int targetY = (MainBottom / 2) - (8 / 2);

    DrawAsciiArt("YOUDIED",targetX, targetY );

    int Input;

    Ls.LogPlayerDeath();
    CommandAddLog("1. 다시 컴파일하기 / 2. 끝내기");
    cin >> Input;

    //게임 다시하기
    if (Input == 1)
    {
        GameSystem& Gs = GameSystem::GetInstance();
        Gs.StartGame();
    }
    else// 게임 끄기
    {
        exit(0);
    }
}

void GraphicManager::DrawDiceRoll(int RollHead, int MaxNumber)
{
    //애니메이션 연출 (주사위가 막 굴러가는 느낌)
    LoggerSystem& Ls = LoggerSystem::GetInstance();
    Ls.hideCursor();

    for (int i = 0; i < 15; i++)
    {
        int tempRoll = (rand() % MaxNumber) + 1;

        DrawCustomDice(tempRoll, MaxNumber);

        Sleep(50 + (i * 10));
    }

    Sleep(200);
    DrawCustomDice(RollHead, MaxNumber);

    int textX = (CurrentWidth / 2) - 12;
    int textY = (MainBottom / 2) + 4;
    GoSpace(textX, textY);
    cout << ">>>  DICE RESULT: " << RollHead << "  <<<";

    Sleep(1000);
}

void GraphicManager::DrawCustomDice(int Number, int MaxNumber)
{
    int diceW = 11;
    int diceH = 5;

    int startX = (CurrentWidth / 2) - (diceW / 2);
    int startY = (MainBottom / 2) - (diceH / 2);

    GoSpace(startX, startY);     cout << ".-------.";
    GoSpace(startX, startY + 1); cout << "|       |";

    GoSpace(startX, startY + 2);
    if (Number < 10)
    {
        cout << "|   " << Number << "   |";
    }
    else
    {
        cout << "|   " << Number << "  |";
    }

    GoSpace(startX, startY + 3); cout << "|       |";
    GoSpace(startX, startY + 4); cout << "'-------'";
}

void GraphicManager::AddLog(const string& Log)
{
    int maxLogLines = BottomEdge - MainBottom - 3;
    if (maxLogLines < 1)
        maxLogLines = 1;

    GameLogs.push_back(Log);
    while (GameLogs.size() > maxLogLines)
    {
        GameLogs.pop_front();
    }

    int logStartY = MainBottom + 3;
    int logWidth = SplitColumn - 4;

    for (int i = 0; i < maxLogLines; i++)
    {
        GoSpace(2, logStartY + i);

        for(int j = 0; j < logWidth; j++)
            cout << " ";

        if (i < GameLogs.size())
        {
            GoSpace(2, logStartY + i);
            cout << "> " << GameLogs[i];
        }
    }
}

void GraphicManager::CommandAddLog(const string& Log)
{
    int targetY = MainBottom + 2;
    int startX = 2;
    int clearWidth = SplitColumn - 4;

    GoSpace(startX, targetY - 1);
    for (int x = 0; x < clearWidth; x++)
    {
        cout << " ";
    }

    GoSpace(startX, targetY);
    for (int x = 0; x < clearWidth; x++)
    {
        cout << " ";
    }

    GoSpace(startX, targetY - 1);
    cout << "  [System Log]";

    GoSpace(startX, targetY);
    cout << "> " << Log;
}

void GraphicManager::ClearLogs()
{
    GameLogs.clear();

    int LogStartY = MainBottom + 1;
    int LogEndY = BottomEdge - 1;
    int ClearWidth = SplitColumn - 4;

    for (int y = LogStartY; y <= LogEndY; y++)
    {
        GoSpace(2, y);

        for (int x = 0; x < ClearWidth; x++)
        {
            cout << " ";
        }
    }

    GoSpace(0, BottomEdge);
}

void GraphicManager::HitMonsterShake(const string& TargetKey, int Force)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int Offsets[] = { -2 - Force, 2 + Force, -1- Force, 1 + Force, 0 };

    int StartX = SplitColumn + ((RightEdge - SplitColumn) * 10 / 100);
    int StartY = (MainBottom * 10) / 100;

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

void GraphicManager::HitPlayerShake(const string& TargetKey, int Force)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int Offsets[] = { -2 - Force, 2 + Force, -1- Force, 1 + Force, 0 };

    int StartX = (SplitColumn * 10) / 100;
    int StartY = (MainBottom * 25) / 100 + 1;

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

void GraphicManager::BossAppearance(const string& BossKey)
{
    for(int i = 0; i < 3; i++)
    {
        int AlertX = CurrentWidth / 2 - 15;
        int AlertY = MainBottom / 2;

        GoSpace(AlertX, AlertY);
        cout << " [ WARNING: SYSTEM INTRUSION ] ";
        Sleep(200);

        GoSpace(AlertX, AlertY);
        cout << "                               ";
        Sleep(100);
    }

    int StartX = SplitColumn + ((RightEdge - SplitColumn) * 10 / 100);
    int StartY = (MainBottom * 10) / 100;

    int LineCount = 0;
    for (const string& line : AsciiAssets[BossKey])
    {
        GoSpace(StartX, StartY + LineCount);

        string noise = (rand() % 2 ? "0xDEADBEEF " : "********** ");
        cout << noise << line;

        LineCount++; // 다음 줄로!
        Sleep(100);  // 500ms는 너무 느릴 수 있으니 100ms 정도로 조절 추천
    }
}

void GraphicManager::GlitchEffect(int DurationMs)
{
    int StartTime = GetTickCount();
    char Noise[] = { '@', '#', '$', '%', '&', '*', '!', '?' };

    while (GetTickCount() - StartTime < DurationMs)
    {
        int Rx = rand() % (RightEdge - 2) + 1;
        int Ry = rand() % (MainBottom - 2) + 1;

        GoSpace(Rx, Ry);
        cout << Noise[rand() % 8];

        Sleep(10);
    }

    DrawCombatLayOut();
}

void GraphicManager::InverseFlash(int DurationMs)
{
    HANDLE HOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(HOut, 0xF0);

    DrawLayout();
    Sleep(DurationMs);
    SetConsoleTextAttribute(HOut, 0x0F);
    DrawLayout();
}

void GraphicManager::SetRageMode(bool IsRage)
{
    HANDLE HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (IsRage) {
        SetConsoleTextAttribute(HConsole, 12);
    } else {
        SetConsoleTextAttribute(HConsole, 15);
    }
}

void GraphicManager::ShowTitle() const
{
    system("cls");
    Sleep(100);
    LoggerSystem& Ls = LoggerSystem::GetInstance();
    Ls.hideCursor();

    for (int i = 0; i <= RightEdge; i++)
    {
        GoSpace(i, 0); cout << "_";
        GoSpace(i, 2); cout << "=";
    }

    for (int i = 1; i < BottomEdge; i++)
    {
        GoSpace(0, i);         cout << "|";
        GoSpace(RightEdge, i); cout << "|";
    }

    for (int i = 0; i <= RightEdge; i++)
    {
        GoSpace(i, BottomEdge - 2); cout << "_";
        GoSpace(i, BottomEdge);     cout << "_";
    }

    GoSpace(2, 1); cout << "[ SYSTEM_TERMINAL_V4.04 ]";
    GoSpace(RightEdge - 25, 1); cout << "[ STATUS: 0xDEADC0DE ]";

    const char* logs[] = {
        "[CPU] [|||||||||||||||||||||||||||||||          ] 72% | [MEM] [■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□□] 92% | [TEMP] 42'C",
        "-------------------------------------------------------------------------------------------------------------------------------------------------------------",
        "[NET_LOG]",
        "> TRACE: 127.0.0.1 ... OK",
        "> ADDR_RECURSIVE ... DETECTED",
        "> ERR: SEG_FAULT (0xDEADBEEF)"
    };

    for (int i = 0; i < 6; i++)
    {
        GoSpace(2, 3 + i);
        cout << logs[i];
        Sleep(30);
    }

    int storageY = BottomEdge - 7;
    GoSpace(2, storageY);     cout << "[STORAGE]";
    GoSpace(2, storageY + 1); cout << "SEC_A: [■■■■■■■□□] 70%";
    GoSpace(2, storageY + 2); cout << "SEC_B: [■■■□□□□□□] 30%";
    GoSpace(2, storageY + 3); cout << "SEC_C: [■■■■■■■■■] 100%";

    GoSpace(2, BottomEdge - 1);
    cout << "[CMD] : /START  /OPTIONS  /RECOVERY  /SHUTDOWN";
    GoSpace(RightEdge - 25, BottomEdge - 1);
    cout << "[TERMINAL_READY]  _";

    int logoW = 60;
    int StartX = (CurrentWidth / 2) - (logoW / 2);
    int StartY = (CurrentHeight / 2) - 4;

    Sleep(200);
    GoSpace(StartX, StartY);     cout << "o  o  o-o  o  o   o   o      o    o--o                  o  ";
    Sleep(100);
    GoSpace(StartX, StartY + 1); cout << "|  | o  /o |  |   |\\  |      |    |                     |  ";
    GoSpace(StartX, StartY + 2); cout << "o--O | / | o--O   | \\ | o-o -o-   O-o  o-o o  o o-o   o-O  ";
    Sleep(50);
    GoSpace(StartX, StartY + 3); cout << "   | o/  o    |   |  \\| | |  |    |    | | |  | |  | |  |  ";
    GoSpace(StartX, StartY + 4); cout << "   o  o-o     o   o   o o-o  o    o    o-o o--o o  o  o-o  ";

    GoSpace((CurrentWidth / 2) - 13, StartY + 6); cout << "[ PROJECT : 404 NOT FOUND ]";
    GoSpace((CurrentWidth / 2) - 11, StartY + 8); cout << "[Press Enter to Start]";

    cin.ignore(100, '\n');
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
            int StartX = (SplitColumn * 10) / 100;
            int StartY = (MainBottom * 20) / 100;
            GoSpace(StartX, StartY + LineOffset++);
            cout << Line;
        }
    }

    if (AsciiAssets.count(Monster) > 0)
    {
        int LineOffset = 0;
        for (const string& Line : AsciiAssets[Monster])
        {
            int StartX = SplitColumn + ((RightEdge - SplitColumn) * 10 / 100);
            int StartY = (MainBottom * 10) / 100;
            GoSpace(StartX, StartY + LineOffset++);
            cout << Line;
        }
    }
}

void GraphicManager::DrawAsciiCombatArt(PlayerManager& Player, BaseMonster& Monster)
{
    string PlayerKey = "PLAYER";
    string MonsterKey = Monster.GetNickname();

    if (AsciiAssets.find(PlayerKey) == AsciiAssets.end() || AsciiAssets.find(MonsterKey) == AsciiAssets.end())
        return;

    int MonsterStartX = 5;
    int MonsterStartY = 2;

    GoSpace(MonsterStartX, MonsterStartY);     cout << "[ ENEMY STATUS ]";
    GoSpace(MonsterStartX, MonsterStartY + 1); cout << "NAME : " << MonsterKey;

    int MonsterHpBarLen = 20;
    int MMaxHp = Monster.GetMaxHealth();
    int MonsterHpLen = (MMaxHp <= 0) ? 0 : (Monster.GetHealth() * MonsterHpBarLen / MMaxHp);

    GoSpace(MonsterStartX, MonsterStartY + 2); cout << "HP   : [";
    for(int i=0; i<MonsterHpBarLen; i++)
        cout << (i < MonsterHpLen ? "■" : " ");
    cout << "] " << Monster.GetHealth() << " / " << MMaxHp;


    int MArtLine = 0;
    int MArtX = SplitColumn + ((RightEdge - SplitColumn) * 10 / 100);
    int MArtY = (MainBottom * 10) / 100;
    for (const string& Line : AsciiAssets[MonsterKey]) {
        GoSpace(MArtX, MArtY + MArtLine++);
        cout << Line;
    }

    int PlayerStartX = SplitColumn;
    int PlayerStartY = MainBottom - 6;

    GoSpace(PlayerStartX, PlayerStartY);     cout << "[ PLAYER STATUS ]";
    GoSpace(PlayerStartX, PlayerStartY + 1); cout << "NAME : " << Player.GetNickname();
    GoSpace(PlayerStartX, PlayerStartY + 2); cout << "Lv." << Player.GetLevel() << "   HP: " << Player.GetHealth() << " / " << Player.GetMaxHealth();

    int PlayerHpBarLen = 20;
    int PMaxHp = Player.GetMaxHealth();
    int PlayerHpLen = (PMaxHp <= 0) ? 0 : (Player.GetHealth() * PlayerHpBarLen / PMaxHp);

    GoSpace(PlayerStartX, PlayerStartY + 3); cout << "HP   : [";
    for(int i=0; i<PlayerHpBarLen; i++)
        cout << (i < PlayerHpLen ? "■" : " ");
    cout << "] " << Player.GetHealth() << " / " << PMaxHp;

    int PArtLine = 0;
    int PArtX = (SplitColumn * 10) / 100;
    int PArtY = (MainBottom * 25) / 100 + 1;
    for (const string& Line : AsciiAssets[PlayerKey]) {
        GoSpace(PArtX, PArtY + PArtLine++);
        cout << Line;
    }

    DrawInventoryData(Player);
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

void GraphicManager::DrawAsciiArtCenter(const string& Name)
{
    if (AsciiAssets.find(Name) == AsciiAssets.end()) return;

    const vector<string>& Asset = AsciiAssets[Name];
    int artHeight = static_cast<int>(Asset.size());

    size_t maxWidth = 0;
    for (const string& line : Asset)
    {
        if (line.length() > maxWidth)
            maxWidth = line.length();
    }
    int artWidth = static_cast<int>(maxWidth);

    int targetX = (CurrentWidth / 2) - (artWidth / 2);
    int targetY = (MainBottom / 2) - (artHeight / 2);

    DrawAsciiArt(Name, targetX, targetY);
}
