#include <iostream>
#include <random>
#include <algorithm>
#include <conio.h>
#include "EventManager.h"
#include "CombatManager.h"
#include "BaseMonster.h"
#include "GraphicManager.h"
#include "LoggerSystem.h"
#include "MonsterData.h"
#include "SoundManager.h"
#include "GameSystem.h"

using namespace std;
CombatManager& cm = CombatManager::GetInstance();

// 준비된 이벤트 목록 25개의 순서를 랜덤하게 섞어주는 함수.
EventManager::EventManager(PlayerManager& InPlayer) : Player(InPlayer), CurrentEventIndex(0)
{
    // 1~20번: 전투 및 보상 이벤트
    for (int i = 1; i <= 20; ++i)
    {
        if (i == 11) continue; // 11번 이벤트 가비지 컬렉션 리스트에서 제거
        NormalEventIds.push_back(i);
    }

    // 21~25번: 상점 이벤트
    for (int i = 21; i <= 25; ++i) ShopEventIds.push_back(i);

    ShuffleEvents();
}

void EventManager::WaitEnter()
{
    cin.clear();
    cin.sync();
    while (_kbhit()) {
        _getch();
    }
    while (true) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 13 || key == 10) {
                break;
            }
        }
    }
}

void EventManager::ShuffleEvents()
{
    random_device rd;
    mt19937 EventRandomRoll(rd());

    shuffle(NormalEventIds.begin(), NormalEventIds.end(), EventRandomRoll);
    shuffle(ShopEventIds.begin(), ShopEventIds.end(), EventRandomRoll);

    EventIds.clear();

    size_t normalIdx = 0;
    for (size_t i = 0; i < 5; ++i)
    {
        vector<int> Chunk;
        for (size_t j = 0; j < 4 && normalIdx < NormalEventIds.size(); ++j)
        {
            Chunk.push_back(NormalEventIds[normalIdx++]);
        }

        if (i < ShopEventIds.size())
        {
            Chunk.push_back(ShopEventIds[i]);
        }

        shuffle(Chunk.begin(), Chunk.end(), EventRandomRoll);
        for (int id : Chunk)
        {
            EventIds.push_back(id);
        }
    }
    CurrentEventIndex = 0;
}

// 함수 호출시 랜덤하게 섞인 이벤트가 순서대로 실행
void EventManager::TriggerNextEvent()
{
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage() + 1;
    gs.SetStage(nextStage);

    if (nextStage == 11) // 11번째 이벤트는 보스전으로 고정
    {
        ChoiceGarbageCollector();
        GraphicManager& Gm = GraphicManager::GetInstance();
        Gm.DrawGameWin(Player);
    }
    if (CurrentEventIndex >= EventIds.size()) ShuffleEvents();

    int id = EventIds[CurrentEventIndex++];

    switch (id)
    {
        // [1~10] 일반 전투 이벤트
        case EV_Guardian:          BattleGuardian(); break;          // 노말 #1 vs시스템 보안 봇
        case EV_Wanderer:          BattleWanderer(); break;          // 노말 #2 vs방랑자 :: delete ptr
        case EV_Breaker:           BattleBreaker(); break;           // 노말 #3 vs분쇄자 :: Break
        case EV_Invader:           BattleInvader(); break;           // 노말 #4 vs침략자 :: 오버플로우
        case EV_Assassin:          BattleAssassin(); break;          // 노말 #5 vs감시자 :: 세그멘테이션 폴트
        case EV_Bridge:            BattleBridge(); break;            // 노말 #6 vs통나무 다리
        case EV_Forest:            BattleForest(); break;            // 노말 #7 vs스산한 소리의 숲
        case EV_DataNoise:         BattleDataNoise(); break;         // 노말 #8 vs데이터 노이즈
        case EV_Gravity:           BattleGravity(); break;           // 노말 #9 vs중력 역전
        case EV_Cliff:             BattleCliff(); break;             // 노말 #10 vs거대한 절벽

        // [11~15] 보상 / 전투 / 회피 이벤트. 중간 보스전도 포함.
        case EV_GarbageCollector:  ChoiceGarbageCollector(); break;  // 보상/전투 #1 vs가비지컬렉션
        case EV_Undeclared:        ChoiceUndeclared(); break;        // 보상/전투 #2 vs언디클레어드
        case EV_DanglingPointer:   ChoiceDanglingPointer(); break;   // 보상/전투 #3 vs댕글링 포인터
        case EV_BrokenActor:       ChoiceBrokenActor(); break;       // 보상/전투 #4 vs깨진 액터
        case EV_UninitArray:       ChoiceUninitArray(); break;       // 보상/전투 #5 vs미초기화 배열

        // [16~20] 보상 이벤트
        case EV_ChestNormal:       ChestNormal(); break;             // 보상 #1 평범한 보물상자
        case EV_ChestConstLock:    ChestConstLock(); break;          // 보상 #2 const 보물상자
        case EV_ChestAndLogic:     ChestAndLogic(); break;           // 보상 #3 && 논리상자
        case EV_ChestPointerSearch: ChestPointerSearch(); break;     // 보상 #4 *ptr 보물찾기
        case EV_ChestBugActorFix:  ChestBugActorFix(); break;        // 보상 #5 버그 액터 수리

        // [21~25] 상점 방문 이벤트
        case EV_ShopChoice:        ShopChoiceEvent(); break;         // 상점 #1 갈림길
        case EV_ShopVillageWay:    ShopVillageWay(); break;          // 상점 #2 바위 길막기
        case EV_ShopGamblerBet:    ShopGamblerBet(); break;          // 상점 #3 도박꾼 보부상
        case EV_ShopBugStoreFix:   ShopBugStoreFix(); break;         // 상점 #4 상점 디버깅
        case EV_ShopAccessDenied:  ShopAccessDenied(); break;        // 상점 #5 Access Denied 상점

        default:
            // 아직 구현되지 않았거나 예외적인 ID일 경우 안전하게 종료
            break;
    }
}

