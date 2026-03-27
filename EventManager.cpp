#include "EventManager.h"
#include "CombatManager.h"
#include "ShopManager.h"
#include "BaseMonster.h"
#include "GraphicManager.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

// 일단 현재 준비된 이벤트 목록은 25개! 25개의 순서를 랜덤하게 섞어주는 함수. 25개가 모자라면 최민서에게 말씀!
EventManager::EventManager(PlayerManager& InPlayer) : Player(InPlayer), CurrentEventIndex(0)
{
    for (int i = 1; i <= 25; ++i) EventIds.push_back(i);
    ShuffleEvents();
}

void EventManager::ShuffleEvents()
{
    random_device rd;
    mt19937 g(rd());
    shuffle(EventIds.begin(), EventIds.end(), g);
    CurrentEventIndex = 0;
}

// 이 함수를 호출할때마다 랜덤하게 섞인 이벤트가 순서대로 실행
// 한번 호출할때마다 하나만 실행하게 했는데, 여기서 무한 순환 돌리면서 보스전 조건까지 달아도 되긴 할수도?
void EventManager::TriggerNextEvent()
{
    if (CurrentEventIndex >= EventIds.size()) ShuffleEvents(); // 이벤트를 다 소진했으면 다시 섞는 함수

    int id = EventIds[CurrentEventIndex++];     // 이번 차례의 이벤트 번호를 꺼내고, 다음 차례로 넘기는 함수

    switch (id)
    {							    // 이번 차례에 맞는 번호의 이벤트 소환
    case 1: BattleFirewall(); break;			// 노말 이벤트 #1 vs시스템 보안 봇
    case 2: BattleMemoryLeak(); break;			// 노말 이벤트 #2 vs방랑자 :: delete ptr
    case 11: ChoiceGarbageCollection(); break;	// 전투/보상 이벤트 #1 vs가비지컬렉션(miniboss)
    case 16: ChestNormal(); break;				// 보상 이벤트 #1 평범한 보물상자
    case 21: ShopChoiceEvent(); break;			// 상점 이벤트 #1 갈림길
    default:                                    // 아직 못 만든 이벤트 번호가 있거나 그 외 상황으로 인해 그 번호에 이벤트가 없을 경우 그냥 호출 안하고 넘기기
        break;
    }
}

// ========== 구분선 ===========
// 일반 전투 이벤트는 맨 앞에 Battle을 붙여서 구분

// 일반 전투 이벤트 #1 파수꾼 :: 시스템 보안 봇 이벤트. BattleFirewall
void EventManager::BattleFirewall()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    int choice;
    bool isBattle = false;

    // 파수꾼 메세지 출력 함수란

    // 파수꾼 선택지 출력 함수란

	while (true)
	{
	    cin >> choice;

        bool isValid = true;
        isBattle = false;

        if (choice == 1)
        {
            Dice.RollDice(20, 13, DexBonus);
            if (!Dice.GetResult()) isBattle = true;
        }
        else if (choice == 2)
        {
            Dice.RollDice(20, 13, IntBonus);
            if (!Dice.GetResult()) isBattle = true;
        }
        else if (choice == 3)
        {
            isBattle = true; // 3번 선택 시 즉시 전투
        }
	    else
	    {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            isValid = false;

            cin.clear();
            cin.ignore(100, '\n');
	    }

        if (isValid) break;
    }

    if (!isBattle)
    {
        // 성공 메세지
        // 경험치 오르고 골드 보상 없이 종료
    }
    else
    {
        // 실패 메세지 출력. 여긴 실패해도 체력 손해는 없음!
        // 보안봇과 전투 함수
    }
}

// 일반 전투 이벤트 #2 방랑자 :: delete ptr; 이벤트 BattleMemoryLeak
void EventManager::BattleMemoryLeak()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    int choice;
    bool isBattle = false;

    // 메모리 누수 메세지 출력 함수란

    // 메모리 누수 선택지 출력 함수란

	while (true)
	{
	    cin >> choice;

        bool isValid = true;
        isBattle = false;

        if (choice == 1)
        {
            Dice.RollDice(20, 13, Player.GetStrength() / 5);
            if (!Dice.GetResult()) isBattle = true;
        }
        else if (choice == 2)
        {
            Dice.RollDice(20, 13, Player.GetDexterity() / 5);
            if (!Dice.GetResult()) isBattle = true;
        }
        else if (choice == 3)
        {
            isBattle = true; // 3번 선택 시 즉시 전투
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            isValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (isValid) break;
    }

    if (!isBattle) {
        // 성공 메세지
        // 경험치 오르고 골드 보상 없이 종료
    }
    else {
        // 실패 메세지
        // 아마도 이 함수로 방랑자 :: delete ptr과 전투?
    }
}

// ============= 구분선 =============
// 이 밑 보스 포함 전투/보상 이벤트
// 전투/보상 이벤트는 맨 앞에 Choice를 붙여서 구분

// 전투/보상 이벤트 #1  처형자 :: 가비지 컬렉션 이벤트 GarbageCollection
void EventManager::ChoiceGarbageCollection()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    int choice;
    bool isBattle = false;

    // 가비지 컬렉션 메세지 출력 함수란

    // 가비지 컬렉션 선택지 출력 함수란

	while (true)
	{
	    cin >> choice;

        bool isValid = true;
        isBattle = false;

        if (choice == 1)
        {
            Dice.RollDice(20, 13, Player.GetDexterity() / 5);
            if (!Dice.GetResult()) isBattle = true;
        }
        else if (choice == 2)
        {
            isBattle = true; // 2번 선택 시 패널티 없이 즉시 전투
        }
        else if (choice == 3)
        {
	    	break; // 보스전은 3번 선택시 즉시 도망 가능
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            isValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (isValid) break;
    }

    if (!isBattle)
    {
        // 성공 메세지 출력
        // 경험치 오르고 골드 보상 얻으며 종료
    }
    else
    {
        // 실패 메세지
        // HP 10 차감, Garbage Collection과의 보스 전투 시작
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
    int choice;
    bool isBattle = false;

    // 평범한 보물상자 이벤트 출력 함수란

    // 평범한 보물상자 선택지 출력 함수란

	while (true)
	{
	    cin >> choice;

        bool isValid = true;
        isBattle = false;

        if (choice == 1)
        {
            Dice.RollDice(20, 13, Player.GetStrength() / 5);
            if (!Dice.GetResult()) isBattle = true;
        }
        else if (choice == 2)
        {
            Dice.RollDice(20, 13, Player.GetDexterity() / 5);
            if (!Dice.GetResult()) isBattle = true;
        }
        else
        {
            Gm.GoSpace(2, 26); cout << "잘못된 입력입니다. 선택지에 맞는 숫자를 입력해주세요.";
            isValid = false;

            cin.clear();
            cin.ignore(100, '\n');
        }

        if (isValid) break;
    }

    if (!isBattle)
    {
        // 판정 성공 메세지
        // 골드 경험치 보상 얻고 종료
    }
    else
    {
        // 판정 실패 메세지
        // 보상 이벤트는 실패 패널티는 없음
		CombatManager::GetInstance().StartBattle(Player, SecurityBot);
    }
}

// ============= 구분선 =============
// 이 밑 상점 이벤트
// 맨 앞에 Shop를 붙여서 구분
// 현재 상점 빈도나 등장 등 관련 구현 못한 상태

// 상점 방문 이벤트
void EventManager::ShopChoiceEvent()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    int choice;
    bool isBattle = false;
}
