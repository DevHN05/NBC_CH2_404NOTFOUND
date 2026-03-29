#include "EventManager.h"
#include "CombatManager.h"
#include "ShopManager.h"
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

void EventManager::ShuffleEvents()
{
    random_device rd;
    mt19937 g(rd());

    shuffle(NormalEventIds.begin(), NormalEventIds.end(), g);
    shuffle(ShopEventIds.begin(), ShopEventIds.end(), g);

    EventIds.clear();

    for (int i = 0; i < 5; ++i)     // 다섯씩 묶어서 상점 이벤트를 랜덤하게 하나씩 넣는 구조입니다.
    {                               // 운이 나쁘면 4전투 2상점 4전투를 만날 수 있지만, 그것도 운 아닐까요?
        vector<int> Chunk;
        for (int j = 0; j < 4; ++j)
        {
            Chunk.push_back(NormalEventIds[i * 4 + j]);
        }
        Chunk.push_back(ShopEventIds[i]);
        shuffle(Chunk.begin(), Chunk.end(), g);

        for (int id : Chunk)
        {
            EventIds.push_back(id);
        }
    }
    CurrentEventIndex = 0;
}

// 이 함수를 호출할때마다 랜덤하게 섞인 이벤트가 순서대로 실행
// 한번 호출할때마다 하나만 실행하게 했는데, 여기서 무한 순환 돌리면서 보스전 조건까지 달아도 되긴 할수도?
void EventManager::TriggerNextEvent()
{
    if (CurrentEventIndex >= EventIds.size()) ShuffleEvents(); // 이벤트를 다 소진했으면 다시 섞는 함수

    int id = EventIds[CurrentEventIndex++];     // 이번 차례의 이벤트 번호를 꺼내고, 다음 차례로 넘기는 함수

    switch (id)
    {
        // [1~10] 일반 전투 이벤트
    case 1:  BattleGuardian(); break;          // 노말 #1 vs시스템 보안 봇
    case 2:  BattleWanderer(); break;          // 노말 #2 vs방랑자 :: delete ptr
    case 3:  BattleBreaker(); break;           // 노말 #3 vs분쇄자 :: Break
    case 4:  BattleInvader(); break;           // 노말 #4 vs침략자 :: 오버플로우
    case 5:  BattleAssassin(); break;          // 노말 #5 vs감시자 :: 세그멘테이션 폴트
    case 6:  BattleBridge(); break;            // 노말 #6 vs통나무 다리
    case 7:  BattleForest(); break;            // 노말 #7 vs스산한 소리의 숲
    case 8:  BattleDataNoise(); break;         // 노말 #8 vs데이터 노이즈
    case 9:  BattleGravity(); break;           // 노말 #9 vs중력 역전
    case 10: BattleCliff(); break;             // 노말 #10 vs거대한 절벽

        // [11~15] 보상 / 전투 / 회피 이벤트. 중간 보스전도 포함입니다.
    case 11: ChoiceGarbageCollector(); break;  // 보상/전투 #1 vs가비지컬렉션
    case 12: ChoiceUndeclared(); break;        // 보상/전투 #2 vs언디클레어드
    case 13: ChoiceDanglingPointer(); break;   // 보상/전투 #3 vs댕글링 포인터
    case 14: ChoiceBrokenActor(); break;       // 보상/전투 #4 vs깨진 액터
    case 15: ChoiceUninitArray(); break;       // 보상/전투 #5 vs미초기화 배열

        // [16~20] 보상 이벤트
    case 16: ChestNormal(); break;             // 보상 #1 평범한 보물상자
    case 17: ChestConstLock(); break;          // 보상 #2 const 보물상자
    case 18: ChestAndLogic(); break;           // 보상 #3 && 논리상자
    case 19: ChestPointerSearch(); break;      // 보상 #4 *ptr 보물찾기
    case 20: ChestBugActorFix(); break;        // 보상 #5 버그 액터 수리

        // [21~25] 상점 방문 이벤트
    case 21: ShopChoiceEvent(); break;         // 상점 #1 갈림길
    case 22: ShopVillageWay(); break;          // 상점 #2 바위 길막기
    case 23: ShopGamblerBet(); break;          // 상점 #3 도박꾼 보부상
    case 24: ShopBugStoreFix(); break;         // 상점 #4 상점 디버깅
    case 25: ShopAccessDenied(); break;        // 상점 #5 Access Denied 상점

    default:
        // 아직 구현되지 않았거나 예외적인 ID일 경우 안전하게 종료
        break;
    }
}

