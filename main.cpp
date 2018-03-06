#include <iostream>
#include <cmath>
#include<sstream>
#include <SFML/Graphics.hpp>

using namespace std;


class EllipseShape : public sf::Shape
{
public :

    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0)) :

    m_radius(radius)
    {
        update();
    }

    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

    virtual unsigned int getPointCount() const
    {
        return 50; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(unsigned int index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

private :

    sf::Vector2f m_radius;
};

class Process : public sf::Drawable
{
private:
    sf::Vector2f Padding = sf::Vector2f(20,10);
    sf::Vector2f Position = sf::Vector2f(0,0); //initial
    sf::Vector2f Scale = sf::Vector2f(1,1);
    sf::Color text_outline_color = sf::Color::Black;
    sf::String str  = "Text_Here";

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // You can draw other high-level objects
            target.draw(r, states);
            target.draw(text, states);
        }

public:

    sf::RectangleShape r;
    sf::Font font;
    sf::Text text;

    Process()
    {
       // void sf::Transformable::setOrigin	(	const Vector2f & 	origin	)

        //cout << "rect: " << r.getSize().x << " , " << r.getSize().y << endl;
        r.setSize(sf::Vector2f(150, 50)); //hve to update on  setstring
        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
        cout << "rect: before: " << r.getGlobalBounds().width << " , " << r.getGlobalBounds().height << endl;
        r.setScale(Scale);
        //cout << "rect: " << r.getSize().x << " , " << r.getSize().y << endl;
        //r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
        cout << "rect: aftr: " << r.getGlobalBounds().width << " , " << r.getGlobalBounds().height << endl;
        r.setPosition(Position);               //mouse
        r.setOutlineThickness(4/(Scale.x+Scale.y));
        r.setOutlineColor(text_outline_color);    //depends on selection state
        r.setFillColor(sf::Color::White);



        if (!font.loadFromFile("Roboto-Regular.ttf"))
        {
            // error...
            std::cout << "Error loading font" << std::endl;
        }

        text.setFont(font); // font is a sf::Font

        text.setString(str);      // have to be user selectable

        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7)); // in pixels, not points! // depends on scale
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
        // set the color
        text.setColor(text_outline_color);
        text.setPosition(Position);
        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    }
    void setString(const sf::String &s)
    {
        str = s;
        //text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
        text.setString(str);

        sf::Vector2f rsize(2*Padding.x + text.getGlobalBounds().width , 2*Padding.y + text.getGlobalBounds().height);
        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
        r.setSize(sf::Vector2f(rsize));
        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);

//
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);


    }

    void setPosition(const sf::Vector2f &pos)
    {
         Position = pos;
         r.setPosition(Position);
         text.setPosition(Position);
    }
//    void setScale(const sf::Vector2f &sc)
//    {
//        Scale = sc;
//        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
//        r.setScale(Scale);
//        r.setOutlineThickness(4/(Scale.x+Scale.y));
//        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
//        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7));
//        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
//    }
    void setColor(const sf::Color color)
    {
        text_outline_color = color;
        r.setOutlineColor(text_outline_color);
        text.setColor(text_outline_color);
    }
};


class Terminator : public sf::Drawable
{
private:
    sf::Vector2f Padding = sf::Vector2f(30,10);
    sf::Vector2f Position = sf::Vector2f(0,0); //initial
    sf::Vector2f Scale = sf::Vector2f(1,1);
    sf::Color text_outline_color = sf::Color::Black;
    sf::String str  = "Text_Here";

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // You can draw other high-level objects
            target.draw(e, states);
            target.draw(text, states);
        }

    void setOrigin()
    {
        e.setOrigin(e.getGlobalBounds().width/2, e.getGlobalBounds().height/2);
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+5*Scale.y);
    }

public:

    EllipseShape e;
    sf::Font font;
    sf::Text text;

    Terminator()
    {
        e.setRadius(sf::Vector2f(70,50));
        setOrigin();
        e.setScale(Scale);
        setOrigin();
        e.setPosition(Position);
        e.setOutlineThickness(4/(Scale.x+Scale.y));
        e.setOutlineColor(text_outline_color);
        e.setFillColor(sf::Color::White);


        if (!font.loadFromFile("Roboto-Regular.ttf"))
            std::cout << "Error loading font" << std::endl;

        text.setFont(font);

        setString(str);

        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7)); // in pixels, not points! // depends on scale
        setOrigin();

        text.setColor(text_outline_color);
        text.setPosition(Position);
        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    }

    void setString(const sf::String &s)
    {
        str = s;
        text.setString(str);

        sf::Vector2f rsize(Padding.x + text.getGlobalBounds().width/2 , Padding.y + text.getGlobalBounds().height/2);
        setOrigin();

        e.setRadius(rsize);
        setOrigin();
    }

    void setPosition(const sf::Vector2f &pos)
    {
         Position = pos;
         e.setPosition(Position);
         text.setPosition(Position);
    }
