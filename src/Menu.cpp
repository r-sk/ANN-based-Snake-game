#include "Menu.h"
#include"Game.h"
#include"Credits.h"
#include "Manual.h"
#define MAX_NUMBER_OF_ITEMS 4


Menu::Menu()
{//constructor
}
Menu::~Menu()
{
    //Destructor
}


/** **/
void Menu::drawWindow(sf::RenderWindow &window)
{
       /** **/
        sf:: RenderWindow windowx;
        Game game;
        Credits credits;
        Manual manual;
        Screens *screenPtrGame,*screenPtrCredits, *screenPtrManual;
        screenPtrGame = &game;
        screenPtrCredits = &credits;
        screenPtrManual= &manual;



	/**Getting without width and height and Creating Menu**/
	window.create(sf::VideoMode(1024, 768), "Gaming with A.I");
	float width =window.getSize().x;
	float height =window.getSize().y;

	 /**Texture and Sprite for background image**/
    sf :: Texture t1;
	t1.loadFromFile("alpha1.jpg");
	sf:: Sprite  background(t1);

	/**Play Background music**/
	sf::Music music;
	music.openFromFile("Stranger_Things1.ogg");
    music.play();

	/**Loading font**/
    if (!font.loadFromFile("mexcel3D.ttf"))
    {
         //error
    }
    /**Writing on the screen**/
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Neural");
	menu[0].setPosition(sf::Vector2f(width / 2.3, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Manual");
	menu[1].setPosition(sf::Vector2f(width / 2.3, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Credits");
	menu[2].setPosition(sf::Vector2f(width / 2.3, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));


	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));




	selectedItemIndex = 0;
    enum buttons {neu,manu,cre,exi};

   /** **/
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up://up
					MoveUp();
					break;

				case sf::Keyboard::Down: //down
					MoveDown();
					break;


				case sf::Keyboard::Return: //hit enter
					switch (GetPressedItem())
					{
					case neu:
                        std::cout << "Neural Mode Selected" << std::endl;
                        music.stop();
                        window.close();
                        screenPtrGame -> drawWindow(window);
                        break;
                    case manu:
                        std::cout << "Manual Mode Selected" << std::endl;
                        music.stop();
                        window.close();
                        screenPtrManual -> drawWindow(window);
                        break;
					case cre:
						std::cout << "Credits Selected" << std::endl;
                        music.stop();
						window.close();
                        screenPtrCredits -> drawWindow(window);
						break;
					case exi:
						std::cout << "Windows Exited !!" << std::endl;
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
        window.draw(background);
        for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        {
            window.draw(menu[i]);
        }

		window.display();
	}

}
/** **/
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
/** **/
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

