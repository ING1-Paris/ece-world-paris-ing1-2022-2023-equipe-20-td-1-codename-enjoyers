#include "../../header.h"

// sur cet exemple Nombre d'lapins fixe :
//    le tableau d'lapins sera d�clar� et utilis� en "automatique"
//    t_lapin tab[Nlapin];
// Pour modifier cette valeur il faut adapter ablapins
#define Nlapin 6

// nombre total de s�quences d'animation du jeu
// ( le nombre d'lapins peut �tre sup�rieur si plusieurs lapins utilisent les m�me graphismes )
// Pour modifier cette valeur il faut modifier le tableau initialis� tabSequences
#define NSEQUENCE 6


/*****************************/
/*       STRUCTURES          */
/*  devront aller dans un .h */
/*****************************/

// donn�es pour chaque s�quence d'animation charg�e initialement
//  ( � ne faire qu'une seule fois au d�but du jeu )
typedef struct sequence
{
    char *nomSource; // nom du fichier image contenant la s�quence
    int nimg;        // nombre d'images dans la s�quence
    int tx,ty;       // largeur et hauteur des images de la s�quence
    int ncol;        // nbr images cotes � cotes horizontalement dans le fichier image
    BITMAP **img;    // tableau de pointeurs pour indiquer les images
} t_sequence;

// donn�es personnelles de chaque lapin qui se d�place
// sur cet exemple on ne g�re que des d�placements horizontaux (pas de dy...)
typedef struct lapin
{
    // g�om�trie et d�placements

    int x,y;         // position du coin sup. gauche
    int dx;          // deplacement
    int tmpdx;       // ralentir d�placements en x (1 pour ne pas ralentir)
    int cptdx;       // compteur pour ralentir d�placement
    int tx,ty;       // largeur hauteur

    // s�quence d'images de l'animation

    int imgcourante; // indice de l'image courante
    int tmpimg;      // ralentir s�quence (image suivante 1 fois sur tmpimg)
    int cptimg;      // compteur pour ralentir s�quence

    // type = num�ro de la sequence � utiliser dans tabSequences
    // ( ici : 0 Dragon  1 Poisson  2 Crabe  3 Abeille  4 Moustique  5 Serpent )

    int type;

} t_lapin;


/*****************************/
/*       PROTOTYPES          */
/*  devront aller dans un .h */
/*****************************/

// Allouer et initialiser un lapin
t_lapin * creerlapin(int type, int x, int y, int dx, int tmpdx, int tmpimg);

// Pour remplir un tableau avec des lapins cr��s
// Sur cet exemple on cr�e 6 lapins, chacun associ� � une s�quence
void remplirTablapins(t_lapin * tab[Nlapin]);


// Actualiser un lapin (bouger ...)
void actualiserlapin(t_lapin *lapin);

// G�rer l'�volution de l'ensemble des lapins
void actualiserTablapins(t_lapin * tab[Nlapin]);


// Dessiner un lapin sur une bitmap bmp
void dessinerlapin(BITMAP *bmp, t_lapin *lapin);

// Dessiner l'ensemble des lapins sur une bitmap bmp
void dessinerTablapins(BITMAP *bmp,t_lapin * tab[Nlapin]);


// Charger les images d'une s�quence d'animation
// D�coupe une image source en plusieurs vignettes
// (doivent �tre rang�es de gauche � droite et de haut en bas)
void chargerSequence(t_sequence * seq);

// Charger toutes les s�quences du tableau global tabSequence
void chargerTabSequences();



/***************************************************/
/*              VARIABLES GLOBALES                 */
/*  les d�clarations devront aller dans un .h      */
/*  les d�finitions devront aller dans un .c       */
/***************************************************/


// tableau global de toutes les s�quences anim�es du jeu
// on s'autorise � utiliser un tableau global car ces donn�es
// n'existent qu'en un seul exemplaire � l'�chelle du programme

