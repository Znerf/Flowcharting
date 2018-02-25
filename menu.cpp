class Sfml;
void textAdder(Sfml*,char[],int,int,int);

class MenuHandler{
    Sfml* sfml;

public:
    MenuHandler(Sfml* s){
        sfml=s;
    }


    void titleMenu(){
        textAdder(sfml,"File",1,0,15);
        textAdder(sfml,"Edit",5,0,15);
        textAdder(sfml,"Help",10,0,15);

    }


};

