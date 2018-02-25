#include <iostream>
#include <SFML/Graphics.hpp>
#include<string.h>


class FontHandler{
public:
        char text[12]="";
        int x;
        int y;

};


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

        void fontUpdate(FontHandler* a,int siz){

            sf::Font font;
            if (!font.loadFromFile("font/a.ttf"))
            {
                std::cout<<"Can't load file"<<std::endl;

            }

            int i=0;
            sf::Text text;

                // select the font
            text.setFont(font); // font is a sf::Font

            while((a[i].x)!=-1){

                // set the string to display
                text.setString(a[i].text);
                // set the character size
                text.setCharacterSize(siz); // in pixels, not points!

                // set the color
                text.setColor(sf::Color::Black);

                int SCRWIDTH=(a[i].x)*(sf::VideoMode::getDesktopMode().width-500)/100;
                int SCRHEIGHT=(a[i].y)*(sf::VideoMode::getDesktopMode().height-150)/100;

                // inside the main loop, between window.clear() and window.display()

                text.setPosition(sf::Vector2f(SCRWIDTH,SCRHEIGHT));

                (*window).draw(text);

                i++;
            }
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




