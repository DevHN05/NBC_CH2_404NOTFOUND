#include "LoggerSystem.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "GraphicManager.h"

//상단 출력 헬퍼
void LoggerSystem::PrintMainArea(const vector<string>& Lines)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    for (int i = 0; i < 17; i++)
    {
        Gm.GoSpace(2, i);
        cout << string(106, ' ');
    }

    for (int i = 0; i < (int)Lines.size() && i < 15; ++i)
    {
        Gm.GoSpace(2, 2 + i);
        for (char C : Lines[i])
        {
            cout << C;
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(15));
        }
        this_thread::sleep_for(chrono::milliseconds(80));
    }
}

//----------------------------전투 관련-----------------------------------
//몬스터가 나타났을때 로그 출력하는 함수
void LoggerSystem::LogMonsterAppear(const string& MonsterName)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ DETECTION ] 버그 개체 [ " + MonsterName + " ] 접근 확인. 디버깅 개시.";

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//공격을 했을 때 로그 출력하는 함수
void LoggerSystem::LogAttack(const string& Attacker, const string& Target, int Damage)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ ATTACK ] " + Attacker + " >> " + Target + " 에 디버깅 실행 / 데미지: " + to_string(Damage);

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//몬스터를 처치했을때 로그 출력하는 함수(해당 몬스터의 처치수를 ++함)
void LoggerSystem::LogMonsterKill(const string& MonsterName)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	MonsterKillLogs[MonsterName]++;
	string Log = "[ DEBUG COMPLETE ] " + MonsterName + " 제거됨. 데이터 수집 중...";

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//보스 페이즈 변화 로그 출력 함수
void LoggerSystem::LogBossPhaseChange(const string& Nickname, const string& SpecialSkillName, int BoostedStrength)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log1 = "[ CRITICAL WARNING ] 버그 개체 [ " + Nickname + " ] 자가 코드 재작성 감지";

    //이놈이 문제
    string Log2 = "  >> 권한 레벨 상승 / " + SpecialSkillName + "활성";

    string Log3 = "  >> ATK -> " + to_string(BoostedStrength) + "  |  디버깅 난이도 상승";

    Gm.AddLog(Log1);
    Gm.AddLog(Log2);
    Gm.AddLog(Log3);

    EventLogs.push_back(Log1);
    EventLogs.push_back(Log2);
    EventLogs.push_back(Log3);
};

//주사위 로그 출력 함수
void LoggerSystem::LogDiceRoll(int Head, bool IsSucceeded)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Result = IsSucceeded ? "성공!" : "실패...";
	string Log = "[ DICE ] 주사위 " + to_string(Head) + " → " + Result;

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
}

//-----------------------------전투 이벤트 관련----------------------------------
//방랑자::delete ptr;
void LoggerSystem::LogEventWanderer(int StrBonus, int DexBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "원래는 평화로웠던 땅이 검게 변색된 [메모리 누수 구역]으로 변해있는 것을 발견합니다.",
        "정체를 알 수 없는 데이터 찌꺼기들이 늪처럼 넘실거립니다.",
        "여기에 발을 들였다간, 버그 데이터랑 맞닥뜨리게 될 것 같은 불길한 느낌이 듭니다.",
        "다행히, 렌더링 오류로 공중에 멈춘 거대한 바위 파편들이 징검다리처럼 놓여 있군요.",
        "고정되지 않은 오브젝트들이라 사이 거리가 제법 된다는 점이 문제지만요."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 오브젝트를 근력으로 쓰러뜨려 평탄한 길을 확보합니다. (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 바위 파편 위를 건너뛰며 건너편으로 갑니다. (판정값 10, 민첩 보정 +" + to_string(DexBonus) + ")");
}

//실패 메세지 - 방랑자::delete ptr;
void LoggerSystem::LogEventFailWanderer()
{
    PrintMainArea({
        "이런, 역부족이었습니다. 당신의 신체 데이터가 누수되는 느낌이 듭니다..",
        "설상가상으로 늪에 발목까지 깊이 빠진 당신에게 알 수 없는 괴물이 접근해옵니다..."
    });
}

//파수꾼::시스템 보안 봇
void LoggerSystem::LogEventGuardian(int DexBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "다음 구역으로 향하던 당신은 관리자 권한 없이는 통과할 수 없는 [방화벽]을 마주합니다.",
        "방화벽에는 데이터가 차단된 플레이어들의 잔영이 매달려 있습니다.",
        "잘못 건드렸다간 시스템 보안 봇에게 침입자로 간주되어 Delete 당할 것 같습니다.",
        "다행히 방화벽의 소스 코드가 꼬여 발생한 보안 취약점이 보입니다.",
        "하지만 실수로 보안 레이어를 건드려 경보를 울린다면, 정말 골치 아픈 일이 벌어질 겁니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 보안 취약점 사이로 재빠르게 지나갑니다. (판정값 13, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 방화벽의 취약점을 분석해 무력화하고 통과합니다. (판정값 13, 지능 보정 +" + to_string(IntBonus) + ")");
}

