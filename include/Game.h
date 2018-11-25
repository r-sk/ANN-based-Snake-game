#ifndef GAME_H
#define GAME_H
#include <Screens.h>
#include <cmath>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include "neural.h"

using namespace sf;
#define X 2



class Game : public Screens
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
    int explore = 0;

    int dir;
    float l,u,r,d;
    float dout;

    struct snake
    { int x,y;}  s[100];

    struct fruit
    { int x,y;} f;

    //Variables for NN
    float* n_in;
    float* n_out;
    float n_er;
    int n_dir=1;
    float re=0;
    float new_q = 0.0;
    float old_q = 0.0;
    int state=1;


public:
    Game();
    void drawWindow(sf:: RenderWindow &window);
    float* input(snake sh,fruit fr);
    void Tick();
    float distance(int p,int q,fruit b);
    int check(int x, int y);
    int get_direction(snake sh,fruit fr);
    virtual ~Game();
};

#endif // GAME_H
