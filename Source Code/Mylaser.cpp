#include "MyLaser.hpp"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

void MyLaserHeli:: gotoxy(int x, int y) {  // to print in any place you want
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

void MyLaserHeli::DrawMyLaser(){//چاپ لیزر کاربر
    if(!dead){
        for (int i = 0; i < 10; i++)
        {   // رشته های لیزررا چاپ میکند
            gotoxy(MyLaserX , MyLaserY+i);cout<<MyLaser[i];
            
        }
    }else{
        for(int i = 0 ; i < 10 ; i++)
        {   //رشته های لیزر را پاک میکند
            gotoxy(MyLaserX , MyLaserY+i);cout<<"   ";
          //  Sleep(1);
        }
    }
}