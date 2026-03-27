#pragma once
#include <vector>
#include "DiceSystem.h"
#include "PlayerManager.h"

class EventManager
{
public:
    EventManager(PlayerManager& InPlayer);
    void TriggerNextEvent();

private:
    int choice;
    bool isBattle;
    void ShuffleEvents();

    void BattleFirewall(); 		             // 노말 이벤트 #1 vs시스템 보안 봇
    void BattleMemoryLeak();	             // 노말 이벤트 #2 vs방랑자 :: delete ptr
	void ChoiceGarbageCollection();			 // 전투/보상 이벤트 #1 vs가비지컬렉션(miniboss)
    void ChestNormal(); 		             // 보상 이벤트 #1 평범한 보물상자
	void ShopChoiceEvent();					 // 상점 이벤트 #1 갈림길

    PlayerManager& Player;
    DiceSystem Dice;
    std::vector<int> EventIds;
    size_t CurrentEventIndex;
    int StrBonus() { return Player.GetStrength() / 5; }
    int DexBonus() { return Player.GetDexterity() / 5; }
    int IntBonus() { return Player.GetIntelligence() / 5; }
    int LukBonus() { return Player.GetLuck() / 5; }
};
