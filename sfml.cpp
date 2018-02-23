#include <SFML/Graphics.hpp>

class Sfml{
    sf::RenderWindow * window;

    public:
        Sfml(sf::RenderWindow * w){
            window=w;
        }

        void close(){  //for closing window
                (*window).close();
        }

        void change(int i, int j, int k){ // blut effect
            (*window).clear(sf::Color(i, j, k));
            (*window).display();
        }

        void eventCheck(){
            sf::Event event;
            while ((*window).pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    this->close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) (*window).close();

            }
        }
};