void DiceWin()
{
    SoundManager& Sm = SoundManager::GetInstance();
    Sm.RegisterSound(SoundType::DiceWinSFX, L"BGM/DiceWin.wav");
    Sm.SetSFXVolume(4);
    Sm.PlaySFX(SoundType::DiceWinSFX);
};

void DiceLose()
{
    SoundManager& Sm = SoundManager::GetInstance();
    Sm.RegisterSound(SoundType::DiceLoseSFX, L"BGM/DiceLose.wav");
    Sm.SetSFXVolume(4);
    Sm.PlaySFX(SoundType::DiceLoseSFX);
};

void PlayDiceVisualEffect(int Result, int DiceSize)
{
    SoundManager& Sm = SoundManager::GetInstance();
    Sm.RegisterSound(SoundType::DiceSFX, L"BGM/DiceSound.wav");
    Sm.SetSFXVolume(4);
    Sm.PlaySFX(SoundType::DiceSFX);

    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.DrawDiceRoll(Result, DiceSize);
}

void EventManager::TutorialEvent()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    SoundManager& Sm = SoundManager::GetInstance();
    Sm.RegisterSound(SoundType::TutorialBGM, L"BGM/TutorialBGM");
    Sm.SetBGMVolume(2);
    Sm.PlayBGM(SoundType::TutorialBGM);
    Logger.ShowStory();

    Gm.GoSpace(30, 8);
    cout << "404 NOT FOUND, 알 수 없는 접속자입니다.";
    Gm.GoSpace(30, 9);
    cout << "...특수 디버깅 툴 확인. 비상모드 실행. 접속자 권한 확인.";
    Gm.GoSpace(30, 11);
    cout << "이름을 입력해 접속 권한을 확보해주세요 > ";
    string InputName;


    cin.clear();
    cin.sync();
    while (true)
    {
        getline(cin, InputName);
        if (InputName.empty() || InputName.find_first_not_of(' ') == string::npos)
        {
            Gm.GoSpace(30, 13);
            cout << "이름은 한 글자 이상 입력해야 합니다.";
            Gm.GoSpace(30, 11); cout << "이름을 입력해 접속 권한을 확보해주세요 > ";

            cin.clear();
            cin.sync();
            continue;
        }

        break;
    }


    Logger.hideCursor();
    Gm.GoSpace(30, 13);
    cout << "[ 시스템 접속 권한 승인. 접속자명 : " << InputName << " ]";
    Gm.GoSpace(30, 14);
    cout << "[ Enter 키를 눌러 시스템 접속을 시도해주세요. ]";

    WaitEnter();

    Logger.RunTutorial();
    Logger.TutorialStatDice();

    random_device rd;
    mt19937 DiceVal(rd());
    uniform_int_distribution<int> RollStat(1, 20);
    Logger.hideCursor();
    WaitEnter();
    int str = RollStat(DiceVal);
    Player.SetStrength(str);

    PlayDiceVisualEffect(str, 20);
    if (str > 10)
    {
        DiceWin();
    }
    else
    {
        DiceLose();
    }

    Gm.PerformAddLog("근력(STR) 주사위 값 : " + to_string(str) + "/20");
    Gm.PerformAddLog(" ");
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... ]");

    WaitEnter();
    Gm.ClearLogs();
    int dex = RollStat(DiceVal);
    Player.SetDexterity(dex);

    PlayDiceVisualEffect(dex, 20);
    if (dex > 10)
    {
        DiceWin();
    }
    else
    {
        DiceLose();
    }

    Gm.PerformAddLog("민첩(DEX) 주사위 값 : " + to_string(dex) + "/20");
    Gm.PerformAddLog(" ");
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... ]");


    WaitEnter();
    Gm.ClearLogs();
    int intel = RollStat(DiceVal);
    Player.SetIntelligence(intel);

    PlayDiceVisualEffect(intel, 20);
    if (intel > 10)
    {
        DiceWin();
    }
    else
    {
        DiceLose();
    }

    Gm.PerformAddLog("지능(INT) 주사위 값 : " + to_string(intel) + "/20");
    Gm.PerformAddLog(" ");
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... ]");

    WaitEnter();
    Gm.ClearLogs();
    int luk = RollStat(DiceVal);
    Player.SetLuck(luk);

    PlayDiceVisualEffect(luk, 20);
    if (luk > 10)
    {
        DiceWin();
    }
    else
    {
        DiceLose();
    }

    Gm.PerformAddLog("행운(Luk) 주사위 값 : " + to_string(luk) + "/20");
    Gm.PerformAddLog(" ");
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... ]");

    WaitEnter();
    Gm.ClearLogs();
    Gm.PerformAddLog("[ 최종 스탯표 ]");
    Gm.PerformAddLog("");
    Gm.PerformAddLog("근력(STR) : " + to_string(str) + "/20");
    Gm.PerformAddLog("민첩(DEX) : " + to_string(dex) + "/20");
    Gm.PerformAddLog("지능(INT) : " + to_string(intel) + "/20");
    Gm.PerformAddLog("행운(LUK) : " + to_string(luk) + "/20");

    WaitEnter();
    Gm.ClearLogs();
    Gm.PerformAddLog("모든 스탯 설정이 완료되었습니다!");
    Gm.PerformAddLog("");
    Gm.PerformAddLog("[ Enter 키를 눌러 디버깅을 시작하세요... ]");

    WaitEnter();
    Gm.ClearLogs();
    Logger.showCursor();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x0F);
}





