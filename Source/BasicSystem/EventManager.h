#pragma once
#include <vector>
#include "DiceSystem.h"
#include "../Character/PlayerManager.h"

enum EEventId {
    // [01~10] 전투 이벤트
    EV_Guardian = 1, EV_Wanderer, EV_Breaker, EV_Invader, EV_Assassin,
    EV_Bridge, EV_Forest, EV_DataNoise, EV_Gravity, EV_Cliff,
    // [11~15] 선택 이벤트
    EV_GarbageCollector, EV_Undeclared, EV_DanglingPointer, EV_BrokenActor, EV_UninitArray,
    // [16~20] 보상 이벤트
    EV_ChestNormal, EV_ChestConstLock, EV_ChestAndLogic, EV_ChestPointerSearch, EV_ChestBugActorFix,
    // [21~25] 상점 이벤트
    EV_ShopChoice, EV_ShopVillageWay, EV_ShopGamblerBet, EV_ShopBugStoreFix, EV_ShopAccessDenied
};

class EventManager
{
public:
    EventManager(PlayerManager& InPlayer);
    static void WaitEnter();
    void TriggerNextEvent();
    void TutorialEvent();                    // 튜토리얼 이벤트 호출 함수

private:
    PlayerManager& Player;
    vector<int> ShopEventIds;
    vector<int> NormalEventIds;
    vector<int> EventIds;
    DiceSystem Dice;
    size_t CurrentEventIndex = 0;
    int Choice;
    bool IsBattle;
    void ShuffleEvents();


    // --- [01~10] 전투 이벤트 ---
    void BattleGuardian();                   // 노말 이벤트 #1 파수꾼 :: 시스템 보안 봇
    void BattleWanderer();                   // 노말 이벤트 #2 방랑자 :: delete ptr
    void BattleBreaker();                    // 노말 이벤트 #3 분쇄자 :: Break
    void BattleInvader();                    // 노말 이벤트 #4 침략자 :: 오버플로우
    void BattleAssassin();                   // 노말 이벤트 #5 암살자 :: 세그멘테이션 폴트
    void BattleBridge();                     // 노말 이벤트 #6 몬스터 재활용 :: 통나무 다리
    void BattleForest();                     // 노말 이벤트 #7 몬스터 재활용 :: 숲 배회
    void BattleDataNoise();                  // 노말 이벤트 #8 몬스터 재활용 :: 데이터 노이즈
    void BattleGravity();                    // 노말 이벤트 #9 몬스터 재활용 :: 중력 역전
    void BattleCliff();                      // 노말 이벤트 #10 몬스터 재활용 :: 절벽

    // --- [11~15] 보상 / 전투 / 회피(줄여서 선택) 이벤트 ---
    void ChoiceGarbageCollector();           // 선택 이벤트 #11 처형자 :: 가비지 컬렉션
    void ChoiceUndeclared();                 // 선택 이벤트 #12 소거자 :: 언디클레어드
    void ChoiceDanglingPointer();            // 선택 이벤트 #13 투영자 :: 댕글링 포인터
    void ChoiceBrokenActor();                // 선택 이벤트 #14 깨진 액터
    void ChoiceUninitArray();                // 선택 이벤트 #15 Array 아파트

    // --- [16~20] 보상 이벤트 (보물상자) ---
    void ChestNormal();                      // #16 평범한 보물상자
    void ChestConstLock();                   // #17 const 보물상자
    void ChestAndLogic();                    // #18 && 논리상자
    void ChestPointerSearch();               // #19 *ptr 보물찾기
    void ChestBugActorFix();                 // #20 버그 액터 수리

    // --- [21~25] 상점 방문 이벤트 ---
    void ShopChoiceEvent();                  // #21 갈림길
    void ShopVillageWay();                   // #22 바위 길막기
    void ShopGamblerBet();                   // #23 도박꾼 보부상
    void ShopBugStoreFix();                  // #24 상점 디버깅
    void ShopAccessDenied();                 // #25 Access Denied 상점


    // --- [스탯 보정값 계산기] ---
    int StrBonus() { return Player.GetStrength() / 5; }
    int DexBonus() { return Player.GetDexterity() / 5; }
    int IntBonus() { return Player.GetIntelligence() / 5; }
    int LukBonus() { return Player.GetLuck() / 5; }
};
