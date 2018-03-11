#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;

class TextWindow{

    sf::Event event2;
    string st;
    sf::String text;
    sf::Font font;
    sf::Text outText;

public:

    string run(string name){
        sf::VideoMode VBMode(300, 300, 32);
        sf::RenderWindow inputField(VBMode, name);

    //event handling
        while (inputField.isOpen())
        {
            while (inputField.pollEvent(event2))
            {

                if (event2.type == sf::Event::Closed)
                    inputField.close();
                                   // In event loop...

                if (event2.type == sf::Event::TextEntered)
                {
                    // Handle ASCII characters only
                    if (event2.text.unicode < 128)
                    {
                        if(event2.text.unicode==8) st=st.substr(0,st.size()-1);
                        else if (event2.text.unicode==13) {
                            inputField.close();

                            return st;
                        }
                        else if (event2.text.unicode >= 32 &&event2.text.unicode <= 126 ) st += (event2.text.unicode);
                    }
                }


            }

            inputField.clear(sf::Color::White);

            fontControl();

            display(inputField);
        }
    }

    void display(sf::RenderWindow& inputField){
        inputField.draw(outText);
        inputField.display();
    }
    void fontControl(){

        if (!font.loadFromFile("arial.ttf"))
        {
            cout<<"error in loading font";
            exit(0);
        }

        // select the font
        outText.setFont(font); // font is a sf::Font
        // set the string to display
        outText.setString(st);
        // set the character size
        outText.setCharacterSize(15); // in pixels, not points!
        // set the color
        outText.setColor(sf::Color::Black);



    }

};



