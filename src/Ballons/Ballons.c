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

    nouv->x = SCREEN_W/2-nouv->tx/2;
    nouv->y = SCREEN_H/3-nouv->ty/2;
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

    nouv->x = SCREEN_W/4-nouv->tx/2;
    nouv->y = SCREEN_H/5-nouv->ty/2;
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

    nouv->x = SCREEN_W/2-nouv->tx/2;
    nouv->y = SCREEN_H/3-nouv->ty/2;
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

    nouv->x = SCREEN_W*2/3-nouv->tx/2;
    nouv->y = SCREEN_H/2-nouv->ty/2;
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

    nouv->x = SCREEN_W/4-nouv->tx/2;
    nouv->y = SCREEN_H/7-nouv->ty/2;
    nouv->dx=0;
    nouv->dy=0;

    return nouv ;
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