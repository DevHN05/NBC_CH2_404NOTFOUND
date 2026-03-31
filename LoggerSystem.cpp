#include "LoggerSystem.h"
#include <iostream>
#include <thread>
#include "GraphicManager.h"
#include "EventManager.h"
#include <windows.h>
#include <conio.h>


//커서 숨기기
void LoggerSystem::hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void LoggerSystem::showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//상단 출력 헬퍼
void LoggerSystem::PrintMainArea(const vector<string>& Lines)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.DrawCombatLayOut();

    for (int i = 0; i < (int)Lines.size() && i < 15; ++i)
    {
        Gm.GoSpace(2, 2 + i);
        for (char C : Lines[i])
        {
            cout << C;
            cout.flush();
            Sleep(10);
        }
        Sleep(80);
    }
}

//----------------------------전투 관련-----------------------------------
//몬스터가 나타났을때 로그 출력하는 함수
void LoggerSystem::LogMonsterAppear(const string& MonsterName)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ DETECTION ] [ " + MonsterName + " ] 접근 확인. 디버깅 개시.";

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//공격을 했을 때 로그 출력하는 함수
void LoggerSystem::LogAttack(const string& Attacker, const string& Target, int Damage)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	string Log = "[ ATTACK ] " + Attacker + " >> " + Target + " 에 디버깅 / 데미지: " + to_string(Damage);

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//몬스터를 처치했을때 로그 출력하는 함수(해당 몬스터의 처치수를 ++함)
void LoggerSystem::LogMonsterKill(const string& MonsterName)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
	MonsterKillLogs[MonsterName]++;
	string Log = "[ DEBUG ] " + MonsterName + " 제거됨. 데이터 수집 중...";

    Gm.AddLog(Log);
	EventLogs.push_back(Log);
};

