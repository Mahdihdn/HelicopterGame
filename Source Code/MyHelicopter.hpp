#ifndef MYHELI_HPP
#define MYHELI_HPP
#include <iostream>
#include <string>
using namespace std ;
class MyHelicopter
{
friend class GamePlayHeli;
private:
    int Life = 3 ;//تعداد جان های هلیکوپتر
    int speed = 1;//سرعت حرکت
    int myHeliX;//موقعیت افقی اولیه هلیکوپتر کاربر
    int myHeliY;//موقعیت عمودی اولیه هلیکوپتر کاربر
    int score = 0 ;//امتیاز

    bool dead;//نابودی هلیکوپتر
    bool isMoving; //در حال اجرا
    bool bombExplode;//انفجار هلیکوپتر

    std::string bombParticle1[4] = {"o   o", " ooo ", " ooo ", "o   o"};
    std::string bombParticle2[4] = {" ooo ", "o   o", "o   o", " ooo "};


    std::string myHeli[4] = {
                    "  - ",
                    "_<|>_",
                    " (|)  ",
                    " * * "
    };

public:
   void gotoxy(int x, int y) ;//برای چاپ در هر مختصات مورد نظر
    void drawMyHelicopter() ;//چاپ هلیوکپتر کاربر
    void bombExplosion() ;//هنگامی که هلیوکپتر های حریف از  ناحیه ی خاص عبور میکند
};

#endif 