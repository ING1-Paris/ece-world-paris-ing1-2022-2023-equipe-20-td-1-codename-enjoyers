
//#include "../../header.h"

#include <allegro.h>


#define NTUILE     213   // Nombre de tuiles graphiques utilisées
#define TXTUILE    16    // Largeur des tuiles
#define TYTUILE    16    // Hauteur des tuiles
#define NCOLTUILE  20    // Nombre de colonnes de tuiles dans le fichier image

#define NXMAP      63      // Nombre de tuiles en largeur sur le terrain
#define NYMAP      44      // Nombre de tuiles en hauteur sur le terrain

#define NRONDIN 1 // Nombre de RONDIN
#define TX 40 // Largeur
#define TY 16 // Hauteur


double temps_ecoule;
double tmpJ1;

/****************************/
/*       STRUCTURE          */
/****************************/


typedef struct rondin{

    int tx,ty;   // taille
    BITMAP *img;
    int posx;
    int posy;
    int depx;

}t_rondin;




typedef struct joueur
{
    int tx, ty;
    int x, y; // coordonn�es (en pixels) des pieds de l'acteur
    int vit;
    BITMAP *img;       // image de l'acteur
} t_joueur;





/****************************/
/*       PROTOTYPE          */
/****************************/
int typeTuiles[NTUILE];
int terrain[NYMAP][NXMAP];


t_rondin* creerRondin(char *nomimage);
void actualiserRondin(t_rondin* rondin_a_actualiser);
void actualiserTabRondin(t_rondin * tab[NRONDIN]);
void remplirTabRondin(t_rondin* MesRondins[NRONDIN]);
void AfficherRondin(BITMAP *bmp,t_rondin *rondin_a_afficher);
void AfficherTabRondin(BITMAP *bmp,t_rondin * tab[NRONDIN]);


t_joueur * creationJoueur(char *nomimage);
void ActualiserJoueur(BITMAP *bmp, t_rondin **img, t_joueur* joueur_a_actualiser, t_rondin* tabrondin[NRONDIN]);
void AfficherJoueur(BITMAP *bmp,t_joueur *joueur_a_afficher);

void AfficherJoueurRondin(t_rondin *img,t_joueur *joueur_a_afficher);

//void dessineTuile(BITMAP *bmp, int ituile, int xmap, int ymap);
//void dessineTerrain(BITMAP *bmp, int terrain[NYMAP][NXMAP]);
//int typeTerrain(t_joueur *joueur, int dx, int dy, int type);


BITMAP * load_bitmap_check(char *nomImage);





/****************************/
/*       SOUS-PROGRAMME     */
/****************************/


BITMAP *tableTuiles;

int typeTuiles[NTUILE] = {
        1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
        1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1,
        1, 1, 0, 1, 0, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        0, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1,
        1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 2, 1, 1, 2, 2
};