////    void setScale(const sf::Vector2f &sc)
////    {
////        Scale = sc;
////        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
////        r.setScale(Scale);
////        r.setOutlineThickness(4/(Scale.x+Scale.y));
////        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
////        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7));
////        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
////    }
    void setColor(const sf::Color color)
    {
        text_outline_color = color;
        e.setOutlineColor(text_outline_color);
        text.setColor(text_outline_color);
    }
};


class Decision : public sf::Drawable
{
private:
    sf::Vector2f Padding = sf::Vector2f(30,30);
    sf::Vector2f Position = sf::Vector2f(0,0); //initial
    sf::Vector2f Scale = sf::Vector2f(1,1);
    sf::Color text_outline_color = sf::Color::Black;
    sf::String str  = "Text_Here";

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // You can draw other high-level objects
            target.draw(shape, states);
            target.draw(text, states);
        }

    void setOrigin()
    {
        shape.setOrigin(shape.getGlobalBounds().width/2, shape.getGlobalBounds().height/2);
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+5*Scale.y);
    }

public:
    sf::CircleShape shape;
    sf::Font font;
    sf::Text text;

    Decision()
    {
        shape.setRadius(40);
        shape.setPointCount(4); //4 is fixed here
        setOrigin();
        shape.setScale(Scale);
        setOrigin();
        shape.setPosition(Position);
        shape.setOutlineThickness(4/(Scale.x+Scale.y));
        shape.setOutlineColor(text_outline_color);
        shape.setFillColor(sf::Color::White);


        if (!font.loadFromFile("Roboto-Regular.ttf"))
            std::cout << "Error loading font" << std::endl;

        text.setFont(font);

        setString(str);

        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7)); // in pixels, not points! // depends on scale
        setOrigin();

        text.setColor(text_outline_color);
        text.setPosition(Position);
        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    }

    void setString(const sf::String &s)
    {
        str = s;
        text.setString(str);

        float rsize(Padding.x + text.getGlobalBounds().width/2);
        setOrigin();
        shape.setRadius(rsize);
        setOrigin();
    }

    void setPosition(const sf::Vector2f &pos)
    {
         Position = pos;
         shape.setPosition(Position);
         text.setPosition(Position);
    }
////    void setScale(const sf::Vector2f &sc)
////    {
////        Scale = sc;
////        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
////        r.setScale(Scale);
////        r.setOutlineThickness(4/(Scale.x+Scale.y));
////        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
////        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7));
////        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
////    }
    void setColor(const sf::Color color)
    {
        text_outline_color = color;
        shape.setOutlineColor(text_outline_color);
        text.setColor(text_outline_color);
    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");



    Process shape;
    cout << "width: " << shape.text.getGlobalBounds().width << " height: " << shape.text.getGlobalBounds().height << endl;
    //shape.setColor(sf::Color::Red);
    //shape.setPosition(sf::Vector2f(500,400));
    //shape.setScale(sf::Vector2f(2,2));
    //shape.setPosition(sf::Vector2f(500,400));
    shape.setString("My name is Sajil Awale");
    shape.setPosition(sf::Vector2f(400,400));

    Terminator shape2;
    //shape2.setColor(sf::Color::Red);
    shape2.setPosition(sf::Vector2f(500,400));
    //shape2.setScale(sf::Vector2f(2,2));
    shape2.setPosition(sf::Vector2f(200,300));
    shape2.setString("Start");
    int a=0;
    bool isAny=false;
    Decision shape3;
    while (window.isOpen())
    {
        //window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            isAny=true;

        }

        window.clear(sf::Color::White);
        window.draw(shape);
        window.draw(shape2);

        if(a==1)window.draw(shape3);

        if(isAny==true){


            float Mx = sf::Mouse::getPosition(window).x;
            float My = sf::Mouse::getPosition(window).y;
            stringstream ss,s2;
            ss << Mx;
            s2 << My;

            string str = ss.str();
            string str2 = s2.str();

            shape3.setString(str +" "+str2);//"if(sajil == you");
            shape3.setPosition(sf::Vector2f(Mx,My));

            a=1;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                isAny=false;


            }

        }

        window.display();
    }

    return 0;
}