// ========== 구분선 ===========
// 일반 전투 이벤트는 맨 앞에 Battle을 붙여서 구분

// 일반 전투 이벤트 #1 파수꾼 :: 시스템 보안 봇 이벤트.
void EventManager::BattleGuardian()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventGuardian(DexBonus(), IntBonus());
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 13, DexBonus());
            // 보정치 13
            if (!Dice.GetResult()) IsBattle = true;
            // 결과가 실패면 실패 선택지 메세지(IsBattle=true)
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 13, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;      // 결과가 실패면 실패 선택지 메세지(IsBattle=true)
        }
        else if (Choice == 3)                           // 3번 선택 시 즉시 전투 출력
        {
            cm.StartBattle(Player, *MonsterData::CreateBot());
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
            // 한글 등 잘못된 입력을 지우는 역할의 함수
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailGuardian();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateBot());
    }
}

// 일반 전투 이벤트 #2 방랑자 :: delete ptr;
// 이벤트 BattleWanderer
void EventManager::BattleWanderer()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventWanderer(Player.GetStrength() / 5, Player.GetDexterity() / 5);

    //Gm.GoSpace(4, 20); cout << "숫자를 입력해 행동 선택 > ";
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 13, Player.GetStrength() / 5);
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 13, Player.GetDexterity() / 5);
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)                            // 3번 선택 시 즉시 전투 출력
        {
            cm.StartBattle(Player, *MonsterData::CreateDeletePtr());
            break;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle && Choice != 3) {
         // 성공 메시지
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        // 경험치 오르고 골드 보상 없이 종료
        Player.SetExperience(Player.GetExperience() + 10);
        Logger.LogExpGain(10, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + (Player.GetStrength() / 5)) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + (Player.GetDexterity() / 5)) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        DiceWin();
        WaitEnter();
        Gm.ClearLogs();
    }
    else if (IsBattle) {
        // 실패 메세지 + hp 5 차감
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + (Player.GetStrength() / 5)) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + (Player.GetDexterity() / 5)) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailWanderer();
        Player.SetHealth(Player.GetHealth() - 5);
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateDeletePtr());
    }
}