int terrain[NYMAP][NXMAP] = {
        {  0,   1,   2,   3,   4,   2,   3,   4,   2,   3,   4,   2,   3,   4,   2,   3,   5,   6,   6,   6,   6,   6,   6,   6,   7,   6,   6,   6,   7,   6,   6,   7,   7,   6,   6,   6,   8,   9,   6,   7,   8,  10,  11,  12,  12,  12,  13,  14,  15,  16 },
        { 17,  18,  19,  20,  21,  22,  20,  21,  22,  20,  21,  22,  20,  21,  23,  24,  25,   6,   6,   6,   7,   6,   6,   6,   6,   6,   6,   6,   6,   7,   7,   6,   6,   7,   6,  26,   8,   9,   6,   7,   8,  11,  27,  28,  28,  28,  14,  13,  14,  15 },
        { 29,  30,  31,  32,  33,  34,  32,  33,  34,  32,  33,  34,  32,  33,  35,  36,   6,   7,   6,   6,   6,   6,   6,   6,   7,  37,   6,   7,   6,   6,  38,  39,  39,  40,  26,  41,  42,  43,   6,   6,  44,  27,  45,  12,  12,  12,  13,  14,  13,  14 },
        { 46,  47,  48,  49,  50,  51,  49,  50,  51,  49,  50,  51,  49,  50,  52,   6,   6,   6,   7,  37,   7,   6,   6,   6,   6,   6,   6,  37,   6,   6,  39,  39,  38,  38,  41,  42,  43,   6,   6,   7,  53,  45,  27,  28,  28,  28,  14,  13,  14,  13 },
        { 54,  47,  55,  56,  57,  58,  56,  57,  58,  56,  57,  58,  56,  57,  59,   6,   6,  60,  61,   6,   6,  60,  61,   6,   6,   6,   7,   6,   6,   6,   6,   6,   6,   6,   8,   9,   6,   6,   6,   6,   6,  53,  45,  12,  12,  12,  13,  14,  13,  62 },
        { 63,  64,  65,  66,  67,  68,  66,  67,  68,  66,  67,  68,  66,  67,  69,   6,  60,  70,  71,  72,  73,  74,  75,  61,   6,   6,   6,   6,  76,  77,  78,  79,  80,   6,  44,  81,  82,   6,   6,   7,   6,   6,  53,  83,  83,  28,  14,  13,  62,   6 },
        {  6,   6,   6,   6,   6,   6,  84,  85,   6,   6,   6,   6,   6,   6,   6,  60,  70,  86,  12,  87,  88,  12,  89,  75,  61,   6,   6,   6,  90,  91,  92,  93,  94,   6,  53,  45,  81,  95,  95,  95,  95,  95,  95,  95,  96,  12,  13,  62,  97,  98 },
        { 99, 100,   6,   6,   6,  84, 101, 102, 103, 103, 103, 103, 103,  85,  60,  70,  86,  13, 104, 105, 106, 104,  45,  89,  75,  61,   6,   6, 107,   4,   2,   3,   5,   6,   6,  53,  45,  12,  12,  12,  12,  12,  12,  12,  13,  83,  62,   6, 108, 109 },
        {110, 111, 112,  82,   6,  63, 113, 113, 113, 113, 113, 113, 113,  64,  70,  86,  13, 114, 115, 116, 117, 115, 118,  45,  89,  75,   6, 119, 120,  21,  23,  24,  25,   7,   6,   7,  53,  83,  83,  83,  83,  83,  83,  83,  62,   6,  97,  98,   6,   6 },
        {121,   6, 122, 123,  82,  60, 124, 124, 124, 124, 124,  61,  99, 100, 125, 126, 114, 127, 128, 129, 129, 129, 130, 118, 131, 132,   6, 133,  32,  33,  35,  36, 134, 134,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6, 108, 109,   6,   6 },
        {135,   6,   6, 136,  81,  74, 137, 137, 137, 137, 137,  71, 110, 111, 125, 138, 139, 129, 129, 140, 129, 129, 129, 141, 142, 132,   6,  48,  49,  50,  52, 134, 134, 134,  38,  38,  39,  40,   7,   6,   6,   7,   6, 143, 144,   6, 119, 120, 145, 146 },
        {  6,   6,   6, 147,  45,  12,  12,  12,  12,  12,  12,  12, 121,   6, 125, 138, 139, 129, 129, 129, 129, 128, 129, 141, 142, 132,   6,  55,  56,  57,  59, 134, 134, 134,  38,  38,  38,  38,   7,   6,   7,   6,   6, 148, 149,   6, 133,  32,  33, 150 },
        {  7,   6,  39,  40,  53,  83, 151, 152, 153, 154,  83,  83, 135,   6, 125, 138, 139, 129, 129, 129, 129, 129, 129, 141, 142, 132,  61,  65,  66,  67,  69,   6,   6,   7,   6,   7,   6,   6,   6,  37,   6,   6,   6,   7,   6,   6,  48,  49,  50,  52 },
        {  6,   7,  38,  38,   6,   6, 133,  32,  33, 150,   6,   6,   6,   6, 155, 156, 157, 158, 129, 129, 128, 129, 129, 141, 159,  89,  75,  61,   6,   6,   6, 112,  82,   6,   6,   6,   6,   6,   7,   6,   6,   6,   6,   6,  40,   6,  55,  56,  57,  59 },
        {  6,   6,   6,   6,   6,   6,  48,  49,  50,  52,   6,   6,   6,   6, 160, 155, 156, 157, 158, 129, 129, 140, 129, 130, 118,  45,  89,  75,  61,   6,   6, 122, 123,  95,  95,  82,   7,   6,   6,   7,   7,   6,   7,   6,   6,   6,  65,  66,  67,  69 },
        {  6,  76,  77,  78,  79,  77, 161, 162, 163,  78,  79,  80, 134,   6,   6, 160, 155, 156, 157, 158, 129, 129, 129, 129, 130, 118,  45,  89,  75,   6,   6,   6, 136,  12,  12,  81,  82,   6,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6 },
        {  6,  90,  91,  92,  93,  91,  92,  93,  91,  92,  93,  94, 134, 134,   6,   6, 160, 155, 156, 157, 158, 129, 164, 165, 129, 130, 118, 131, 132,   6,   6,   7, 147,  83,  83,  45,  81,  82,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6 },
        {  6, 107,   4,   2,   3,   4,   2,   3,   4,   2,   3,   5, 134,   6,   6,   6,   6, 160, 155, 156, 157, 158, 166, 167, 129, 129, 141, 142, 132,   6,   7,   6,   6,   6,   6,  53,  45,  81,  95,  95,  95,  95,  95,  82,   6,   6,   6,   7, 134,   6 },
        {  6, 168, 169, 170,  24, 169, 171,  20,  21,  22,  20, 145, 146, 134,   6,   6,   6,   7, 160, 155, 156, 157, 172, 173, 173, 174, 175, 176, 177,   6,  39,  40,   6,   6,   6,   6,  53,  45,  12,  12,  12,  12,  12,  81,  82,   6,   6, 134,   7,   6 },
        {  6,   6, 178, 179,  36, 178,  31,  32,  33,  34,  32,  33, 150, 134, 134,   6,   7,   6,   6, 160, 155, 156, 180, 181, 181, 182, 176, 177, 183,   6,  38,  38,   6, 134,   6,   6,   6,  53,  83,  83,  83,  83,  83,  45,  81,  82,   7,   6,   6,  99 },
        {  6,   6, 6,   6,   6,   6,  48,  49,  50,  51,  49,  50,  52, 134,   7,   6,  38,  39,  39,  40, 160, 155, 185, 185, 185, 185, 177, 183,   7,   6,  38,  39,   6,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,  53,  45,  81,  95,  95,  95,  96 },
        { 85,   6, 184, 184,   6, 184,  55,  56,  57,  58,  56,  57,  59, 134,   6,   7,  39,  39,  38,  38,   6, 160, 186, 186, 186, 186, 183,   6,   6,   7,  39,  39,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,  53,  45,  12,  12,  12,  13 },
        {102,  85,  84,  85,   6,   6,  65,  66,  67,  68,  66,  67,  69,   6,   6,   6,  39,  40,   6,   6,   6,   6,   6,   6, 187, 188,   6,   6, 189,   6,   6,   6,   6, 187, 190, 191, 188,   6,   6,   6,   6,   6,   6,   6,   6,  53,  83,  83,  83,  62 },
        {166, 166, 166, 166, 166, 166,  166, 166, 166,   166, 166, 166,   166, 166, 166,  166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166 },
        {166, 166, 166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, 166, 166, 166, },
        {166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, 166,  166, 166, 166,   166, 166,166, 166, 166, },
        {  173,   174,   173,   174,   173,   174,   6,   6,   6,   6,   6,   6,  166, 166, 166, 166, 166,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,  63, 113, 113, 113, 113,  64,   6,   6,   6,   6,   6,   6,   6,   6,  63, 113, 113, 113, 113, 113 },
        { 181,  181,  181,  181,  181,  181,  78,  79,  77,  78,  79,  77,  78,  79,  80,   6,   6,   6,   6,   6,   6,   6, 134, 134,   6,   6, 134, 134,   6,  76,  77,  78,  79,  80,   6,   6,   6,  60, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124 },
        { 185,  185,  185,  185,  185,  185,  92,  93,  91,  92,  93,  91,  92,  93,  94,   6,   6,   6,   6,   6,   6,   6,   6,   6, 134,   6,   6, 134,   6,  90,  91,  92,  93,  94,   6,   6,  60,  70, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137 },
        {  186,   186,   186,   186,   186,   186,   2,   3,   4,   2,   3,   4,   2,   3,   5,   6,   6,   6,   6,   6,   6,  76,  77,  78,  79,  80,   6,   6,   6, 107,   4,   2,   3,   5,   6,  60,  70,  86,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12 },
        { 22,  20,  21,  22,  20,  21,  22,  20,  21,  22,  20,  21,  22,  20, 145, 146,   6,   6,   6,   6,   6,  90,  91,  92,  93,  94,   6,   6, 119, 120,  21,  22,  20, 145, 146,  70,  86,  13, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104 },
        { 34,  32,  33,  34,  32,  33,  34,  32,  33,  34,  32,  33,  34,  32,  33, 150,   6,   6,   6,   6,   6, 107,   4,   2,   3,   5,   6,   6, 133,  32,  33,  34,  32,  33, 150, 125, 126, 114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115 },
        { 51,  49,  50,  51,  49,  50,  51,  49,  50,  51,  49,  50,  51,  49,  50,  52,   6,   6,   6,   7,   6, 168, 169, 170,  24,  25,   6,   6,  48,  49,  50,  51,  49,  50,  52, 125, 138, 139, 129, 140, 129, 129, 129, 128, 129, 129, 129, 129, 129, 140 },
        { 58,  56,  57,  58, 205, 163, 206, 162, 163, 206, 162, 163, 206, 162, 207,  59,   6,   6,   6,   6,   6,   6, 178, 179,  36,   6,   7,   6,  55,  56,  57,  58,  56,  57,  59, 125, 138, 139, 129, 129, 129, 129, 129, 129, 208, 173, 173, 173, 173, 173 },
        { 68,  66,  67,  68, 209,  91,  92,  93,  91,  92,  93,  91,  92,  93, 210,  69,   6,   6, 134,   6,   6,   6,   6,   6,   6,   6,   6,   6,  65,  66,  67,  68,  66,  67,  69, 125, 138, 139, 129, 129, 129, 140, 129, 211, 212, 181, 181, 181, 181, 181 }
};



