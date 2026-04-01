#pragma once

class DiceSystem
{
public:
    int GetDiceSize();
    int GetDiceHead();
    bool GetResult();
    
    void SetDiceSize(int Size);
    void SetDiceHead(int Head);
    void SetResult(bool IsSucceeded);
    
    // size = 주사위의 최댓값, target = 판정값, bonus = 보너스 판정값
    void RollDice(int Size = 20, int Target = 1, int Bonus = 0);
    
    // 주사위 굴리기 결과 판정 함수
    void Decise(int Target, int Bonus, int Result);
    
private:
    // 주사위의 최댓값
    int Size = 20;
    // 주사위의 결과값
    int Head = 1;
    // 판정 결과
    bool IsSucceeded = false;
};
