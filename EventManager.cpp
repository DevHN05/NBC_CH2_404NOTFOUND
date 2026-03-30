#include "EventManager.h"
#include "CombatManager.h"
#include "BaseMonster.h"
#include "GraphicManager.h"
#include <iostream>
#include <random>
#include <algorithm>
#include "LoggerSystem.h"
#include "MonsterData.h"

using namespace std;
CombatManager& cm = CombatManager::GetInstance();

// 일단 현재 준비된 이벤트 목록은 25개! 25개의 순서를 랜덤하게 섞어주는 함수. 25개가 모자라면 최민서에게 말씀!
EventManager::EventManager(PlayerManager& InPlayer) : Player(InPlayer), CurrentEventIndex(0)
{
    // 1~20번: 전투 및 보상 이벤트
    for (int i = 1; i <= 20; ++i) NormalEventIds.push_back(i);

    // 21~25번: 상점 이벤트
    for (int i = 21; i <= 25; ++i) ShopEventIds.push_back(i);

    ShuffleEvents();
}

void EventManager::WaitEnter()
{
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
    cin.get();
}

void EventManager::ShuffleEvents()
{
    random_device rd;
    mt19937 EventRandomRoll(rd());

    shuffle(NormalEventIds.begin(), NormalEventIds.end(), EventRandomRoll);
    shuffle(ShopEventIds.begin(), ShopEventIds.end(), EventRandomRoll);

    EventIds.clear();

    for (int i = 0; i < 5; ++i)     // 다섯씩 묶어서 상점 이벤트를 랜덤하게 하나씩 넣는 구조입니다.
    {                               // 운이 나쁘면 4전투 2상점 4전투를 만날 수 있지만, 그것도 운 아닐까요?
        vector<int> Chunk;
        for (int j = 0; j < 4; ++j)
        {
            Chunk.push_back(NormalEventIds[i * 4 + j]);
        }
        Chunk.push_back(ShopEventIds[i]);
        shuffle(Chunk.begin(), Chunk.end(), EventRandomRoll);

        for (int id : Chunk)
        {
            EventIds.push_back(id);
        }
    }
    CurrentEventIndex = 0;
}

// 이 함수를 호출할때마다 랜덤하게 섞인 이벤트가 순서대로 실행
void EventManager::TriggerNextEvent()
{
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

        // [11~15] 보상 / 전투 / 회피 이벤트. 중간 보스전도 포함입니다.
        case EV_GarbageCollector:  ChoiceGarbageCollector(); break;  // 보상/전투 #1 vs가비지컬렉션
        case EV_Undeclared:        ChoiceUndeclared(); break;        // 보상/전투 #2 vs언디클레어드
        case EV_DanglingPointer:   ChoiceDanglingPointer(); break;   // 보상/전투 #3 vs댕글링 포인터
        case EV_BrokenActor:       ChoiceBrokenActor(); break;       // 보상/전투 #4 vs깨진 액터
        case EV_UninitArray:       ChoiceUninitArray(); break;       // 보상/전투 #5 vs미초기화 배열

        // [16~20] 보상 이벤트
        case EV_ChestNormal:       ChestNormal(); break;             // 보상 #1 평범한 보물상자
        case EV_ChestConstLock:    ChestConstLock(); break;          // 보상 #2 const 보물상자
        case EV_ChestAndLogic:     ChestAndLogic(); break;           // 보상 #3 && 논리상자
        case EV_ChestPointerSearch: ChestPointerSearch(); break;      // 보상 #4 *ptr 보물찾기
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


void EventManager::TutorialEvent()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ShowStory();

    random_device rd;
    mt19937 DiceVal(rd());
    uniform_int_distribution<int> RollStat(1, 20);

    Gm.CommandAddLog("[ 캐릭터 초기 스탯 굴리기 ]");
    Gm.CommandAddLog("Enter를 누를 때마다 스탯이 하나씩 결정됩니다.");

    WaitEnter();
    int str = RollStat(DiceVal);
    Player.SetStrength(str);
    Gm.CommandAddLog("근력(STR) 주사위 값 : " + to_string(str) + "/20");

    WaitEnter();
    int dex = RollStat(DiceVal);
    Player.SetDexterity(dex);
    Gm.CommandAddLog("민첩(DEX) 주사위 값 : " + to_string(dex) + "/20");

    WaitEnter();
    int intel = RollStat(DiceVal);
    Player.SetIntelligence(intel);
    Gm.CommandAddLog("지능(INT) 주사위 값 : " + to_string(intel) + "/20");

    WaitEnter();
    int luk = RollStat(DiceVal);
    Player.SetLuck(luk);
    Gm.CommandAddLog("행운(LUK) 주사위 값 : " + to_string(luk) + "/20");

    WaitEnter();
    Gm.CommandAddLog("모든 스탯 설정이 완료되었습니다! 디버깅을 시작합니다.");

    WaitEnter();
}




