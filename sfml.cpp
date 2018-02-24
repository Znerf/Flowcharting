#include <iostream>
#include <SFML/Graphics.hpp>
class FontHandler;
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
        }

        void fontUpdate(){
            sf::Font font;
            if (!font.loadFromFile("a.ttf"))
            {
                std::cout<<"Can't load file"<<std::endl;

            }
            sf::Text text;

            // select the font
            text.setFont(font); // font is a sf::Font

            // set the string to display
            text.setString("Hello world");
            // set the character size
            text.setCharacterSize(24); // in pixels, not points!

            // set the color
            text.setColor(sf::Color::Red);
            // set the text style
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            //
            //...
            float SCRWIDTH=sf::VideoMode::getDesktopMode().width-500;
            float SCRHEIGHT=sf::VideoMode::getDesktopMode().height-150;
            // inside the main loop, between window.clear() and window.display()
            text.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f));

            (*window).draw(text);
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