t_rondin* creerRondin(char *nomimage){
    t_rondin* rondin_temp;
    int position[(525 - 322) + 322]; //creer un truc pour ne pas que les rondins se chevauchent

    rondin_temp = (t_rondin *) malloc(sizeof(t_rondin));

    rondin_temp->img=load_bitmap(nomimage,NULL);
    if (!rondin_temp->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    rondin_temp->tx = rondin_temp->img->w;
    rondin_temp->ty = rondin_temp->img->h;

    rondin_temp->posx= (rand()%SCREEN_W-TX+1-TX)+TX;
    rondin_temp->posy = 322;//rand() % (525 - 300) + 300;



    rondin_temp->depx = 2;

    return rondin_temp;
}



void actualiserRondin(t_rondin* rondin_a_actualiser){
    if ( (rondin_a_actualiser->posx<0 && rondin_a_actualiser->depx<0) || (rondin_a_actualiser->posx>SCREEN_W && rondin_a_actualiser->depx>0) )
    {
        rondin_a_actualiser->posx = -rondin_a_actualiser->posx>SCREEN_W;
        rondin_a_actualiser->depx=rondin_a_actualiser->depx;

    }
    rondin_a_actualiser->posx=rondin_a_actualiser->posx+rondin_a_actualiser->depx;

}


void actualiserTabRondin(t_rondin * tab[NRONDIN]) {
    int i;
    for (i = 0; i < NRONDIN; i++) {
        actualiserRondin(tab[i]);
    }
}

void remplirTabRondin(t_rondin* MesRondins[NRONDIN]){
    for (int i = 0; i < NRONDIN; ++i) {
        MesRondins[i] = creerRondin("bois1.bmp");
    }
}

void AfficherRondin(BITMAP *bmp,t_rondin *rondin_a_afficher){
    draw_sprite(bmp,rondin_a_afficher->img,rondin_a_afficher->posx,rondin_a_afficher->posy);
}


void AfficherTabRondin(BITMAP *bmp,t_rondin * tab[NRONDIN]){
    for (int i=0;i<NRONDIN;i++) {
        AfficherRondin(bmp, tab[i]);
    }
}



t_joueur * creationJoueur(char *nomimage){
    t_joueur *joueur_temp;

    joueur_temp = (t_joueur *)malloc(1*sizeof(t_joueur));


    joueur_temp->img=load_bitmap(nomimage,NULL);
    if (!joueur_temp->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    joueur_temp->tx = joueur_temp->img->w;
    joueur_temp->ty = joueur_temp->img->h;

    joueur_temp->x = 600;
    joueur_temp->y = 200;
    joueur_temp->vit = 1;

    return joueur_temp;
}

void AfficherJoueurRondin(t_rondin *img,t_joueur *joueur_a_afficher){
    draw_sprite((BITMAP *) img, joueur_a_afficher->img, joueur_a_afficher->x - joueur_a_afficher->img->w / 2, joueur_a_afficher->y - joueur_a_afficher->img->h + 8);

}

void ActualiserJoueur(BITMAP *bmp, t_rondin **img, t_joueur* joueur_a_actualiser, t_rondin* tabrondin[NRONDIN]){

    if ((key[KEY_RIGHT]))
        joueur_a_actualiser->x += 4;

    if (key[KEY_LEFT] )//&& !typeTerrain(joueur, -4, 0, 1))
        joueur_a_actualiser->x -= 4;

    if(key[KEY_DOWN]) //&& !typeTerrain(joueur, 0, 4, 1))
    {
        if (joueur_a_actualiser->y <= 320)
            joueur_a_actualiser->y += 4;

        else {
            textprintf_centre_ex(bmp, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), 0, "PLOUF !");
            joueur_a_actualiser->y = 200;
            joueur_a_actualiser->x = 600;
        }
    }

    for (int i = 0; i < NRONDIN; ++i) {
        if((key[KEY_SPACE])&&((joueur_a_actualiser->x >= tabrondin[i]->posx)&&(joueur_a_actualiser->y >= tabrondin[i]->posy))) {
            joueur_a_actualiser->vit=tabrondin[i]->depx;
            joueur_a_actualiser->x = tabrondin[i]->posx+70;
            joueur_a_actualiser->y=tabrondin[i]->posy+10;
            //AfficherJoueurRondin(tabrondin[i], joueur_a_actualiser);

        }

        else if (key[KEY_SPACE]) {
            joueur_a_actualiser->y = joueur_a_actualiser->y + 10;

            if (joueur_a_actualiser->y > 320) {

                joueur_a_actualiser->y = 200;
                joueur_a_actualiser->x = 600;

                textprintf_centre_ex(bmp, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), 0, "PLOUF !");


            }
        }
    }


    if (key[KEY_UP] )//&& !typeTerrain(joueur, 0, -4, 1))
        joueur_a_actualiser->y -= 4;

    //if( key[KEY_SPACE] ) && !typeTerrain(joueur,0,-4,1) )


}


