#include <iostream>
#include <SFML/Graphics.hpp>


#include<sstream>
#include <cmath>
#include<cstring>
#include<vector>

#include "shape.h"
#include "text.h"


#define COLORCLICK Red

using namespace std;

class Arrow : public sf::Drawable
{
private:
    vector <sf::Vector2f> Points;
    sf::Color outline_color = sf::Color::Black;
    float thickness = 2.f;
    int tri_radius = 7;

    vector <sfLine> lines;
    sf::CircleShape triangle;

    int cou=0;
    void setOrigin()
    {
        triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
    }

    float find_rotation(sf::Vector2f pointA, sf::Vector2f pointB)
    {
        float delx = pointB.x - pointA.x;
        float dely = pointB.y - pointA.y;
        float angle = atan(dely/delx) *180/PI;

        if((delx >= 0 && dely >= 0) || (delx >= 0 && dely <= 0))
        {
            angle += 90;
        }
        else
        {
            angle -= 90;
        }

        return angle;

    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for(int i =0; i < lines.size(); i++)
        {
            target.draw(lines[i]);
        }

        target.draw(triangle);
    }

public:
    void setArrow(const vector <sf::Vector2f> &points)
    {
        Points = points;

        triangle.setRadius(tri_radius);
        triangle.setPointCount(3);
        triangle.setFillColor(outline_color);
        setOrigin();

        for(int i = 0; i< (Points.size() - 1); i++)
        {
            sfLine line;
            line.Init_(Points[i], Points[i+1]);
            lines.push_back(line);

        }


        //after drawing the lines

        sf::Vector2f midPoint;
        midPoint.x = (Points[Points.size() - 1].x + Points[Points.size() - 2].x)/2.0;
        midPoint.y = (Points[Points.size() - 1].y + Points[Points.size() - 2].y)/2.0;

        triangle.setPosition(midPoint);

//        statcic int i = 0;

        if(cou == 0)
        {
            float angle = find_rotation(Points[Points.size() - 2], Points[Points.size() - 1]);
            triangle.rotate(angle);
          //  cout << "Called" << endl;

            cou++;
      }



    }

    void setLine(const vector <sf::Vector2f> &points)
    {
        Points = points;

        triangle.setRadius(tri_radius);
        triangle.setPointCount(3);
        triangle.setFillColor(outline_color);
        setOrigin();

        for(int i = 0; i< (Points.size() - 1); i++)
        {
            sfLine line;
            line.Init_(Points[i], Points[i+1]);
            lines.push_back(line);

        }
    }

};



class Run{
    vector<Process> process;
    vector<Terminator> terminator;
    vector<Decision> decision;
    vector<InputOutput> inputOutput;

    enum shape{DECISION,TERMINATOR,INPUTOUTPUT,PROCESS,NONE};

    int pro=-1,ter=-1,dec=-1,inp=-1;

    shape clickClass=NONE;
    int clicknumber=0;


    //temprorary variables
    Process temProcess;
    Terminator temTerminator;
    Decision temDecision;
    InputOutput temInputOutput;

    Process debugger;

    sf::RenderWindow* window;
    sf::RenderWindow win;
    string st;

    bool isDecision=false,isProcess=false,isTerminator=false,isInputOutput=false;

    bool isChangeMode=false,isArrow=false;
    bool isScreenshot=false;
   // Decision shape3;
    int a=0;

    vector<sf::Vector2f> arrowX;
    //shape shapeTem[1];
    //int shapeNumber[1];
//    Arrow temArrow;

    Arrow sha;
    vector<Arrow> arrow;





public:
    Run(sf::RenderWindow* windo){
        window= windo;

       debugger.setPosition(sf::Vector2f(60,590));
       debugger.setString("");

       temVectorReset();
    }

    void temVectorReset(){
        temProcess.setString("Place shape in screen");
        temDecision.setString("Place shape in screen");
        temInputOutput.setString("Place shape in screen");
        temTerminator.setString("Place shape in screen");

    }

    void resetAll(){ //is pressed checked
        isProcess=false;
        isDecision=false;
        isTerminator=false;
        isInputOutput=false;
    }

    void clear(){

        window->clear(sf::Color::White);

    }

    float cursorX(){
        return sf::Mouse::getPosition(*window).x;
    }
    float cursorY(){
        return sf::Mouse::getPosition(*window).y;
    }


