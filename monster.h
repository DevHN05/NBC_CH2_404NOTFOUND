// monster.h

#pragma once
#include "character.h"
#include <string>

// =====================================================
//  character 를 상속받는 몬스터 클래스
//
//  character 에서 물려받는 것:
//    - health_          → 현재 HP
//    - maxHealth_       → HP 상한
//    - strength_        → 공격력
//    - dexterity_       → 방어/회피 관련
//    - nickname_        → 몬스터 이름
//    - gold_            → 골드 보상
//    - getter, setter
//
//  Monster 에서 추가하는 것:
//    - xpReward_        → 경험치 보상
//    - description_     → 세계관 설명 텍스트
//    - getter
//    - isAlive()        → 생존 여부
//    - takeDamage()     → 방어력 차감 데미지 계산
//    - resetHealth()        → HP 전체 회복
//    - onPhaseChange()  → 보스 전용 훅
// =====================================================


class monster : public character {
public:
    monster(
        const string& name,
        int           max_health,
        int           attack,
        int           defense,
        int           xp_reward,
        int           gold_reward,
        const string& description = "");

    virtual ~monster() = default;


    // =====================================================
    // monster 전용 getter
    // =====================================================
    int get_xp_reward() const;
    string get_description() const;
    bool is_alive() const;



    // =====================================================
    // 전투 메서드
    // =====================================================
    virtual int take_damage(int damage);     // 방어력(dexterity_) 차감 후, 실제로 깎인 HP 반환
    void reset_health();


    // =====================================================
    //  페이즈 전환 훅 — BossMonster 에서만 override
    // =====================================================
    virtual void on_phase_change() {}


protected:
    int xp_reward_;                          //경험치 보상 (처치 후 지급)
    string description_;                    //출력되는 설명


};