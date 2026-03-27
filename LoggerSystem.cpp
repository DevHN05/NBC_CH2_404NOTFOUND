#include "LoggerSystem.h"
#include <iostream>
#include "GraphicManager.h"

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

    Gm.AddLog( Log );
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

    //이놈이 문제[
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

void LoggerSystem::LogItemNotFound(const string& ItemName)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    string Log = "[ ERROR ] " + ItemName + " — 인벤토리에서 찾을 수 없음";
    Gm.AddLog(Log);
    EventLogs.push_back(Log);
}


//-----------------------------요약----------------------------------
//처치한 몬스터와 획득한 총 골드와 경험치를 보여주는 함수
void LoggerSystem::PrintSummary()
{
	cout << "======================================\n";
	cout << "[ DEBUG REPORT ] 디버깅 세션 종료\n";
	cout << "======================================\n";

	cout << "[ 제거된 버그 개체 ]\n";
	 if (MonsterKillLogs.empty())
	{
		cout << "  제거된 버그 개체 없음\n";
	}
	else
	{
		for (auto& Entry : MonsterKillLogs)
		{
			cout << "  >> " << Entry.first << " x" << Entry.second << " 제거 완료\n";
		}
	}

	cout << "[ 총 확보 골드    ] : " << TotalGold << " G\n";
	cout << "[ 총 수집 데이터  ] : " << TotalExp << " EXP\n";
	cout << "======================================\n";
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
