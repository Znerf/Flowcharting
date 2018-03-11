
#include <iostream>
#include <SFML/Graphics.hpp>

class CheckPoint{
public:
    int x_product(sf::Vector2f a, sf::Vector2f b)
    {
        return ((a.x)*(b.y)-(a.y)*(b.x));
    }



    int get_side(sf::Vector2f a, sf::Vector2f b)
    {
        int x = x_product(a, b);

        if (x < 0)
            return 1;  //left
        else if (x > 0)
            return 0; //right
        else
            return -1;  //none
    }


    sf::Vector2f v_sub(sf::Vector2f a, sf::Vector2f b)
    {
        sf::Vector2f temp;
        temp.x = a.x-b.x;
        temp.y = a.y-b.y;
        return temp;
    }

    virtual bool checkPoint(sf::Vector2f , int ) =0;//n_vertices == number of vertices



};

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

class Process : public sf::Drawable,public CheckPoint
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

    void setOrigin()
    {
        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+5*Scale.y);
    }
public:
    sf::Vector2f getPosition(){
        return Position;
    }

    sf::RectangleShape r;

    sf::Font font;
    sf::Text text;


    Process()
    {
       // void sf::Transformable::setOrigin	(	const Vector2f & 	origin	)

        //cout << "rect: " << r.getSize().x << " , " << r.getSize().y << endl;
//        r.setSize(sf::Vector2f(150, 50)); //hve to update on  setstring
//        setOrigin();
//        cout << "rect: before: " << r.getGlobalBounds().width << " , " << r.getGlobalBounds().height << endl;
//        r.setScale(Scale);
//        //cout << "rect: " << r.getSize().x << " , " << r.getSize().y << endl;
//        //r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
//        cout << "rect: aftr: " << r.getGlobalBounds().width << " , " << r.getGlobalBounds().height << endl;
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
        setOrigin();
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
        setOrigin();
        r.setSize(sf::Vector2f(rsize));
        setOrigin();

//

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

    void getCornerCoordinates(sf::Vector2f *vertices)
    {
        Position = r.getPosition();
        sf::FloatRect Bounds = r.getGlobalBounds();

        vertices[0].x = (Position.x - (Bounds.width)/2);
        vertices[0].y = (Position.y + (Bounds.height)/2);

        vertices[1].x = (Position.x + (Bounds.width)/2);
        vertices[1].y = (Position.y + (Bounds.height)/2);

        vertices[2].x = (Position.x + (Bounds.width)/2);
        vertices[2].y = (Position.y - (Bounds.height)/2);

        vertices[3].x = (Position.x - (Bounds.width)/2);
        vertices[3].y = (Position.y - (Bounds.height)/2);
    }


    bool checkPoint(sf::Vector2f point,  int n_vertices=4) //n_vertices == number of vertices
    {
        sf::Vector2f vertices[4];
        getCornerCoordinates(vertices);
        //returns true if point lies inside the convexshape or false if outside the shape

        int previous_side = -1;
        for(int n = 0; n < n_vertices; n++)
        {
            sf::Vector2f a, b;
            a = vertices[n];
            b = vertices[(n+1)%n_vertices];

            sf::Vector2f affine_segment = v_sub(b, a);
            sf::Vector2f affine_point = v_sub(point, a);
            int current_side = get_side(affine_segment, affine_point);
             if (current_side ==  -1)
                 return false; //outside or over an edge

            else if (previous_side == -1) //first segment
                previous_side = current_side;

            else if (previous_side != current_side)
                return false;
        }

        return true;

    }
    Process clone(){
        return(*this);
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

    sf::Vector2f getPosition(){
        return Position;
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

    bool checkPoint(sf::Vector2f point)
    {
        //returns if the point is inside or outside, on the edge is concidered as outside
        sf::Vector2f center = e.getPosition();
        sf::Vector2f radius = e.getRadius();
        float v;

        v = pow(point.x - center.x ,2)/(pow(radius.x , 2)) +  pow(point.y - center.y ,2)/(pow(radius.y , 2));
        if(v < 1)
            return true;
        else
            return false;
    }
    Terminator clone(){
        return(*this);
    }

};


class Decision : public sf::Drawable,public CheckPoint
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

    sf::Vector2f getPosition(){
        return Position;
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

    void getCornerCoordinates(sf::Vector2f *vertices)
    {
        Position = shape.getPosition();
        float radius = shape.getRadius();

        vertices[0].x = Position.x;
        vertices[0].y = Position.y + radius;

        vertices[1].x = Position.x + radius;
        vertices[1].y = Position.y;

        vertices[2].x = Position.x;
        vertices[2].y = Position.y - radius;

        vertices[3].x = Position.x - radius;
        vertices[3].y = Position.y;
    }
    bool checkPoint(sf::Vector2f point, int n_vertices=4) //n_vertices == number of vertices
    {
        //returns true if point lies inside the convexshape or false if outside the shape
        sf::Vector2f vertices[4];
        getCornerCoordinates(vertices);
        int previous_side = -1;
        for(int n = 0; n < n_vertices; n++)
        {
            sf::Vector2f a, b;
            a = vertices[n];
            b = vertices[(n+1)%n_vertices];

            sf::Vector2f affine_segment = v_sub(b, a);
            sf::Vector2f affine_point = v_sub(point, a);
            int current_side = get_side(affine_segment, affine_point);
             if (current_side ==  -1)
                 return false; //outside or over an edge

            else if (previous_side == -1) //first segment
                previous_side = current_side;

            else if (previous_side != current_side)
                return false;
        }

        return true;

    }

    Decision clone(){
        return(*this);
    }
};

class InputOutput : public sf::Drawable,public CheckPoint
{
private:
    sf::Vector2f Padding = sf::Vector2f(20,10);
    sf::Vector2f Position = sf::Vector2f(0,0); //initial
    int deltax = 30;
    sf::Vector2f rsize;
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

    void setSize()
    {
            shape.setPoint(0, sf::Vector2f(deltax,0));
            shape.setPoint(1, sf::Vector2f(2*deltax+rsize.x,0));
            shape.setPoint(2, sf::Vector2f(deltax+rsize.x,rsize.y));
            shape.setPoint(3, sf::Vector2f(0,rsize.y));
    }

public:
    sf::ConvexShape shape;
    sf::Font font;
    sf::Text text;

    InputOutput()
    {
        shape.setPointCount(4); //4 is fixed here

        {
            setSize();
        }

        shape.setOutlineColor(text_outline_color);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(4/(Scale.x+Scale.y));

        setOrigin();
        shape.setScale(Scale);
        setOrigin();
        shape.setPosition(Position);


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

    sf::Vector2f getPosition(){
        return Position;
    }
    void setString(const sf::String &s)
    {
        str = s;
        text.setString(str);

        //sf::Vector2f rsize (2*Padding.x + text.getGlobalBounds().width , 2*Padding.y + text.getGlobalBounds().height);
        rsize.x = 2*Padding.x + text.getGlobalBounds().width;
        rsize.y = 2*Padding.y + text.getGlobalBounds().height;

        setOrigin();
        setSize();
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

    void getCornerCoordinates(sf::Vector2f *vertices)
    {
        vertices[0].x = Position.x - (rsize.x)/2 - deltax;
        vertices[0].y = Position.y + rsize.y/2;

        vertices[1].x = Position.x + (rsize.x)/2;
        vertices[1].y = Position.y + (rsize.y)/2;

        vertices[2].x = Position.x + (rsize.x)/2 + deltax;
        vertices[2].y = Position.y - rsize.y/2;

        vertices[3].x = Position.x - (rsize.x)/2;
        vertices[3].y = Position.y - (rsize.y)/2;
    }

    bool checkPoint(sf::Vector2f point, int n_vertices=4) //n_vertices == number of vertices
    {
        //returns true if point lies inside the convexshape or false if outside the shape
        sf::Vector2f vertices[4];

        getCornerCoordinates(vertices);

        int previous_side = -1;
        for(int n = 0; n < n_vertices; n++)
        {
            sf::Vector2f a, b;
            a = vertices[n];
            b = vertices[(n+1)%n_vertices];

            sf::Vector2f affine_segment = v_sub(b, a);
            sf::Vector2f affine_point = v_sub(point, a);
            int current_side = get_side(affine_segment, affine_point);
             if (current_side ==  -1)
                 return false; //outside or over an edge

            else if (previous_side == -1) //first segment
                previous_side = current_side;

            else if (previous_side != current_side)
                return false;
        }

        return true;

    }
    InputOutput clone(){
        return(*this);
    }
};

class sfLine : public sf::Drawable
{
public:
    sfLine():
        color(sf::Color::Black), thickness(2.f)
    {

    }

    void Init_(const sf::Vector2f& point1, const sf::Vector2f& point2)
    {
        sf::Vector2f direction = point2 - point1;
        sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

        sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

        vertices[0].position = point1 + offset;
        vertices[1].position = point2 + offset;
        vertices[2].position = point2 - offset;
        vertices[3].position = point1 - offset;

        for (int i=0; i<4; ++i)
            vertices[i].color = color;
    }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(vertices,4,sf::Quads);
    }

private:
    sf::Vertex vertices[4];
    float thickness;
    sf::Color color;
};


