#include "Manual.h"
#include "Neural.h"
#include "Menu.h"
#include "Score.h"
#include <string>
#include <sstream>



void Manual::drawWindow(sf::RenderWindow &window)
{
    srand(time(0));
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

        //Check if the keyboard is pressed and store update the value if dir accordingly
        if (Keyboard::isKeyPressed(Keyboard::Left))     dir=1;
        if (Keyboard::isKeyPressed(Keyboard::Right))    dir=2;
        if (Keyboard::isKeyPressed(Keyboard::Up))       dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down))     dir=0;

		if (timer>delay)
        {
            timer=0;
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

void Manual:: Tick()
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