// 일반 전투 이벤트 #3 분쇄자 :: Break.
// BattleBreaker
void EventManager::BattleBreaker()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventBreaker(StrBonus(), IntBonus());

    //Gm.GoSpace(4, 20);
    cout << "숫자를 입력해 행동 선택 > ";
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + 30);

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailBreaker();
        Player.SetHealth(max(0, Player.GetHealth() - 5));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateBreak());
    }
}

// 일반 전투 이벤트 #4 침략자 :: 오버플로우.
// BattleInvader
void EventManager::BattleInvader()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventInvader(DexBonus(), LukBonus());
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + 30);

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailInvader();
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateOverflow());
    }
}

// 일반 전투 이벤트 #5 암살자 :: 세그멘테이션 폴트.
// BattleAssassin
void EventManager::BattleAssassin()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventAssassin(StrBonus(), IntBonus());
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 12, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 12, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience() + 30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailAssassin();
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateSemicolon());
    }
}

// 일반 전투 이벤트 #6 몬스터 재활용 :: 통나무 다리.
// BattleBridge
void EventManager::BattleBridge()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventBridge(DexBonus(), LukBonus(), StrBonus());
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            Dice.RollDice(20, 15, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailBridge();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 일반 전투 이벤트 #7 몬스터 재활용 :: 숲 배회 BattleForest
void EventManager::BattleForest()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventForest(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, IntBonus());
            // 지능 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, LukBonus());
            // 행운 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력 (전투 미 발생, 패널티 면제)
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        // 경험치 오르고 골드 보상 없이 종료
        Player.SetExperience(Player.GetExperience() + 30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력 및 몬스터 랜덤 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailForest();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 일반 전투 이벤트 #8 몬스터 재활용 :: 데이터 노이즈 BattleDataNoise
void EventManager::BattleDataNoise()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventDataNoise(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, IntBonus());
            // 지식 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, LukBonus());
            // 행운 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience() + 30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // HP 10 차감, 실패 메세지 출력 및 몬스터 랜덤 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailDataNoise();
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 일반 전투 이벤트 #9 몬스터 재활용 :: 중력 역전 BattleGravity
void EventManager::BattleGravity()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventGravity(LukBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 12, LukBonus());
            // 행운 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 12, IntBonus());
            // 지식 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + 30);

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력, HP 5 차감 및 몬스터 랜덤 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailGravity();
        Player.SetHealth(max(0, Player.GetHealth() - 5));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 일반 전투 이벤트 #10 몬스터 재활용 :: 절벽 BattleCliff
void EventManager::BattleCliff()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.LogEventCliff(DexBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
            Gm.ClearLogs();
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience() + 30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.LogEventFailCliff();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}




// ============= 구분선 =============
// 이 밑 보스 포함 전투/보상 이벤트
// 전투/보상 이벤트는 맨 앞에 Choice를 붙여서 구분

// 전투/보상 이벤트 #1 처형자 :: 가비지 컬렉션 이벤트 ChoiceGarbageCollector
void EventManager::ChoiceGarbageCollector()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChoiceGarbageCollector(DexBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 15, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        Player.SetHealth(Player.GetHealth() + 20);
        Gm.AddLog("Hp가 20 회복됩니다.");

        Logger.ChoiceGarbageCollectorSuccess();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBossBattle(Player, *MonsterData::CreateShadowLord());
    }
    else
    {
        if (Choice == 1)
        {
            Gm.ClearLogs();
            DiceLose();
            Gm.AddLog("판정 실패!");
            Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + " [ 실패 ]");

            Logger.ChoiceGarbageCollectorFail();
            Player.SetHealth(max(0, Player.GetHealth() - 20));
            Gm.AddLog("Hp가 20 손실됩니다.");
            WaitEnter();
            Gm.ClearLogs();
            cm.StartBossBattle(Player, *MonsterData::CreateShadowLord());
        }
    }
}

