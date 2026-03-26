#include "LoggerSystem.h"
#include <iostream>

//----------------------------전투 관련-----------------------------------
//몬스터가 나타났을때 로그 출력하는 함수
void LoggerSystem::LogMonsterAppear(const string& MonsterName) 
{
	string Log = "[ DETECTION ] 버그 개체 [ " + MonsterName + " ] 접근 확인. 디버깅 개시.";
	cout << Log << "\n";
	EventLogs.push_back(Log);
};

//공격을 했을 때 로그 출력하는 함수
void LoggerSystem::LogAttack(const string& Attacker, const string& Target, int Damage) 
{
	string Log = "[ ATTACK ] " + Attacker + " >> " + Target + " 에 디버깅 실행 / 데미지: " + to_string(Damage);
	cout << Log << "\n";
	EventLogs.push_back(Log);
};

//몬스터를 처치했을때 로그 출력하는 함수(해당 몬스터의 처치수를 ++함)
void LoggerSystem::LogMonsterKill(const string& MonsterName) 
{
	MonsterKillLogs[MonsterName]++;
	string Log = "[ DEBUG COMPLETE ] " + MonsterName + " 제거됨. 데이터 수집 중...";
	cout << Log << "\n";
	EventLogs.push_back(Log);
};

//보스 페이즈 변화 로그 출력 함수
void LoggerSystem::LogBossPhaseChange(const string& Nickname, const string& SpecialSkillName, int BoostedStrength)
{
	string Log = "[ CRITICAL WARNING ] 버그 개체 [ " + Nickname + " ] 자가 코드 재작성 감지\n"
		+ "  >> 권한 레벨 상승 / " + SpecialSkillName + " 활성화\n"
		+ "  >> ATK → " + to_string(BoostedStrength) + "  |  디버깅 난이도 상승";
	cout << Log << "\n";
	EventLogs.push_back(Log);
};

//주사위 로그 출력 함수
void LoggerSystem::LogDiceRoll(int Head, bool IsSucceeded)
{
	string Result = IsSucceeded ? "성공!" : "실패...";
	string Log = "[ DICE ] 주사위 " + to_string(Head) + " → " + Result;
	cout << Log << "\n";
	EventLogs.push_back(Log);
}
//-----------------------------캐릭터 관련--------------------------------------
void LoggerSystem::LogLevelUp(int NewLevel) //레벨업 했을때 로그 출력하는 함수 
{
	string Log = "[ SYSTEM ] 디버깅 툴 강화 완료 — 권한 레벨 " + to_string(NewLevel) + " 해금";
	cout << Log << "\n";
	EventLogs.push_back(Log);
};
void LoggerSystem::LogPlayerDeath() //플레이어 사망시 로그 출력하는 함수
{
	string Log = "[ CONNECTION LOST ] 디버거 강제 종료. 재접속 시도 중...";
	cout << Log << "\n";
	EventLogs.push_back(Log); 
};

//----------------------------------------아이템 관련----------------------------------------
//아이템 사용시 로그 출력하는 함수(아이템명과 효과)
void LoggerSystem::LogItemUse(const string& ItemName, const string& Effect) 
{
	string Log = "[ TOOL ACTIVATED ] " + ItemName + " 가동 — " + Effect;
	cout << Log << "\n";
	EventLogs.push_back(Log);
};
//-----------------------------------보상 관련-------------------------------------------
//경험치 획득시 로그 출력하는 함수(얻은량, 현재경험치/레벨업에 필요한 총 경험치)
void LoggerSystem::LogExpGain(int Amount, int MyExp, int MaxExp) 
{
	TotalExp += Amount;
	string Log = "[ DATA COLLECTED ] " + to_string(Amount) + " 데이터 수집 / 현재: " + to_string(MyExp) + " / " + to_string(MaxExp);
	EventLogs.push_back(Log);
};

//골드 획득시 로그 출력하는 함수(얻은량, 현재 골드량)
void LoggerSystem::LogGoldGain(int Amount) 
{
	TotalGold += Amount;
	string Log = "[ RESOURCE ] " + to_string(Amount) + " 골드 확보 / 누적 골드: " + to_string(TotalGold);
	EventLogs.push_back(Log);
};


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