//실패 메세지 - 파수꾼::시스템 보안 봇
void LoggerSystem::LogEventFailGuardian()
{
    PrintMainArea({
        "이런, 보안 레이어를 건드려버리고 말았습니다.",
        "경보음이 울리고, 시스템 보안 봇이 당신을 발견합니다..."
    });
}

//분쇄자::Break
void LoggerSystem::LogEventBreaker(int StrBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "여정을 이어가던 당신은 조건이 어긋나 똑같은 풍경이 끝없이 반복되는 [무한 루프문]에 진입합니다.",
        "마을 사람 NPC도 특정 행동만을 반복하며 굳어 있고, Break도 보이지 않습니다.",
        "이 루프를 끊어내지 못하면 프로세스 점유율이 치솟아 시스템이 다운되고 말 것입니다.",
        "루프를 강제로 종료하거나, 조건문을 건드려 탈출 조건을 만들어내야 합니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 루프문 코드를 디버그 툴로 파괴해 물리적으로 종료합니다. (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 조건문을 수정해서 디버깅해, 반복문을 정상으로 되돌립니다. (판정값 10, 지능 보정 +" + to_string(IntBonus) + ")");
}

//실패 메세지 - 분쇄자::Break
void LoggerSystem::LogEventFailBreaker()
{
    PrintMainArea({
        "루프가 끊기지 않고 오히려 더 복잡하게 꼬여버렸습니다!",
        "과부하로 인해 연산 장치가 뜨거워지며, 빈틈을 노려 버그가 다가옵니다."
    });
}

//침략자::2147483648
void LoggerSystem::LogEventInvader(int DexBonus, int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "길을 가던 당신은 텅 비어 있어야 할 공간에 정체불명의 데이터가 가득 찬 오버플로우 지점을 발견합니다.",
        "할당된 메모리 범위를 넘어선 데이터들이 주변을 오염시키며 괴상한 형태로 뒤틀려 있습니다.",
        "잘못 건드렸다간 당신의 데이터마저 오염되어 엉뚱한 영향을 받을 것 같습니다.",
        "오버플로우에 휩쓸리지 않고 다음 지역으로 넘어가야 합니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 오버플로우에 영향받기 전에 재빠르게 다음 구역으로 질주합니다. (판정값 13, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 자료형에 맞는 데이터가 담기길 기대하며 다음 구역으로 향합니다. (판정값 13, 행운 보정 +" + to_string(LukBonus) + ")");
}

//실패 메세지 - 침략자::2147483648
void LoggerSystem::LogEventFailInvader()
{
    PrintMainArea({
        "실수로 오버플로우에 닿아버리고 맙니다. 당신의 체력값 역시 영향을 피할 수 없습니다.",
        "HP값이 변동되며, 나타난 버그와의 전투를 치뤄야만 합니다."
    });
}

//암살자::세미콜론
void LoggerSystem::LogEventAssassin(int StrBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 가파른 오르막길에 자리한 계단을 마주합니다.",
        "계단 한 칸 한 칸이 세미콜론(;) 모양으로 생겼습니다.",
        "세미콜론을 하도 빼먹어서 분노한 세미콜론이 모든 오브젝트를 바꿔버린 모양입니다.",
        "정작 필요한 세미콜론은 빠져있어, 계단이 두 칸이 하나로 이어지거나 아예 깨져 있습니다.",
        "한 칸이라도 잘못 밟으면 컴파일 에러가 일어나 큰 일이 벌어질 것 같습니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 세미콜론이 빠진 곳을 잘 피해 성큼성큼 뛰어갑니다. (판정값 13, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 빠진 세미콜론을 넣고 계단 데이터를 복구하며 나아갑니다. (판정값 13, 지능 보정 +" + to_string(IntBonus) + ")");
}