// ========== 구분선 ===========
// 일반 전투 이벤트는 맨 앞에 Battle을 붙여서 구분

// 일반 전투 이벤트 #1 파수꾼 :: 시스템 보안 봇 이벤트. BattleGuardian
void EventManager::BattleGuardian()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.LogEventGuardian(DexBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 13, DexBonus()); // 보정치를 받아서 13을 굴립니당
            if (!Dice.GetResult()) IsBattle = true;      // 결과가 실패면 실패 선택지 메세지(IsBattle=true)로 갑니당
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 13, IntBonus());
           if (!Dice.GetResult()) IsBattle = true;      // 결과가 실패면 실패 선택지 메세지(IsBattle=true)로 갑니당
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
            cin.ignore(100, '\n');        // 한글 등 잘못된 입력을 지우는 역할의 함수입니당
            Gm.ClearLogs();
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        // 경험치 오르고 골드 보상 없이 종료
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력 들어갈 곳. 여긴 실패해도 체력 손해는 없음!
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.LogEventFailGuardian();
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateBot());
    }
}

// 일반 전투 이벤트 #2 방랑자 :: delete ptr; 이벤트 BattleWanderer
void EventManager::BattleWanderer()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
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
            cm.StartBattle(Player, *MonsterData::CreateDeletePtr()); break;
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
        // 성공 메세지
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 성공!");
        // 경험치 오르고 골드 보상 없이 종료
        Logger.LogExpGain(10, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + 10);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else if (IsBattle) {
        // 실패 메세지 + hp 5 차감
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.LogEventFailWanderer();
        Player.SetHealth(Player.GetHealth() - 5);
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateDeletePtr());
    }
}


// 일반 전투 이벤트 #3 분쇄자 :: Break. BattleBreaker
void EventManager::BattleBreaker()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.LogEventBreaker(StrBonus(), IntBonus());

    //Gm.GoSpace(4, 20); cout << "숫자를 입력해 행동 선택 > ";
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.LogEventFailBreaker();
        Player.SetHealth(max(0, Player.GetHealth() - 5));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateBreak());
    }
}

// 일반 전투 이벤트 #4 침략자 :: 오버플로우. BattleInvader
void EventManager::BattleInvader()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.LogEventFailInvader();
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateOverflow());
    }
}

// 일반 전투 이벤트 #5 암살자 :: 세그멘테이션 폴트. BattleAssassin
void EventManager::BattleAssassin()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.LogEventFailAssassin();
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        WaitEnter();
        Gm.ClearLogs();
        cm.StartBattle(Player, *MonsterData::CreateSemicolon());
    }
}