// ========== 구분선 ===========
// 일반 전투 이벤트는 맨 앞에 Battle을 붙여서 구분

// 일반 전투 이벤트 #1 파수꾼 :: 시스템 보안 봇 이벤트. BattleGuardian
void EventManager::BattleGuardian()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Logger = LoggerSystem::GetInstance(); // 이벤트 출력 함수입니당
    Gm.ClearLogs();
    Logger.LogEventGuardian(DexBonus(), IntBonus());    // 선택지 출력 함수입니당

    Gm.GoSpace(4, 20); cout << "Player Select Enter> ";

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
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 3번 선택 시 즉시 전투 출력
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');        // 한글 등 잘못된 입력을 지우는 역할의 함수입니당
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
        // 경험치 오르고 골드 보상 없이 종료
        int SuccessExp = 10;
        Logger.LogExpGain(SuccessExp,Player.GetExperience(),Player.GetMaxExperience());
    }
    else
    {
        // 실패 메세지 출력 들어갈 곳. 여긴 실패해도 체력 손해는 없음!
        cm.StartBattle(Player, *MonsterData::CreateBot());
    }
}

// 일반 전투 이벤트 #2 방랑자 :: delete ptr; 이벤트 BattleWanderer
void EventManager::BattleWanderer()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 메모리 누수 메세지 출력 함수란

    // 메모리 누수 선택지 출력 함수란

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
        else if (Choice == 3)
        {
            IsBattle = true; // 3번 선택 시 즉시 전투
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle) {
        // 성공 메세지
        // 경험치 오르고 골드 보상 없이 종료
    }
    else {
        // 실패 메세지
        // 아마도 이곳에서 함수로 방랑자 :: delete ptr과 전투
    }
}


// 일반 전투 이벤트 #3 분쇄자 :: Break. BattleBreaker
void EventManager::BattleBreaker()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 무한 루프 메세지 출력 함수란

    // 무한 루프 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
    }
    else
    {
        Player.SetHealth(max(0, Player.GetHealth() - 5));
        // 실패 메세지 및 전투 발생
    }
}

// 일반 전투 이벤트 #4 침략자 :: 오버플로우. BattleInvader
void EventManager::BattleInvader()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 오버플로우 메세지 출력 함수란

    // 오버플로우 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
    }
    else
    {
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        // 실패 메세지 및 전투 발생
    }
}

// 일반 전투 이벤트 #5 암살자 :: 세그멘테이션 폴트. BattleAssassin
void EventManager::BattleAssassin()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 세그폴트 메세지 출력 함수란

    // 세그폴트 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
    }
    else
    {
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        // 실패 메세지 및 전투 발생
    }
}

// 일반 전투 이벤트 #6 몬스터 재활용 :: 통나무 다리. BattleBridge
void EventManager::BattleBridge()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 구역 메세지 출력 함수란

    // 구역 선택지 출력 함수란

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
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
    }
    else
    {
        // 실패 메세지 및 전투 발생
    }
}

// 일반 전투 이벤트 #7 몬스터 재활용 :: 숲 배회 BattleForest
void EventManager::BattleForest()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 숲 메세지 출력 함수란

    // 숲 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력 (전투 미 발생, 패널티 면제)
        // 경험치 오르고 골드 보상 없이 종료
    }
    else
    {
        // 실패 메세지 출력
        // [당신의 방안은 탁월한 효과를 보였습니다. 버그를 찾아내는데 말입니다... 너무 탁월해서 버그가 바로 앞에 있었거든요...]
        // 전용 메세지 출력 및 몬스터 랜덤 전투 발생
    }
}

// 일반 전투 이벤트 #8 몬스터 재활용 :: 데이터 노이즈 BattleDataNoise
void EventManager::BattleDataNoise()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 데이터 노이즈 메세지 출력 함수란

    // 데이터 노이즈 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력 (전투 미 발생, 패널티 면제)
        // 경험치 오르고 골드 보상 없이 종료
    }
    else
    {
        // 실패 메세지 출력
        // [아무래도 잘못 건드린 모양입니다. 깨진 데이터가 당신의 데이터마저 조금 깨뜨립니다...]
        // HP 10 차감, 전용 메세지 출력 및 몬스터 랜덤 전투 발생
    }
}

