

#include <Grapic.h>

#define CORRECTION

using namespace grapic;
using namespace std;

const int WIN_DIM_X = 300;
const int WIN_DIM_Y = 300;

struct CaseGrille
{
    int mines;
    bool decouverte;
    bool drapeau;
};

struct Jeu
{
    CaseGrille g[100][100];
	int dx,dy;
	int nb_mines;
	int nb_cases_a_decouvrir;
	bool perdu;
	Image im_mine;
	Image im_drapeau;
};


void placeMines(Jeu& jj)
{
	// A faire

}


void compteMinesVoisines(Jeu& jj)
{
	// A faire

}



	// A faire




void init(Jeu& jj)
{
	jj.dx = 10;
	jj.dy = 10;
	jj.im_mine = image("data/mines/mine.png");
	jj.im_drapeau = image("data/mines/flag.png");
	int i,j;
	for(i=0;i<jj.dx;++i)
        for(j=0;j<jj.dy;++j)
        {
            jj.g[i][j].mines = 0;
            jj.g[i][j].decouverte = false;
            jj.g[i][j].drapeau = false;
        }
    jj.nb_mines = 4;
    jj.nb_cases_a_decouvrir = jj.dx * jj.dy - jj.nb_mines;
    jj.perdu = false;

    placeMines(jj);
    compteMinesVoisines(jj);
}

int caseVersEcranX(const Jeu& jj, int x)
{
    return int(x * WIN_DIM_X/jj.dx);
}

int caseVersEcranY(const Jeu& jj, int y)
{
    return int(y * WIN_DIM_Y/jj.dy);
}

int ecranVersCaseX(const Jeu& jj, int x)
{
    return int(x / (WIN_DIM_X/jj.dx));
}

int ecranVersCaseY(const Jeu& jj, int y)
{
    return int(y / (WIN_DIM_Y/jj.dy));
}


void draw(Jeu& jj)
{
	int i,j;
	backgroundColor( 100, 80, 200, 255 );

	color(255, 0, 0);
	grid(0, 0, WIN_DIM_X-1, WIN_DIM_Y-1, jj.dx, jj.dy);

	color(255, 255, 0);
	fontSize(15);

	// A faire



	for (i = 0; i < jj.dx; ++i)
	{
        print( caseVersEcranX(jj,i)+10, caseVersEcranY(jj,2)+5, i);
        image_draw( jj.im_mine, caseVersEcranX(jj,2) + 5, caseVersEcranY(jj,i) + 5, WIN_DIM_X/jj.dx - 10, WIN_DIM_Y/jj.dy -10);
	}

	if (isMousePressed(SDL_BUTTON_LEFT))
	{
		int x, y, i, j;
		mousePos(x, y);

        i = ecranVersCaseX(jj,x);
        j = ecranVersCaseY(jj,y);

        image_draw( jj.im_mine, caseVersEcranX(jj,i) + 5, caseVersEcranY(jj,j) + 5, WIN_DIM_X/jj.dx - 10, WIN_DIM_Y/jj.dy -10);
	}

	if (isMousePressed(SDL_BUTTON_RIGHT))
	{
		int x, y, i, j;
		mousePos(x, y);

        i = ecranVersCaseX(jj,x);
        j = ecranVersCaseY(jj,y);

        image_draw( jj.im_drapeau, caseVersEcranX(jj,i) + 5, caseVersEcranY(jj,j) + 5, WIN_DIM_X/jj.dx - 10, WIN_DIM_Y/jj.dy -10);
	}
}





int main(int , char ** )
{
    Jeu jeu;
    bool stop=false;
	winInit("Minesweeper", WIN_DIM_X, WIN_DIM_Y);
	setKeyRepeatMode(false);
	init(jeu);
	while( !stop )
    {
        backgroundColor( 100, 150, 250 );
        winClear();
        draw(jeu);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

