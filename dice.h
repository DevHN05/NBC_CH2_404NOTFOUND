#pragma once

class dice
{
public:
    int get_dice_size();
    int get_dice_head();
    bool get_result();
    
    void set_dice_size(int size);
    void set_dice_head(int head);
    void set_result(bool is_succeeded);
    
    // size = 주사위의 최댓값, target = 판정값, bonus = 보너스 판정값
    void roll_dice(int size = 20, int target = 1, int bonus = 0);
    
    // 주사위 굴리기 결과 판정 함수
    void decise(int target, int bonus, int result);
    
private:
    // 주사위의 최댓값
    int size_ = 20;
    // 주사위의 결과값
    int head_ = 1;
    // 판정 결과
    bool is_succeeded_ = false;
};
