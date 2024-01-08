#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <iostream>
#include <string>
class EnemyHelicopter
{

friend class GamePlayHeli;

private:
    int enemyX[4];//چاپ دشمن ها
    int enemyY[4] = {-8, -18, -28, -38} ;//موقعیت عمودی ثابت دشمن
    int enemyPositionX;//موقعیت افقی دشمن X
    int enemyPositionY;//موقعیت عمودی دشمن
    int enemyNum;//شماره دشمن
    //نمایش انفجار هلیکوپتر :

public:
    void gotoxy(int x, int y) ;//برای چاپ در هر مختصات مورد نظر
    void drawEnemyHelicopter() ;//چاپ هلیکوپتر های حریف
    void CreateEnemyhelicopter();//تابع ساخت دشمن 
};
#endif 