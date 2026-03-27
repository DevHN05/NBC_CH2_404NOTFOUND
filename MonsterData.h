#pragma once

// =====================================================
//  MonsterData.h
//    - 모든 몬스터/보스의 스펙을 한 곳에서 관리
//
//  사용법:
//    #include "MonsterData.h"
//    shared_ptr<BaseMonster> Goblin = MonsterData::CreateGoblin();
//    헤더에서 "using namespace MonsterData;" 쓰지 말기
// =====================================================

#include "BaseMonster.h"
#include "BaseBossMonster.h"
#include <memory>


namespace MonsterData
{
    // =====================================================
    //  일반 몬스터
    //
    //  생성자 인자 순서 : 이름, 최대HP, 공격력, 경험치보상, 골드보상, 설명(//설명부분은 임시 작성이라 수정 필요)
    // =====================================================

    // 난이도 하
    inline shared_ptr<BaseMonster> CreateBot()
    {
        return make_shared<BaseMonster>("파수꾼 :: 시스템 보안 봇", 80, 12, 30, 10, "파수꾼 관련된 소개 문장");
    }

    // 난이도 중하
    inline shared_ptr<BaseMonster> CreateDeletePtr()
    {
        return make_shared<BaseMonster>("방랑자 :: delete ptr;", 80, 18, 40, 15, "방랑자 관련된 소개 문장");
    }

    // 난이도 중하
    inline shared_ptr<BaseMonster> CreateBreak()
    {
        return make_shared<BaseMonster>("분쇄자 :: Break", 90, 20, 45, 18, "분쇄자 관련된 소개 문장");
    }

    // 난이도 중
    inline shared_ptr<BaseMonster> CreateSemicolon()
    {
        return make_shared<BaseMonster>("암살자 :: 세미콜론", 120, 35, 80, 40, "암살자 관련된 소개 문장");
    }

    // 난이도 중
    inline shared_ptr<BaseMonster> CreateOverflow()
    {
        return make_shared<BaseMonster>("침략자 :: 2147483648", 150, 28, 70, 30, "침략자 관련된 소개 문장");
    }



    // =====================================================
    //  보스 몬스터
    //
    //  생성자 인자 순서: 이름, 최대HP, 공격력, 경험치보상, 골드보상, 플레이어 특수스킬이름, 특수스킬데미지, 설명
    //
    //  반환 타입 shared_ptr<BaseBossMonster>이지만,
    //  CombatManager에서 shared_ptr<BaseMonster>로 받아도 됨 (자식->부모 업캐스팅)
    // =====================================================

    // 난이도 상
    inline shared_ptr<BaseBossMonster> CreateForestGuardian()
    {
        return make_shared<BaseBossMonster>(
            "투영자 :: 댕글링 포인터",   350,  40,  200, 150,
            "nullptr",   60,
            "(예시)~~~~~한 투영자. HP 50% 이하에서 각성한다."
        );
    }

    // 난이도 상
    inline shared_ptr<BaseBossMonster> CreateVolcanicDragon()
    {
        return make_shared<BaseBossMonster>(
            "소거자 :: 언디클레어드",   500,  55,  350, 250,
            "#(헤더)",     90,
            "(예시)~~~~~한 소거자. HP 50% 이하에서 각성한다."
        );
    }

    // 난이도 최상
    inline shared_ptr<BaseBossMonster> CreateShadowLord()
    {
        return make_shared<BaseBossMonster>(
            "처형자 :: 가비지 컬렉션",   450,  62,  400, 300,
            "부모 클래스의 가호", 100,
            "(예시)~~~~~한 처형자. HP 50% 이하에서 각성한다."
        );
    }

}
