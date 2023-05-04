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


void ActualiserJoueur(BITMAP *bmp, t_joueuur* joueur_a_actualiser, t_rondin* tabrondin[NRONDIN]){

    if (key[KEY_RIGHT]) {
        joueur_a_actualiser->x = joueur_a_actualiser->x + joueur_a_actualiser->vit;
        joueur_a_actualiser->skin_utilise = 6;
    }

    if (key[KEY_LEFT] ) {
        joueur_a_actualiser->skin_utilise = 3;
        joueur_a_actualiser->x = joueur_a_actualiser->x - joueur_a_actualiser->vit;
    }

    /*

    for (int i = 0; i < NRONDIN; ++i) {

        if ((joueur_a_actualiser->x+70 == tabrondin[i]->posx) && (joueur_a_actualiser->y+10 == tabrondin[i]->posy)) {

            //blit(bmp, bmp, joueur_a_actualiser->x, joueur_a_actualiser->y, tabrondin[i]->posx, tabrondin[i]->posy, SCREEN_W, SCREEN_H);

            //joueur_a_actualiser->vit = tabrondin[i]->depx;
            joueur_a_actualiser->x = tabrondin[i]->posx + 70;
            joueur_a_actualiser->y = tabrondin[i]->posy + 10;
            //AfficherJoueurRondin(tabrondin[i], joueur_a_actualiser);

            if ((key[KEY_DOWN])&&((joueur_a_actualiser->y+70==tabrondin[i]->posy)&&(joueur_a_actualiser->x+70 == tabrondin[i]->posx))){
                joueur_a_actualiser->x = tabrondin[i]->posx + 100;
                joueur_a_actualiser->y = tabrondin[i]->posy + 10;
            }
        }
    }
    */

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