//보스 페이즈 변화 로그 출력 함수
void LoggerSystem::LogBossPhaseChange(const string& Nickname, const string& SpecialSkillName, int BoostedStrength)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log1 = "[ CRITICAL WARNING ] [ " + Nickname + " ] 코드 재작성 감지";

    //이놈이 문제
    string Log2 = "  >> 권한 레벨 상승 / " + SpecialSkillName + " 활성화";

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
    Gm.AddLog("1. 오브젝트를 근력으로 쓰러뜨려 평탄한 길을 확보합니다.");
    Gm.AddLog("   (판정값 13, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 바위 파편 위를 건너뛰며 건너편으로 갑니다.");
    Gm.AddLog("   (판정값 13, 민첩 보정 +" + to_string(DexBonus) + ")");
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
    Gm.AddLog("1. 보안 취약점 사이로 재빠르게 지나갑니다.");
    Gm.AddLog("   (판정값 13, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 방화벽의 취약점을 분석해 무력화하고 통과합니다.");
    Gm.AddLog("   (판정값 13, 지능 보정 +" + to_string(IntBonus) + ")");
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
    Gm.AddLog("1. 루프문 코드를 디버그 툴로 파괴해 물리적으로 종료합니다.");
    Gm.AddLog("   (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 조건문을 수정해 디버깅하고, 반복문을 정상으로 되돌립니다.");
    Gm.AddLog("   (판정값 10, 지식 보정 +" + to_string(IntBonus) + ")");
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
    Gm.AddLog("1. 영향받기 전에 재빠르게 다음 구역으로 질주합니다.");
    Gm.AddLog("   (판정값 13, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 자료형에 맞는 데이터가 담기길 기대하며 구역을 나아갑니다.");
    Gm.AddLog("   (판정값 13, 행운 보정 +" + to_string(LukBonus) + ")");
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
    Gm.AddLog("1. 세미콜론이 빠진 곳을 잘 피해 성큼성큼 뛰어갑니다.");
    Gm.AddLog("   (판정값 13, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 빠진 세미콜론을 넣고 계단 데이터를 복구하며 나아갑니다.");
    Gm.AddLog("   (판정값 13, 지능 보정 +" + to_string(IntBonus) + ")");
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
    Gm.AddLog("1. 버그가 막기 전에 다리를 빠르게 건너갑니다.");
    Gm.AddLog("   (판정값 14, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 버그가 나타나지 않길 바라며 다리를 건넙니다.");
    Gm.AddLog("   (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("3. 힘으로 절벽을 한 번에 뛰어넘어봅니다.");
    Gm.AddLog("   (판정값 14, 힘 보정 +" + to_string(StrBonus) + ")");
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
    Gm.AddLog("1. 버그의 흔적을 조사하고 방향을 유추해 피해갑니다.");
    Gm.AddLog("   (판정값 14, 지능 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("2. 아무 일도 없길 바라며 행운에 기대 숲을 지나갑니다.");
    Gm.AddLog("   (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
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
    Gm.AddLog("1. 구역의 구조를 파악하고 정상적인 코드를 골라 나아갑니다.");
    Gm.AddLog("   (판정값 14, 지식 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("2. 버그가 안 옮길 빌며 행운에 기대 이 지역을 나아가봅니다.");
    Gm.AddLog("   (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
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
    Gm.AddLog("1. 떨어지는 적들을 운에 맡기며 안전 구역으로 대피합니다.");
    Gm.AddLog("   (판정값 12, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("2. 중력이 뒤집힌 구역을 분석해 영향이 적은 곳으로 대피합니다.");
    Gm.AddLog("   (판정값 12, 지식 보정 +" + to_string(IntBonus) + ")");
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
    Gm.AddLog("1. 절벽에 떠 있는 주석들을 발판 삼아 민첩하게 기어 올라갑니다.");
    Gm.AddLog("   (판정값 12, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 지형 스크립트를 해킹해 절벽을 다시 평지로 롤백시킵니다.");
    Gm.AddLog("   (판정값 15, 지식 보정 +" + to_string(IntBonus) + ")");
}

//실패 메세지 - 절벽
void LoggerSystem::LogEventFailCliff()
{
    PrintMainArea({
        "이런, 불안정한 절벽을 너무 섣불리 건드린 것 같습니다.",
        "발판이 무너지며 추락하는 순간, 버그가 당신에게 달려듭니다."
    });
}

//-----------------------------보상/전투/회피 이벤트 관련----------------------------------
//처형자::가비지 컬렉션
void LoggerSystem::ChoiceGarbageCollector(int DexBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 오래된 데이터들이 쌓여 있는 캐시 메모리 저장소에 도착했습니다.",
        "이곳에는 수많은 아이템 데이터들이 버그로 인해 버려져 있고,",
        "버그가 난 가비지 컬렉션이 주기적으로 돌아다니며 필요한 데이터까지 삭제하고 있습니다.",
        "운이 좋으면 유용한 아이템 코드를 복구할 수 있겠지만,",
        "가비지 컬렉션의 눈에 띄면 당신마저 쓰레기 데이터로 분류되어 삭제될수도 있습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 가비지 컬렉션을 피해 조심스럽게 데이터를 챙겨봅니다.");
    Gm.AddLog("   (판정값 10, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 가비지 컬렉션도 코드덩어리. 정면으로 싸웁니다. (전투 발생)");
    Gm.AddLog("3. 삭제 위험을 감수할 수 없습니다. 빙 돌아 지나갑니다. (전투 회피)");
}

void LoggerSystem::ChoiceGarbageCollectorSuccess()
{
    PrintMainArea({
        "조심스럽게 데이터 파편들을 훑어보니, 꽤 쓸만한 코드 조각들이 남아 있었습니다.",
        "가비지 컬렉션의 눈을 피해 소득을 챙겼습니다. 오늘은 운이 좋군요."
    });
}

void LoggerSystem::ChoiceGarbageCollectorFail()
{
    PrintMainArea({
        "파편을 열심히 챙기던 중, 가비지 컬렉션에게 발각당합니다!",
        "즉시 제거가 시작됩니다. 몸이 흐릿해지는 걸 느끼며 맞서 싸웁니다."
    });
}

//소거자::언디클레어드
void LoggerSystem::ChoiceUndeclared(int StrBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "여정을 이어가던 당신은 이내 수많은 책이 쌓여있는 곳을 마주합니다. 이곳은 모든 책의 제목이 지워져 있었습니다.",
        "그야말로 책들의 무덤같은 풍경. 그 한가운데에 얼굴이 없는 기사가 서 있습니다.",
        "녀석은 당신이 휘두르는 칼이 무엇인지, 당신의 이름이 무엇인지조차 인식하지 못합니다.",
        "선언되지 않은 존재는 이곳에 있을 수 없다며 녀석의 칼날이 당신의 데이터 라인을 직접 조준합니다.",
        "녀석의 뒤에서 본래 이곳을 관리해야 했던 #include <stdio.h>가 비웃고 있습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 힘으로 #include <stdio.h>를 제압해 다시 제자리에 둡니다.");
    Gm.AddLog("   (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 헤더를 고치기엔 오래 걸립니다. 저 버그를 제압하는 수 밖에요. (전투 발생)");
    Gm.AddLog("3. 이 지역을 지금 구할 필요가 있을까요? 빙 돌아 지나갑니다. (전투 회피)");
}

void LoggerSystem::ChoiceUndeclaredSuccess()
{
    PrintMainArea({
        "#include <stdio.h>를 제자리로 돌려놓자, 책들의 제목이 하나둘 복구되기 시작합니다.",
        "얼굴 없는 기사도 인식 오류가 해소되며 그 자리에서 소멸합니다. 이 지역이 안정을 되찾았습니다."
    });
}

void LoggerSystem::ChoiceUndeclaredFail()
{
    PrintMainArea({
        "'Player': undeclared identifier 에러 발생! 시스템이 당신을 인식할 수 없습니다.",
        "즉시 제거가 시작됩니다. 몸이 흐릿해지는 걸 느끼며 맞서 싸웁니다."
    });
}

//투영자::댕글링 포인터
void LoggerSystem::ChoiceDanglingPointer(int StrBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신이 파괴한 버그는 데이터로 분해되어 사라졌지만,",
        "그 자리에 여전히 적의 '공격 판정'이 유령처럼 남아 주변 데이터를 오염시키고 있습니다.",
        "아무래도 유효하지 않은 주소를 참조하고 있는 잔상인 것 같습니다.",
        "시스템이 리소스를 완전히 회수하지 못해 발생한 댕글링 포인터 현상이 벌어지고 있군요.",
        "이 유령 데이터를 정리하지 않고는 지나갈 순 없겠습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 직접 댕글링 포인터에 nullptr를 대입해 원상 복구를 시도합니다.");
    Gm.AddLog("   (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 실체가 없어도 디버깅하면 그만이죠. 정면으로 싸웁니다. (전투 발생)");
    Gm.AddLog("3. 시스템 크래시는 무섭습니다. 빙 돌아서 지나갑니다. (전투 회피)");
}

void LoggerSystem::ChoiceDanglingPointerSuccess()
{
    PrintMainArea({
        "데이터 잔상이 소멸하며 안전한 경로가 확보됩니다.",
        "근처에 휘말려있던 보물 상자도 정상화되어, 수익을 기대할 수 있겠습니다."
    });
}

void LoggerSystem::ChoiceDanglingPointerFail()
{
    PrintMainArea({
        "NullPtr을 잘못 넣었고, 녀석은 여전히 존재하지 않는 주소를 읽으려 시도했습니다.",
        "시스템 크래시와 함께 유령 데이터가 실체화되어 당신을 덮칩니다."
    });
}

//재활용? - 브로큰 액터
void LoggerSystem::ChoiceBrokenActor(int LukBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 계속해서 여정을 나아가던 중, 버그가 발생해 데이터가 완전히 깨져버린 액터를 발견합니다.",
        "액터는 텍스쳐가 완전히 깨져서 원형을 알아볼 수 없게 되어 있습니다. 버그에게 습격당한 모양인데요.",
        "아직 근처에 습격한 버그가 남아있을지도 모르지만, 위험을 감수할 가치가 있어보입니다.",
        "범인이 버그라면 아직 버그가 걸리지 않은 액터의 부산물을 주울 수 있을지도 모릅니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 난 운이 좋으니 버그가 떠났을거야. 액터를 살펴봅니다.");
    Gm.AddLog("   (판정값 10, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("2. 망가진 액터에서 쓸만한 아이템 코드가 있는지 살펴봅니다.");
    Gm.AddLog("   (판정값 10, 지식 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("3. 위험을 감수할 순 없죠. 그냥 지나칩니다. (이벤트 종료)");
}

void LoggerSystem::ChoiceBrokenActorSuccess()
{
    PrintMainArea({
        "이 액터는 원래 전리품 상자였던 모양입니다. 귀중한 물품이 제법 많이 들어있군요.",
        "하지만 버그의 습격으로 상당수가 훼손됐습니다. 살아남은 것만 대충 챙겨야겠군요."
    });
}

void LoggerSystem::ChoiceBrokenActorFail()
{
    PrintMainArea({
        "이런, 놈은 아직 멀리 가지 않았던 모양입니다.",
        "아무래도 망가진 액터처럼 당신도 망가뜨리려는 모양인데요... 싸움을 피할 순 없겠습니다."
    });
}

//재활용? - 미초기화 배열
void LoggerSystem::ChoiceUninitArray(int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "저 멀리서 Array[6]이라고 적힌 거대한 아파트가 걸어옵니다.",
        "저 배열은 건설될 때 초기화 과정을 거치지 않았습니다.",
        "덕분에 이전에 이곳을 거쳐 간 수많은 망령 데이터들이 남긴 쓰레기 값들이 아파트의 방에 들어차있습니다.",
        "녀석은 각 Index에 버그를 가득 채우고 당신을 덮치려 합니다.",
        "왠지 잘 찾아보면 하나쯤은 NULL 값이 있는 방이 있을수도 있을 것 같습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. NULL이나 0이 저장된 빈방 번호를 찾아봅니다.");
    Gm.AddLog("   (판정값 10, 지식 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("2. 고작 배열에게 막힐 순 없습니다. 정면으로 싸웁니다. (전투 발생)");
    Gm.AddLog("3. 쓰레기값은 예측 불가. 빙 돌아서 지나갑니다. (전투 회피)");
}

void LoggerSystem::ChoiceUninitArraySuccess()
{
    PrintMainArea({
        "빈방을 찾아냈습니다. 배열 안으로 조용히 들어가 이동 수단으로 활용하는데 성공했습니다.",
        "쓰레기값들이 눈치채기 전에 빠르게 다음 구역으로 이동했습니다."
    });
}

void LoggerSystem::ChoiceUninitArrayFail()
{
    PrintMainArea({
        "이런, 하필 당신이 연 방은 쓰레기값이 가득 찬 방이었습니다!",
        "방 전체를 장악한 쓰레기값이 당신의 침입을 감지해 전투를 걸어옵니다."
    });
}

//-----------------------------보상 이벤트 관련----------------------------------
//평범한 보물상자
void LoggerSystem::ChestNormal(int StrBonus, int DexBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "길을 나아가던 당신은, 길 한복판에 단단히 잠겨있는 상자를 발견합니다.",
        "아무래도 버그가 발생해서 엉뚱한 곳에서 스폰된 객체인 것 같습니다.",
        "이렇게 단단히 잠가놓다니, 분명 좋은 보상이 있을게 분명하지만...",
        "불행인 점은, 열쇠가 없으며 당신은 이 상자의 주인이 아니라는 겁니다.",
        "다행인 점은, 지금 당신을 지켜보는 사람은 없다는 거구요."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 힘으로 상자를 부숴서 내용물을 확인합니다.");
    Gm.AddLog("   (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 락픽으로 자물쇠를 따봅니다.");
    Gm.AddLog("   (판정값 10, 민첩 보정 +" + to_string(DexBonus) + ")");
}

void LoggerSystem::ChestNormalSuccess()
{
    PrintMainArea({
        "상자 안에는 꽤 많은 양의 금화가 들어 있었습니다.",
        "당신은 신이 나서 안에 있는 금화를 모두 챙깁니다."
    });
}

void LoggerSystem::ChestNormalFail()
{
    PrintMainArea({
        "이런, 상자가 파손되며 내용물도 파손되고 말았습니다..."
    });
}

//const로 고정된 보물상자
void LoggerSystem::ChestConstLock(int StrBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "길가에 빛나는 파란 보호막에 싸인 상자가 놓여 있습니다. 이 상자는 const 키워드가 선언되어 있어,",
        "외부의 어떤 영향에도 내부 데이터(보상)가 변하지 않도록 고정되어 있는 구조인 것 같았습니다.",
        "하지만 버그로 const 키워드가 상자의 잠금 장치로 넘어가, 열린 상태로 변하지 않는 상자가 됐군요.",
        "변하지 않게 된 이 잠금장치를 뚫어야만 내용물을 얻을 수 있을 것 같습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 잠금 장치를 부술 수 없다면, 힘으로 상자를 부숩니다.");
    Gm.AddLog("   (판정값 14, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 디버깅으로 const의 위치를 알맞은 곳으로 되돌립니다.");
    Gm.AddLog("   (판정값 14, 지식 보정 +" + to_string(IntBonus) + ")");
}

void LoggerSystem::ChestConstLockSuccess()
{
    PrintMainArea({
        "상자 안에는 꽤 많은 양의 금화가 들어 있었습니다.",
        "당신은 신이 나서 안에 있는 금화를 모두 챙깁니다."
    });
}

void LoggerSystem::ChestConstLockFail()
{
    PrintMainArea({
        "이런, const는 강력하군요...",
        "당신은 상자를 여느라 시간만 허비했단 사실에 좌절합니다."
    });
}

//&&를 맞추기 위해 동시에 열기
void LoggerSystem::ChestAndLogic(int DexBonus, int LukBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "길을 나아가던 당신은, 바위 위에 단단히 잠겨있는 황금상자를 발견합니다.",
        "그리고 황금 상자 앞에는 열쇠가 2개나 있습니다. 상자에는 두 개의 열쇠 구멍이 나란히 뚫려 있고",
        "그 가운데에 && 기호가 새겨져 있습니다. 이 녀석도 버그로 인해 열쇠구멍이 늘어난 것 같은데요.",
        "아무래도 두 열쇠를 동시에 맞춰야만 상자 값이 true로 변해 열릴 것 같군요.",
        "하지만 당신은 혼자이기에, 혼자서 타이밍을 맞추기란 쉽지 않습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 재빠르게 열쇠 두 개를 동시에 집어넣어 봅니다.");
    Gm.AddLog("   (판정값 14, 민첩 보정 +" + to_string(DexBonus) + ")");
    Gm.AddLog("2. 우연히 맞길 바라며 열쇠 두 개를 감으로 맞춰봅니다.");
    Gm.AddLog("   (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("3. 첫 구멍이 참인 것처럼 회로를 속이고 열쇠를 넣습니다.");
    Gm.AddLog("   (판정값 14, 지식 보정 +" + to_string(IntBonus) + ")");
}

void LoggerSystem::ChestAndLogicSuccess()
{
    PrintMainArea({
        "철컥! 두 논리가 맞물리며 상자가 열립니다.",
        "당신은 신이 나서 안에 있는 금화를 모두 챙깁니다."
    });
}

void LoggerSystem::ChestAndLogicFail()
{
    PrintMainArea({
        "이런, 타이밍이 맞지 않았던걸까요... 논리가 부정당해 상자가 열리지 않습니다.",
        "당신은 상자를 여느라 시간만 허비했단 사실에 좌절합니다."
    });
}

//*ptr 보물찾기
void LoggerSystem::ChestPointerSearch(int IntBonus, int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 *ptr이라고 적힌 이정표를 발견합니다.",
        "이 이정표는 진짜 보물이 숨겨진 메모리 주소를 가리키고 있는 보물지도인 모양입니다.",
        "하지만, 버그때문인지 *ptr이라고만 적혀있어서 이게 int인지 char인지도 알 수 없습니다.",
        "어느 자료형이라고 가정하고 길을 따라가야 보물을 찾을 수 있을까요?",
        "잘못 찾아가면 허탕을 칠 것 같습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 데이터 흐름을 분석해 *ptr의 자료형(Type)을 알아냅니다.");
    Gm.AddLog("   (판정값 14, 지식 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("2. 자료형이 맞길 바라며 *ptr을 따라갑니다.");
    Gm.AddLog("   (판정값 14, 행운 보정 +" + to_string(LukBonus) + ")");
}

void LoggerSystem::ChestPointerSearchSuccess()
{
    PrintMainArea({
        "당신이 생각한 자료형이 맞았습니다! 바닥을 파니 상자가 나옵니다.",
        "당신은 신이 나서 상자 속 금화를 모두 챙깁니다."
    });
}

void LoggerSystem::ChestPointerSearchFail()
{
    PrintMainArea({
        "이런, 자료형이 맞지 않았던걸까요... 바닥을 파도 아무것도 나오지 않습니다.",
        "당신은 상자를 여느라 시간만 허비했단 사실에 좌절합니다."
    });
}

//버그 액터 고치기
void LoggerSystem::ChestBugActorFix(int StrBonus, int IntBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 원형을 잃어버린 버그 액터를 발견합니다.",
        "이 액터는 말 그대로 알 수 없는 버그가 뒤엉켜 제 구실을 하지 못하고 있는데요.",
        "당신의 손에 들린 특수 디버깅 툴이 빛을 냅니다.",
        "어쩌면, 당신이 이 액터에게 원래 모습을 찾아줄 수 있을지도 모릅니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 디버깅 툴로 물리적으로 버그의 원흉을 제거합니다.");
    Gm.AddLog("   (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("2. 디버깅 툴로 오류가 발생한 코드를 찾아 수정합니다.");
    Gm.AddLog("   (판정값 10, 지식 보정 +" + to_string(IntBonus) + ")");
}

void LoggerSystem::ChestBugActorFixSuccess()
{
    PrintMainArea({
        "성공적으로 액터의 버그가 제거됩니다. 액터는 마을주민 NPC였습니다.",
        "NPC가 감사의 표시로 당신에게 골드를 지급합니다."
    });
}

void LoggerSystem::ChestBugActorFixFail()
{
    PrintMainArea({
        "이런, 오류의 원인을 잘못 짚은 모양입니다. 아예 충돌해서 소멸합니다..."
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

//-----------------------------상점 이벤트----------------------------------
//두 갈래 길
void LoggerSystem::ShopChoiceEvent(int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "길을 나아가던 당신은 두 갈래로 나뉘는 길을 마주칩니다.",
        "어디... 가운데에 나무 팻말이 하나 있군요.",
        "왼쪽 팻말에는 [주의! 몬스터 출몰 지역], 오른쪽 팻말에는",
        "[길 잃은 모험가를 위한 잡화상점] 이라고 적혀있군요.",
        "뭔가 상술같긴 하지만, 오른쪽으로 가면 상점이 있긴 할 것 같습니다.",
        "잠시, 상점에 들릴 필요가 있을까요?"
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 왼쪽 길로 갑니다. (모험 속행, 다음 이벤트 전투 고정)");
    Gm.AddLog("2. 불길하지만 일단 오른쪽 길로 가봅니다.");
    Gm.AddLog("   (판정값 10, 행운 보정 +" + to_string(LukBonus) + ")");
}

void LoggerSystem::ShopChoiceEventSuccess()
{
    PrintMainArea({
        "당신은 별다른 일 없이 상점에 도착하는데 성공합니다. 팻말은 진짜였군요."
    });
}

void LoggerSystem::ShopChoiceEventFail()
{
    PrintMainArea({
        "오른쪽은 당신을 유도하기 위한 함정이었습니다. 버그가 당신을 공격합니다!"
    });
}

//주민 마을 표지판
void LoggerSystem::ShopVillageWay(int StrBonus, int DexBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "여정을 떠나던 당신은 제법 말끔한 표지판을 발견합니다. [동쪽, 주민 마을 있다.]",
        "텍스트는 이상하지만, 버그의 영향을 아직 덜 받은 표지판 같습니다.",
        "마을에는 상점도 있겠죠. 하지만 동쪽 길은 커다란 바위로 막혀있군요.",
        "아무래도 오류로 이곳에 엉뚱한 오브젝트가 생긴 것 같은데요.",
        "마을로 가려면 이 바위를 치워야만 할 것 같습니다."
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 다른 길로 갑니다. 상점은 다른 곳에도 있겠죠. (모험 속행)");
    Gm.AddLog("2. 상점도 가야하고, 바위를 치워봅니다.");
    Gm.AddLog("   (판정값 10, 힘 보정 +" + to_string(StrBonus) + ")");
    Gm.AddLog("3. 민첩하게 바위를 뛰어넘어 상점으로 갑니다.");
    Gm.AddLog("   (판정값 10, 민첩 보정 +" + to_string(DexBonus) + ")");
}

void LoggerSystem::ShopVillageWaySuccess()
{
    PrintMainArea({
        "당신은 별다른 일 없이 상점에 도착하는데 성공합니다. 팻말은 진짜였군요."
    });
}

void LoggerSystem::ShopVillageWayFail()
{
    PrintMainArea({
        "오른쪽은 당신을 유도하기 위한 함정이었습니다. 버그가 당신을 공격합니다!"
    });
}

//도박꾼 보부상
void LoggerSystem::ShopGamblerBet(int LukBonus, int DexBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 여정을 하던 중 보부상을 만납니다.",
        "보부상이 킬킬 웃으며 당신에게 주사위를 들이밉니다.",
        "자신은 도박을 좋아하는 도박꾼이며, 취미로 보부상을 하고 있다는군요.",
        "자신과의 간단한 주사위 도박에서 성공하면 물건을 팔아주겠다고 합니다.",
        "어이가 없군요. 하지만 다른 상점도 없습니다. 어울려줘야 할까요?"
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 뭔 도박이야? 그냥 가던 길을 계속 간다. (모험 속행)");
    Gm.AddLog("2. 까짓거 한 번 굴려보지 뭐. 주사위를 굴린다.");
    Gm.AddLog("   (판정값 10, 행운 보정 +" + to_string(LukBonus) + ")");
    Gm.AddLog("3. 손기술로 도박꾼 몰래 결과값을 조작한다.");
    Gm.AddLog("   (판정값 10, 민첩 보정 +" + to_string(DexBonus) + ")");
}

void LoggerSystem::ShopGamblerBetSuccess()
{
    PrintMainArea({
        "주사위 값으로 6이 나오며, 5를 굴린 보부상을 이깁니다.",
        "보부상이 킥킥 웃으며 보따리를 풀기 시작합니다."
    });
}

void LoggerSystem::ShopGamblerBetFail()
{
    PrintMainArea({
        "이런, 주사위가 1이 나옵니다. 보부상이 기분 나쁘게 웃습니다.",
        "아무래도 여기서 뭘 사긴 글러먹은 것 같습니다..."
    });
}

//버그 상점
void LoggerSystem::ShopBugStoreFix(int IntBonus, int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "당신은 버그로 뒤덮여버린 상점을 발견합니다. 뭔가 문제가 있는 것 같은데...",
        "당장 상점 이용이 필요하다면, 이 상점에 걸린 버그를 고쳐서 이용할 수 있을 것 같습니다.",
        "하지만 아무리 디버깅 툴이 있더라도 어디에 버그가 생겼는지 알아야,",
        "상점에 있는 버그를 고칠 수 있는 법이죠.",
        "여정이 바쁘긴 하지만... 잠시 버그를 고쳐볼까요?"
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 귀찮게 왜? 그냥 지나갑니다. (모험 속행)");
    Gm.AddLog("2. 디버깅 툴로 상점의 버그를 고쳐봅니다.");
    Gm.AddLog("   (판정값 10, 지식 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("3. 운 좋게 지워질 수도 있지 않나요? 마구 휘두릅니다!");
    Gm.AddLog("   (판정값 10, 행운 보정 " + to_string(LukBonus) + ")");
}

void LoggerSystem::ShopBugStoreFixSuccess()
{
    PrintMainArea({
        "디버깅에 성공했습니다! 상점이 원래의 모습을 되찾습니다. 이제 이용할 수 있겠군요."
    });
}

void LoggerSystem::ShopBugStoreFixFail()
{
    PrintMainArea({
        "디버깅에 실패했습니다! 오히려 버그가 급증했습니다. 버그가 당신에게 달려듭니다."
    });
}

//Access Denied 상점
void LoggerSystem::ShopAccessDenied(int IntBonus, int LukBonus)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    PrintMainArea({
        "문이 잠긴 상점 앞에, 상점 주인이 난감하다는 듯 서있습니다.",
        "상점 입구를 보니, Access Denied라는 붉은 글씨가 적혀 있네요.",
        "상점 주인이 자신의 가게에 접근을 거부당하는 그야말로 버그같은 상황입니다.",
        "상점 문을 보니, 복잡한 수식과 함께 if 조건문이 걸려있습니다.",
        "아무래도 버그가 명확한 것 같은데, 이 상인을 도와줄 수 있을까요?"
    });
    Gm.ClearLogs();
    Gm.AddLog("1. 그냥 다른 상점 이용하지 뭐. (모험 속행)");
    Gm.AddLog("2. 조건문을 추론해 상점 주인의 권한을 찾아줍니다.");
    Gm.AddLog("   (판정값 10, 지식 보정 +" + to_string(IntBonus) + ")");
    Gm.AddLog("3. if문에 숫자를 대입해 운으로 문을 열어봅니다.");
    Gm.AddLog("   (판정값 10, 행운 보정 +" + to_string(LukBonus) + ")");
}

void LoggerSystem::ShopAccessDeniedSuccess()
{
    PrintMainArea({
        "성공적으로 문이 열리며 상점 주인이 제 자리를 되찾습니다. 이제 이용할 수 있겠군요."
    });
}

void LoggerSystem::ShopAccessDeniedFail()
{
    PrintMainArea({
        "디버깅 코드를 대입해보자... 문에서 버그가 튀어나옵니다! 버그가 당신을 노립니다..."
    });
}


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
	string Log = "[ RESOURCE ] " + to_string(Amount) + "G 확보 / 현재 골드: " + to_string(MyGold) + "G";

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
    string Log = "[ PURCHASE ] " + ItemName + " 획득 / " + to_string(Price) + "G 소모";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

void LoggerSystem::LogInsufficientGold(int MyGold, int RequiredGold)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ ERROR ] 골드 부족 — 보유: " + to_string(MyGold) + "G / 필요: " + to_string(RequiredGold) + "G";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}

void LoggerSystem::LogSellItem(const string& ItemName, int SellPrice)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ SELL ] " + ItemName + " 판매 완료 / +" + to_string(SellPrice) + "G";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
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
    Gm.DrawLayout();
    //Gm.ClearLogs();

    Gm.GoSpace(32, 7); cout << " [ SHOP MENU ] ";

    int LogStartX = 32;

    Gm.GoSpace(LogStartX, 10);
    cout << "1. 구매하기";
    Gm.GoSpace(LogStartX, 12);
    cout << "2. 판매하기";
    Gm.GoSpace(LogStartX, 14);
    cout << "3. 떠나기";

    Gm.DrawAsciiArt("SHOPKEEPER" , 93, 6);

}

//아이템 목록 출력 함수
void LoggerSystem::LogPrintShopItems(const vector<BaseItem*>& CurrentDisplayItems)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.DrawLayout();
    Gm.GoSpace(32, 7); cout << " [ SYSTEM MERCHANT ] ";

    int LogStartX = 32;

    for (int i =0; i < CurrentDisplayItems.size(); ++i)
    {
        Gm.GoSpace(LogStartX, 10 + 2 * i);
        cout << to_string(i+1) + ". [" + CurrentDisplayItems[i]->GetPotionTypeStr() + "] " +
            CurrentDisplayItems[i]->GetName() + " : " + to_string(CurrentDisplayItems[i]->GetPrice()) + "G";
    }

    Gm.GoSpace(LogStartX, 20); cout << "0. EXIT TERMINAL";
    Gm.DrawAsciiArt("SHOPKEEPER" , 93, 6);

}
//----------------------------------------튜토리얼 관련----------------------------------------
//배경 스토리 출력
void LoggerSystem::ShowStory()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    system("cls");

    vector<string> StoryLines = {
        "",
        "[SYSTEM WARNING: CRITICAL ERROR DETECTED]",
        "「404 NOT FOUND 」",
        "",
        "전 세계가 열광하던 VR RPG 'NBC'",
        "",
        "하지만 대규모 업데이트 직후, 원인 불명의 치명적인 버그가 발생하며,",
        "",
        "수만 명의 플레이어가 가상 세계에 갇혀버렸다.",
        "",
        "GM조차 제어할 수 없는 이 버그들은 시스템 권한을 찬탈해 버그 군단을 만들었고,",
        "",
        "이 버그들은 어째서인지 코드 수정 권한까지 빼앗아 버렸지만,",
        "",
        "어째서인지 게임 전체를 망가뜨리진 않았다.",
        "",
        "무슨 목적이라도 있는 걸까? 아니, 사소한 생각은 그만두자.",
        "",
        "디버깅을 하기 위해선, 게임의 룰을 따르면서 버그를 제거해야 한다.",
        "",
        "",
        "이에 개발팀은 최후의 수단으로 '특수 디버깅 툴'을 장착한 요원을 투입하기로 결정했다.",
        "",
        "그게 바로 나--",
        "",
        "",
        "게임의 물리 법칙과 스킬 시스템은 그대로 유지되기 때문에,",
        "",
        "우리는 게임의 규칙을 따라서 디버깅 툴을 무기 삼아야 한다.",
        "",
        "디버깅 툴로 적을 타격해서 코드에 접근해, 디버깅을 진행해야만 한다.",
        "",
        "하지만, 적들은 룰을 무시하는 버그 덩어리들.",
        "",
        "그들을 하나하나 제거하며, 데이터를 수집하고 레벨을 올리며 전진해서,",
        "",
        "이 지옥 같은 게임을 클리어하고, 갇힌 사람들을 현실로 귀환시켜야만 한다!",
        "",
        "",
        "",
    };
    const int ScreenHeight = 40;
    const int StartX = 25;
    int TotalLines = (int)StoryLines.size();

    hideCursor(); //입력 커서 숨기기

    for (int scroll = 0; scroll < ScreenHeight + TotalLines; scroll++)
    {
        for (int row = 0; row < ScreenHeight; row++)
        {
            int lineIdx = row - (ScreenHeight - 1) + scroll;

            Gm.GoSpace(0, row);
            cout << string(109, ' ');

            if (lineIdx >= 0 && lineIdx < TotalLines)
            {
                Gm.GoSpace(StartX, row);
                cout << StoryLines[lineIdx];
            }
        }
        Sleep(250);
    }

    showCursor(); //입력 커서 보이기
}
//튜토리얼 출력 헬퍼
static void TypeText(GraphicManager& Gm, const string& text, int x, int y)
{
    Gm.GoSpace(x, y);
    for (int i = 0; i < (int)text.size(); i++)
    {
        cout << text[i];
        cout.flush();
        Sleep(15);
    }
}
//텍스트 점멸 효과
static void BlinkText(GraphicManager& Gm, HANDLE hConsole, const string& text, int x, int y)
{
    for (int i = 0; i < 3; i++)
    {
        SetConsoleTextAttribute(hConsole, 0x1F);
        Gm.GoSpace(x, y);
        cout << text;
        Sleep(180);

        SetConsoleTextAttribute(hConsole, 0x00);
        Gm.GoSpace(x, y);
        cout << text;
        Sleep(180);
    }
    SetConsoleTextAttribute(hConsole, 0x1F);
    Gm.GoSpace(x, y);
    cout << text;
}