void AfficherJoueur(BITMAP *bmp,t_joueur *joueur_a_afficher){
    draw_sprite(bmp, joueur_a_afficher->img, joueur_a_afficher->x - joueur_a_afficher->img->w/2, joueur_a_afficher->y - joueur_a_afficher->img->h + 8);
}




/******************************************/
/*         SOUS-PROGRAMMES TERRAIN        */
/******************************************/


void dessineTuile(BITMAP *bmp, int ituile, int xmap, int ymap){
    int lig, col;

    lig = ituile / NCOLTUILE;
    col = ituile % NCOLTUILE;

    blit(tableTuiles, bmp, col*TXTUILE, lig*TYTUILE,
         xmap*TXTUILE, ymap*TYTUILE, TXTUILE, TYTUILE);


    /*if (key[KEY_SPACE])
    {
        if (typeTuiles[ituile]==1)
            rect(bmp, xmap*TXTUILE, ymap*TYTUILE, xmap*TXTUILE+TXTUILE-1, ymap*TYTUILE +TYTUILE-1, makecol(255,0,0));
        if (typeTuiles[ituile]==2)
            rect(bmp, xmap*TXTUILE, ymap*TYTUILE, xmap*TXTUILE+TXTUILE-1, ymap*TYTUILE +TYTUILE-1, makecol(0,0,255));
    }*/
}


