// BossMonsterManager.h

#pragma once
#include "MonsterManager.h"

// =====================================================
//  상속 관계 : BaseCharacter → MonsterManager → BossMonsterManager
//
//  일반 몬스터와 차별점:
//    - Health가 50% 이하로 떨어지면 페이즈 2로 전환되어, 공격력이 1.5배로 강화되고 특수 스킬이 해금됨
//    - onPhaseChange()를 override
//    - printStatus()를 override하여 페이즈/스킬 정보 추가 출력
// 
//  BossMonsterManager 에서 추가하는 것:
//    - Phase                   → 현재 보스 상태
//    - PhaseTriggered          → 버프 1회 적용
//    - SpecialSkillName        → 페이즈 2에서 해금되는 스킬 이름 (출력용)
//    - SpecialSkillDamage      → 특수 스킬의 고정 데미지 수치
//    - getter
// =====================================================




class BossMonsterManager : public MonsterManager
{
public:
    BossMonsterManager(
        const string&   InName,
        int             InMaxHealth,
        int             InAttack,
        int             InDefense,
        int             InHealthReward,
        int             InGoldReward,
        const string&   SpecialSkillName,
        int             SpecialSkillDamage,
        const string&   InDescription = "");

    ~BossMonsterManager() override = default;


    // =====================================================
    // BossMonsterManager 전용 getter
    // =====================================================
    int GetPhase() const;
    bool GetPhaseTriggered() const;
    string GetSpecialSkillName() const;
    int GetSpecialSkillDamage() const;


    // -------------------------------------------------
    //  override
    // -------------------------------------------------
    void OnPhaseChange() override;
    void PrintCharacterStatus() const override;


private:
    int    Phase;
    bool   PhaseTriggered;
    string SpecialSkillName;
    int    SpecialSkillDamage;
};

