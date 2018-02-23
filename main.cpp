#include"sfml.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width-500 ,
    sf::VideoMode::getDesktopMode().height-150),"FlowCharting",sf::Style::Default);

    Sfml sfml(&window);

    while (window.isOpen())
    {
        sfml.eventCheck();//handle user input
        sfml.change(255,255,255); //blut

    }

    return 0;
}
