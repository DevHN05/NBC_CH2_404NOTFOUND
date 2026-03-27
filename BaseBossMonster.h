// BaseBossMonster.h

#pragma once
#include "BaseMonster.h"

// =====================================================
//  상속 관계 : BaseCharacter → BaseMonster → BaseBossMonster
//
//  일반 몬스터와 차별점:
//    - Health가 50% 이하로 떨어지면 페이즈 2로 전환되어, 공격력이 1.5배로 강화되고 특수 스킬이 해금됨
//    - onPhaseChange()를 override
//    - printStatus()를 override하여 페이즈/스킬 정보 추가 출력
//
//  BaseBossMonster 에서 추가하는 것:
//    - Phase                   → 현재 페이즈 번호. 초기값 1, onPhaseChange() 발동 시 2로 변경
//    - PhaseTriggered          → 페이즈 전환 중복 방지
//    - SpecialSkillName        → 페이즈 2에서 해금되는 플레이어 스킬 이름 (출력용)
//    - SpecialSkillDamage      → 특수 스킬의 고정 데미지 수치. CombatManager가 직접 읽어야 함.
//    - override
//      - OnPhaseChange()       → CombatManager가 매 턴 호출. 조건부로 딱 한 번 발동 (조건은 함수 선언부 참고)
//    - getter
//      - GetPhase()            → 현재 페이즈 반환 (1 = 일반, 2 = 각성)
// =====================================================




class BaseBossMonster : public BaseMonster
{
public:
    BaseBossMonster(
        const string&   InName,
        int             InMaxHealth,
        int             InAttack,
        int             InHealthReward,
        int             InGoldReward,
        const string&   SpecialSkillName,
        int             SpecialSkillDamage,
        const string&   InDescription = "");

    ~BaseBossMonster() override = default;


    // =====================================================
    // BossMonsterManager 전용 getter
    // =====================================================
    int GetPhase() const;
    string GetSpecialSkillName() const;
    int GetSpecialSkillDamage() const;


    // =====================================================
    //  override
    //    - OnPhaseChange()는 두 가지 조건을 동시에 만족해야 발동
    //      1) PhaseTriggered == false  → 아직 한 번도 전환 안 됨
    //      2) 현재 HP <= 최대 HP / 2    → 절반 이하로 깎였을 때
    // =====================================================
    void OnPhaseChange() override;
    void PrintCharacterStatus() const override;


private:
    int    Phase;
    bool   PhaseTriggered;
    string SpecialSkillName;
    int    SpecialSkillDamage;
};

