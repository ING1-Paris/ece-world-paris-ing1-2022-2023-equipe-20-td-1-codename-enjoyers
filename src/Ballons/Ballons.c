//
// Created by thais on 15/05/2023.
//

#include "../../header.h"

/// Allouer et initialiser les ballons

t_ballon * creerBallon(char *nomimage) {

    t_ballon * nouv;

    // Allouer
    nouv = (t_ballon *)malloc(1*sizeof(t_ballon));

    // Initialiser
    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = rand()%((SCREEN_W-nouv->tx/2)-(0-nouv->tx/2))+(0-nouv->tx/2);
    nouv->y = rand()%((SCREEN_H/2-nouv->tx/2)-(SCREEN_H/6-nouv->tx/2))+(SCREEN_H/6-nouv->tx/2);
    nouv->dx=0;
    nouv->dy=0;

    return nouv ;
}



// Actualiser les ballons (les bouger au hasard)
void actualiserBallon(t_ballon * ballon){

    // proba de changement de déplacement : une chance sur 50
    if (rand() % 50 == 0) {
        // Nouveau vecteur déplacement
        ballon->dx = rand() % 11 - 5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if ((ballon->x < 0 && ballon->dx < 0) ||
        (ballon->x + ballon->tx > SCREEN_W && ballon->dx > 0))
        ballon->dx = -ballon->dx;

    // nouvelle position = position actuelle + déplacement
    ballon->x = ballon->x + ballon->dx;
    ballon->y = ballon->y + ballon->dy;

}


// Dessiner les ballons sur la bitmap bmp
void dessinerBallon(BITMAP *bmp, t_ballon * ballon) {
    draw_sprite(bmp,ballon->img,ballon->x,ballon->y);
}