t_sequence tabSequences[NSEQUENCE] =
        {
                //          nomSource           , nimg,  tx,  ty, ncol
                { "../assets/Item/sprites_lapins.bmp"    ,    8, 112,  140,    8 },
                { "../assets/Item/sprites_lapins.bmp"   ,    8,  112,  140,    8 },
                { "../assets/Item/sprites_lapins.bmp"   ,    8,  112,  140,    8 },
                { "../assets/Item/sprites_lapins.bmp"   ,    8,  112,  140,    8 },
                { "../assets/Item/sprites_lapins.bmp" ,    8,  112,  140,    8 },
                { "../assets/Item/sprites_lapins.bmp"   ,    8, 112,  140,    8 }
        };



/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

int jeu_course()
{
    // Le tableau regroupant tous les lapins
    // c'est un tableau de pointeurs sur structures t_lapins
    t_lapin * meslapins[Nlapin];

    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;

    // Image de fond
    BITMAP *decor;

    // Cr�ation du buffer d'affichage � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // charger image de fond
    decor=load_bitmap("../assets/maps/map_course.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver map_course.bmp");
        exit(EXIT_FAILURE);
    }


    // Chargement des images des s�quences anim�es
    chargerTabSequences();

    // Initialisation al�atoire des param�tres des lapins :
    // remplir le tableau avec des lapins allou�s et initialis�s
    remplirTablapins(meslapins);

    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {

        // 1)  EFFACER BUFFER, en appliquant d�cor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // 2) DETERMINER NOUVELLEs POSITIONs
        actualiserTablapins(meslapins);

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        dessinerTablapins(page,meslapins);

        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE � chaque fois sinon �a va trop vite...
        rest(20);
    }

    return 0;
}



/************************************************/
/*     DEFINITIONS DES SOUS-PROGRAMMES          */
/*  devront aller dans un autre .c : lapins.c  */
/************************************************/


// Allouer et initialiser un lapin
t_lapin * creerlapin(int type, int x, int y, int dx, int tmpdx, int tmpimg)
{
    // pointeur sur l'lapin qui sera cr�� (et retourn�)
    t_lapin *lapin;

    // Cr�ation (allocation)
    lapin = (t_lapin *)malloc(1*sizeof(t_lapin));

    // Initialisation g�om�trie et d�placement
    lapin->x=x;
    lapin->y=y;
    lapin->dx=dx;
    lapin->tmpdx=tmpdx;
    lapin->cptdx=0;
    lapin->tx=tabSequences[type].tx;
    lapin->ty=tabSequences[type].ty;

    // Initialisation s�quence d'images de l'animation
    lapin->imgcourante=0;
    lapin->tmpimg=tmpimg;
    lapin->cptimg=0;

    // num�ro de s�quence
    lapin->type=type;

    // on retourne cet lapin fraichement cr��
    return lapin;
}

// Pour remplir un tableau avec des lapins cr��s
// Sur cet exemple on cr�e 6 lapins, chacun associ� � une s�quence
void remplirTablapins(t_lapin * tab[Nlapin])
{
    // ( ici : 0 Dragon  1 Poisson  2 Crabe  3 Abeille  4 Moustique  5 Serpent )

    // Appeler Nlapin fois creerlapin avec les param�tres souhait�s :
    //                (type,   x,   y,  dx, tmpdx, tmpimg )
    tab[0]=creerlapin(   0, 2,   10,  4,     rand()%(6-1)+1,      4 );
    tab[1]=creerlapin(   1, 2, 100,   4,     rand()%(6-1)+1,      4 );
    tab[2]=creerlapin(   2, 2, 200,   4,     rand()%(6-1)+1,     4 ); // + tmpdx est grand, moins l'lapin avance vite
    tab[3]=creerlapin(   3, 2, 300,  4,     rand()%(6-1)+1,      4 );
    tab[4]=creerlapin(   4, 2,  400,   4,     rand()%(6-1)+1,      4 );
    tab[5]=creerlapin(   5, 2, 500,  4,     rand()%(6-1)+1,      4 );
}