void dessineTerrain(BITMAP *bmp, int terrain[NYMAP][NXMAP]){
    int xmap,ymap;

    for (ymap=0;ymap<NYMAP;ymap++)
        for (xmap=0;xmap<NXMAP;xmap++)
            dessineTuile(bmp,terrain[ymap][xmap],xmap,ymap);
}


/*int typeTerrain(t_joueur *joueur, int dx, int dy, int type){
    int xmap,ymap,ituile;
    int decx,decy;
    int cx,cy;

    // Pour chacun des 4 coins...
    for (decy=-TYTUILE/2; decy<TYTUILE/2; decy+=TYTUILE-1)
        for (decx=-TXTUILE/2; decx<TXTUILE/2; decx+=TXTUILE-1)
        {
            // Coord. du coin
            cx=joueur->x+dx+decx;
            cy=joueur->y+dy+decy;

            // Si on sort du terrain...
            if (cx<0 || cx>=NXMAP*TXTUILE || cy<0 || cy>=NYMAP*TYTUILE)
            {
                if (type==1)
                    return 1;           // Oui c'est un obstacle
                else
                    return 0;          // Non ce n'est pas autre chose...
            }

            // Trouver les coordonnées matrice
            xmap=cx/TXTUILE;
            ymap=cy/TYTUILE;

            // Récupérer le numéro de tuile sur laquelle on arrive
            ituile=terrain[ymap][xmap];

            // Retourner OUI si le type de la tuile est bien celui recherché
            if (typeTuiles[ituile]==type)
                return 1;
        }

    // Donc NON, on n'a pas trouvé le type recherché
    return 0;
}*/



