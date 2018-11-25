#include "Game.h"
#include "Neural.h"
#include "Menu.h"
#include "Score.h"
#include <string>
#include <sstream>


Game::Game()
{

}

Game::~Game()
{    //dtor
}

void Game::drawWindow(sf::RenderWindow &window)
{
    srand(time(0));

    Neural nn(5 ,4 ,5 ,5 ,0.0001);
    nn.init();

    sf::RenderWindow windowx;
	Screens *screenPtrMenu;
	Menu menu;
	screenPtrMenu = &menu;

	sf::Music music;
	music.openFromFile("Stranger_Things.ogg");
	music.play();

	//Create window for snake game
    window.create (VideoMode(w, h), "Snake Game!");

    Texture t1,t2,t3,bk;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/apple.png");
    bk.loadFromFile("images/background.jpg");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite backgnd(bk);

	Clock clock;

    //Creating fonts:
    Font arial;
    arial.loadFromFile("arial.ttf");

    //Text to display "Score : " text:
    Text score_text;
    score_text.setFont(arial);
    score_text.setCharacterSize(40);
    score_text.setFillColor(sf::Color::Blue);
    score_text.setStyle(sf::Text::Bold);
    score_text.setPosition(160,40);
    score_text.setString("Score: ");

    //Text to display score:
    Text score;
    score.setFont(arial);
    score.setCharacterSize(40);
    score.setFillColor(sf::Color::Blue);
    score.setStyle(sf::Text::Bold);
    score.setPosition(300,40);

    //Text to display "Max Score :" text:
    Text high_score_text;
    high_score_text.setFont(arial);
    high_score_text.setCharacterSize(40);
    high_score_text.setFillColor(sf::Color::Blue);
    high_score_text.setStyle(sf::Text::Bold);
    high_score_text.setPosition(520,40);
    high_score_text.setString("Max Score: ");

    //Text to display High Score:
    Text high_score;
    high_score.setFont(arial);
    high_score.setCharacterSize(40);
    high_score.setFillColor(sf::Color::Blue);
    high_score.setStyle(sf::Text::Bold);
    high_score.setPosition(740,40);

    //Text to display Exit:
    Text exit;
    exit.setFont(arial);
    exit.setCharacterSize(20);
    exit.setFillColor(sf::Color::Blue);
    exit.setStyle(sf::Text::Bold);
    exit.setPosition(350,710);
    exit.setString("Press ESC to exit the game");


    //Text to display "Ouch!!" text:
    Text ouch;
    ouch.setFont(arial);
    ouch.setCharacterSize(100);
    ouch.setFillColor(sf::Color::Red);
    ouch.setStyle(sf::Text::Bold);
    ouch.setPosition(230,200);
    ouch.setString("OUCH !!!");

    //Variable declarations and initializations:
    float time;
    float timer=0;

	f.x=10;
    f.y=10;

    s[0].x=20;
    s[0].y=40;
    //Infinite loop until window in open:
    while (window.isOpen())
    {
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
        timer+=time;
        Event e;

        //Close window when X clicked:
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

		}

        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            std::cout<<"Escape was pressed."<<std::endl;
            window.close();
            music.pause();
            screenPtrMenu -> drawWindow(windowx);

        }

        //Neural Play Mode:
        if(0==0)
            dir = get_direction(s[0],f);

        //Manual Play Mode:
		else if(0==1)
        {
            //Check if the keyboard is pressed and store update the value if dir accordingly
            if (Keyboard::isKeyPressed(Keyboard::Left))     dir=1;
            if (Keyboard::isKeyPressed(Keyboard::Right))    dir=2;
            if (Keyboard::isKeyPressed(Keyboard::Up))       dir=3;
            if (Keyboard::isKeyPressed(Keyboard::Down))     dir=0;
        }

//        nn.learn(dout);

		if (timer>delay)
        {
            timer=0;

            n_in = input(s[0],f);
            n_out = nn.feed(n_in);

            //To view Neural Inputs and Outputs:
            n_in = input(s[0],f);
            std::cout<< *n_in<<"\t\t"<< *(n_in+1)<<"    "<< *(n_in+2)<<"    "<< *(n_in+3)<<"    "<< *(n_in+4)<<"\t|\t";
            std::cout<< *n_out <<"\t\t"<< *(n_out+1)<<"\t\t"<< *(n_out+2)<<"\t\t"<< *(n_out+3)<<"\t\t"<<std::endl;


            Tick();
            if(die==1)
            {
                die=0;
                window.draw(ouch);
                window.display();
                Sleep(5000);        //Wait for 5 sec
            }
        }