// Actualiser un lapin (bouger ...)
void actualiserlapin(t_lapin *lapin)
{

    // gestion des bords
    // sur cet exemple seulement sur l'axe x (car pas de dy)
    if (lapin->x+lapin->tx/2 > SCREEN_W)
        lapin->x=SCREEN_W-lapin->tx/2;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement seulement une fois sur tmpdx
    // sur cet exemple seulement sur l'axe x (car pas de dy)
    lapin->cptdx++;
    if (lapin->cptdx >= lapin->tmpdx){
        lapin->cptdx=0;
        lapin->x = lapin->x + lapin->dx;
    }

    // gestion enchainement des images
    // incr�menter imgcourante une fois sur tmpimg
    lapin->cptimg++;
    if (lapin->cptimg >= lapin->tmpimg){
        lapin->cptimg=0;
        lapin->imgcourante++;
        // quand l'indice de l'image courante arrive � nimg de la s�quence
        // on recommence la s�quence � partir de 0
        if ( lapin->imgcourante >= tabSequences[ lapin->type ].nimg )
            lapin->imgcourante=0;
    }
}

// G�rer l'�volution de l'ensemble des lapins
void actualiserTablapins(t_lapin * tab[Nlapin])
{
    int i;

    for (i=0;i<Nlapin;i++)
        actualiserlapin(tab[i]);
}


// Dessiner un lapin sur une bitmap bmp
void dessinerlapin(BITMAP *bmp, t_lapin *lapin)
{
    // Pointeur sur la s�quence concern�e (prise en compte du type de l'lapin)
    t_sequence *seq;
    seq=&tabSequences[ lapin->type ];

    //  Prise en compte du num�ro d'image courante de l'lapin dans cette s�quence
    draw_sprite(bmp, seq->img[ lapin->imgcourante ], lapin->x, lapin->y);
}

// Dessiner l'ensemble des lapins sur une bitmap bmp
void dessinerTablapins(BITMAP *bmp,t_lapin * tab[Nlapin])
{
    int i;

    for (i=0;i<Nlapin;i++)
        dessinerlapin(bmp,tab[i]);
}


// Charger les images d'une s�quence d'animation
// D�coupe une image source en plusieurs vignettes
// (doivent �tre rang�es de gauche � droite et de haut en bas)
void chargerSequence(t_sequence * seq)
{
    BITMAP *source;  // la bitmap qui charge l'image de s�quence (temporairement)
    int i;           // indice de l'image dans la s�quence
    int ix,iy;       // indices (horizontal et vertical) dans le "tableau" des images
    int sx,sy;       // coordonn�es correspondantes (en pixels)


    // Charger l'image de s�quence
    source=load_bitmap(seq->nomSource,NULL);
    if (!source)
    {
        allegro_message("pas pu trouver %s", seq->nomSource);
        exit(EXIT_FAILURE);
    }

    // Allouer le tableau de pointeur sur les images de l'animation
    seq->img=(BITMAP **)malloc(seq->nimg*sizeof(BITMAP *));

    // Allouer les images de l'animation et les r�cup�rer sur l'image source
    ix=0;
    iy=0;
    for (i=0;i<seq->nimg;i++)
    {
        // allouer image
        seq->img[i]=create_bitmap(seq->tx,seq->ty);

        // r�cup�rer image
        sx=ix*seq->tx;
        sy=iy*seq->ty;
        blit(source,seq->img[i],sx,sy,0,0,seq->tx,seq->ty);

        // pr�parer indices pour l'image suivante
        ix++;          // colonne suivante
        if (ix >= seq->ncol)  // si je suis � droite de la derni�re colonne alors...
        {
            ix=0;      // repartir sur la colonne 0
            iy++;      // � la ligne en dessous
        }
    }

    // On a fini de r�cup�rer s�par�ment chaque �tape (image) de l'animation
    // on n'a donc plus besoin de l'image source qui les regroupe
    destroy_bitmap(source);
}

// Charger toutes les s�quences du tableau global tabSequence
void chargerTabSequences()
{
    int i;

    for (i=0;i<NSEQUENCE;i++)
        chargerSequence(&tabSequences[i]);
}