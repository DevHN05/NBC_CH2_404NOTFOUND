#include <random>
#include "DiceSystem.h"

using namespace std;

int DiceSystem::GetDiceSize()
{
    return Size;
}

int DiceSystem::GetDiceHead()
{
    return Head;
}

bool DiceSystem::GetResult()
{
    return IsSucceeded;
}

void DiceSystem::SetDiceSize(const int Size)
{
    this->Size = Size;
}

void DiceSystem::SetDiceHead(const int Head)
{
    this->Head = Head;
}

void DiceSystem::SetResult(const bool IsSucceeded)
{
    this->IsSucceeded = IsSucceeded;
}

void DiceSystem::RollDice(const int Size, const int Target, const int Bonus)
{
    random_device Rd;
    mt19937 Mt(Rd());
    uniform_int_distribution<int> Dist(1, Size);
    
    SetDiceHead(Dist(Mt));
    
    Decise(Target, Bonus, Dist(Mt));
}

// target = 판정값, bonus = 보너스 판정값, result = 주사위 결과
void DiceSystem::Decise(const int Target, const int Bonus, const int Result)
{
    if (Result == 1)
        // 주사위가 1일 경우 대실패 (무조건 실패)
            SetResult(false);
    else if (Result == GetDiceSize()) 
        // 주사위가 최댓값일 경우 대성공 (무조건 성공)
            SetResult(true);
    else if (Result + Bonus >= Target) 
        // 주사위 결과 + 보너스 판정값이 판정값보다 크거나 같을 경우 성공
            SetResult(true);
    else 
        // 주사위가 판정값보다 작을 경우 실패
            SetResult(false);
}
