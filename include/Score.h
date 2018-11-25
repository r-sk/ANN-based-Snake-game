#ifndef SCORE_H
#define SCORE_H

#include <Screens.h>


class Score : public Screens
{
    public:
        Score();
        void drawWindow(sf::RenderWindow &window);
        virtual ~Score();
    private:
            sf::Font font;
            sf::Text score[3];
};

#endif // SCORE_H
