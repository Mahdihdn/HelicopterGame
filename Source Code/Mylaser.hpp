#ifndef LASER_HPP
#define LASER_HPP
#include <iostream>
#include <string>
#include "./MyHelicopter.hpp"

class MyLaserHeli : private MyHelicopter //ارث بری کلاس لیزر از کلاس هلیکوپتر کاربر
{

friend class GamePlayHeli;//کلاس لیزر دوست کلاس گیم پلی هلیکوپتر

private:

    int MyLaserX;//موقعیت افقی اولیه لیزر
    int MyLaserY;//موقعیت اولیه عمودی لیزر

    bool dead;// نابودی هلیکوپترکاربر

   std:: string MyLaser[10]={
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  ",
                    "  ^  "
    };
public:
    void gotoxy(int x, int y) ;//برای چاپ در هر مختصات مورد نظر
    void DrawMyLaser();//چاپ لیزر هلیکوپتر کاربر
};
#endif 
