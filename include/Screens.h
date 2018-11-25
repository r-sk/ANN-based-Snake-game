#ifndef SCREENS_H
#define SCREENS_H
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

class Screens
{
    public:
        Screens();
        virtual void drawWindow(sf::RenderWindow &window) = 0; //Pure Virtual function
        virtual ~Screens();

    protected:
        float width;
        float height;

};

#endif // SCREENS_H