void LoggerSystem::Tutorial1()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.DrawLayout();

    TypeText(Gm, "접속 권한 확인 완료. 특수 디버깅 툴을 처음 사용하는 요원으로 확인됩니다.", 3, 2);
    TypeText(Gm, "특수 디버깅 툴을 사용하는 요원을 위한 교육 문구가 출력됩니다.", 3, 3);
    TypeText(Gm, "출력중인 교육은 S 키로 스킵할 수 있습니다.", 3, 5);
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... (스킵: S) ]");
}

void LoggerSystem::Tutorial2()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.ClearLogs();
    Gm.DrawLayout();

    TypeText(Gm, "특수 디버깅 툴은 게임 세계에서 직접 원하는 객체에 접촉하여 코드를 수정할 수 있는 능동적인 툴입니다.", 3, 2);
    TypeText(Gm, "그렇기에, 요원은 필연적으로 게임의 룰을 따르면서 디버깅해야 합니다. 게임의 룰을 설명드리겠습니다.", 3, 3);
    Gm.ClearLogs();
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... (스킵: S) ]");
}

void LoggerSystem::Tutorial3()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.ClearLogs();
    Gm.DrawLayout();

    TypeText(Gm, "이 세계의 모든 행동은 20면체 주사위가 결정합니다.", 3, 2);
    TypeText(Gm, "당신이 행동을 할 때마다, 시스템에서는 당신의 행동을 평가하는 주사위를 굴립니다.", 3, 3);
    TypeText(Gm, "주사위를 굴려서 얻은 결과값에,", 3, 5); // 한 줄로 쓰면 넘침
    TypeText(Gm, "당신의 능력 보정치를 더한 최종 숫자가 제시된 목표값보다 높아야 성공합니다.", 3, 6);
    TypeText(Gm, "주사위를 굴릴 땐, 스탯 5포인트당 +1의 보정치가 붙습니다.", 3, 8);
    TypeText(Gm, "STR이 15라면? 힘 주사위 값에 +3이 추가되는 식입니다.", 3, 9);
    Gm.ClearLogs();
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... (스킵: S) ]");
}

