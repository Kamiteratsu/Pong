#include <Grapic.h>
#include <string>
#include <time.h>

using namespace grapic;
using namespace std;

const int DIMW = 1280;
const int DIMH = 720;

struct Complex
{
    float x,y;
};

Complex make_complex(float r, float i)
{
    Complex c;
    c.x = r;
    c.y = i;
    return c;
}

struct Batte //Joueur
{
    Complex pos;
    bool pret;
    char cskin[50];
    int skins, etat;
    float taille;
    Image skin[8];
};

struct Balle
{
    Complex pos;
    bool etat[2]; //Pour le sens/direction
    int skins;
    char cskin[50];
    Image skin[8];
};

struct World //Structure regroupant tout les éléments du jeu
{
    Batte p[2];
    Balle balle;
    char cfond[50], cmenu[50], n[11], cresultat[50];
    int etape, choix_m, score[2], sizetext, timer, compte; //etape sert a savoir si on est à la sélection des mondes (choix_m), personnages, balles, si on est dans une partie ou à l'affichages des résultats
    float temps, v;
    Image fond[3], menu[5], resultat[2];
};

void init(World& w)
{
    w.etape = w.score[0] = w.score[1] = w.p[0].pos.x = w.timer = w.p[0].skins = w.p[1].skins = w.balle.skins = w.choix_m = w.p[0].pret = w.p[1].pret = w.p[0].etat = w.p[1].etat = w.balle.skins = 0;
    w.v = 1.5;
    w.compte = 4;
    w.temps = (float)clock()/(float)CLOCKS_PER_SEC;
    w.sizetext = w.p[0].taille = w.p[1].taille = 150;
    strcpy(w.n, "0123456789");
    strcpy(w.p[0].cskin, "Data/Perso/0.png");
    strcpy(w.p[1].cskin, "Data/Perso/0.png");
    strcpy(w.balle.cskin, "Data/Balle/0.png");
    strcpy(w.cfond, "Data/Theme/0/background.png");
    strcpy(w.cmenu, "Data/Menu/0.png");
    strcpy(w.cresultat, "Data/Theme/0.png");
    for(int x=0; x < 8; x++) //Chargement de toutes les images
    {
        if(x<=1)
        {
            w.cresultat[11] = w.n[x];
            w.resultat[x] = image(w.cresultat);
        }
        if(x<=2)
        {
            w.cfond[11] = w.n[x];
            w.fond[x] = image(w.cfond);
        }
        if(x<=4)
        {
            w.cmenu[10] = w.n[x];
            w.menu[x] = image(w.cmenu);
        }
        w.p[0].cskin[11] = w.n[x];
        w.p[0].skin[x] = w.p[1].skin[x] = image(w.p[0].cskin);
        w.balle.cskin[11] = w.n[x];
        w.balle.skin[x] = image(w.balle.cskin);
    }
    w.p[1].pos.x = DIMW - 35;
    w.p[0].pos.y = w.p[1].pos.y = (DIMH-100)/2;
    w.balle.pos = make_complex((DIMW-20)/2, (DIMH-20)/2);
    w.balle.etat[0] = w.balle.etat[1] = true;
}

void draw(World w)
{
    image_draw(w.fond[w.choix_m], 0, 0, DIMW, DIMH);
    image_draw(w.p[0].skin[w.p[0].skins], w.p[0].pos.x, w.p[0].pos.y, 35, w.p[0].taille);
    image_draw(w.p[1].skin[w.p[1].skins], w.p[1].pos.x, w.p[1].pos.y, 35, w.p[1].taille, 0, 1);
    image_draw(w.balle.skin[w.balle.skins], w.balle.pos.x, w.balle.pos.y, 20, 20);
    fontSize(w.sizetext);
    if(w.choix_m == 1) //Texte en blanc si le thème est noir
    {
        color(255, 255, 255);
    }
    else
    {
        color(0,0,0);
    }
    print(w.sizetext, DIMH-180, w.score[0]);
    print((DIMW/2)+w.sizetext, DIMH-180, w.score[1]);
    if(w.etape == 3 and w.compte != -1) //Dessin du compte à rebours
    {
        print((DIMW-80)/2, (DIMH-180)/2, w.compte);
    }
    color(255, 0, 0);
    fontSize(130);
    if(w.timer != 0) //Dessin du score possible en rouge si la partie est lancé
    {
        print(DIMW/2, 0, w.timer);
    }
    if(w.etape == 0 or w.etape == 1 or w.etape == 2 or w.etape == 4)
    {
        image_draw(w.menu[4], 0, 0, DIMW, DIMH);
    }
    if(w.etape == 0)
    {
        image_draw(w.menu[0], ((DIMW-200)/2)-300, 100, 200, 200);
        image_draw(w.menu[1], (DIMW-200)/2, 100, 200, 200);
        image_draw(w.menu[2], ((DIMW-200)/2)+300, 100, 200, 200);
        image_draw(w.menu[3], ((DIMW-75)/2)-300+w.choix_m*300, 10, 75, 75);
    }
    if(w.etape == 1)
    {
        image_draw(w.p[0].skin[w.p[0].skins], (DIMW-70)/4, (DIMH-200)/2, 70, 200);
        image_draw(w.p[1].skin[w.p[1].skins], ((DIMW-70)/4)*3, (DIMH-200)/2, 70, 200, 0, 1);
    }
    if(w.etape == 2)
    {
        image_draw(w.balle.skin[w.balle.skins], (DIMW-100)/2, (DIMH-100)/2, 100, 100);
    }
    if(w.etape == 4)
    {
        image_draw(w.resultat[w.p[0].etat], (DIMW-400)/8, ((DIMH-400)/2), 400, 400);
        image_draw(w.resultat[w.p[1].etat], ((DIMW-400)/8)*7, ((DIMH-400)/2), 400, 400);
    }
}

