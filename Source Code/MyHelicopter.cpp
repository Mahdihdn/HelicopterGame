#include "MyHelicopter.hpp"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

void MyHelicopter::gotoxy(int x, int y){
//to print in any place you want
//این تابع وظیفه تنظیم موقعیت کرسر روی صفحه نمایش است  
    COORD coord; //یک متغیر برای نگهداری موقعیت مورد نظر
    coord.X = x;
    coord.Y = y;
    //این دستور به کمک تابع  زیر موقعیت را تغییر میدهد
    // حاوی اطلاعات مکانی است برای تنظیم موقعیت مکانی coordکد 
    //SetConsoleCursorPositionبرای تنظیم موقعیت مکانی وکرسر در کنسول 
    //GetStdHandle(STD_OUTPUT_HANDLE) برای دریافت ورودی و خروجی در صفحه نمایش
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MyHelicopter::drawMyHelicopter() {  // تابع برای نمایش هلیکوپتر شما 
    if (!dead) {    //اگر هلیکوپتر شما منفجر نشده باشد
        for (int i = 0; i < 4; i++) {//حلقه برای نمایش بخش های مختلف خودرو
            gotoxy(myHeliX, myHeliY+i);
            cout << myHeli[i];
            //تنظیم موقعیت نمایش و چاپ بخش  مربوطه از هلیکوپتر
        }
        // gotoxy(myCarX, myCarY); cout << "888";
    } else {//اگر خودرو منفجر شده باشد 
        for (int i = 0; i < 4; i++) {//حلقه برای پاک کردن بخش های مختلف خودرو
            gotoxy(myHeliX, myHeliY+i);
            cout << "    ";
            //تنظیم موقعیت نمایش وپاک کردن بخش مربوطه از هلیکوپتر
        }    
        // gotoxy(myCarX, myCarY); cout << "    ";
    }
}

void MyHelicopter::bombExplosion() {  // تابع نمایش انفجار
    if (bombExplode) {  //اگر بمب انفجار شده باشد
        for (int i = 0; i < 4; i++) {
            gotoxy(myHeliX - 1, myHeliY - 1 + i);// رفتن به موقعیت مناسب برای چاپ
            cout << bombParticle1[i] << endl;// چاپ رشته‌های انفجار نوع اول
        }
        bombExplode = false;//تنظیم مجدد بمب به حالت منفجر نشده
    } else {
        for (int i = 0; i < 4; i++) {
            gotoxy(myHeliX - 1, myHeliY - 1 + i);// رفتن به موقعیت مناسب برای چاپ
            cout << bombParticle2[i] << endl;// چاپ رشته‌های انفجار نوع دوم
        }
        bombExplode = true;// تنظیم بمب به حالت انفجار شده
    }
    Sleep(50);// توقف برنامه برای ۱۰۰ میلی‌ثانیه
}