//실패 메세지 - 암살자
void LoggerSystem::LogEventFailAssassin()
{
    PrintMainArea({
        "실수로 컴파일 에러가 발생하고 맙니다. 당신은 순간적으로 의식을 잃습니다.",
        "정신을 차리니, 데이터가 일부 소실됐고 암살자 :: 세미콜론이 당신을 노려보고 있습니다."
    });
}

//재활용 - 통나무 다리
void LoggerSystem::LogEventBridge(int DexBonus, int LukBonus, int StrBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 오류가 가득한 통나무 다리를 발견합니다.",
        "다리는 버그로 인해 지역 변수로 변해 있었습니다.",
        "한 명이 지나가면 스택 프레임이 반환되어 다리 개체 자체가 소멸해버립니다.",
        "일방통행이라 건너는 도중 도착 지점에 버그가 나타난다면 전투를 치러야 합니다.",
        "저 멀리서 깨진 음향 파일 같은 기분 나쁜 소음이 들려옵니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 버그가 앞길을 막기 전에 다리를 빠르게 건너갑니다. (판정값 14, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 버그가 나타나지 않길 바라며 다리를 건넙니다. (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("3. 힘으로 절벽을 한 번에 뛰어넘어봅니다. (판정값 14, 힘 보정 +" + to_string(StrBonus - 5) + ")");
}

//실패 메세지 - 통나무 다리
void LoggerSystem::LogEventFailBridge()
{
    PrintMainArea({
        "이런, 다리를 다 건너지 못했는데 버그가 건너편에 나타나고 맙니다.",
        "다리의 출구를 버그가 가로막습니다. 전투를 피할 수 없겠습니다..."
    });
}

