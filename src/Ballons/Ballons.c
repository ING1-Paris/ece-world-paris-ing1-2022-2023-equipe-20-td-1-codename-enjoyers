//
// Created by thais on 15/05/2023.
//

#include "../../header.h"

/// Allouer et initialiser les ballons

t_ballon * creerBallon_bleu(char *nomimage){
    t_ballon *nouv;

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


t_ballon * creerBallon_rose(char *nomimage){
    t_ballon *nouv;

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


t_ballon * creerBallon_vert(char *nomimage){
    t_ballon *nouv;

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


t_ballon * creerBallon_violet(char *nomimage){
    t_ballon *nouv;

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


t_ballon * creerBallon_rouge(char *nomimage){
    t_ballon *nouv;

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
void actualiserBallon_bleu(t_ballon *ballon_bleu){

    // proba de changement de déplacement : une chance sur 50
    if (rand() % 50 == 0) {
        // Nouveau vecteur déplacement
        ballon_bleu->dx = rand() % 11 - 5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if ((ballon_bleu->x < 0 && ballon_bleu->dx < 0) ||
        (ballon_bleu->x + ballon_bleu->tx > SCREEN_W && ballon_bleu->dx > 0))
        ballon_bleu->dx = -ballon_bleu->dx;

    // nouvelle position = position actuelle + déplacement
    ballon_bleu->x = ballon_bleu->x + ballon_bleu->dx;
    ballon_bleu->y = ballon_bleu->y + ballon_bleu->dy;

}


void actualiserBallon_rose(t_ballon *ballon_rose){

    // proba de changement de déplacement : une chance sur 50
    if (rand() % 50 == 0) {
        // Nouveau vecteur déplacement
        ballon_rose->dx = rand() % 11 - 5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if ((ballon_rose->x < 0 && ballon_rose->dx < 0) ||
        (ballon_rose->x + ballon_rose->tx > SCREEN_W && ballon_rose->dx > 0))
        ballon_rose->dx = -ballon_rose->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_rose->x = ballon_rose->x + ballon_rose->dx;
    ballon_rose->y = ballon_rose->y + ballon_rose->dy;

}

void actualiserBallon_vert(t_ballon *ballon_vert){

    // proba de changement de déplacement : une chance sur 50
    if (rand() % 50 == 0) {
        // Nouveau vecteur déplacement
        ballon_vert->dx = rand() % 11 - 5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if ((ballon_vert->x < 0 && ballon_vert->dx < 0) ||
        (ballon_vert->x + ballon_vert->tx > SCREEN_W && ballon_vert->dx > 0))
        ballon_vert->dx = -ballon_vert->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_vert->x = ballon_vert->x + ballon_vert->dx;
    ballon_vert->y = ballon_vert->y + ballon_vert->dy;
}


void actualiserBallon_violet(t_ballon *ballon_violet){

    // proba de changement de déplacement : une chance sur 50
    if (rand() % 50 == 0) {
        // Nouveau vecteur déplacement
        ballon_violet->dx = rand() % 11 - 5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if ((ballon_violet->x < 0 && ballon_violet->dx < 0) ||
        (ballon_violet->x + ballon_violet->tx > SCREEN_W && ballon_violet->dx > 0))
        ballon_violet->dx = -ballon_violet->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_violet->x = ballon_violet->x + ballon_violet->dx;
    ballon_violet->y = ballon_violet->y + ballon_violet->dy;

}

void actualiserBallon_rouge(t_ballon *ballon_rouge){

    // proba de changement de déplacement : une chance sur 50
    if (rand() % 50 == 0) {
        // Nouveau vecteur déplacement
        ballon_rouge->dx = rand() % 11 - 5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if ((ballon_rouge->x < 0 && ballon_rouge->dx < 0) ||
        (ballon_rouge->x + ballon_rouge->tx > SCREEN_W && ballon_rouge->dx > 0))
        ballon_rouge->dx = -ballon_rouge->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_rouge->x = ballon_rouge->x + ballon_rouge->dx;
    ballon_rouge->y = ballon_rouge->y + ballon_rouge->dy;
}

// Dessiner les ballons sur la bitmap bmp
void dessinerBallon_bleu(BITMAP *bmp,t_ballon *ballon_bleu){
    draw_sprite(bmp,ballon_bleu->img,ballon_bleu->x,ballon_bleu->y);
}
void dessinerBallon_rose(BITMAP *bmp,t_ballon *ballon_rose){
    draw_sprite(bmp,ballon_rose->img,ballon_rose->x,ballon_rose->y);
}
void dessinerBallon_vert(BITMAP *bmp,t_ballon *ballon_vert){
    draw_sprite(bmp,ballon_vert->img,ballon_vert->x,ballon_vert->y);
}
void dessinerBallon_violet(BITMAP *bmp,t_ballon *ballon_violet){
    draw_sprite(bmp,ballon_violet->img,ballon_violet->x,ballon_violet->y);
}
void dessinerBallon_rouge(BITMAP *bmp,t_ballon *ballon_rouge){
    draw_sprite(bmp,ballon_rouge->img,ballon_rouge->x,ballon_rouge->y);
}