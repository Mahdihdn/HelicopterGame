#include "GamePlayHeli.hpp"
#include "MyHelicopter.hpp"
#include "EnemyHelicopter.hpp"
#include "MyLaser.hpp"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

MyHelicopter Helicopter;//ایجاد شی برای کلاس هلیکوپتر کاربر
EnemyHelicopter Enemy;//ایجاد شی برای کلاس دشمن
MyLaserHeli Laser;//ایجاد شی برای کلاس لیزر کاربر
void GamePlayHeli::gotoxy(int x, int y)
{
// to print in any place you want
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GamePlayHeli::startUp()
{
    // all values once the game starts
    srand(time(NULL));
    exitGame = false;//وضعیت خزوج از بازی
    Helicopter.isMoving = false;//وضعیت اجرای بازی
    gameOver = false;//وضعیت باختن 
    Helicopter.dead = false;//وضعیت نابودی هلیکوپتر
    Helicopter.bombExplode = false;//وضعیت بمب
    Helicopter.Life = 3;//تعداد جان های هلیکوپتر
    height = 20;//طول یا ارتفاع بازی X
    width = 30;//عرض صفحه بازی Y
    Helicopter.myHeliX = 8;//موقعیت اولیه افقی هلیوکپتر کاربر
    Helicopter.myHeliY = 16;//موقعیت اولیه عمودی هلیکوپتر  کاربر
    Laser.MyLaserX = 8 ;//موقعیت اولیه افقی لیزر کاربر
    Laser.MyLaserY = 7;//موقعیت اولیه عمودی لیزر کاربر
    Helicopter.speed = 1;
    Enemy.enemyNum = 2;//تعداد دشمن ها
    Helicopter.score = 0;//مقدار دهی به امتیاز کاربر
     for (int i = 0; i < Enemy.enemyNum; i++)
     //تولید دشمن به صورت رندوم در سه مختصات مختلف افقی
    {
        Enemy.enemyPositionX = rand() % 3;
        if (Enemy.enemyPositionX == 0)
            Enemy.enemyX[i] = 2;
        else if (Enemy.enemyPositionX == 1)
            Enemy.enemyX[i] = 8;
        else if (Enemy.enemyPositionX == 2)
            Enemy.enemyX[i] = 14;
    }
    //مختصات ثابت عمودی دشمن
    Enemy.enemyY[0] = -8;
    Enemy.enemyY[1] = -18;
    Enemy.enemyY[2] = -28;
    Enemy.enemyY[3] = -38;
}

void GamePlayHeli::Scores()
{
    Helicopter.score += 1;//این تابع برای محاسبه امتیاز های کاربر است.
}

void   GamePlayHeli:: layout()
{  // to print the game layout
    for (int i = 0; i < height; i++) //برای هر ردیف از چیدمان
   {   gotoxy(0, i); // حرکت کرسر به موقعیت شروع ردیف
        std::cout << "|                  |";
        //چاپ قسمت‌های ثابت در ابتدا و انتهای هر ردیف
        if (i % 2 == 0 && Helicopter.isMoving) 
        { //اگر ردیف فرد بود و بازی در حال حرکت بود
         gotoxy(6, i);//حرکت کرسر به مکان مناسب
        std::cout << "             "; // پاک کردن فضای مناسب برای حرکت
        }
        // در غیر اینصورت اگر ردیف زوج بود و بازی در حال حرکت نبود
        else if (i % 2 != 0 && !Helicopter.isMoving )
        {
            gotoxy(6, i); //حرکت کرسر به مکان مناسب
         std::cout << "            ";
        }
    }
    gotoxy(5, 21); std::cout << "Life: " << Helicopter.Life;// چاپ تعداد جان‌های بازیکن
    gotoxy(5, 22); std::cout << "Score: " << Helicopter.score;// چاپ امتیاز بازیکن
}

void GamePlayHeli:: input()
{ // to control your Heli using keyboard input
    if (_kbhit())
    {
        switch (_getch())// برای دسترسی به کاراکتر ورودی
        {
        case 72:// اگر کلید فشرده شده "بالا" باشد
            if (Helicopter.myHeliY > 0 && !Helicopter.dead)
            // اگر ماشین شما در حدودی بالاتر از صفحه باشد و شما نابود نشده باشید
            {
                Helicopter.myHeliY -= Helicopter.speed;
                Laser.MyLaserY -= Helicopter.speed;
            }
            break;
        case 75:// اگر کلید فشرده شده "چپ" باشد
            if (Helicopter.myHeliX > 2 && !Helicopter.dead) 
           // اگر هلیکوپتر شما در حدود 2 واحدی به سمت چپ صفحه باشد و شما نابود نشده باشید
            {
                Helicopter.myHeliX -= 6;
                Laser.MyLaserX -= 6;
                //به اندازه 6 تا خونه به سمت چپ حرکت میکند
            }
            break;
        case 77:// اگر کلید فشرده شده "راست" باشد
            if (Helicopter.myHeliX < 14 && !Helicopter.dead)
            
         // اگر هلیکوپتر شما در حدود 14 واحدی به سمت راست صفحه باشد و نابود نشده باشید
            {
                Helicopter.myHeliX += 6;
                Laser.MyLaserX += 6;
                //به اندازه 6 تا خونه به سمت راست حرکت میکند
            }
            break;
        case 80:// اگر کلید فشرده شده "پایین" باشد
            if (Helicopter.myHeliY < 16 && !Helicopter.dead)
            // اگر هلیکوپتر شما در حدودی پایین تر از صفحه باشد و شما نابود نشده باشید باشید
            {

                Helicopter.myHeliY += Helicopter.speed;
                Laser.MyLaserY += Helicopter.speed;
                //به اندازه مقدار سرعت که یک است به سمت پایین میاید
            }
            break;

        case 115:
        case 83:
            //بازی ذخیره میشودsدرصورت دریافت
            ofstream outFile("player.txt");// باز کردن فایل "player.txt" برای نوشتن
            if (outFile.is_open())// بررسی می‌شود که آیا فایل باز شده است یا خیر
            {  
                // نوشتن اطلاعات بازیکن در فایل
                outFile << Helicopter.score  << endl;
                outFile << Helicopter.Life   << endl;
                outFile << Helicopter.speed  << endl;
                outFile << Helicopter.myHeliX << endl;
                outFile << Helicopter.myHeliY << endl;
                outFile <<  Laser.MyLaserX<< endl;
                outFile <<  Laser.MyLaserY<< endl;
                outFile.close();// بستن فایل
                std::cout << endl
                     << "Player data has been saved to file." << endl;
                     // نمایش پیام موفقیت آمیز بودن ذخیره سازی اطلاعات بازیکن در فایل
            }
            else
            {
                cerr << "Unable to open file for writing." << endl;
                return;
                
                // نمایش پیام خطا در صورت عدم توانایی در باز کردن فایل
            }
            game_Saved();
            break;
        }
    }
}

void GamePlayHeli::mechanic() 
{  // all mechanics, rules and logics GAME
    srand( time(NULL) );
    for (int i = 0; i < Enemy.enemyNum; i++) {//حرکت زیگ زاگی دشمن
       
           Enemy.enemyY[i] += 1;//حرکت دشمن به سمت پایین
          int random = rand ()%3 ;//تولید اعداد رندوم برای حرکت زیگ زاگ
        //  int ran = rand()%2;
           if( Enemy.enemyX[i] ==  2 )
           { 
             if(random==2){
              Enemy.enemyX[i] = 8 ;
              }
              else if(random==1)
              {
                Enemy.enemyX[i]=14;
              }
              else if(random == 0){
                Enemy.enemyX[i]=2 ;
              }
           }
           else if(Enemy.enemyX[i] ==14)
            {   if(random == 2 ){
                Enemy.enemyX[i]= 8 ;}
                else if(random==1)
                {
                    Enemy.enemyX[i]=2;
                }else if(random==0)
                {
                    Enemy.enemyX[i]==14;
                }
            }
            else if(Enemy.enemyX[i]==8)
            {
                if(random==2)
                {
                  Enemy.enemyX[i] = 2   ; 
                //  drawEnemyHeli(); 
                } else if(random=1)
                   {Enemy.enemyX[i] =14 ;
                  // drawEnemyHeli();
                   }else if(random==0)
                   {
                    Enemy.enemyX[i] = 8;
                   }
                // drawEnemyHeli();
            }
    }
      Enemy.CreateEnemyhelicopter();//فراخوانی تابع ایجاد دشمن
    for (int i = 0; i < Enemy.enemyNum; i++) {  // چک کردن عبور کردن دشمن ها از محدوده مشخص
        if (((Helicopter.myHeliY <= Enemy.enemyY[i]+3 && Helicopter.myHeliY >= Enemy.enemyY[i])) && Helicopter.myHeliX == Enemy.enemyX[i] ||Enemy.enemyY[i] == 16 ) {
            died();//فراخوانی تابع مرگ
        }
        else if (Helicopter.myHeliX == Enemy.enemyX[i]  ) {
           Enemy.enemyY[i] = 21;//تنظیم موقعیت دشمن
         Enemy.CreateEnemyhelicopter();//فراخوانی تابع ایجاد دشمن
         Scores();
        }
    }
}


void GamePlayHeli::hideCursor() {  // to hide cursor
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 10;//اندازه نشانگر 
    cursor.bVisible = false;
    //برای نمایش یا مخفی کردن نشانگر است این تابع که در اینجانادرست است 
    //پس نشانگر را نمایش نمیدهد
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    //وظیفه این تابع اعمال ویژگی‌های مورد نظر بر روی نشانگر است تا آن را مخفی یا نمایان کند.
}
void GamePlayHeli::game_Over() {  // when player's life == 0
    if (Helicopter.Life == 0) {
        gameOver = true;
//(کنسول)برای تغییر مکان کرسر را فراخوانی میکند و سپس متنی که پنجره بازی gotoxyتابعی به نام 
//راپرمیکند را چاپ میکند
        do {
            gotoxy(0, 0);  std:: cout <<"____________________";
            gotoxy(0, 1);  std::cout << "|                  |";
            gotoxy(0, 2);  std::cout << "|                  |";
            gotoxy(0, 3);  std::cout << "|                  |";
            gotoxy(0, 4);  std::cout << "|                  |";
            gotoxy(0, 5);  std::cout << "|                  |";
            gotoxy(0, 6);  std::cout << "|    GAME OVER!!   |";
            gotoxy(0, 7);  std::cout << "|                  |";
            gotoxy(0, 8);  std::cout << "|    HIGHSCORE     |";
            gotoxy(0, 9);  std::cout << "|                  |";
            gotoxy(0, 10); std::cout << "|       "<<Helicopter.score<<"         |";
            gotoxy(0, 11); std::cout << "|                  |";
            gotoxy(0, 12); std::cout << "|                  |";
            gotoxy(0, 13); std::cout << "|                  |";
            gotoxy(0, 14); std::cout << "|                  |";
            gotoxy(0, 15); std::cout << "|                  |";
            gotoxy(0, 16); std::cout << "|    PRESS   'X'   |";
            gotoxy(0, 17); std::cout << "|     TO EXIT      |";
            gotoxy(0, 18); std::cout << "|                  |";
            gotoxy(0, 19); std::cout << "|__________________|";
            gotoxy(0, 20); std::cout << "|                  |";
            gotoxy(0, 21); std::cout << "|                  |" ;
        } while (getch() != 'x') ;//نباشد ادامه پیدا میکندxتا زمانی که  
        std::exit(1);// برنامه خاتمه می‌یابد
    }
}

void GamePlayHeli::game_Saved()//اجرا میشود sاین تابع پس از ورودی
{
    do
    {
        gotoxy(0, 0);
        std::cout << "____________________";
        gotoxy(0, 1);
        std::cout << "|                  |";
        gotoxy(0, 2);
        std::cout << "|                  |";
        gotoxy(0, 3);
        std::cout << "|                  |";
        gotoxy(0, 4);
        std::cout << "|                  |";
        gotoxy(0, 5);
        std::cout << "|                  |";
        gotoxy(0, 6); 
        std::cout << "|    GAME Saved!!  |";
        gotoxy(0, 7);
        std::cout << "|                  |";
        gotoxy(0, 8);
        std::cout << "|    HIGHSCORE     |";
        gotoxy(0, 9);
        std::cout << "|                  |";
        gotoxy(0, 10);
        std::cout << "|        "<<Helicopter.score<<"       |";
        gotoxy(0, 11);
        std::cout << "|    come back     |";
        gotoxy(0, 12);
        std::cout << "|      soon:)      |";
        gotoxy(0, 13);
        std::cout << "|                  |";
        gotoxy(0, 14);
        std::cout << "|                  |";
        gotoxy(0, 15);
        std::cout << "|                  |";
        gotoxy(0, 16);
        std::cout << "|    PRESS   'X'   |";
        gotoxy(0, 17);
        std::cout << "|     TO EXIT      |";
        gotoxy(0, 18);
        std::cout << "|                  |";
        gotoxy(0, 19);
        std::cout << "|                  |";
        gotoxy(0, 20);
        std::cout << "|__________________|";
        gotoxy(0, 21);
        std::cout << "|                  |";
    } while (getch() != 'x');//دریافت نکند صفحه بالا را نمایش میدهدxتازمانی که
    std::exit(1);//خروج
}
void GamePlayHeli::died() {  //هنگامی که هلیوکپتر های حریف از  ناحیه ی خاص عبور میکند
    // if (dead) {
        Helicopter.dead = true;//تنظیم مردن
        Helicopter.Life -= 1;//کم شدن یکی از جان ها 
        int count = 0;//تعریف و مقدار دهی شمارنده
        while (count != 10) {
            input();// تابع ورودی را فراخوانی می‌کند
            Helicopter.bombExplosion();// انفجار بمب را اجرا می‌کند
            gotoxy(2, 22); std::cout << "You got " << Helicopter.score << " Score!";//امتیاز را چاپ میکند
            count ++;
        }
        gotoxy(2, 22); std::cout << "                    "; 
        reposition();// تابع بازگرداندن موقعیت
        Helicopter.dead = false; 

}

void GamePlayHeli::reposition() {   //تعیین موقعیت اولیه هلیکوپتر کاربر

    Helicopter.myHeliX = 8;   //موقعیت افقی اولیه هلیکوپتر کاربر
    Helicopter.myHeliY = 16;  //موقعیت عمودی هلیکوپتر کاربر
    Laser.MyLaserX = 8 ; 
    Laser.MyLaserY = 7;
    Helicopter.speed = 1;    //سرعت هلیکوپتر کاربر
    //تولید موقعیت تصادفی برای دشمن ها 
    for (int i = 0; i < Enemy.enemyNum; i++) { 
        Enemy.enemyPositionX = rand() % 3;
        if (Enemy.enemyPositionX == 0) Enemy.enemyX[i] = 2;
        else if (Enemy.enemyPositionX == 1) Enemy.enemyX[i] = 8;
        else if (Enemy.enemyPositionY == 2) Enemy.enemyX[i] = 14;
    }
    Enemy.enemyY[0] = -8;
    Enemy.enemyY[1] = -18;
    Enemy.enemyY[2] = -28;
    Enemy.enemyY[3] = -38;
}

void GamePlayHeli::first()// انتظار برای ورودی کاربر برای شروع بازی
{ 
    gotoxy(0, 0);  std::cout << "___________________";
    gotoxy(0, 1);  std::cout << "|                 |";
    gotoxy(0, 2);  std::cout << "|                 |";
    gotoxy(0, 3);  std::cout << "| helicopter GAME |";
    gotoxy(0, 4);  std::cout << "|                 |";
    gotoxy(0, 5);  std::cout << "|                 |";
    gotoxy(0, 6);  std::cout << "|                 |";
    gotoxy(0, 7);  std::cout << "|   PRESS   'L'   |";
    gotoxy(0, 8);  std::cout << "|   TO LOADGAME   |";
    gotoxy(0, 9);  std::cout << "|   PRESS 'SPACE' |";
    gotoxy(0, 10);  std::cout <<"|   TO NEWGAME    |";
    gotoxy(0, 11); std::cout << "|                 |";
    gotoxy(0, 12); std::cout << "|                 |";
    gotoxy(0, 13); std::cout << "|                 |";
    gotoxy(0, 14); std::cout << "|                 |";
    gotoxy(0, 15); std::cout << "|                 |";
    gotoxy(0, 16); std::cout << "|                 |";
    gotoxy(0, 17); std::cout << "|                 |";
    gotoxy(0, 18); std::cout << "|                 |";
    gotoxy(0, 19); std::cout << "|_________________|";
    gotoxy(0, 20); std::cout << "|_________________|";
  
        switch (_getch())
        {
            case 32:playNew();// بازی جدیدی ایجاد میشودspaceدر صورت وارد کردن
              break;
            case 108 : //بازی که در گذشته ذخیره شده بود اجرا میشودLدرصورت دریافت
            case 76: 
            playLoadGame();
              break;

        }       
}

void GamePlayHeli:: playLoadGame()
{
    hideCursor();// کرسر را مخفی می کند
    LoadstartUp();//عملیات اولیه را شروع میکند
    transition();// انتقال به صحنه‌ی بازی را انجام می‌دهد
    games();// بازی‌ها را شروع می‌کند
    while (!Helicopter.dead) {
        layout();// طرح‌بندی بازی را به روز می‌کند
        input(); // ورودی‌ها را دریافت می‌کند
        mechanic();// عملکرد مکانیکی را اجرا می‌کند
        Helicopter.drawMyHelicopter(); // هلیکوپتر کاربر را روی صفحه می‌کشد
        Laser.DrawMyLaser();//لیزر کاربر را میکشد
        Enemy.CreateEnemyhelicopter();// هلیکوپتر دشمن را روی صفحه می‌کشد
        game_Over();// بازی را پایان می‌دهد
       
        Sleep(45); // برنامه را برای ۵۰ میلی‌ثانیه متوقف می‌کند

}
 std::system("cls");// صفحه را پاک می‌کند
    std::cout << "\n\n\n\n\tThank You for playing!!";
}
void GamePlayHeli::transition() {  // to print transition
    for (int i = 19; i >= 0; i--) {
    // یک حلقه برای چاپ خطوط "#" به شکل نزولی و تاخیر هر خط 15 میلی‌ثانیه
        gotoxy(1, i); std::cout << "__________________";
        Sleep(15);
    }
    // یک حلقه برای پاک کردن خطوط فعلی به شکل صعودی و تاخیر هر خط 15 میلی‌ثانیه
    for (int i = 1; i < 20; i++) {
        gotoxy(1, i); std::cout << "                  ";
        Sleep(15);
    }
}
void GamePlayHeli:: games() {
    do {
    gotoxy(0, 0);  std::cout << "___________________";
    gotoxy(0, 1);  std::cout << "|                 |";
    gotoxy(0, 2);  std::cout << "|                 |";
    gotoxy(0, 3);  std::cout << "| helicopter GAME |";
    gotoxy(0, 4);  std::cout << "|                 |";
    gotoxy(0, 5);  std::cout << "|                 |";
    gotoxy(0, 6);  std::cout << "|                 |";
    gotoxy(0, 7);  std::cout << "|                 |";
    gotoxy(0, 8);  std::cout << "|                 |";
    gotoxy(0, 9);  std::cout << "|                 |";
    gotoxy(0, 10);  std::cout <<"|  PRESS 'SPACE'  |";
    gotoxy(0, 11); std::cout << "|     TO Play     |";
    gotoxy(0, 12); std::cout << "|  PRESS 'S'      |";
    gotoxy(0, 13); std::cout << "|     TO SAVE     |";
    gotoxy(0, 14); std::cout << "|                 |";
    gotoxy(0, 15); std::cout << "|                 |";
    gotoxy(0, 16); std::cout << "|                 |";
    gotoxy(0, 17); std::cout << "|                 |";
    gotoxy(0, 18); std::cout << "|                 |";
    gotoxy(0, 19); std::cout << "|                 |";
    gotoxy(0, 20); std::cout << "___________________";
    } while (getch() != 32);// انتظار برای ورودی کاربر برای شروع بازی
}

void GamePlayHeli:: LoadstartUp() //با ورودی L اطلاعات رو میخونه
{ // all values once the game starts
    // Read player data from the text file
    ifstream inFile("player.txt");
    if (inFile.is_open())
    {
        //inFile >> GameLevel;
        inFile >> Helicopter.score;
        inFile >> Helicopter.Life;
        inFile >> Helicopter.speed;
        inFile >> Helicopter.myHeliX;
        inFile >> Helicopter.myHeliY;
        inFile >> Laser.MyLaserX;
        inFile >> Laser.MyLaserY;
        inFile.close();
    }
    else
    {
        cerr << "Unable to open file for reading." << endl;
    }
    srand(time(NULL));//ایجاد اعداد رندوم بر اساس زمان سیستم
    exitGame = false;
    Helicopter.isMoving = false;
    gameOver = false;
    Helicopter.dead = false;
    Helicopter.bombExplode = false;
    height = 20;
    width = 30;
    Enemy.enemyNum = 2;

    for (int i = 0; i < Enemy.enemyNum; i++) //تولید دشمن جدید 
    {
        Enemy.enemyPositionX = rand() % 3;
        if (Enemy.enemyPositionX == 0)
            Enemy.enemyX[i] = 2;
        else if (Enemy.enemyPositionX == 1)
            Enemy.enemyX[i] = 8;
        else if (Enemy.enemyPositionX == 2)
            Enemy.enemyX[i] = 14;
    }
    Enemy.enemyY[0] = -8;
    Enemy.enemyY[1] = -18;
    Enemy.enemyY[2] = -28;
    Enemy.enemyY[3] = -38;
}
void GamePlayHeli::playNew() {

    hideCursor();// کرسر را مخفی می کند
    startUp();//عملیات اولیه را شروع میکند
    transition();// انتقال به صحنه‌ی بازی را انجام می‌دهد
    games();// بازی‌ها را شروع می‌کند
    //playLoadGame();
    while (!Helicopter.dead) {
        layout();// طرح‌بندی بازی را به روز می‌کند
        input(); // ورودی‌ها را دریافت می‌کند
        mechanic();// عملکرد مکانیکی را اجرا می‌کند
        Helicopter.drawMyHelicopter();//هلیکوپتر کاربر را چاپ میکند
        Laser.DrawMyLaser();//لیزر کاربر را چاپ میکند
        Enemy.drawEnemyHelicopter();// هلیکوپتر دشمن را روی صفحه می‌کشد
        game_Over();// بازی را پایان می‌دهد
       
        Sleep(45); // برنامه را برای ۵۰ میلی‌ثانیه متوقف می‌کند

    }
}