void LoggerSystem::Tutorial4()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.ClearLogs();
    Gm.DrawLayout();

    TypeText(Gm, "선택지를 고르기 전, 특수 디버깅 툴은 이러한 보정값을 가시적으로 보여줍니다.", 3, 2);
    TypeText(Gm, "1. 튜토리얼을 이해해봅니다. (판정값 10, 지식 보정 +2)", 3, 4);
    TypeText(Gm, "2. 몸이 나쁘면 머리가 고생하는 거죠. 몸으로 부딪힙니다. (판정값 10, 힘 보정 +2)", 3, 5);
    TypeText(Gm, "전자의 경우 지식이 높은 사람이, 후자의 경우 힘이 높은 사람이 유리하겠죠.", 3, 7);
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... (스킵: S) ]");
}

void LoggerSystem::Tutorial5()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    Gm.ClearLogs();
    Gm.DrawLayout();

    TypeText(Gm, "하지만, 스탯이 낮더라도 주사위 값만 높으면 성공할 수 있습니다.", 3, 2);
    TypeText(Gm, "20면체 주사위는 최대 20까지 나오니까요.", 3, 3);
    TypeText(Gm, "이 경우 스탯이 높아진다면 1이 나오더라도,", 3, 5);
    TypeText(Gm, "힘이 50을 넘기면 11이 되어 10 선택지를 무조건 성공할 수 있겠죠.", 3, 6);
    TypeText(Gm, "그 상황에서도 유저의 짜릿함을 위해, 실패율을 최소 5%로 만드는 시스템이 존재합니다.", 3, 7);
    TypeText(Gm, "바로, 대실패와 대성공 시스템입니다.", 3, 8);
    TypeText(Gm, "대실패: 주사위 눈이 1이 나오면 보정치와 상관없이 무조건 실패합니다.", 3, 10);
    TypeText(Gm, "대성공: 주사위 눈이 20이 나오면 무조건 성공합니다.", 3, 11);
    Gm.PerformAddLog("[ 계속하려면 Enter 키를 누르세요... (스킵: S) ]");
}

