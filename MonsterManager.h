// MonsterManager.h

#pragma once
#include "BaseCharacter.h"
#include <string>

// =====================================================
//  BaseCharacter 를 상속받는 몬스터 클래스
//
//  BaseCharacter 에서 물려받는 것:
//    - Health             → 현재 HP
//    - MaxHealth         → HP 상한
//    - Strength           → 공격력
//    - Nickname           → 몬스터 이름
//    - getter, setter
//    - PrintCharacterStatus
//
//  MonsterManager 에서 추가하는 것:
//    - HealthReward          → 경험치 보상
//    - GoldReward        → 골드 보상
//    - Description        → 세계관 설명 텍스트
//    - getter
//    - IsAlive()           → 생존 여부
//    - TakeDamage()       → 방어력 차감 데미지 계산
//    - ResetHealth()      → HP 전체 회복
//    - OnPhaseChange()   → 보스 전용 훅
// =====================================================


class MonsterManager : public BaseCharacter {
public:
    MonsterManager(
        const string& InName,
        int           InMaxHealth,
        int           InAttack,
        int           InHealthReward,
        int           InGoldReward,
        const string& InDescription = "");

    virtual ~MonsterManager() = default;


    // =====================================================
    // MonsterManager 전용 getter
    // =====================================================
    int GetHealthReward() const;
    int GetGoldReward() const;
    string GetDescription() const;
    bool IsAlive() const;


    // =====================================================
    // 전투 메서드
    // =====================================================
    virtual int TakeDamage(int InDamage);    // 방어력(dexterity_) 차감 후, 실제로 깎인 HP 반환
    void ResetHealth();


    // =====================================================
    //  페이즈 전환 훅 — BossMonster 에서만 override
    // =====================================================
    virtual void OnPhaseChange() {}


    // -------------------------------------------------
    //  override
    // -------------------------------------------------
    void PrintCharacterStatus() const override;


protected:
    int HealthReward;       //경험치 보상 (처치 후 지급)
    int GoldReward;         //골드 보상 (처치 후 지급)
    string Description;     //출력되는 설명


};