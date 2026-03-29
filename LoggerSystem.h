#pragma once
#include <map>
#include <vector>
#include <string>
#include "ItemManager.h"

using namespace std;

class LoggerSystem
{
public:
    LoggerSystem(const LoggerSystem&) = delete;
    void operator=(const LoggerSystem&) = delete;

    static LoggerSystem& GetInstance()
    {
        static LoggerSystem Instance;
        return Instance;
    }

    //전투 관련
    void LogMonsterAppear(const string& MonsterName); //몬스터 등장
    void LogAttack(const string& Attacker, const string& Target, int Damage); //공격시 출력
    void LogMonsterKill(const string& MonsterName); //몬스터 처치
    void LogBossPhaseChange(const string& Nickname, const string& SpecialSkillName, int BoostedStrength); //보스 페이즈 변경
    void LogDiceRoll(int Head, bool IsSucceeded); //주사위 판정

    //캐릭터 관련
    void LogLevelUp(int NewLevel); //레벨업
    void LogPlayerDeath(); //플레이어 사망

    //아이템 관련
    void LogItemUse(const string& ItemName, const string& Effect); //아이템 사용

    //보상 관련
    void LogExpGain(int Amount, int MyExp, int MaxExp); //경험치 획득
    void LogGoldGain(int Amount, int MyGold); //골드 획득

    //상점 관련
    void LogShopPrompt(); //상점 입장 선택지 (출력 문구는 수정해야할 수 있음)
    void LogShopEnter(); //상점 입장 (출력 문구는 수정해야할 수 있음)
    void LogShopDecline(); //상점 입장 거절 (출력 문구는 수정해야할 수 있음)
    void LogBuyItem(const string& ItemName, int Price); //구매한 아이템, 소모 골드
    void LogInsufficientGold(int MyGold, int RequiredGold); //골드가 부족할 때
    void LogSellItem(const string& ItemName, int SellPrice); //판매 완료한 아이템과 얻은 골드
    void LogShopSellPrompt(); //판매 아이템 입력칸
    void LogItemNotFound(const string& ItemName); //인벤토리에 아이템 없음
    void LogPrintShopItems(const vector<shared_ptr<ItemManager>>& Items, const vector<shared_ptr<ItemManager>>& CurrentDisplayItems); //상점의 아이템 목록
    void LogPrintShopMenu(); //상점 메뉴

    //전투 이벤트
    void LogEventWanderer(int StrBonus, int DexBonus); //방랑자
    void LogEventFailWanderer();

    void LogEventGuardian(int DexBonus, int IntBonus); //파수꾼
    void LogEventFailGuardian();

    void LogEventBreaker(int StrBonus, int IntBonus); //분쇄자
    void LogEventFailBreaker();

    void LogEventInvader(int DexBonus, int LukBonus); //침략자
    void LogEventFailInvader();

    void LogEventAssassin(int StrBonus, int IntBonus); //암살자
    void LogEventFailAssassin();

    void LogEventBridge(int DexBonus, int LukBonus, int StrBonus); //아래로 쭉 재활용 몬스터
    void LogEventFailBridge();

    void LogEventForest(int IntBonus, int LukBonus);
    void LogEventFailForest();

    void LogEventDataNoise(int IntBonus, int LukBonus);
    void LogEventFailDataNoise();

    void LogEventGravity(int LukBonus, int IntBonus);
    void LogEventFailGravity();

    void LogEventCliff(int DexBonus, int IntBonus);
    void LogEventFailCliff();

    //보상/전투/회피 이벤트(
    void ChoiceGarbageCollector(int DexBonus); //제일 쎔 - 처형자 :: 가비지 컬렉션
    void ChoiceGarbageCollectorSuccess();
    void ChoiceGarbageCollectorFail();

    void ChoiceUndeclared(int StrBonus); //중간 - 소거자 :: 언디클레어드
    void ChoiceUndeclaredSuccess();
    void ChoiceUndeclaredFail();

    void ChoiceDanglingPointer(int StrBonus); //중간 - 투영자 :: 댕글링 포인터
    void ChoiceDanglingPointerSuccess();
    void ChoiceDanglingPointerFail();

    void ChoiceBrokenActor(int LukBonus, int IntBonus);
    void ChoiceBrokenActorSuccess();
    void ChoiceBrokenActorFail();

    void ChoiceUninitArray(int IntBonus);
    void ChoiceUninitArraySuccess();
    void ChoiceUninitArrayFail();

    //요약
    void PrintSummary(); //처치 몬스터 수, 획득 골드, 획득 경험치
    void PrintEventLog(); //플레이하면서 출력한 이벤트 로그 (선택지, 상점 목록같은 Prompt는 제외)

private:
    int TotalGold;
    int TotalExp;
    LoggerSystem() : TotalGold(0), TotalExp(0) {}
    map<string, int> MonsterKillLogs;
    vector<string> EventLogs;
    void PrintMainArea(const vector<string>& Lines);
};