    void hangingIcon(){

        float Mx = cursorX();
        float My = cursorY();
//
//        if(isArrow){
//      //      temArrow())
//        }
        if(isProcess==true){
                temProcess.setPosition(sf::Vector2f(Mx,My));
                //temProcess.setString("Place shape in screen");
                temProcess.setColor(sf::Color(0,255,255));
                window->draw(temProcess);

            }
            else if(isTerminator==true){
                temTerminator.setPosition(sf::Vector2f(Mx,My));
                //temTerminator.setString("Place shape in screen");
                temTerminator.setColor(sf::Color(0,255,255));
                window->draw(temTerminator);

            }
            else if(isDecision==true){
                temDecision.setPosition(sf::Vector2f(Mx,My));
               // temDecision.setString("Place shape in screen");
                temDecision.setColor(sf::Color(0,255,255));
                window->draw(temDecision);

            }
            else if(isInputOutput==true){
                temInputOutput.setPosition(sf::Vector2f(Mx,My));
              //  temInputOutput.setString("Place shape in screen");
                temInputOutput.setColor(sf::Color(0,255,255));
                window->draw(temInputOutput);

            }

    }
    void handleKeyboard(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) (*window).close();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            resetClickClass();
            isDecision=true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            isTerminator=true;
            resetClickClass();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            resetClickClass();
            isProcess=true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            isInputOutput=true;
            resetClickClass();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
            if(clickClass!=NONE){
                switch(clickClass){
                    case DECISION:
                        arrowX.push_back(decision[clicknumber].getPosition());
                       // cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
                        break;
                    case TERMINATOR:
                        arrowX.push_back(terminator[clicknumber].getPosition());
                        //cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
                        break;
                    case PROCESS:
                        arrowX.push_back(process[clicknumber].getPosition());
                        //cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
                        break;
                    case INPUTOUTPUT:
                        arrowX.push_back(inputOutput[clicknumber].getPosition());
                        //cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;

                }

                isArrow=true;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
            isScreenshot=true;


        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
            if(clickClass!=NONE) {
                isChangeMode=true;

                switch(clickClass){
                    case DECISION:
                        temDecision=decision[clicknumber].clone();
                        isDecision=true;
                        break;
                    case TERMINATOR:
                        temTerminator=terminator[clicknumber].clone();
                        isTerminator=true;
                        break;
                    case PROCESS:
                        temProcess=process[clicknumber].clone();
                        isProcess=true;
                        break;
                    case INPUTOUTPUT:
                        temInputOutput=inputOutput[clicknumber].clone();
                        isInputOutput=true;
                        break;

                }
            }
        }
    }


    void eventHandle(){
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

        }

        handleMouse();


        //keyboard hndling
        handleKeyboard();



    }

    void resetClickClass(){
        clickClass=NONE;
        setColorBlack();
    }

    void handleMouse(){

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left));

            if(isArrow == true){
                    //asdfsajdfasjdfhkhdf

                if(dec>-1){
                    arrowX.push_back(decision[dec].getPosition());
                    isArrow=false;
                    sha.setArrow(arrowX);
                    arrow.push_back(sha);
                    arrowX.clear();
                    cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
//                     if(arrowX.size()>1){
//                        sha.setArrow(arrowX);
//                        (*window).draw(sha);
//                    }

                }else if(ter>-1){

                    arrowX.push_back(terminator[ter].getPosition());

                    cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;

                    sha.setArrow(arrowX);
                    arrowX.clear();
                    arrow.push_back(sha);
//                     if(arrowX.size()>1){
//                        sha.setArrow(arrowX);
//                        (*window).draw(sha);
//                    }
                    isArrow=false;
                }
                else if(inp>-1){
                    arrowX.push_back(inputOutput[inp].getPosition());

                    sha.setArrow(arrowX);
                    arrow.push_back(sha);
                    arrowX.clear();

                    cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
//                     if(arrowX.size()>1){
//                        sha.setArrow(arrowX);
//                        (*window).draw(sha);
//                    }
                    isArrow=false;
                }else if(pro>-1){

                    arrowX.push_back(process[pro].getPosition());

                    sha.setArrow(arrowX);
                    arrow.push_back(sha);
                    cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
                    sha.setArrow(arrowX);

//                    if(arrowX.size()>1){
//                        sha.setArrow(arrowX);
//                        (*window).draw(sha);
//                    }
                    isArrow=false;
                }
                else{
                    arrowX.push_back(sf::Vector2f(cursorX(),cursorY()));
                    cout<<arrowX.back().x<<" "<<arrowX.back().y<<endl;
                }
                //  isArrow=false;
            } else if(dec>-1){

                if(clickClass ==NONE ){
                        decision[dec].setColor(sf::Color::COLORCLICK);
                        clicknumber=dec;
                        clickClass=DECISION;

                }else if(clickClass==DECISION && clicknumber==dec){
                    TextWindow edit;
                    string str =edit.run("Decision rename");
                    decision[dec].setString(str);
                    clickClass=NONE;
                    setColorBlack();
                }


            }else if(ter>-1){
                if(clickClass ==NONE ){
                    terminator[ter].setColor(sf::Color::COLORCLICK);
                    clicknumber=ter;
                    clickClass=TERMINATOR;

                }else if(clickClass==TERMINATOR && clicknumber==ter){
                    TextWindow edit;
                    string str =edit.run("terminator rename");
                    terminator[ter].setString(str);
                    clickClass=NONE;
                    setColorBlack();
                };

            }else if(inp>-1){
                if(clickClass ==NONE ){

                    inputOutput[inp].setColor(sf::Color::COLORCLICK);
                    clicknumber=inp;
                    clickClass=INPUTOUTPUT;

                }else if(clickClass==INPUTOUTPUT && clicknumber==inp){
                    TextWindow edit;
                    string str =edit.run("input rename");
                    inputOutput[inp].setString(str);
                    clickClass=NONE;
                    setColorBlack();
                };
            }else if(pro>-1){

                if(clickClass ==NONE ){
                    process[pro].setColor(sf::Color::COLORCLICK);
                    clicknumber=pro;
                    clickClass=PROCESS;

                }else if(clickClass==PROCESS && clicknumber==pro){
                    TextWindow edit;
                    string str =edit.run("process rename");
                 //   str+="hi";
                    process[pro].setString(str);



                    clickClass=NONE;
                    setColorBlack();
                };
            }else{
                if(isArrow!=true){
                    clickClass=NONE;
      //          clicked = "a";
                    setColorBlack();
                }
            }



        }

    }


    void mouseRight(){
        if(clickClass!=NONE){
             if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {

                while(sf::Mouse::isButtonPressed(sf::Mouse::Right));

                if(dec>-1){
                    clickClass = NONE;
                    decision.erase (decision.begin()+clicknumber);


//                    setColorBlack();

                }else if(ter>-1){
                    terminator.erase (terminator.begin()+clicknumber);
                    clickClass = NONE;
  //                  setColorBlack();
                }else if(inp>-1){
                    inputOutput.erase (inputOutput.begin()+clicknumber);
                    clickClass = NONE;
    //                setColorBlack();

                }else if(pro>-1){
                    process.erase (process.begin()+clicknumber);
                    clickClass = NONE;
      //              setColorBlack();

                }


            }
        }
    }

    void setColorBlack(){
        for(int count=0;count<process.size();count++){
            process[count].setColor(sf::Color::Black);

          //  exit(0);
        }
//
        for(int count=0;count<decision.size();count++){
            decision[count].setColor(sf::Color::Black);

        }
        for(int count=0;count<terminator.size();count++){
            terminator[count].setColor(sf::Color::Black);

        }

        for(int count=0;count<inputOutput.size();count++){
            inputOutput[count].setColor(sf::Color::Black);


        }
//        dec=-1;
//        inp=-1;
//
//        ter=-1;
//        pro=-1;

    }

    void logic(){
        eventHandle();


        clear();
        if(isDecision==true|| isTerminator==true || isProcess==true|| isInputOutput==true){

            hangingIcon();
            a=1; // a means is something hovering in pointer which is true here;

            //for adding object
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                if(isChangeMode==false){
                    TextWindow textWindow;
                    st=textWindow.run("Input");
                    //st+="try";

                }
                a=0; // shuldnot hover pointer now
                eventHandle();
                setVectorField();
                //isAny=false;
                resetAll();
            }

        }

      //  cout<<(int)process.size();
        if(arrowX.size()>1){
                sha.setLine(arrowX);
                (*window).draw(sha);
        }
        window->draw(debugger);

        drawAll();
        detectobj();
        mouseRight();


    }


    void setVectorField(){
            if(isProcess==true){
         //       rocess.resize(process.size()+1);
                temProcess.setColor(sf::Color::Black);
                if(isChangeMode==true){

                    process[clicknumber]=(temProcess).clone();
                    isChangeMode=false;
                }else {
                    temProcess.setString(st);
                    process.push_back(temProcess);
                }
            }
            else if(isTerminator==true){
         //       rocess.resize(process.size()+1);

                temTerminator.setColor(sf::Color::Black);
                if(isChangeMode==true){
                    terminator[clicknumber]=temTerminator.clone();
                    isChangeMode=false;
                }else{

                        temTerminator.setString(st);
                        terminator.push_back(temTerminator);

                }

            }
            else if(isDecision==true){
         //       rocess.resize(process.size()+1);

                temDecision.setColor(sf::Color::Black);
                if(isChangeMode==true){
                    decision[clicknumber]=temDecision.clone();
                    isChangeMode=false;
                }else {

                    temDecision.setString(st);
                    decision.push_back(temDecision);

                }

            }else if(isInputOutput==true){
         //       rocess.resize(process.size()+1);
                temInputOutput.setColor(sf::Color::Black);

                if(isChangeMode==true){
                    inputOutput[clicknumber]=temInputOutput.clone();
                    isChangeMode=false;
                }else{
                    temInputOutput.setString(st);
                    inputOutput.push_back(temInputOutput);

                }

            }

            temVectorReset();


    }

    void detectobj(){
        float px=cursorX();
        float py=cursorY();
        sf::Vector2f coord = sf::Vector2f(px,py);

        for(int count=0;count<process.size();count++){
           // process[count].setColor(sf::Color::Black);

            if(process[count].checkPoint(coord)==true){
                string stringy=to_string((int)px)+" "+to_string(count);
                debugger.setString("process "+stringy);
                pro=count;
          //      clicknumber=pro;
                break;
            }else pro=-1;
          //  exit(0);
        }
//
        for(int count=0;count<decision.size();count++){
            if(decision[count].checkPoint(coord)==true){
                string stringy=to_string((int)px)+" "+to_string(count);
                debugger.setString("Decision "+stringy);
                dec=count;
            //    clicknumber=dec;
                break;
            }else dec=-1;
  //          exit(0);
        }
        for(int count=0;count<terminator.size();count++){
            if(terminator[count].checkPoint(coord)==true){
                string stringy=to_string((int)px)+" "+to_string(count);
                debugger.setString("term "+stringy);
                ter=count;
              //  clicknumber=ter;
                break;
            }else ter=-1;
        }

        for(int count=0;count<inputOutput.size();count++){

            if(inputOutput[count].checkPoint(coord)==true){
                string stringy=to_string((int)px)+" "+to_string(count);
                debugger.setString("input "+stringy);
                inp=count;
               // clicknumber=inp;
                break;
            }else inp=-1;
          //  exit(0);
        }


    }
    void close(){
        (*window).close();
    }
    void drawAll(){

        for(int count=0;count<arrow.size();count++){
            window->draw(arrow[count]);
        }

        for(int count=0;count<process.size();count++){
           // process[count].setColor(sf::Color::Black);
            window->draw(process[count]);

        }
//
        for(int count=0;count<decision.size();count++){
            //decision[count].setColor(sf::Color::Black);
            window->draw(decision[count]);
        }
        for(int count=0;count<terminator.size();count++){
            //terminator[count].setColor(sf::Color::Black);
            window->draw(terminator[count]);
        }

        for(int count=0;count<inputOutput.size();count++){
            //inputOutput[count].setColor(sf::Color::Black);

            window->draw(inputOutput[count]);
          //  exit(0);
        }

        if(isScreenshot){
            screenshot();
        }
    }


    void screenshot(){
        static int num=-1;
        num++;
        sf::Image img = (*window).capture();//tex.copyToImage();
        img.saveToFile("screenshot/test"+to_string(num)+".png");
        isScreenshot=false;
    }
};







int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600,32), "SFML works!");

    Run controlObject(&window);

    while (window.isOpen())
    {

        controlObject.logic();

        window.display();
    }

    return 0;
}
