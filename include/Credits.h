#ifndef CREDITS_H
#define CREDITS_H

#include <Screens.h>
#define MAX_NUMBER_OF_ITEMS 3
using namespace sf;

class Credits : public Screens
{
    public:
        Credits();
        void drawWindow(sf::RenderWindow &window);
        virtual ~Credits();

    private:
        sf::Font font;
        sf::Text credits[6];
};

#endif // CREDITS_H
