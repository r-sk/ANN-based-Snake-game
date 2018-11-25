#ifndef MANUAL_H
#define MANUAL_H
#include <Screens.h>
#include <cmath>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include "neural.h"

using namespace sf;
#define X 2



class Manual : public Screens
{
private:
    //Game Initializers:
    int N =      50;          //Weight of Game screen
    int M =      30;          //Height of Game screen
    int speed =   10;         //Speed of snake
    int num =     4;          //Initial length of snake
    int size =   16;          //Size of each snake piece

    //Variable declarations:
    int w = 1024;   //size*N;
    int h = 768;    //size*M;
    float delay = 1/float(speed);
    int hscore =0;
    int die=0;
//    int mode=0;
    int adj_x = 110;
    int adj_y = 200;
    int dir=1;

    struct snake
    { int x,y;}  s[100];

    struct fruit
    { int x,y;} f;

public:
    void drawWindow(sf:: RenderWindow &window);
    void Tick();
};

#endif // GAME_H