// 일반 전투 이벤트 #9 몬스터 재활용 :: 중력 역전 BattleGravity
void EventManager::BattleGravity()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 중력 역전 메세지 출력 함수란

    // 중력 역전 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력 (전투 미 발생, 패널티 면제)
        // 경험치 오르고 골드 보상 없이 종료
    }
    else
    {
        // 실패 메세지 출력
        // [이런, 엄청난 속도로 추락한 거대 버그와 정면으로 충돌했습니다! 충격으로 인해 시야가 흔들리는 가운데...]
        // HP 5 차감, 전용 메세지 출력 및 몬스터 랜덤 전투 발생
    }
}

// 일반 전투 이벤트 #10 몬스터 재활용 :: 절벽 BattleCliff
void EventManager::BattleCliff()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 훼손 데이터 메세지 출력 함수란

    // 훼손 데이터 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지
    }
    else
    {
        // 실패 메세지 및 전투 발생
    }
}




// ============= 구분선 =============
// 이 밑 보스 포함 전투/보상 이벤트
// 전투/보상 이벤트는 맨 앞에 Choice를 붙여서 구분

// 전투/보상 이벤트 #1 처형자 :: 가비지 컬렉션 이벤트 ChoiceGarbageCollector
void EventManager::ChoiceGarbageCollector()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 가비지 컬렉션 메세지 출력 함수란
    // 가비지 컬렉션 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 가비지 컬렉션에게 걸리지 않도록 주의하며 데이터를 챙겨봅니다. [cite: 4]
            Dice.RollDice(20, 10, DexBonus()); // 민첩 보정치 [cite: 5]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 가비지 컬렉션도 결국 코드덩어리. 정면으로 싸움을 겁니다. [cite: 5, 6]
            IsBattle = true;
        }
        else if (Choice == 3)
        {
           // 삭제당할 위험을 감수할 수 없습니다. 욕심을 버리고 빙 돌아서 지나갑니다. [cite: 6, 7]
           return; // 전투 회피 후 즉시 이벤트 종료
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
        // 보상 (골드 지급, 특별 장비)
    }
    else
    {
        // 실패 메세지 출력
        // 즉시 제거가 시작됩니다. 몸이 흐릿해지는 걸 느끼며 맞서 싸웁니다. [cite: 8, 9]
        Player.SetHealth(max(0, Player.GetHealth() - 10)); // HP 10 차감 [cite: 9]
        // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #2 소거자 :: 언디클레어드 이벤트 ChoiceUndeclared
void EventManager::ChoiceUndeclared()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 언디클레어드 메세지 출력 함수란
    // 언디클레어드 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 힘으로 #include <stdio.h>를 제압해 이곳을 다시 관리하도록 제자리에 둡니다. [cite: 17]
            Dice.RollDice(20, 10, StrBonus()); // 근력 보정치 [cite: 18]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 헤더를 고치기엔 너무 멀리 왔습니다. 저 버그 덩어리를 제압하는 수 밖에요. [cite: 18, 19]
            IsBattle = true;
        }
        else if (Choice == 3)
        {
           // 이 지역을 지금 구할 필요가 있을까요? 욕심을 버리고 빙 돌아서 지나갑니다. [cite: 19, 20]
           return;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
    }
    else
    {
        // 실패 메세지 출력
        // 시스템이 당신을 인식할 수 없습니다. 즉시 제거가 시작됩니다. 몸이 흐릿해지는 걸 느끼며 맞서 싸웁니다. [cite: 21, 22]
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #3 투영자 :: 댕글링 포인터 이벤트 ChoiceDanglingPointer
void EventManager::ChoiceDanglingPointer()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 댕글링 포인터 메세지 출력 함수란
    // 댕글링 포인터 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 위험하지만, 직접 댕글링 포인터에 nullptr를 대입하여 원상 복구를 시도합니다 [cite: 27]
            Dice.RollDice(20, 10, StrBonus()); // 근력 보정치 [cite: 27]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 실체가 없더라도 디버깅하면 그만이죠. 정면으로 싸움을 겁니다. [cite: 27, 28]
            IsBattle = true;
        }
        else if (Choice == 3)
        {
           // 시스템 크래시는 무섭습니다. 욕심을 버리고 빙 돌아서 지나갑니다. [cite: 28, 29]
           return;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
        // 데이터 잔상이 소멸하며 안전한 경로가 확보됩니다. [cite: 29]
    }
    else
    {
        // 실패 메세지 출력
        // 녀석은 여전히 존재하지 않는 주소를 읽으려 시도했습니다. 시스템 크래시와 함께 유령 데이터가 실체화되어 당신을 덮칩니다. [cite: 31]
        Player.SetHealth(max(0, Player.GetHealth() - 10));
        // 보스 전투 시작
    }
}