void update(World& w)
{
    if(w.etape == 0) //Sélection du monde
    {
        if ((isKeyPressed(SDLK_a) or isKeyPressed(SDLK_LEFT)) and w.choix_m != 0)
        {
            w.choix_m--;
            w.p[0].skins--;
            w.p[1].skins--;
            w.balle.skins--;
        }
        if ((isKeyPressed(SDLK_d) or isKeyPressed(SDLK_RIGHT)) and w.choix_m < 2)
        {
            w.choix_m++;
            w.p[0].skins++;
            w.p[1].skins++;
            w.balle.skins++;
        }
        if (isKeyPressed(SDLK_SPACE) or isKeyPressed(SDLK_RETURN))
        {
            if(w.choix_m == 2)
            {
                w.etape=1;
            }
            else
            {
                w.etape=3;
            }
        }
    }
    if(w.etape == 1) //Sélection des personnages
    {
        if (isKeyPressed(SDLK_a) and !w.p[0].pret)
        {
            if(w.p[0].skins == 0)
            {
                w.p[0].skins=8;
            }
            w.p[0].skins--;
        }
        if (isKeyPressed(SDLK_d) and !w.p[0].pret)
        {
            if(w.p[0].skins == 7)
            {
                w.p[0].skins=-1;
            }
            w.p[0].skins++;
        }
        if(isKeyPressed(SDLK_LEFT) and !w.p[1].pret)
        {
            if(w.p[1].skins == 0)
            {
                w.p[1].skins=8;
            }
            w.p[1].skins--;
        }
        if(isKeyPressed(SDLK_RIGHT) and !w.p[1].pret)
        {
            if(w.p[1].skins == 7)
            {
                w.p[1].skins=-1;
            }
            w.p[1].skins++;
        }
        if(isKeyPressed(SDLK_SPACE))
        {
            w.p[0].pret=true;
        }
        if(isKeyPressed(SDLK_RETURN))
        {
            w.p[1].pret=true;
        }
        if (w.p[0].pret and w.p[1].pret)
        {
            w.etape=2;
        }
    }
    if(w.etape == 2) //Sélection de la balle
    {
        if (isKeyPressed(SDLK_a) or isKeyPressed(SDLK_LEFT))
        {
            if(w.balle.skins == 0)
            {
                w.balle.skins=8;
            }
            w.balle.skins--;
        }
        if (isKeyPressed(SDLK_d) or isKeyPressed(SDLK_RIGHT))
        {
            if(w.balle.skins == 7)
            {
                w.balle.skins=-1;
            }
            w.balle.skins++;
        }
        if (isKeyPressed(SDLK_SPACE) or isKeyPressed(SDLK_RETURN))
        {
            w.etape=3;
        }
    }
    if(w.etape == 3) //Partie
    {
        if((((float)clock()/(float)CLOCKS_PER_SEC) - w.temps) >= 1 and w.compte != -1) //Compte à rebours
        {
            w.compte--;
            w.temps = (float)clock()/(float)CLOCKS_PER_SEC;
        }
        if(w.compte == -1) //Partie lancé
        {
            if((((float)clock()/(float)CLOCKS_PER_SEC) - w.temps) >= 0.1)
            {
                w.timer++;
                if(w.v < 5) //Limitation de la vitesse de la balle
                {
                    w.v+=0.05;
                }
                if(w.p[0].taille > 30) //Limitation de la taille du joueur droit
                {
                    w.p[0].taille-= 0.5;
                }
                if(w.p[1].taille > 30) //Limitation de la taille du joueur gauche
                {
                    w.p[1].taille-= 0.5;
                }
                w.temps = (float)clock()/(float)CLOCKS_PER_SEC;
            }
            if(w.balle.pos.x > 0 and w.balle.pos.x < (DIMW-20))
            {
                if (w.balle.etat[0]) //Balle en direction du joueur gauche
                {
                    w.balle.pos.x+= w.v;
                }
                else //Balle en direction du joueur gauche
                {
                    w.balle.pos.x-= w.v;
                }
            }
            else //Quand quelqu'un marque
            {
                w.balle.pos = make_complex((DIMW-20)/2, (DIMH-20)/2);
                if(w.balle.etat[0]) //Score en plus pour le joueur droit
                {
                    w.score[0]+= w.timer;
                }
                else //Score en plus pour le joueur gauche
                {
                    w.score[1]+= w.timer;
                }
                if(w.score[0] >= 1000) //Joueur droit gagne
                {
                    w.p[0].etat = 0;
                    w.p[1].etat = 1;
                    w.etape++;
                }
                if(w.score[1] >= 1000) //Joueur gauche gagne
                {
                    w.p[0].etat = 1;
                    w.p[1].etat = 0;
                    w.etape++;
                }
                w.balle.etat[0] = !w.balle.etat[0];
                w.timer = 0;
                w.v = 1.5;
                w.p[0].taille = w.p[1].taille =  150;
                w.p[1].pos.x = DIMW - 35;
                w.p[0].pos.y = w.p[1].pos.y = (DIMH-100)/2;
            }
            if((w.balle.pos.x <= w.p[0].pos.x+35 and w.balle.pos.x+20 >= w.p[0].pos.x+20 and w.balle.pos.y+20 >= w.p[0].pos.y and w.balle.pos.y <= w.p[0].pos.y+w.p[0].taille) or (w.balle.pos.x+20 >= w.p[1].pos.x and w.balle.pos.x <= w.p[1].pos.x+15 and w.balle.pos.y+20 >= w.p[1].pos.y and w.balle.pos.y <= w.p[1].pos.y+w.p[1].taille)) //Change la direction en x de la balle si un joueur la touche
            {
                w.balle.etat[0] = !w.balle.etat[0];
            }
            if(w.balle.pos.y <= DIMH-20 and w.balle.etat[1]) //Déplacement de la balle en y
            {
                w.balle.pos.y+=w.v;
            }
            if(w.balle.pos.y >= 0 and !w.balle.etat[1]) //Déplacement de la balle en y
            {
                w.balle.pos.y-=w.v;
            }
            if (w.balle.pos.y <= 0 or w.balle.pos.y >= DIMH-20) //Change la direction en y
            {
                w.balle.etat[1] = !w.balle.etat[1];
            }
        }
        // Deplacement des Joueurs
        if (isKeyPressed(SDLK_UP) and w.p[1].pos.y<(DIMH-w.p[1].taille))
        {
            w.p[1].pos.y+= w.v + 5;
        }
        if (isKeyPressed(SDLK_DOWN) and w.p[1].pos.y>0)
        {
            w.p[1].pos.y-= w.v + 5;
        }
        if (isKeyPressed(SDLK_z) and w.p[0].pos.y<(DIMH-w.p[0].taille))
        {
            w.p[0].pos.y+= w.v + 5;
        }
        if (isKeyPressed(SDLK_s) and w.p[0].pos.y>0)
        {
            w.p[0].pos.y-= w.v + 5;
        }
    }
    if(w.etape == 4) //Résultat
    {
        if (isKeyPressed(SDLK_SPACE) or isKeyPressed(SDLK_RETURN)) //Relancer le jeu
        {
            w.etape = w.score[0] = w.score[1] = w.p[0].pos.x = w.timer = w.p[0].skins = w.p[1].skins = w.balle.skins = w.choix_m = w.p[0].pret = w.p[1].pret = w.p[0].etat = w.p[1].etat = w.balle.skins = 0;
            w.v = 1.5;
            w.compte = 4;
        }
    }
}

int main(int , char** )
{
	winInit("PWorld", DIMW, DIMH);
    World w;
    bool stop=false;
    init(w);
    setKeyRepeatMode(false);
    fontSize(w.sizetext);
	while( !stop )
    {
        if(w.etape==3) //On peut maintenir les touches durant une partie
        {
            setKeyRepeatMode(true);
        }
        else
        {
            setKeyRepeatMode(false);
        }
        winClear();
        draw(w);
        update(w);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}
