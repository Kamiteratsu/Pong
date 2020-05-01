#include <Grapic.h>
using namespace grapic;

const int DIMW = 500;

struct Data
{
    int x1,y1;
    int x2,y2;
    int etat;       // 0=aucun carre, 1=selection en cours, 2=un carre
};

void init(Data& d)
{
    d.etat = 0;
}

void draw(Data& d)
{
    color(255,255, 0);
    fontSize(14);
    print( 10, 10, "Press the left mouse button and drag the mouse to draw a square");
    //if (d.etat) {
        color( 255, 255, 128);
        rectangle( d.x1, d.y1, d.x2, d.y2);
    //}
    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        int x,y;
        mousePos(x, y);
        if((x >= d.x1 && x <= d.x2) && (y >= d.y1 && y <= d.y2))
            d.etat = 1;
        if (d.etat==1) {
          d.x1 = x;
          d.y1 = y;
          d.x2 = d.x1+60;
          d.y2 = d.y1+60;
        }
        /*if (d.etat!=1)
        {
            d.etat = 1;
            d.x1 = x;
            d.y1 = y;
        }
        else
        {
            d.x2 = x;
            d.y2 = y;
        }*/
    }
    else
      d.etat = 0;
    /*else
    {
        if (d.etat==1) d.etat=2;
    }*/

}

int main(int , char** )
{
    Data dat;
    bool stop=false;
	winInit("Tutorials", DIMW, DIMW);
	init(dat);
    backgroundColor( 100, 50, 200 );
  dat.x1 = dat.y1 = 30;
  dat.x2 = dat.x1+60;
  dat.y2 = dat.y1+60;
	while( !stop )
    {
        winClear();
        draw(dat);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}