// 전투/보상 이벤트 #4 깨진 액터 이벤트 ChoiceBrokenActor
void EventManager::ChoiceBrokenActor()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 깨진 액터 메세지 출력 함수란
    // 깨진 액터 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 난 운이 좋으니 버그가 떠났을거야. 운에게 맡기며 액터를 살펴봅니다. [cite: 37]
            Dice.RollDice(20, 10, LukBonus()); // 행운 보정치 [cite: 38]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 망가진 액터의 원형을 상상하며 쓸만한 아이템 코드가 남아있는지 살펴봅니다. [cite: 38]
            Dice.RollDice(20, 10, IntBonus()); // 지식 보정치 [cite: 39]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
           // 위험을 감수할 순 없죠. 그냥 지나칩니다. [cite: 39]
           return; // 전투 미발생, 이벤트 종료 [cite: 40]
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
        // 귀중한 물품이 제법 많이 들어있군요. 살아남은 것만 대충 챙겨야겠군요. [cite: 41, 42]
    }
    else
    {
        // 실패 메세지 출력
        // 아무래도 망가진 액터처럼 당신도 망가뜨리려는 모양인데요... 싸움을 피할 순 없겠습니다. [cite: 43]
        // 전투 발생 [cite: 43]
    }
}

// 전투/보상 이벤트 #5 Array 아파트 이벤트 ChoiceUninitArray
void EventManager::ChoiceUninitArray()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 배열 메세지 출력 함수란
    // 배열 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 녀석의 몸에 적힌 방 번호 중 NULL이나 0이 저장된 빈방을 찾아봅니다. [cite: 49]
            Dice.RollDice(20, 10, IntBonus()); // 지식 보정치 [cite: 50]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 고작해야 배열에게 막힐 순 없습니다. 정면으로 싸움을 겁니다. [cite: 50, 51]
            IsBattle = true;
        }
        else if (Choice == 3)
        {
           // 쓰레기값은 예측할 수 없습니다. 욕심을 버리고 빙 돌아서 지나갑니다. [cite: 51, 52]
           return;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공 메세지 출력
    }
    else
    {
        // 실패 메세지 출력
        // 방 전체를 장악한 쓰레기값이 당신의 침입을 감지해 전투를 걸어옵니다. [cite: 53]
        Player.SetHealth(max(0, Player.GetHealth() - 10)); // HP 10 차감 [cite: 53]
        // 보스 전투 시작
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

    // 평범한 보물상자 이벤트 출력 함수란
    // 평범한 보물상자 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 힘으로 상자를 부숴서 내용물을 확인합니다. [cite: 56]
            Dice.RollDice(20, 10, StrBonus()); // 힘 보정치 [cite: 57]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 락픽을 이용해 자물쇠를 따봅니다. [cite: 57]
            Dice.RollDice(20, 10, DexBonus()); // 민첩 보정치 [cite: 58]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 판정 성공 메세지
        // 당신은 신이 나서 안에 있는 금화를 모두 챙깁니다. [cite: 59]
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 상자가 파손되며 내용물도 파손되고 말았습니다... [cite: 60]
    }
}

// 보상 이벤트 #2 const 보물상자 이벤트 ChestConstLock
void EventManager::ChestConstLock()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // const 상자 이벤트 출력 함수란
    // const 상자 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 잠금 장치를 부술 수 없다면, 힘으로 상자를 부숩니다. [cite: 65]
            Dice.RollDice(20, 14, StrBonus()); // 힘 보정치, 판정값 14 [cite: 66, 67]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 디버깅을 해서 const의 위치를 알맞은 곳으로 되돌립니다. [cite: 66]
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치, 판정값 14 [cite: 67]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 판정 성공 메세지
        // 당신은 신이 나서 안에 있는 금화를 모두 챙깁니다. [cite: 68]
    }
    else
    {
        // 판정 실패 메세지
        // 이런, const는 강력하군요... [cite: 69]
    }
}

