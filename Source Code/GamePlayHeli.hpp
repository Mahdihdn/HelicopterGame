#ifndef C3684005_CF6C_41F8_8E71_6B0F5EC590EF
#define C3684005_CF6C_41F8_8E71_6B0F5EC590EF
#include <iostream>
#include <string>
#include "MyHelicopter.hpp"
#include "EnemyHelicopter.hpp"
#include "MYLaser.hpp"
using namespace std;
class GamePlayHeli
{
private:
        
    int  width;//عرض
    int  height;//طول


    bool exitGame; //خروج از بازی
    bool gameOver; //باختن

public:
    void gotoxy(int x, int y) ;//برای چاپ در هر مختصات مورد نظر
    void layout() ; //چاپ کردن چیدمان بازی 
    void input() ;//این تابع ورودی هایی دریافت میکند و براساس این ورودی ها تغییراتی اعمال میکند
    void Scores();
    void mechanic(); //حرکت هلیکوپتر های دشمن
    void hideCursor() ;//cursorمخفی کردن
    void game_Over() ;// اجرا میشود life == 0وقتی
    void game_Saved();//اجرا میشود sاین تابع پس از ورودی
    void transition();//اجرا انیمیشین در ابتدا اجرا صفحه بازی 
    void died() ;//هنگامی که هلیوکپتر های حریف از  ناحیه ی خاص عبور میکند
    void first();// انتظار برای ورودی کاربر برای شروع بازی ذخیره شده یا جدید
    void reposition() ;// تعیین موقعیت اولیه هلیکوپتر کاربروحریف
    void playLoadGame();//اجرای بازی ذخیره شده
    void playNew(); //اجرای بازی جدید
    void games() ; //چاپ چیدمان دوم 
    void LoadstartUp();//میخواندLاطلاعات بازی  ذخیره شده را با ورودی
    void startUp() ;//مقدار دهی هنگامی که بازی اجرا میشه

};
#endif 
