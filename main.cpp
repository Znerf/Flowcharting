#include<string.h>
#include"sfml.h"
void textAdder(FontHandler* a){
    int i=0;
    strcpy(a[i].text,"File");
    a[i].x=50;
    a[i].y=50;
    i++;
    strcpy(a[i].text,"File");
    a[i].x=20;
    a[i].y=20;
    i++;
    a[i].x=-1;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width-500 ,
    sf::VideoMode::getDesktopMode().height-150),"FlowCharting",sf::Style::Default);

    Sfml sfml(&window);

    FontHandler a[1000];

    while (window.isOpen())
    {
        sfml.eventCheck();//handle user input

        sfml.change(255,255,255); //blut
        textAdder(a);
        sfml.fontUpdate(a);

    }
    return 0;
}