// 일반 전투 이벤트 #6 몬스터 재활용 :: 통나무 다리. BattleBridge
void EventManager::BattleBridge()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.LogEventForest(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, IntBonus()); // 지능 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, LukBonus()); // 행운 보정치
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        // 경험치 오르고 골드 보상 없이 종료
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // [당신의 방안은 탁월한 효과를 보였습니다. 버그를 찾아내는데 말입니다... 너무 탁월해서 버그가 바로 앞에 있었거든요...]
        // 전용 메세지 출력 및 몬스터 랜덤 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.LogEventDataNoise(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 14, LukBonus()); // 행운 보정치
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // [아무래도 잘못 건드린 모양입니다. 깨진 데이터가 당신의 데이터마저 조금 깨뜨립니다...]
        // HP 10 차감, 전용 메세지 출력 및 몬스터 랜덤 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.LogEventGravity(LukBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;

        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 12, LukBonus()); // 행운 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            Dice.RollDice(20, 12, IntBonus()); // 지식 보정치
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // [이런, 엄청난 속도로 추락한 거대 버그와 정면으로 충돌했습니다! 충격으로 인해 시야가 흔들리는 가운데...]
        // HP 5 차감, 전용 메세지 출력 및 몬스터 랜덤 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 및 전투 발생
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.ChoiceGarbageCollector(DexBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            Dice.RollDice(20, 10, DexBonus()); // 민첩 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            IsBattle = true;
        }
        else if (Choice == 3)
        {
            WaitEnter();
            Gm.ClearLogs();
            return; // 전투 회피 후 즉시 이벤트 종료
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 60; // 보스 몬스터 경험치
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        if (Choice == 1) // 2를 골랐는데도 실패 선택지를 출력하고 패널티를 받지 않도록 수정
        {
            Gm.ClearLogs();
            Gm.AddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [실패]");
            Logger.ChoiceGarbageCollectorFail();
            Player.SetHealth(max(0, Player.GetHealth() - 10)); // HP 10 차감
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBossBattle(Player, *MonsterData::CreateShadowLord()); // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #2 소거자 :: 언디클레어드 이벤트 ChoiceUndeclared
void EventManager::ChoiceUndeclared()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ChoiceUndeclared(StrBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 힘으로 #include <stdio.h>를 제압해 이곳을 다시 관리하도록 제자리에 둡니다.
            Dice.RollDice(20, 10, StrBonus()); // 근력 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 헤더를 고치기엔 너무 멀리 왔습니다. 저 버그 덩어리를 제압하는 수 밖에요.
            IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 이 지역을 지금 구할 필요가 있을까요? 욕심을 버리고 빙 돌아서 지나갑니다.
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
        Gm.AddLog("판정 성공!");
        int SuccessExp = 60; // 보스 몬스터 경험치
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // 시스템이 당신을 인식할 수 없습니다. 즉시 제거가 시작됩니다. 몸이 흐릿해지는 걸 느끼며 맞서 싸웁니다.
        if (Choice == 1)
        {
            Gm.ClearLogs();
            Gm.AddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [실패]");
            Logger.ChoiceUndeclaredFail();
            Player.SetHealth(max(0, Player.GetHealth() - 10));
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBossBattle(Player, *MonsterData::CreateVolcanicDragon()); // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #3 투영자 :: 댕글링 포인터 이벤트 ChoiceDanglingPointer
void EventManager::ChoiceDanglingPointer()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ChoiceDanglingPointer(StrBonus());

    // 댕글링 포인터 메세지 출력 함수란
    // 댕글링 포인터 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 위험하지만, 직접 댕글링 포인터에 nullptr를 대입하여 원상 복구를 시도합니다
            Dice.RollDice(20, 10, StrBonus()); // 근력 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 실체가 없더라도 디버깅하면 그만이죠. 정면으로 싸움을 겁니다.
            IsBattle = true;
        }
        else if (Choice == 3)
        {
           // 시스템 크래시는 무섭습니다. 욕심을 버리고 빙 돌아서 지나갑니다.
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
        // 성공 메세지 출력
        // 데이터 잔상이 소멸하며 안전한 경로가 확보됩니다.
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 60; // 보스 몬스터 경험치
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // 녀석은 여전히 존재하지 않는 주소를 읽으려 시도했습니다. 시스템 크래시와 함께 유령 데이터가 실체화되어 당신을 덮칩니다.
        if (Choice == 1)
        {
            Gm.ClearLogs();
            Gm.AddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [실패]");
            Logger.ChoiceDanglingPointerFail();
            Player.SetHealth(max(0, Player.GetHealth() - 10));
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBossBattle(Player, *MonsterData::CreateForestGuardian()); // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #4 깨진 액터 이벤트 ChoiceBrokenActor
void EventManager::ChoiceBrokenActor()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ChoiceBrokenActor(LukBonus(), IntBonus());

    // 깨진 액터 메세지 출력 함수란
    // 깨진 액터 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 난 운이 좋으니 버그가 떠났을거야. 운에게 맡기며 액터를 살펴봅니다.
            Dice.RollDice(20, 10, LukBonus()); // 행운 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 망가진 액터의 원형을 상상하며 쓸만한 아이템 코드가 남아있는지 살펴봅니다.
            Dice.RollDice(20, 10, IntBonus()); // 지식 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 위험을 감수할 순 없죠. 그냥 지나칩니다.
            return; // 전투 미발생, 이벤트 종료
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
        // 성공 메세지 출력
        // 귀중한 물품이 제법 많이 들어있군요. 살아남은 것만 대충 챙겨야겠군요.
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 30; // 일반 몬스터 경험치
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // 아무래도 망가진 액터처럼 당신도 망가뜨리려는 모양인데요... 싸움을 피할 순 없겠습니다.
        Gm.ClearLogs();
        Gm.AddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [실패]");
        Logger.ChoiceBrokenActorFail();
        WaitEnter();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster()); // 일반 전투 발생
        Gm.ClearLogs();
    }
}

// 전투/보상 이벤트 #5 Array 아파트 이벤트 ChoiceUninitArray
void EventManager::ChoiceUninitArray()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ChoiceDanglingPointer(IntBonus());

    // 배열 메세지 출력 함수란
    // 배열 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 녀석의 몸에 적힌 방 번호 중 NULL이나 0이 저장된 빈방을 찾아봅니다.
            Dice.RollDice(20, 10, IntBonus()); // 지식 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 고작해야 배열에게 막힐 순 없습니다. 정면으로 싸움을 겁니다.
            IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 쓰레기값은 예측할 수 없습니다. 욕심을 버리고 빙 돌아서 지나갑니다.
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
        // 성공 메세지 출력
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        int SuccessExp = 30; // 일반 몬스터 경험치
        Logger.LogExpGain(SuccessExp, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience() + SuccessExp);
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 실패 메세지 출력
        // 방 전체를 장악한 쓰레기값이 당신의 침입을 감지해 전투를 걸어옵니다.
        if (Choice == 1)
        {
            Gm.ClearLogs();
            Gm.AddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + " [실패]");
            Player.SetHealth(max(0, Player.GetHealth() - 10)); // HP 10 차감
            WaitEnter();
            Gm.ClearLogs();
        }
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster()); // 일반 전투 시작
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
    Logger.ChestNormal(StrBonus(), DexBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 힘으로 상자를 부숴서 내용물을 확인합니다.]
            Dice.RollDice(20, 10, StrBonus()); // 힘 보정치
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 락픽을 이용해 자물쇠를 따봅니다.
            Dice.RollDice(20, 10, DexBonus()); // 민첩 보정치
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
        // 판정 성공 메세지, 경험치와 골드를 획득
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ChestNormalSuccess();
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 판정 실패 메세지, 아무것도 얻지 못하고 종료
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.ChestConstLock(StrBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 잠금 장치를 부술 수 없다면, 힘으로 상자를 부숩니다
            Dice.RollDice(20, 14, StrBonus()); // 힘 보정치, 판정값 14]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 디버깅을 해서 const의 위치를 알맞은 곳으로 되돌립니다.
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치, 판정값 14
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
        // 판정 성공 메세지
        // 당신은 신이 나서 안에 있는 금화를 모두 챙깁니다.
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ChestConstLockSuccess();
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 판정 실패 메세지
        // 이런, const는 강력하군요...
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.ChestAndLogic(DexBonus(), LukBonus(), IntBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 재빠르게 열쇠 두 개를 동시에 집어넣어 봅니다
            Dice.RollDice(20, 14, DexBonus()); // 민첩 보정치, 판정값 14
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 우연히 들어맞길 바라며 열쇠 두 개를 감으로 맞춰봅니다.
            Dice.RollDice(20, 14, LukBonus()); // 행운 보정치, 판정값 14
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 회로 하나를 조작해 첫 번째 구멍이 참인 것처럼 속이고 열쇠를 넣습니다.
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치, 판정값 14
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
        // 판정 성공 메세지
        // 두 논리가 맞물리며 상자가 열립니다.
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ChestAndLogicSuccess();
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 타이밍이 맞지 않았던걸까요... 논리가 부정당해 상자가 열리지 않습니다
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.ChestPointerSearch(IntBonus(), LukBonus());

    // 포인터 보물찾기 이벤트 출력 함수란
    // 포인터 보물찾기 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 주변의 데이터 흐름을 분석해 *ptr이 가리키는 자료형(Type)을 알아냅니다.
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치, 판정값 14
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 우연히 자료형이 맞길 바라며 하나를 정하고 *ptr을 따라갑니다.
            Dice.RollDice(20, 14, LukBonus()); // 행운 보정치, 판정값 14
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
        // 판정 성공 메세지
        // 당신이 생각한 자료형이 맞았습니다! 바닥을 파니 상자가 나옵니다.
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ChestPointerSearchSuccess();
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 자료형이 맞지 않았던걸까요... 바닥을 파도 아무것도 나오지 않습니다.
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.ChestBugActorFix(StrBonus(), IntBonus());

    // 버그 액터 수리 이벤트 출력 함수란
    // 버그 액터 수리 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 디버깅 툴을 이용해서 물리적으로 버그의 원흉을 제거합니다.
            Dice.RollDice(20, 10, StrBonus()); // 힘 보정치, 판정값 10
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 디버깅 툴을 이용해서 오류가 발생한 코드를 찾아 수정합니다.
            Dice.RollDice(20, 10, IntBonus()); // 지식 보정치, 판정값 10
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
        // 판정 성공 메세지
        // 성공적으로 액터의 버그가 제거됩니다. 액터는 마을주민 NPC였습니다.
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ChestBugActorFixSuccess();
        Logger.LogExpGain(30, Player.GetExperience(), Player.GetMaxExperience());
        Player.SetExperience(Player.GetExperience()+30);
        Player.SetGold(Player.GetGold()+30);
        Logger.LogGoldGain(30, Player.GetGold());
        WaitEnter();
        Gm.ClearLogs();
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 오류의 원인을 잘못 짚은 모양입니다. 아예 충돌해서 소멸합니다...
        Gm.ClearLogs();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
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
    Logger.ShopChoiceEvent(LukBonus()); // 갈림길 이벤트 로거, 행운 보정치만 사용

    // 갈림길 메세지 출력 함수란
    // 갈림길 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 여정을 쉴 수는 없지, 왼쪽 길로 갑니다. (모험 속행, 다음 이벤트가 전투로 고정)
            IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 뭔가 불길한데... 상점이 급하니 일단 오른쪽 길로 가봅니다.
            Dice.RollDice(20, 10, LukBonus()); // 행운 주사위 판정, 10 이하일 경우 전투 조우
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
        // 당신은 별다른 일 없이 상점에 도착하는데 성공합니다. 팻말은 진짜였군요.
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopChoiceEventSuccess();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        // 오른쪽은 당신을 유도하기 위한 함정이었습니다. 버그가 당신을 공격합니다!
        cin.clear();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopChoiceEventFail();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 상점 방문 이벤트 #2 바위 길막기 ShopVillageWay
void EventManager::ShopVillageWay()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ShopVillageWay(StrBonus(), DexBonus()); // 바위 길막기 로거

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 그냥 다른 길로 갑니다. 상점은 다른곳에도 있겠죠.
            return; // 모험 속행 (상점 포기)
        }
        else if (Choice == 2)
        {
            // 상점도 가야하고, 주민들도 불편할거야. 바위를 치워봅니다.
            Dice.RollDice(20, 10, StrBonus()); // 힘 판정
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 민첩하게 바위를 뛰어넘어 상점을 이용하러 갑니다.
            Dice.RollDice(20, 10, DexBonus()); // 민첩 판정
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
        // 당신은 별다른 일 없이 상점에 도착하는데 성공합니다. 팻말은 진짜였군요.
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopVillageWaySuccess();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        // 오른쪽은 당신을 유도하기 위한 함정이었습니다. 버그가 당신을 공격합니다!
        cin.clear();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopVillageWayFail();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 상점 방문 이벤트 #3 도박꾼 보부상 ShopGamblerBet
void EventManager::ShopGamblerBet()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ShopGamblerBet(LukBonus(), DexBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 뭔 도박이야? 그냥 가던 길을 계속 간다.
            return; // 모험 속행 (상점 포기)
        }
        else if (Choice == 2)
        {
            // 까짓거 한 번 굴려보지 뭐. 주사위를 굴린다.
            Dice.RollDice(20, 10, LukBonus()); // 행운 판정
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 도박꾼에게 들키지 않게 손기술을 부여 결과값을 조작한다.
            Dice.RollDice(20, 10, DexBonus()); // 민첩 판정
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
        // 주사위 값으로 6이 나오며, 5를 굴린 보부상을 이깁니다. 보부상이 킥킥 웃으며 보따리를 풀기 시작합니다.
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopGamblerBetSuccess();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        // 이런, 주사위가 1이 나옵니다. 보부상이 기분 나쁘게 웃습니다.
        cin.clear();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopGamblerBetFail();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}

// 상점 방문 이벤트 #4 상점 디버깅 ShopBugStoreFix
void EventManager::ShopBugStoreFix()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ShopBugStoreFix(IntBonus(), LukBonus() - 5); // 상점 디버깅 로거

    // 상점 디버깅 메세지 출력 함수란
    // 상점 디버깅 선택지 출력 함수란
    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 귀찮게 왜? 그냥 지나갑니다.
            return; // 모험 속행 (상점 포기)
        }
        else if (Choice == 2)
        {
            // 디버깅 툴을 이용해서 상점에 있는 버그를 디버깅해봅니다.
            Dice.RollDice(20, 10, IntBonus()); // 지식 판정
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 운 좋게 버그 난 곳 지워질수도 있는거 아닌가요? 그냥 되는대로 휘두릅니다!
            Dice.RollDice(20, 10, LukBonus() - 5); // 행운 판정, 역보정 -5
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
        // 디버깅에 성공했습니다! 상점이 원래의 모습을 되찾습니다. 이제 이용할 수 있겠군요.
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopBugStoreFixSuccess();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        // 디버깅에 실패했습니다! 오히려 버그가 급증했습니다. 버그가 당신에게 달려듭니다.
        cin.clear();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopBugStoreFixFail();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}
// 상점 방문 이벤트 #5 Access Denied 상점 ShopAccessDenied
void EventManager::ShopAccessDenied()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance();
    Logger.ShopAccessDenied(IntBonus(), LukBonus());

    Gm.CommandAddLog("숫자를 입력해 행동 선택 > ");

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 그냥 다른 상점 이용하지 뭐.
            return; // 모험 속행 (상점 포기)
        }
        else if (Choice == 2)
        {
            // 잘 추론해서 조건문의 조건을 디버깅해 상점주인의 권한을 찾아줍니다.
            Dice.RollDice(20, 10, IntBonus()); // 지식 판정
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // if문을 달성할만한 숫자를 대충 넣어서 운 좋게 열리길 빌어봅니다.
            Dice.RollDice(20, 10, LukBonus()); // 행운 판정
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
        Gm.ClearLogs();
        Gm.AddLog("판정 성공!");
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopAccessDeniedSuccess();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.UpdateStoreUI(Player);
    }
    else
    {
        cin.clear();
        Gm.CommandAddLog("판정 결과 : " + to_string(Dice.GetDiceHead()) + (Dice.GetResult() ? " [성공]" : " [실패]"));
        Logger.ShopAccessDeniedFail();
        cin.ignore(LLONG_MAX, '\n');
        cin.get();
        cin.clear();
        cm.StartBattle(Player, *MonsterData::CreateRandomMonster());
    }
}
