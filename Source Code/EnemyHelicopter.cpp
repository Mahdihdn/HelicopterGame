#include "EnemyHelicopter.hpp"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

void EnemyHelicopter:: gotoxy(int x, int y) {  // to print in any place you want
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
void EnemyHelicopter::drawEnemyHelicopter() {  // to print enemy helicpter
    for (int i = 0; i < enemyNum; i++) {
        if (enemyY[i]+3 > 0) {   // اگر موقعیت عمودی هلیکوپتر+3 بیشتر از 0 باشد
            gotoxy(enemyX[i], enemyY[i] + 3);
            cout << " ! "; //چاپ قسمت بالایی از خودرو با نماد
        }if (enemyY[i]+2 > 0) {// اگر موقعیت عمودی هلیکوپتر +2 بیشتر از 0 باشد
            gotoxy(enemyX[i], enemyY[i] + 2);
            cout << "<*>";// چاپ قسمت میانی از هلیکوپتر با نماد # و فضای خالی
        }
      
        if (enemyY[i]+3 >20) {// اگر موقعیت عمودی هلیکوپتر +3 بیشتر از ارتفاع بازی باشد
            gotoxy(enemyX[i], enemyY[i] + 3);
            cout << "   "; // پاک کردن قسمت بالایی از خودرو
        }if (enemyY[i]+2 > 20) {// اگر موقعیت عمودی هلیکوپتر +2 بیشتر از ارتفاع بازی باشد
            gotoxy(enemyX[i], enemyY[i] + 2);
            cout << "   ";// پاک کردن قسمت میانی از خودرو
        }if (enemyY[i]+1 > 20) {// اگر موقعیت عمودی هلیکوپتر +1 بیشتر از ارتفاع بازی باشد
            gotoxy(enemyX[i], enemyY[i] + 1);
            cout << "   ";// پاک کردن قسمت پایینی از خودرو
        }if (enemyY[i] > 20) {// اگر موقعیت عمودی هلیکوپتر بیشتر از ارتفاع بازی باشد
            gotoxy(enemyX[i], enemyY[i]);
            cout << "   ";//پاک کردن قسمت پایینی از هلیکوپتر
        }
    }
}

void EnemyHelicopter::CreateEnemyhelicopter(){ //پس از ساخت هر دشمن یک امتیاز به ما اضافه میشود
        for (int i = 0; i < enemyNum; i++) { //تولید عدد تصادفی برای موقعیت افقی دشمن
            if (enemyY[i] > 21) {
                enemyPositionX = rand() % 3;
                if (enemyPositionX == 0) enemyX[i] = 2;// اگر مقدار تصادفی برابر با صفر بود
                else if (enemyPositionX == 1) enemyX[i] = 8;
                else if (enemyPositionX == 2) enemyX[i] = 14;
                enemyY[i] = -8;// تنظیم موقعیت ابتدایی عمودی دشمن
                //score += 1;// افزودن یک واحد به امتیاز
            }
        }
    }