// 전투/보상 이벤트 #2 소거자 :: 언디클레어드 이벤트 ChoiceUndeclared
void EventManager::ChoiceUndeclared()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChoiceUndeclared(StrBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            IsBattle = true;
        }
        else if (Choice == 3)
        {
            return;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience() + 60);
        Logger.LogExpGain(60, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        Logger.ChoiceUndeclaredSuccess();

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        if (Choice == 1)
        {
            Gm.ClearLogs();
            DiceLose();
            Gm.AddLog("판정 실패!");

            if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + " [ 실패 ]");
            else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [ 실패 ]");

            Logger.ChoiceUndeclaredFail();
            Player.SetHealth(max(0, Player.GetHealth() - 10));
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBossBattle(Player, *MonsterData::CreateVolcanicDragon());
        // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #3 투영자 :: 댕글링 포인터 이벤트 ChoiceDanglingPointer
void EventManager::ChoiceDanglingPointer()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChoiceDanglingPointer(StrBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            IsBattle = true;
        }
        else if (Choice == 3)
        {
           return;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Logger.LogExpGain(60, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + 60);

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        Logger.ChoiceDanglingPointerSuccess();

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        if (Choice == 1)
        {
            Gm.ClearLogs();
            DiceLose();
            Gm.AddLog("판정 실패!");

            if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + " [ 실패 ]");
            else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [ 실패 ]");

            Logger.ChoiceDanglingPointerFail();
            Player.SetHealth(max(0, Player.GetHealth() - 10));
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBossBattle(Player, *MonsterData::CreateForestGuardian());
        // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #4 깨진 액터 이벤트 ChoiceBrokenActor
void EventManager::ChoiceBrokenActor()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChoiceBrokenActor(LukBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            return;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience() + 30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChoiceBrokenActorSuccess();
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChoiceBrokenActorFail();
        WaitEnter();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
        Gm.ClearLogs();
    }
}

// 전투/보상 이벤트 #5 Array 아파트 이벤트 ChoiceUninitArray
void EventManager::ChoiceUninitArray()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChoiceDanglingPointer(IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            IsBattle = true;
        }
        else if (Choice == 3)
        {
            return;
        }
        else
        {

            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Player.SetExperience(Player.GetExperience() + 30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        if (Choice == 1)
        {
            Gm.ClearLogs();
            DiceLose();
            Gm.AddLog("판정 실패!");

            if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + " [ 실패 ]");
            else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [ 실패 ]");

            Player.SetHealth(max(0, Player.GetHealth() - 10));
            // HP 10 차감
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
        // 일반 전투 시작
    }
}

// ============= 구분선 =============
// 이 밑 보상 이벤트
// 보상 이벤트는 맨 앞에 Chest를 붙여서 구분
// 보상 이벤트는 판정 성공시 보상, 실패시 보상 획득 불가능

// 보상 이벤트 #1 평범한 보물상자 이벤트 ChestNormal
void EventManager::ChestNormal()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChestNormal(StrBonus(), DexBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, StrBonus());
            // 힘 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, DexBonus());
            // 민첩 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.ClearLogs();
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestNormalSuccess();
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        Gm.DrawInventoryData(Player);
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestNormalFail();
        WaitEnter();
        Gm.ClearLogs();
    }
}