// 보상 이벤트 #3 && 논리상자 이벤트 ChestAndLogic
void EventManager::ChestAndLogic()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 논리 상자 이벤트 출력 함수란
    // 논리 상자 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 재빠르게 열쇠 두 개를 동시에 집어넣어 봅니다. [cite: 74]
            Dice.RollDice(20, 14, DexBonus()); // 민첩 보정치, 판정값 14 [cite: 74, 76]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 우연히 들어맞길 바라며 열쇠 두 개를 감으로 맞춰봅니다. [cite: 74]
            Dice.RollDice(20, 14, LukBonus()); // 행운 보정치, 판정값 14 [cite: 75, 76]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 회로 하나를 조작해 첫 번째 구멍이 참인 것처럼 속이고 열쇠를 넣습니다. [cite: 75]
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치, 판정값 14 [cite: 76]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 판정 성공 메세지
        // 두 논리가 맞물리며 상자가 열립니다. [cite: 77]
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 타이밍이 맞지 않았던걸까요... 논리가 부정당해 상자가 열리지 않습니다. [cite: 78]
    }
}

// 보상 이벤트 #4 *ptr 보물찾기 이벤트 ChestPointerSearch
void EventManager::ChestPointerSearch()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 포인터 보물찾기 이벤트 출력 함수란
    // 포인터 보물찾기 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 주변의 데이터 흐름을 분석해 *ptr이 가리키는 자료형(Type)을 알아냅니다. [cite: 83]
            Dice.RollDice(20, 14, IntBonus()); // 지식 보정치, 판정값 14 [cite: 84, 85]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 우연히 자료형이 맞길 바라며 하나를 정하고 *ptr을 따라갑니다. [cite: 84]
            Dice.RollDice(20, 14, LukBonus()); // 행운 보정치, 판정값 14 [cite: 85]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 판정 성공 메세지
        // 당신이 생각한 자료형이 맞았습니다! 바닥을 파니 상자가 나옵니다. [cite: 85, 86]
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 자료형이 맞지 않았던걸까요... 바닥을 파도 아무것도 나오지 않습니다. [cite: 87]
    }
}

// 보상 이벤트 #5 버그 액터 수리 이벤트 ChestBugActorFix
void EventManager::ChestBugActorFix()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 버그 액터 수리 이벤트 출력 함수란
    // 버그 액터 수리 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 디버깅 툴을 이용해서 물리적으로 버그의 원흉을 제거합니다. [cite: 92]
            Dice.RollDice(20, 10, StrBonus()); // 힘 보정치, 판정값 10 [cite: 93, 94]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 디버깅 툴을 이용해서 오류가 발생한 코드를 찾아 수정합니다. [cite: 93]
            Dice.RollDice(20, 10, IntBonus()); // 지식 보정치, 판정값 10 [cite: 94]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 판정 성공 메세지
        // 성공적으로 액터의 버그가 제거됩니다. 액터는 마을주민 NPC였습니다. [cite: 94, 95]
    }
    else
    {
        // 판정 실패 메세지
        // 이런, 오류의 원인을 잘못 짚은 모양입니다. 아예 충돌해서 소멸합니다... [cite: 95, 96]
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

    // 갈림길 메세지 출력 함수란
    // 갈림길 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 여정을 쉴 수는 없지, 왼쪽 길로 갑니다. (모험 속행, 다음 이벤트가 전투로 고정) [cite: 101, 102]
            IsBattle = true;
        }
        else if (Choice == 2)
        {
            // 뭔가 불길한데... 상점이 급하니 일단 오른쪽 길로 가봅니다. [cite: 102]
            Dice.RollDice(20, 10, LukBonus()); // 행운 주사위 판정, 10 이하일 경우 전투 조우 [cite: 103]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 당신은 별다른 일 없이 상점에 도착하는데 성공합니다. 팻말은 진짜였군요. [cite: 103, 104]
        // 상점 진입 코드 작성
    }
    else
    {
        // 오른쪽은 당신을 유도하기 위한 함정이었습니다. 버그가 당신을 공격합니다! [cite: 104, 105]
        // 전투 발생 코드 작성
    }
}

