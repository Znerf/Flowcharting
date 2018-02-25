#include<string.h>
#include"sfml.h"
#include"menu.h"

void textAdder(Sfml* sfml,char str[20],int x, int y,int siz){

    static FontHandler a[1000];

    static int i=0;

    strcpy(a[i].text,str);
    a[i].x=x;
    a[i].y=y;
    i++;
    a[i].x=-1;

    sfml->fontUpdate(a,siz);


}


int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width-500 ,
    sf::VideoMode::getDesktopMode().height-150),"FlowCharting",sf::Style::Default);

    Sfml sfml(&window);
    MenuHandler menu(&sfml);

    while (window.isOpen())
    {
        sfml.eventCheck();//handle user input

        sfml.change(255,255,255); //blut

        menu.titleMenu();//textAdder(&sfml,"hi",4,5);


    }
    return 0;
}



