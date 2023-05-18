#include "../../header.h"

/***************************************************/
/*              VARIABLES GLOBALES                 */
/***************************************************/

// tableau global de toutes les séquences animées du jeu
// on s'autorise à utiliser un tableau global car ces données n'existent qu'en un seul exemplaire é l'échelle du programme

t_sequence tabSequences[NSEQUENCE] =
        {
                //          nomSource           , nimg,  tx,  ty, ncol
                { "../assets/Item/Course/sprites_lapins.bmp"    ,    8, 112,  140,    8 },
                { "../assets/Item/Course/sprites_lapins.bmp"   ,    8,  112,  140,    8 },
                { "../assets/Item/Course/sprites_lapins.bmp"   ,    8,  112,  140,    8 },
                { "../assets/Item/Course/sprites_lapins.bmp"   ,    8,  112,  140,    8 },
                { "../assets/Item/Course/sprites_lapins.bmp" ,    8,  112,  140,    8 },
                { "../assets/Item/Course/sprites_lapins.bmp"   ,    8, 112,  140,    8 }
        };



/******************************************/
/*           PROGRAMME PRINCIPAL          */
/******************************************/

void jeu_course()
{
    fflush(stdin);
    int tab_paris[2] = {0, 0};
    int tab_joueurs[NOMBRE_JOUEURS];

    char pari_lapin_temp[256]="";

    int alive = 1 ;

    DIALOG GUI_paris[] =
            {
                    // (dialog proc)     (x)   (y)   (w)   (h) (fg)(bg) (key) (flags)     (d1) (d2)    (dp)                   (dp2) (dp3)
                    { d_box_proc,           0, 0, 500, 200, 0, 0, 0,        0,          0,  0,       NULL,               NULL, NULL},
                    { d_text_proc,         2,  10,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Pariez sur un lapin (entre 1 et 5) :",  NULL, NULL  },
                    { d_text_proc,         4,  25,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)">>",  NULL, NULL  },
                    { d_edit_proc,       28,  25,  160,    8,   0,  0,    0, D_EXIT,      64,   0,    (void*)pari_lapin_temp,      NULL, NULL  },


                    { d_button_proc,     160,   190,  160,   16,   0,  0,    0, D_EXIT,       0,   0,    (void*)"OK",            NULL, NULL  },
                    { d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
                    { NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
            };

    gui_fg_color = makecol(0, 0, 0);
    gui_mg_color = -1;
    gui_bg_color = makecol(255, 255, 255);
    set_dialog_color (GUI_paris, gui_fg_color, gui_bg_color);
    centre_dialog(GUI_paris);


    for (int i = 0; i < 2; ++i) { // afin que les joueurs puissent parier sur leur lapin

        do {

            strcpy(pari_lapin_temp, "");

            do_dialog(GUI_paris, 3);

        } while ((strlen(pari_lapin_temp) < 1)||(strlen(pari_lapin_temp) > 1) || (atoi(pari_lapin_temp) < 1 || atoi(pari_lapin_temp) > 6));

        tab_paris[i] = atoi(pari_lapin_temp) - 1 ; //pour la comparaison avec le type (qui lui est de 0 à 5)
    }


    // Le tableau regroupant tous les lapins
    // c'est un tableau de pointeurs sur structures t_lapins
    t_lapin * meslapins[Nlapin];

    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;

    // Image de fond
    BITMAP *decor;

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

    // remplir le tableau avec des lapins alloués et initialisés
    remplirTablapins(meslapins);


    // Boucle d'animation (pas d'interaction)
    while (alive)
    {

        // 1)  EFFACER BUFFER, en appliquant d�cor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // 2) DETERMINER NOUVELLEs POSITIONs
        actualiserTablapins(meslapins, tab_paris, &alive, &page, tab_joueurs);

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        dessinerTablapins(page,meslapins);

        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE � chaque fois sinon �a va trop vite...
        rest(20);
    }


}

/************************************************/
/*     DEFINITIONS DES SOUS-PROGRAMMES          */
/************************************************/


// Allouer et initialiser un lapin
t_lapin * creerlapin(int type, int x, int y, int dx, int tmpdx, int tmpimg)
{
    // pointeur sur l'lapin qui sera cr�� (et retourn�)
    t_lapin *lapin;

    // Création (allocation)
    lapin = (t_lapin *)malloc(1*sizeof(t_lapin));

    // Initialisation et déplacement
    lapin->x=x;
    lapin->y=y;
    lapin->dx=dx;
    lapin->tmpdx=tmpdx;
    lapin->cptdx=0;
    lapin->tx=tabSequences[type].tx;
    lapin->ty=tabSequences[type].ty;

    // Initialisation séquence d'images de l'animation
    lapin->imgcourante=0;
    lapin->tmpimg=tmpimg;
    lapin->cptimg=0;

    // numéro de séquence
    lapin->type=type;

    return lapin;
}

//remplir le tableau de lapins (6 lapins)
void remplirTablapins(t_lapin * tab[Nlapin])
{
    // Appeler Nlapin fois creerlapin avec les paramètres souhaités :
    //                (type,   x,   y,  dx, tmpdx, tmpimg )
    tab[0]=creerlapin(   0, 2,   10,  4,     rand()%(6-1)+1,      4 );
    tab[1]=creerlapin(   1, 2, 100,   4,     rand()%(6-1)+1,      4 );
    tab[2]=creerlapin(   2, 2, 200,   4,     rand()%(6-1)+1,     4 ); // + tmpdx est grand, moins le lapin avance vite
    tab[3]=creerlapin(   3, 2, 300,  4,     rand()%(6-1)+1,      4 );
    tab[4]=creerlapin(   4, 2,  400,   4,     rand()%(6-1)+1,      4 );
    tab[5]=creerlapin(   5, 2, 500,  4,     rand()%(6-1)+1,      4 );
}


// Actualiser un lapin
void actualiserlapin(t_lapin *lapin, int tabParis[2], int *alive, BITMAP *page, t_joueur tableau_joueurs[NOMBRE_JOUEURS])
{

    // gestion des bords sur l'axe x

    if (lapin->x+lapin->tx/2 > SCREEN_W){
        lapin->x=SCREEN_W-lapin->tx/2;
        *alive = 0;

        int gagnant = 0;

        for (int i = 0; i < 2; ++i) {

            if(lapin->type == tabParis[i]) {
                gagnant = 1;
            }
        }

        if (gagnant) {

            if(lapin->type == tabParis[0]) {
                tableau_joueurs[0].tickets = tableau_joueurs[0].tickets+1 ;
                allegro_message("joueur 1, vous avez gagné un ticket !");
            }
            else {
                tableau_joueurs[1].tickets = tableau_joueurs[1].tickets+1;
                allegro_message("joueur 2, vous avez gagné un ticket !");
            }

        }
        else {

            //textout_ex(page, font, "vous avez perdu", 150, 300, makecol(255, 255, 255), -1);
            //textprintf_ex(page,font,150, 300, makecol(255,255,255), -1,"vous avez perdu");
            allegro_message("vous avez perdu");

        }
    }


    // calculer nouvelle position
    // nouvelle position = position actuelle + déplacement seulement une fois sur tmpdx
    lapin->cptdx++;
    if (lapin->cptdx >= lapin->tmpdx){
        lapin->cptdx=0;
        lapin->x = lapin->x + lapin->dx;
    }

    // gestion enchainement des images
    // incrémenter imgcourante une fois sur tmpimg
    lapin->cptimg++;
    if (lapin->cptimg >= lapin->tmpimg){
        lapin->cptimg=0;
        lapin->imgcourante++;
        // quand l'indice de l'image courante arrive à nimg de la séquence on recommence la séquence à 0
        if ( lapin->imgcourante >= tabSequences[ lapin->type ].nimg )
            lapin->imgcourante=0;
    }

    //changement de vitesse durant la course
    lapin->dx = rand()%(8-1)+1;
}

// Gérer l'évolution de l'ensemble des lapins
void actualiserTablapins(t_lapin * tab[Nlapin], int tabParis[2], int *alive, BITMAP *page, t_joueur tableau_joueurs[NOMBRE_JOUEURS])
{
    int i;
    for (i=0;i<Nlapin;i++)
        actualiserlapin(tab[i], tabParis, alive, page, tableau_joueurs);
}


// Dessiner un lapin sur une bitmap bmp
void dessinerlapin(BITMAP *bmp, t_lapin *lapin)
{
    // Pointeur sur la séquence concernée (prise en compte du type du lapin)
    t_sequence *seq;
    seq=&tabSequences[ lapin->type ];

    //  Prise en compte du numéro d'image courante du lapin dans cette séquence
    draw_sprite(bmp, seq->img[ lapin->imgcourante ], lapin->x, lapin->y);
}

// Dessiner l'ensemble des lapins sur une bitmap bmp
void dessinerTablapins(BITMAP *bmp,t_lapin * tab[Nlapin])
{
    int i;
    for (i=0;i<Nlapin;i++)
        dessinerlapin(bmp,tab[i]);
}


// Charger les images d'une séquence d'animation
// Découpe une image source en plusieurs vignettes
void chargerSequence(t_sequence * seq)
{
    BITMAP *source;  // la bitmap qui charge l'image de séquence (temporairement)
    int i;           // indice de l'image dans la séquence
    int ix,iy;       // indices (horizontal et vertical) dans le "tableau" des images
    int sx,sy;       // coordonnées correspondantes (en pixels)


    // Charger l'image de séquence
    source=load_bitmap(seq->nomSource,NULL);
    if (!source)
    {
        allegro_message("pas pu trouver %s", seq->nomSource);
        exit(EXIT_FAILURE);
    }

    // Allouer le tableau de pointeur sur les images de l'animation
    seq->img=(BITMAP **)malloc(seq->nimg*sizeof(BITMAP *));

    // Allouer les images de l'animation et les récupérer sur l'image source
    ix=0;
    iy=0;
    for (i=0;i<seq->nimg;i++)
    {
        // allouer image
        seq->img[i]=create_bitmap(seq->tx,seq->ty);

        // récupérer l'image
        sx=ix*seq->tx;
        sy=iy*seq->ty;
        blit(source,seq->img[i],sx,sy,0,0,seq->tx,seq->ty);

        // préparer indices pour l'image suivante
        ix++;
    }

    destroy_bitmap(source);
}

// Charger toutes les séquences du tableau global tabSequence
void chargerTabSequences()
{
    int i;

    for (i=0;i<NSEQUENCE;i++)
        chargerSequence(&tabSequences[i]);
}