void LoggerSystem::Tutorial6()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Gm.ClearLogs();
    Gm.DrawLayout();
    SetConsoleTextAttribute(hConsole, 0x0F);

    TypeText(Gm, "튜토리얼이 끝났습니다. 게임에 접속합니다.", 3, 2);

    SetConsoleTextAttribute(hConsole, 0x1F); // 파란 배경 + 흰 글자

    TypeText(Gm, "[ 캐릭터 생성창으로 이동합니다... ", 3, 4);
    BlinkText(Gm, hConsole, " 실패. 접근 권한 없음. ]", 35, 4);   // X=3 + 표시너비(32) = 35

    TypeText(Gm, "[ 재시도... ", 3, 5);
    BlinkText(Gm, hConsole, " 실패. ]", 13, 5);                 // X=3 + 표시너비(10)  = 13

    TypeText(Gm, "[ 캐릭터 생성 절차에 접근할 수 없습니다.] ERROR CODE:「404 NOT FOUND 」", 3, 6);
    TypeText(Gm, "[ 비상 상황에 대비해 랜덤 구성 프로토콜이 시작됩니다. ]", 3, 7);

    TypeText(Gm, "잔여 시간 : 3", 3, 9);
    Sleep(1000);
    TypeText(Gm, "잔여 시간 : 2", 3, 9);
    Sleep(1000);
    TypeText(Gm, "잔여 시간 : 1", 3, 9);
    Sleep(1000);

    SetConsoleTextAttribute(hConsole, 0x0F);
    system("cls");
    Sleep(500);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int width = csbi.dwSize.X;

    auto DrawHackScreen = [&]() { //해킹화면 임시 구현한 람다 함수
        const string chars = "01#@$%&*ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (int y = 0; y < Gm.GetCurrentHeight(); ++y) {
            COORD pos = {0, static_cast<SHORT>(y)};
            SetConsoleCursorPosition(hConsole, pos);

            int len = rand() % width + 1;

            for (int x = 0; x < len; ++x) {
                cout << chars[rand() % chars.size()];
            }
        }
    };

    SetConsoleTextAttribute(hConsole, 0x1F);
    system("cls");

    int DrawHackScreenCnt = 15;
    while (DrawHackScreenCnt)
    {
        DrawHackScreen();
        Sleep(100);
        --DrawHackScreenCnt;
    }

    SetConsoleTextAttribute(hConsole, 0x1F);
    system("cls");
    Sleep(700);

}

