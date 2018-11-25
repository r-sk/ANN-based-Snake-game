//Header files
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <Screens.h>
#include <fstream>
#include "Menu.h"
#include "Game.h"
#include "Neural.h"
#include "Manual.h"


int main()
{
    std::cout<<"ACTIVITY LOG:"<<std:: endl;

    sf::RenderWindow window;    //Declaring and initializing the window

	Screens *screenPtrMenu;     //Screens is abstract class and is base class to Menu,Game,Credits,Score
                                //And creating pointer to object using abstract class

	Menu menu;                  //Creating menu Object of Menu class

	screenPtrMenu = &menu;      //Assigning address of menu obj to screenPtrMenu pointer

	screenPtrMenu -> drawWindow(window);    //Accessing drawWindow function of Menu class using arrow operator

    return 0;

}