//##############################################################################################################//

        //Drawings:
        window.clear();

        //Draw Background:
        sprite3.setPosition(0,  0);
        window.draw(backgnd);

        //Draw white background:
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++)
            { sprite1.setPosition(i*size+adj_x,j*size+adj_y);  window.draw(sprite1); }

        //Draw Snake pieces:
        for (int i=0;i<num;i++)
            { sprite2.setPosition(s[i].x*size+adj_x, s[i].y*size+adj_y);  window.draw(sprite2); }

        //Draw Fruit:
        sprite3.setPosition(f.x*size+adj_x,  f.y*size+adj_y);  window.draw(sprite3);

        //Draw Score display panel:
        window.draw(score_text);
        std::stringstream score_str;
        score_str << (num-4);
        score.setString(score_str.str());
        window.draw(score);

        //Draw High score display panel:
        window.draw(high_score_text);
        std::stringstream high_score_str;
        high_score_str << hscore;
        high_score.setString(high_score_str.str());
        window.draw(high_score);

        //Draw "Press ESC to exit" :
        window.draw(exit);

        window.display();

//##############################################################################################################//
    }


}

//Takes head and fruit coordinate and generates Neural Inputs:
float* Game::input(snake sh,fruit fr)
{
    float i[5];

    i[0] = distance(sh.x,sh.y,fr);
    i[1] = check(sh.x-1,sh.y  );    //Check Left coordinate
    i[2] = check(sh.x  ,sh.y-1);    //Check Up coordinate
    i[3] = check(sh.x+1,sh.y  );    //Check Right coordinate
    i[4] = check(sh.x  ,sh.y+1);    //Check Down coordinate

//    std::cout<<i[0]<<"\t\t"<<i[1]<<"\t"<<i[2]<<"\t"<<i[3]<<"\t"<<i[4]<<"\t|\t";
    return i;
}

void Game:: Tick()                  //Updates the coordinate of each snake pieces
 {
//    sf::RenderWindow windowx;
//	Screens *screenPtrScore;
//	Score score;
//	screenPtrScore = &score;
for (int i=num;i>0;--i)
	 {s[i].x=s[i-1].x;
	 s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;
    if (dir==1) s[0].x-=1;
    if (dir==2) s[0].x+=1;
    if (dir==3) s[0].y-=1;

	if ((s[0].x==f.x) && (s[0].y==f.y))
    { num++;
    	f.x=rand() % N;
        f.y=rand() % M;
    }

    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;

    for (int i=1;i<num;i++)
    if (s[0].x==s[i].x && s[0].y==s[i].y)
    {
        die=1;
        num=i;
        if(num<4)
            num = 4;
    }

    if(hscore<num-4)
        hscore = num-4;



 }

float Game:: distance(int p,int q,fruit b)      //Calculates the distance between head coordinate and fruit coordinate
{
    float d;
    d = sqrt( (b.x-p)*(b.x-p) + (b.y-q)*(b.y-q) );
    return d;
}

//Takes a coordinate to check whether it is safe(1) or danger(0):
int Game :: check(int x, int y)
{
    for(int chk=1; chk <num; chk++)
        if (x==s[chk].x && y==s[chk].y)
            return 0;   //Danger
    return 1;


}

//Gets the best possible direction on the basis of neural output:
int Game:: get_direction(snake sh,fruit fr)
{
    int drn;
    static int roam=0;
    roam++;

   dout =  re + 0.9 * new_q - old_q;
//	learn(dout);


    if(check(sh.x-1,sh.y) == 1)
    {
         l=distance(sh.x-1,sh.y,f);    //Check Left coordinate
         if(roam%5==0)
         {
             l=3;
         }

    }


    else    l=1000;

    if(check(sh.x,sh.y-1) == 1)
    {
            u=distance(sh.x,sh.y-1,f);    //Check Up coordinate
            if(roam%7==0)
                u=3;
    }

    else    u=1001;

    if(check(sh.x+1,sh.y) == 1)
    {
        r=distance(sh.x+1,sh.y,f);    //Check Right coordinate
        if(roam%9==0)
            r=3;

    }
    else    r=1002;

    if(check(sh.x,sh.y+1) == 1)
    {
        d=distance(sh.x,sh.y+1,f);     //Check Down coordinate
        if(roam%11==0)
            d=3;


    }
    else    d=1003;

//    std::cout<<l<<"\t\t"<<u<<"\t\t"<<r<<"\t\t"<<d<<"\t\t"<<std::endl;

    if( l<=u && l<=r && l<=d)  drn=1;
    if( u<=l && u<=r && u<=d)  drn=3;
    if( r<=l && r<=u && r<=d)  drn=2;
    if( d<=l && d<=u && d<=r)  drn=0;

    if(roam>=100)
        roam=0;

    if(explore==1)
    {
        return rand()%3;
    }
    else
        return drn;
}