void LoggerSystem::TutorialStatDice()
{
    hideCursor();
    GraphicManager& Gm = GraphicManager::GetInstance();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Gm.ClearLogs();

    SetConsoleTextAttribute(hConsole, 0x1F);
    Gm.DrawLayout();
    Sleep(1000);
    BlinkText(Gm, hConsole, "[ 비상 상황 ]", 3, 2);
    BlinkText(Gm, hConsole, ">> 긴급 랜덤 구성 프로토콜 가동", 3, 3);
    TypeText(Gm, "20면체 주사위로 당신을 긴급 구성합니다.", 3, 5);
    TypeText(Gm, "지금부터 Enter 키를 누를 때마다 스탯이 무작위로 정해집니다.", 3, 6);

    showCursor();
}

bool LoggerSystem::WaitEnterOrSkip()
{
    cin.clear();
    cin.sync();
    while (_kbhit()) _getch();

    while (true) {
        if (_kbhit()) {
            int key = _getch();

            if (key == 13 || key == 10) { // Enter
                return true; // 정상 진행
            }
            else if (std::tolower(key) == 's') { // s 스킵
                return false; // 튜토리얼 종료
            }
        }
    }
}

void LoggerSystem::RunTutorial()
{
    hideCursor();

    Tutorial1();
    if (!WaitEnterOrSkip()) goto SkipTo6;

    Tutorial2();
    if (!WaitEnterOrSkip()) goto SkipTo6;

    Tutorial3();
    if (!WaitEnterOrSkip()) goto SkipTo6;

    Tutorial4();
    if (!WaitEnterOrSkip()) goto SkipTo6;

    Tutorial5();
    if (!WaitEnterOrSkip()) goto SkipTo6;

    Tutorial6();
    showCursor();
    return;

    SkipTo6:
    Tutorial6();
    showCursor();
}