// 상점 방문 이벤트 #2 바위 길막기 ShopVillageWay
void EventManager::ShopVillageWay()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 바위 길막기 메세지 출력 함수란
    // 바위 길막기 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 그냥 다른 길로 갑니다. 상점은 다른곳에도 있겠죠. [cite: 109]
            return; // 모험 속행 (상점 포기) [cite: 110]
        }
        else if (Choice == 2)
        {
            // 상점도 가야하고, 주민들도 불편할거야. 바위를 치워봅니다. [cite: 110]
            Dice.RollDice(20, 10, StrBonus()); // 힘 판정 [cite: 111, 112]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 민첩하게 바위를 뛰어넘어 상점을 이용하러 갑니다. [cite: 111]
            Dice.RollDice(20, 10, DexBonus()); // 민첩 판정 [cite: 112]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 당신은 별다른 일 없이 상점에 도착하는데 성공합니다. 팻말은 진짜였군요. [cite: 113, 114]
        // 상점 진입 코드 작성
    }
    else
    {
        // 오른쪽은 당신을 유도하기 위한 함정이었습니다. 버그가 당신을 공격합니다! [cite: 114, 115]
        // 전투 발생 코드 작성
    }
}

// 상점 방문 이벤트 #3 도박꾼 보부상 ShopGamblerBet
void EventManager::ShopGamblerBet()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 보부상 메세지 출력 함수란
    // 보부상 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 뭔 도박이야? 그냥 가던 길을 계속 간다. [cite: 118]
            return; // 모험 속행 (상점 포기) [cite: 119]
        }
        else if (Choice == 2)
        {
            // 까짓거 한 번 굴려보지 뭐. 주사위를 굴린다. [cite: 119]
            Dice.RollDice(20, 10, LukBonus()); // 행운 판정 [cite: 120, 121]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 도박꾼에게 들키지 않게 손기술을 부여 결과값을 조작한다. [cite: 120]
            Dice.RollDice(20, 10, DexBonus()); // 민첩 판정 [cite: 121]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 주사위 값으로 6이 나오며, 5를 굴린 보부상을 이깁니다. 보부상이 킥킥 웃으며 보따리를 풀기 시작합니다. [cite: 122, 123]
        // 상점 진입 코드 작성
    }
    else
    {
        // 이런, 주사위가 1이 나옵니다. 보부상이 기분 나쁘게 웃습니다. [cite: 123, 124]
        // 전투 발생 코드 작성
    }
}

// 상점 방문 이벤트 #4 상점 디버깅 ShopBugStoreFix
void EventManager::ShopBugStoreFix()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 상점 디버깅 메세지 출력 함수란
    // 상점 디버깅 선택지 출력 함수란

    while (true)
    {
        cin >> Choice;
        bool IsValid = true;
        IsBattle = false;

        if (Choice == 1)
        {
            // 귀찮게 왜? 그냥 지나갑니다. [cite: 127]
            return; // 모험 속행 (상점 포기) [cite: 128]
        }
        else if (Choice == 2)
        {
            // 디버깅 툴을 이용해서 상점에 있는 버그를 디버깅해봅니다. [cite: 128]
            Dice.RollDice(20, 10, IntBonus()); // 지식 판정 [cite: 129, 130]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else if (Choice == 3)
        {
            // 운 좋게 버그 난 곳 지워질수도 있는거 아닌가요? 그냥 되는대로 휘두릅니다! [cite: 129, 130]
            Dice.RollDice(20, 10, LukBonus() - 5); // 행운 판정, 역보정 -5 [cite: 130]
            if (!Dice.GetResult()) IsBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 디버깅에 성공했습니다! 상점이 원래의 모습을 되찾습니다. 이제 이용할 수 있겠군요. [cite: 131, 132]
        // 상점 진입 코드 작성
    }
    else
    {
        // 디버깅에 실패했습니다! 오히려 버그가 급증했습니다. 버그가 당신에게 달려듭니다. [cite: 132, 133]
        // 전투 발생 코드 작성
    }
}

// 상점 방문 이벤트 #5 Access Denied 상점 ShopAccessDenied
void EventManager::ShopAccessDenied()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    // 접근 거부 메세지 출력 함수란
    // 접근 거부 선택지 출력 함수란

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
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            IsValid = false;
            cin.clear(); cin.ignore(100, '\n');
        }

        if (IsValid) break;
    }

    if (!IsBattle)
    {
        // 성공적으로 문이 열리며 상점 주인이 제 자리를 되찾습니다. 이제 이용할 수 있겠군요.
        // 상점 진입 코드 작성
    }
    else
    {
        // 문에서 버그가 튀어나옵니다! 버그가 당신을 노립니다...
        // 전투 발생 코드 작성
    }
}
