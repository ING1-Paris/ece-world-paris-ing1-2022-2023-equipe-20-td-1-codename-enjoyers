//
// Created by lucie on 03/05/2023.
//

#include "../../header.h"


/****************************/
/*       SOUS-PROGRAMME     */
/****************************/




t_rondin* creerRondin(char *nomimage){
    t_rondin* rondin_temp;

    rondin_temp = (t_rondin *) malloc(sizeof(t_rondin));

    rondin_temp->img=load_bitmap(nomimage,NULL);
    if (!rondin_temp->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    rondin_temp->tx = rondin_temp->img->w;
    rondin_temp->ty = rondin_temp->img->h;

    rondin_temp->posx= 3;//(rand()%SCREEN_W-TX+1-TX)+TX;

    rondin_temp->posy = rand() % 5;

    if(rondin_temp->posy == 0)
        rondin_temp->posy = 320;

    if(rondin_temp->posy == 1)
        rondin_temp->posy = 370;

    if(rondin_temp->posy == 2)
        rondin_temp->posy = 420;

    if(rondin_temp->posy == 3)
        rondin_temp->posy = 470;

    if(rondin_temp->posy == 3)
        rondin_temp->posy = 520;

    if(rondin_temp->posy == 4)
        rondin_temp->posy = 520;

    rondin_temp->depx = 1;


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
        MesRondins[i] = creerRondin("../assets/Item/Riviere/bois1.bmp");
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



t_joueuur * creationJoueur(BITMAP* tab_de_Skin[12]){


    t_joueuur *joueur_temp;

    joueur_temp = (t_joueuur *)malloc(1*sizeof(t_joueuur));

    for (int j = 0; j < 12; ++j)
    {
        joueur_temp->skin_perso[j] = tab_de_Skin[j];

    }

    joueur_temp->skin_utilise = 0;
    joueur_temp->tx = 48;
    joueur_temp->ty = 48;
    joueur_temp->x = 600;
    joueur_temp->y = 200;
    joueur_temp->vit = 2;


    return joueur_temp;
}



void ActualiserJoueur(BITMAP *bmp, t_joueuur* joueur_a_actualiser, t_rondin* tabrondin[NRONDIN], int anim){

    /*if (joueur_a_actualiser->y !=200){
        joueur_a_actualiser->skin_utilise = 0;
        joueur_a_actualiser->y= joueur_a_actualiser->y + joueur_a_actualiser->vit;
    }*/

    if (key[KEY_RIGHT]) {

        if(joueur_a_actualiser->x==920){

        }
        else {
            joueur_a_actualiser->x = joueur_a_actualiser->x + joueur_a_actualiser->vit;
            joueur_a_actualiser->skin_utilise = 6;
        }
    }

    if (key[KEY_LEFT] )
    {
        joueur_a_actualiser->skin_utilise = 3;
        joueur_a_actualiser->x = joueur_a_actualiser->x - joueur_a_actualiser->vit;
    }



    /*for (int i = 0; i < NRONDIN; ++i) {

        if ((joueur_a_actualiser->x = tabrondin[i]->posx) && (joueur_a_actualiser->y = tabrondin[i]->posy)) {

            AfficherJoueur(joueur_a_actualiser,tabrondin[i]->img,anim);

        }
    }*/


    if(key[KEY_DOWN])
    {
        joueur_a_actualiser->skin_utilise = 0;

        if (joueur_a_actualiser->y <= 700) {
            joueur_a_actualiser->y = joueur_a_actualiser->y + joueur_a_actualiser->vit;
        }

        else {
            textprintf_centre_ex(bmp, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), 0, "PLOUF !");
            joueur_a_actualiser->y = 200;
            joueur_a_actualiser->x = 600;
        }
    }

    if (key[KEY_UP] ) {
        joueur_a_actualiser->skin_utilise = 9;
        joueur_a_actualiser->y = joueur_a_actualiser->y - joueur_a_actualiser->vit;
    }
}


void detectionBuche();

void AfficherJoueur(t_joueuur *joueur_a_afficher, BITMAP *bmp,int animation){
    if (joueur_a_afficher != NULL){
        //AfficherJoueur(joueur_a_afficher, bmp, animation);
        masked_blit(joueur_a_afficher->skin_perso[joueur_a_afficher->skin_utilise + animation],bmp,0,0,joueur_a_afficher->x,joueur_a_afficher->y,joueur_a_afficher->tx,joueur_a_afficher->ty);
    }
}




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




void deplacement_joueurs_riv(BITMAP * bmp, t_joueuur *joueur_a_actualiser[NOMBRE_JOUEURS],int innactivite[NOMBRE_JOUEURS],t_rondin *rondin_riv[NRONDIN]) {

    int compteur = 0;
    int i;
    int ligne;
    int colonne;
    int couleurPixel;
    int marron = makecol(142, 72, 24);
    int rouge = makecol(255, 0,0);


    // DEPLACEMENTS DU JOUEUR 1
    if (key[KEY_UP]) {

        if (joueur_a_actualiser[0]->y < 0) {
            // on bloque
        } else {

            joueur_a_actualiser[0]->y = joueur_a_actualiser[0]->y - joueur_a_actualiser[0]->vit;
            joueur_a_actualiser[0]->skin_utilise = 9;
            innactivite[0] = 0;
        }
    }


    if (key[KEY_DOWN]) {

        if (joueur_a_actualiser[0]->y + joueur_a_actualiser[0]->ty >= SCREEN_H) {
            // on bloque
        } else {

            joueur_a_actualiser[0]->y = joueur_a_actualiser[0]->y + joueur_a_actualiser[0]->vit;
            joueur_a_actualiser[0]->skin_utilise = 0;
            innactivite[0] = 0;
        }

        for (int j = 0; j < NRONDIN; ++j) {
            for(ligne = 0; ligne <rondin_riv[j]->img->h; ligne ++) {
                for (colonne = 0; colonne < rondin_riv[j]->img->w; colonne++) {
                    couleurPixel = getpixel(rondin_riv[j]->img, colonne, ligne);
                    if ((joueur_a_actualiser[0]->x < rondin_riv[j]->posx)&&(couleurPixel == marron)){
                        joueur_a_actualiser[0]->x=rondin_riv[j]->posx;
                        joueur_a_actualiser[0]->y = rondin_riv[j]->posy;
                        putpixel(rondin_riv[j]->img, colonne, ligne, rouge);
                    }
                }
            }
            //masked_blit(joueur_a_actualiser[0]->skin_perso[4], rondin_riv[j]->img,0,0,rondin_riv[j]->posy, rondin_riv[j]->posy,rondin_riv[j]->tx, rondin_riv[j]->ty);

        }
    }


    if (key[KEY_RIGHT]) {

        if (joueur_a_actualiser[0]->x + joueur_a_actualiser[0]->tx >= SCREEN_W) {
            // on bloque
        } else {

            joueur_a_actualiser[0]->x = joueur_a_actualiser[0]->x + joueur_a_actualiser[0]->vit;
            joueur_a_actualiser[0]->skin_utilise = 6;
            innactivite[0] = 0;

        }
    }


    if (key[KEY_LEFT]) {

        if (joueur_a_actualiser[0]->x < 0) {
            // on bloque
        } else {

            joueur_a_actualiser[0]->x = joueur_a_actualiser[0]->x - joueur_a_actualiser[0]->vit;
            joueur_a_actualiser[0]->skin_utilise = 3;
            innactivite[0] = 0;
        }

    }



    // DEPLACEMENTS DU JOUEUR 2
    if (key[KEY_W]) {

        if (joueur_a_actualiser[1]->y < 0) {
            // on bloque

        } else {

            joueur_a_actualiser[1]->y = joueur_a_actualiser[1]->y - joueur_a_actualiser[1]->vit;
            joueur_a_actualiser[1]->skin_utilise = 9;
            innactivite[1] = 0;
        }
    }


    if (key[KEY_S]) {

        if (joueur_a_actualiser[1]->y + joueur_a_actualiser[1]->ty >= SCREEN_H) {
            // on bloque
        } else {

            joueur_a_actualiser[1]->y = joueur_a_actualiser[1]->y + joueur_a_actualiser[1]->vit;
            joueur_a_actualiser[1]->skin_utilise= 0;
            innactivite[1] = 0;
        }
    }


    if (key[KEY_D]) {

        if (joueur_a_actualiser[1]->x + joueur_a_actualiser[1]->tx >= SCREEN_W) {

            // on bloque

        } else {

            joueur_a_actualiser[1]->x = joueur_a_actualiser[1]->x + joueur_a_actualiser[1]->vit;
            joueur_a_actualiser[1]->skin_utilise = 6;
            innactivite[1] = 0;

        }

    }


    if (key[KEY_A]) {

        if (joueur_a_actualiser[1]->x < 0) {

            // on bloque

        } else {

            joueur_a_actualiser[1]->x = joueur_a_actualiser[1]->x - joueur_a_actualiser[1]->vit;
            joueur_a_actualiser[1]->skin_utilise = 3;
            innactivite[1] = 0;
        }

    }

}


int collision_joueur_buche(t_rondin * rondin, t_joueuur * joueur_actuel) {

    int retour;
    int m[4], imin, i;


    m[0] = joueur_actuel->x + joueur_actuel->tx - rondin->posx; // 0: à droite
    m[1] = rondin->posx - joueur_actuel->x; // 1: à gauche
    m[2] = joueur_actuel->y + joueur_actuel->ty ; //- rondin->posy; // 2: en bas
    m[3] = rondin->posy - joueur_actuel->y; // 3: en haut

    // Chercher l'indice de la plus petite marge
    imin=0;
    for (i=1;i<4;i++)
        if (m[i]<m[imin])
            imin=i;

    // A priori pas de collision
    retour=0;

    // Si la plus petite marge n'est pas strictement négative
    // alors c'est qu'on a une collision et cette collision est de ce coté
    if (m[imin]>=0)
        retour=1;  // on retourne l'indice du coté + 1 (car 0 signifie "pas de collision")

    return retour;
}


/*
int collision_riv(t_rondin * rondin, t_joueur * joueur_actuel){
    if (joueur_actuel->y+40 <= pixel marron)
        return 1

    else return 0
}
*/