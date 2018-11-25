#include "Credits.h"
#include "Menu.h"
#include "Score.h"

Credits::Credits()
{
    //ctor
}

Credits::~Credits()
{
    //dtor
}
 void Credits :: drawWindow(sf::RenderWindow &window)
 {
    sf::RenderWindow windowx;
	Screens *screenPtrMenu,*screenPtrScore;
	Menu menu;
	Score score;
	screenPtrMenu = &menu;
    screenPtrScore = &score;

	window.create(sf::VideoMode(1024, 768), "Credits");
	float width =window.getSize().x;
	float height =window.getSize().y;

	sf::Music music;
	music.openFromFile("Stranger_Things1.ogg");
    music.play();

    	 /**Texture and Sprite for background image**/
    sf :: Texture t1;
	t1.loadFromFile("alpha2.jpg");
	sf:: Sprite  background(t1);

    font.loadFromFile("mexcel3D.ttf");
      /**Writing on the screen**/
	credits[0].setFont(font);
	credits[0].setColor(sf::Color::Yellow);
	credits[0].setString("Created by:");
	credits[0].setPosition(sf::Vector2f(width -600, height-550 ));

	credits[1].setFont(font);
	credits[1].setColor(sf::Color::White);
	credits[1].setString("Rashik Shrestha 073BEX432");
	credits[1].setPosition(sf::Vector2f(width -600, height-500));

    credits[2].setFont(font);
	credits[2].setColor(sf::Color::White);
	credits[2].setString("Sagar Bhandari 073BEX435");
	credits[2].setPosition(sf::Vector2f(width -600, height-450));

	credits[3].setFont(font);
	credits[3].setColor(sf::Color::White);
	credits[3].setString("Shirish Shrestha 073BEX440");
	credits[3].setPosition(sf::Vector2f(width -600, height-400));

    credits[4].setFont(font);
	credits[4].setColor(sf::Color::White);
	credits[4].setString("Shrutee Dwa 073BEX444");
	credits[4].setPosition(sf::Vector2f(width -600, height-350));


    credits[5].setFont(font);
	credits[5].setColor(sf::Color::Yellow);
	credits[5].setString("Press S to view SCORES!!!");
	credits[5].setPosition(sf::Vector2f(width -500, height-100));


    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

        }
        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            std::cout<<"Escape was pressed."<<std::endl;
            music.pause();
            window.close();
            screenPtrMenu -> drawWindow(windowx);

        }
        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            std::cout<<"S was pressed."<<std::endl;
            music.pause();
            window.close();
            screenPtrScore -> drawWindow(windowx);

        }



     window.clear();
     window.draw(background);
	for (int i = 0; i < 6; i++)
	{
		window.draw(credits[i]);
	}
		window.display();

	}
}