//재활용 - 숲
void LoggerSystem::LogEventForest(int IntBonus, int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "숲을 걷고 있던 당신. 어디선가 스산한 소리가 들려오기 시작합니다.",
        "적대적인 존재의 것 같은데, 모습은 보이지 않고 소리도 깨져서 방향을 알 수 없습니다.",
        "여정을 계속하려면 이 숲을 빨리 지나가야 하는데, 왜인지 마주칠 것만 같습니다.",
        "이대로는 안되겠군요. 무언가 방안을 세워야만 할 것 같습니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 버그의 흔적을 조사하고 방향을 유추해 피해갑니다. (판정값 14, 지능 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("2. 아무 일도 없길 바라며 행운에 기대 숲을 지나갑니다. (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
}

//실패 메세지 - 숲
void LoggerSystem::LogEventFailForest()
{
    PrintMainArea({
        "당신의 방안은 탁월한 효과를 보였습니다. 버그를 찾아내는데 말입니다.",
        "다만, 너무 탁월해서 문제입니다. 버그가 당신의 바로 앞에 있었거든요..."
    });
}

//재활용 - 데이터 노이즈
void LoggerSystem::LogEventDataNoise(int IntBonus, int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "다음 구역으로 진입하자마자 시야가 심하게 흔들립니다.",
        "사방에 깨진 코드로 인한 데이터 노이즈가 일렁입니다.",
        "한 걸음만 잘못 내디뎌도 맵 밖으로 추락하거나 벽 속에 갇혀버릴 것만 같습니다.",
        "어디선가 이 데이터 노이즈를 일으킨 버그들의 기척이 느껴집니다.",
        "당신까지 버그가 나기 전에, 이 혼란스러운 코드를 안전하게 빠져나가야 합니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 구역의 구조를 파악하고 정상적인 코드를 골라 나아갑니다. (판정값 14, 지능 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("2. 버그가 안 옮길 빌며 행운에 기대 이 지역을 나아가봅니다. (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
}

//실패 메세지 - 데이터 노이즈
void LoggerSystem::LogEventFailDataNoise()
{
    PrintMainArea({
        "아무래도 잘못 건드린 모양입니다. 깨진 데이터가 당신의 데이터마저 조금 깨뜨립니다.",
        "그와 동시에 깨진 데이터에는 늘 존재하는 버그가 당신을 마주합니다."
    });
}

//재활용 - 중력
void LoggerSystem::LogEventGravity(int LukBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "갑자기 주변의 중력 값이 음수로 변하는 연산 오류가 발생합니다!",
        "바닥에 있어야 할 돌멩이와 꽃들이 하늘로 솟구치는데, 다행히 당신에겐 아직 영향이 없습니다.",
        "반대로 하늘을 날던 버그 몬스터들이 중력을 거슬러 당신이 있는 바닥으로 추락하기 시작합니다.",
        "하늘에서 적들이 쏟아지며 말 그대로 아수라장이 펼쳐지기 시작합니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 떨어지는 적들을 운에 맡기며 안전 구역으로 대피합니다. (판정값 12, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("2. 중력이 뒤집힌 구역을 분석해 영향이 적은 곳으로 대피합니다. (판정값 12, 지능 보정 +" + to_string(IntBonus) + ")");
}

//실패 메세지 - 중력
void LoggerSystem::LogEventFailGravity()
{
    PrintMainArea({
        "이런, 엄청난 속도로 추락한 거대 버그와 정면으로 충돌했습니다!",
        "충격으로 인해 시야가 흔들리는 가운데, 떨어진 버그가 당신에게 덤벼듭니다."
    });
}

//재활용 - 절벽
void LoggerSystem::LogEventCliff(int DexBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "지도 데이터에는 넓은 평지가 있어야 할 곳인데, 거대한 절벽이 앞을 가로막고 있습니다.",
        "알 수 없는 버그가 지형 스크립트를 출력하는 기능까지 망쳐버린 것이 분명합니다.",
        "원래는 없어야 할 지형이라 그런지 절벽 단면에 다 지워지지 않은 주석들이 둥둥 떠다닙니다.",
        "빙 돌아가면 시간 소모가 너무 클 것 같습니다. 기어오르거나 정상으로 돌려놓아야 합니다."
    });

    Gm.ClearLogs();
    Gm.AddLog("1. 절벽에 떠 있는 주석들을 발판 삼아 민첩하게 기어 올라갑니다. (판정값 12, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 지형 스크립트를 해킹해 절벽을 다시 평지로 롤백시킵니다. (판정값 15, 지능 보정 +" + to_string(IntBonus) + ")");
}

//실패 메세지 - 절벽
void LoggerSystem::LogEventFailCliff()
{
    PrintMainArea({
        "이런, 불안정한 절벽을 너무 섣불리 건드린 것 같습니다. 바닥이 사라지며 아래로 떨어집니다.",
        "수정된 코드를 지키기 위해, 충격에서 벗어나지 못한 당신에게 버그 하나가 접근합니다."
    });
}

//-----------------------------캐릭터 관련--------------------------------------
void LoggerSystem::LogLevelUp(int NewLevel) //레벨업 했을때 로그 출력하는 함수
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ SYSTEM ] 디버깅 툴 강화 완료 — 권한 레벨 " + to_string(NewLevel) + " 해금";

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

void LoggerSystem::LogPlayerDeath() //플레이어 사망시 로그 출력하는 함수
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ CONNECTION LOST ] 디버거 강제 종료. 재접속 시도 중...";

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//----------------------------------------아이템 관련----------------------------------------
//아이템 사용시 로그 출력하는 함수(아이템명과 효과)
void LoggerSystem::LogItemUse(const string& ItemName, const string& Effect)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ TOOL ACTIVATED ] " + ItemName + " 가동 — " + Effect;

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//-----------------------------------보상 관련-------------------------------------------
//경험치 획득시 로그 출력하는 함수(얻은량, 현재경험치/레벨업에 필요한 총 경험치)
void LoggerSystem::LogExpGain(int Amount, int MyExp, int MaxExp)
{
	TotalExp += Amount;
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ DATA COLLECTED ] " + to_string(Amount) + " 데이터 수집 / 현재: " + to_string(MyExp) + " / " + to_string(MaxExp);

    Gm.AddLog(Log);
    EventLogs.push_back(Log);
};

