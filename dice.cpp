#include <random>
#include "dice.h"

using namespace std;

int dice::get_dice_size()
{
    return size_;
}

int dice::get_dice_head()
{
    return head_;
}

bool dice::get_result()
{
    return is_succeeded_;
}

void dice::set_dice_size(const int size)
{
    size_ = size;
}

void dice::set_dice_head(const int head)
{
    head_ = head;
}

void dice::set_result(const bool is_succeeded)
{
    is_succeeded_ = is_succeeded;
}

void dice::roll_dice(const int size, const int target, const int bonus)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, size);
    
    set_dice_head(dist(mt));
    
    decise(target, bonus, dist(mt));
}

// target = 판정값, bonus = 보너스 판정값, result = 주사위 결과
void dice::decise(const int target, const int bonus, const int result)
{
    if (result == 1)
        // 주사위가 1일 경우 대실패 (무조건 실패)
            set_result(false);
    else if (result == get_dice_size()) 
        // 주사위가 최댓값일 경우 대성공 (무조건 성공)
            set_result(true);
    else if (result >= target + bonus) 
        // 주사위가 판정값 + 보너스 판정값보다 크거나 같을 경우 성공
            set_result(true);
    else 
        // 주사위가 판정 숫자보다 작을 경우 실패
            set_result(false);
    
}