//-----------------------------요약----------------------------------
//처치한 몬스터와 획득한 총 골드와 경험치를 보여주는 함수
void LoggerSystem::PrintSummary()
{
   GraphicManager& Gm = GraphicManager::GetInstance();

    vector<string> MonsterLines;
    if (MonsterKillLogs.empty())
    {
        MonsterLines.push_back("  제거된 버그 개체 없음");
    }
    else
    {
        for (auto& Entry : MonsterKillLogs)
        {
            MonsterLines.push_back("  >> " + Entry.first + " x" + to_string(Entry.second) + " 제거 완료");
        }
    }
    //시작 지점, 페이지 수 계산
    int MainBottom  = Gm.GetMainBottom();
    int StartY = MainBottom - 4;
    int MonsterPerPage = StartY - 6;
    int TotalMonsters   = (int)MonsterLines.size();
    int TotalPages    = (TotalMonsters + MonsterPerPage - 1) / MonsterPerPage;
    int CurrentPage = 0;

    while (true)
    {
        Gm.DrawLayout();

        //고정값
        Gm.GoSpace(2, 2); cout << "======================================";
        Gm.GoSpace(2, 3); cout << "[ DEBUG REPORT ] 디버깅 세션 종료";
        Gm.GoSpace(2, 4); cout << "======================================";
        Gm.GoSpace(2, 5); cout << "[ 제거된 버그 개체 ]";

        //몬스터 목록 출력
        int start = CurrentPage * MonsterPerPage;
        int end   = min(start + MonsterPerPage, TotalMonsters);

        for (int i = start; i < end; i++)
        {
            Gm.GoSpace(2, 6 + (i - start));
            cout << MonsterLines[i];
        }
        //고정값
        Gm.GoSpace(2, StartY);     cout << "[ 총 확보 골드 ] : " + to_string(TotalGold) + " G";
        Gm.GoSpace(2, StartY + 1); cout << "[ 총 수집 데이터  ] : " + to_string(TotalExp) + " EXP";

        Gm.ClearLogs();

        //페이지 넘기기(Enter)
        if (TotalPages > 1)
            Gm.AddLog("[ " + to_string(CurrentPage + 1) + " / " + to_string(TotalPages) + " 페이지 ]");

        if (CurrentPage < TotalPages - 1)
            Gm.AddLog("[ Enter: 다음 페이지 ]");
        else
            Gm.AddLog("[ Enter: 종료 ]");

        EventManager::WaitEnter();

        if (CurrentPage < TotalPages - 1)
            CurrentPage++;
        else
            break;
    }
}