//골드 획득시 로그 출력하는 함수(얻은량, 현재 골드량)
void LoggerSystem::LogGoldGain(int Amount, int MyGold)
{
	TotalGold += Amount;
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ RESOURCE ] " + to_string(Amount) + " 골드 확보 / 누적 골드: " + to_string(MyGold);

    Gm.AddLog(Log);
    EventLogs.push_back(Log);
};

//----------------------------------------상점 관련----------------------------------------
void LoggerSystem::LogShopPrompt()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "수상한 상인이 접근한다. 거래하시겠습니까? (1: 수락 / 0: 거절)";

    Gm.AddLog(Log);
}

void LoggerSystem::LogShopEnter()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ SHOP ] 상인을 발견했다. 거래를 시작합니다.";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

void LoggerSystem::LogShopDecline()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ SHOP ] 거래를 거절했다. 상인이 자리를 떠난다.";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

void LoggerSystem::LogBuyItem(const string& ItemName, int Price)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ PURCHASE ] " + ItemName + " 획득 / " + to_string(Price) + "골드 소모";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

void LoggerSystem::LogInsufficientGold(int MyGold, int RequiredGold)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ ERROR ] 골드 부족 — 보유: " + to_string(MyGold) + "골드 / 필요: " + to_string(RequiredGold) + "골드";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

void LoggerSystem::LogSellItem(const string& ItemName, int SellPrice)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ SELL ] " + ItemName + " 판매 완료 / +" + to_string(SellPrice) + "골드";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

//"판매할 아이템 이름" 입력칸 출력 함수
void LoggerSystem::LogShopSellPrompt()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.AddLog("판매할 아이템 이름을 입력하세요 >> ");
}

void LoggerSystem::LogItemNotFound(const string& ItemName)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ ERROR ] " + ItemName + " — 인벤토리에서 찾을 수 없음";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}
//상점 메뉴 출력 함수
void LoggerSystem::LogPrintShopMenu()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.ClearLogs();
    Gm.AddLog("1. 아이템 구매");
    Gm.AddLog("2. 아이템 판매");
    Gm.AddLog("3. 상점 나가기");
    Gm.AddLog("선택 >> ");
}

//아이템 목록 출력 함수
void LoggerSystem::LogPrintShopItems(const vector<shared_ptr<ItemManager>>& Items)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.ClearLogs();
    for (int i = 0; i < (int)Items.size(); i++)
    {
        Gm.AddLog(to_string(i + 1) + ". " + Items[i]->GetName()
            + " (" + to_string(Items[i]->GetPrice()) + "G)");
    }
    Gm.AddLog("선택 >> ");
}

//-----------------------------요약----------------------------------
//처치한 몬스터와 획득한 총 골드와 경험치를 보여주는 함수
void LoggerSystem::PrintSummary()
{
    vector<string> Lines;
    Lines.push_back("======================================");
    Lines.push_back("[ DEBUG REPORT ] 디버깅 세션 종료");
    Lines.push_back("======================================");
    Lines.push_back("[ 제거된 버그 개체 ]");

    if (MonsterKillLogs.empty())
    {
        Lines.push_back("  제거된 버그 개체 없음");
    }
    else
    {
        for (auto& Entry : MonsterKillLogs)
        {
            Lines.push_back("  >> " + Entry.first + " x" + to_string(Entry.second) + " 제거 완료");
        }
    }

    Lines.push_back("[ 총 확보 골드    ] : " + to_string(TotalGold) + " G");
    Lines.push_back("[ 총 수집 데이터  ] : " + to_string(TotalExp) + " EXP");
    Lines.push_back("======================================");

    PrintMainArea(Lines);
}


//출력한 로그들을 한번에 보여주는 함수(플레이 이력)
void LoggerSystem::PrintEventLog()
{
	cout << "======================================\n";
	cout << "[ SYSTEM LOG ] 디버깅 이력 전체 출력\n";
	cout << "======================================\n";

    if (EventLogs.empty())
	{
		cout << "  기록된 이력이 없습니다.\n";
	}
	else
	{
		for (const string& Log : EventLogs)
		{
			cout << "  " << Log << "\n";
		}
	}
	cout << "======================================\n";
}