BITMAP * load_bitmap_check(char *nomImage){
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}





/******************************************/
/*          PROGRAMME PRINCIPAL           */
/******************************************/

void jeu_riviere() {

    t_rondin *mesRondins[NRONDIN];
    t_joueur *joueur;    // Un joueur (� cr�er)
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 700, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    //tableTuiles = load_bitmap_check("images/tilemapZelda/tableTuiles.bmp");



    remplirTabRondin(mesRondins);

    decor = load_bitmap_check("MAP_RIVIERE_TEST2.bmp");



    for (int j = 0; j < 2; j++) {
        time_t temps_precedent = time(NULL);

        joueur = creationJoueur("shrek4.bmp");


        while (joueur->y <= 580) {


            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

            //dessineTerrain(page, terrain);
            AfficherTabRondin(page, mesRondins);
            AfficherJoueur(page, joueur);
            actualiserTabRondin(mesRondins);

            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%d",joueur->y);


            time_t temps_actuel = time(NULL);
            temps_ecoule = difftime(temps_actuel, temps_precedent);


            ActualiserJoueur(decor, mesRondins, joueur, mesRondins);


            /*if (typeTerrain(joueur, 0, 0, 2)) { // dans l'eau ?
                joueur->x = 32;
                joueur->y = 200;
                //acteur->x+=1;
                textprintf_centre_ex(page, font, 400, 570, makecol(255, 255, 255), 0, " COULE ");
            } else
                textprintf_centre_ex(page, font, 400, 570, makecol(255, 255, 255), 0, "MARCHE");*/



            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            rest(15);


        }

        allegro_message("vous avez traversé la rivière en %.1f secondes", temps_ecoule);
        if (j == 0)
            tmpJ1 = temps_ecoule;
        else {
            if (tmpJ1 < temps_ecoule)
                allegro_message("Joueur 1, vous avez gagné un ticket !");
            else
                allegro_message("Joueur 2, vous avez gagné un ticket !");

        }

    }
}