// 보상 이벤트 #2 const 보물상자 이벤트 ChestConstLock
void EventManager::ChestConstLock()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChestConstLock(StrBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestConstLockSuccess();
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        Gm.DrawInventoryData(Player);
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestConstLockFail();
        WaitEnter();
        Gm.ClearLogs();
    }
}

// 보상 이벤트 #3 && 논리상자 이벤트 ChestAndLogic
void EventManager::ChestAndLogic()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChestAndLogic(DexBonus(), LukBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            Dice.RollDice(20, 14, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestAndLogicSuccess();
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        Gm.DrawInventoryData(Player);
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestAndLogicFail();
        WaitEnter();
        Gm.ClearLogs();
    }
}

// 보상 이벤트 #4 *ptr 보물찾기 이벤트 ChestPointerSearch
void EventManager::ChestPointerSearch()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChestPointerSearch(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestPointerSearchSuccess();
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        Gm.DrawInventoryData(Player);
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestPointerSearchFail();
        WaitEnter();
        Gm.ClearLogs();
    }
}

// 보상 이벤트 #5 버그 액터 수리 이벤트 ChestBugActorFix
void EventManager::ChestBugActorFix()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ChestBugActorFix(StrBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestBugActorFixSuccess();
        Player.SetExperience(Player.GetExperience()+30);
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        Gm.DrawInventoryData(Player);
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 1) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ChestBugActorFixFail();
        WaitEnter();
        Gm.ClearLogs();
    }
}

// ============= 구분선 =============
// 이 밑 상점 이벤트
// 맨 앞에 Shop를 붙여서 구분
// 상점은 판정 실패 시 전투(IsBattle = true), 성공 시 상점 UI 출력(!IsBattle)

// 상점 방문 이벤트 #1 갈림길 ShopChoiceEvent
void EventManager::ShopChoiceEvent()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ShopChoiceEvent(LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopChoiceEventSuccess();
        WaitEnter();
        Gm.ClearLogs();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopChoiceEventFail();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 상점 방문 이벤트 #2 바위 길막기 ShopVillageWay
void EventManager::ShopVillageWay()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ShopVillageWay(StrBonus(), DexBonus()); // 바위 길막기 로거

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            return;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, StrBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            Dice.RollDice(20, 10, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopVillageWaySuccess();
        WaitEnter();
        Gm.ClearLogs();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + StrBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopVillageWayFail();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 상점 방문 이벤트 #3 도박꾼 보부상 ShopGamblerBet
void EventManager::ShopGamblerBet()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ShopGamblerBet(LukBonus(), DexBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            return;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            Dice.RollDice(20, 10, DexBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopGamblerBetSuccess();
        WaitEnter();
        Gm.ClearLogs();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + DexBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopGamblerBetFail();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 상점 방문 이벤트 #4 상점 디버깅 ShopBugStoreFix
void EventManager::ShopBugStoreFix()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ShopBugStoreFix(IntBonus(), LukBonus() - 5); // 상점 디버깅 로거

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            return;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            Dice.RollDice(20, 10, LukBonus() - 5);
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + (LukBonus() - 5)) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopBugStoreFixSuccess();
        WaitEnter();
        Gm.ClearLogs();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + (LukBonus() - 5)) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopBugStoreFixFail();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}
// 상점 방문 이벤트 #5 Access Denied 상점 ShopAccessDenied
void EventManager::ShopAccessDenied()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    GameSystem& gs = GameSystem::GetInstance();
    int nextStage = gs.GetStage();
    Gm.PerformAddLog("▶ 현재 스테이지: " + to_string(nextStage));
    Logger.ShopAccessDenied(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");
    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            return;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 10, IntBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            Dice.RollDice(20, 10, LukBonus());
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.CommandAddLog("잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.");
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        DiceWin();
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopAccessDeniedSuccess();
        cin.ignore(LLONG_MAX, '\n');
        WaitEnter();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        Gm.ClearLogs();
        DiceLose();
        Gm.AddLog("판정 실패!");

        if (Choice == 2) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + IntBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else if (Choice == 3) Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead() + LukBonus()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));
        else Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [ 성공 ]" : " [ 실패 ]"));

        Logger.ShopAccessDeniedFail();
        cin.ignore(LLONG_MAX, '\n');
        WaitEnter();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}