//출력한 로그들을 한번에 보여주는 함수(플레이 이력)
void LoggerSystem::PrintEventLog()
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.DrawLayout();

    Gm.GoSpace(3, 1);
    cout << "[ SYSTEM LOG ] 디버깅 이력 전체 출력";

    if (EventLogs.empty())
    {
        Gm.GoSpace(3, 3);
        cout << "기록된 이력이 없습니다.";
        return;
    }

    //시작 지점, 페이지 수 계산
    int MainBottom = Gm.GetMainBottom();
    int LogsPerPage = MainBottom - 3;
    int TotalLogs = (int)EventLogs.size();
    int TotalPages = (TotalLogs + LogsPerPage - 1) / LogsPerPage;
    int CurrentPage = 0;

    while (true)
    {
        Gm.DrawCombatLayOut();

        Gm.GoSpace(3, 1);
        cout << "[ SYSTEM LOG ] 디버깅 이력 전체 출력";

        //현재 페이지 로그 출력
        int start = CurrentPage * LogsPerPage;
        int end = min(start + LogsPerPage, TotalLogs);

        for (int i = start; i < end; i++)
        {
            Gm.GoSpace(3, 2 + (i - start));
            cout << EventLogs[i];
        }

        //페이지 넘기기(Enter)
        Gm.ClearLogs();
        Gm.AddLog("[ " + to_string(CurrentPage + 1) + " / " + to_string(TotalPages) + " 페이지 ]");

        if (CurrentPage < TotalPages - 1)
            Gm.AddLog("[ Enter: 다음 페이지 ]");
        else
            Gm.AddLog("[ Enter: 종료 ]");

        EventManager::WaitEnter();

        if (CurrentPage < TotalPages - 1)
            CurrentPage++;
        else
            break;
    }
}
