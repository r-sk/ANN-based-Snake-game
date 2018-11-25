#ifndef MENU_H
#define MENU_H
#define MAX_NUMBER_OF_ITEMS 4
#include <Screens.h>


class Menu : public Screens                             //Menu is derived class of Screens class
{
    public:
        Menu();                                         //Default Constructor
        void drawWindow(sf::RenderWindow &window);      //Overriding the drawWindow function of base class
        void MoveUp();                                  //Using UP key to move up the selection
        void MoveDown();                                //Using DOWN key to move down the selection
        int GetPressedItem() { return selectedItemIndex; }  //Returns the index for the item selected
        ~Menu();                                            //Virtual Destructor
    protected:
        int selectedItemIndex;
         sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Text man;

};

#endif // MENU_H
