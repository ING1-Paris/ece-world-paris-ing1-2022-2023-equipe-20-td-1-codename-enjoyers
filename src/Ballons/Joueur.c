//
// Created by thais on 15/05/2023.
//
#include "../../header.h"


// Allouer et initialiser un joueur
t_joueur_ballons * creerJoueur(char *nomimage){
    t_joueur_ballons *nouv;

    // Allouer
    nouv = (t_joueur_ballons *)malloc(1*sizeof(t_joueur_ballons));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/2-nouv->tx/2; //emplacement du joueur (le fusil) sur la bitmap
    nouv->y = SCREEN_H*7/8-nouv->ty/2;
    nouv->vit = 5;

    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;

    return nouv;
}

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur_ballons *joueur,t_listeActeurs *la){

    // Déplacements avec les flèches du clavier // le fusil est bloqué sur les bords de l'écran

    if (key[KEY_LEFT]){
        joueur->x -= joueur->vit;
        if (joueur->x<0)
            joueur->x=0;
    }

    if (key[KEY_RIGHT]){
        joueur->x += joueur->vit;
        if (joueur->x+joueur->tx > SCREEN_W)
            joueur->x=SCREEN_W-joueur->tx;
    }

    // Gestion du tir : incrémenter la tempo des tirs
    joueur->cpttir0++;
    joueur->cpttir1++;

    // si le joueur appui sur la gachette (barre d'espace), un acteur est lancé (une balle est tirée)
    if (key[KEY_SPACE] && joueur->cpttir0>=5){
        ajouterActeur(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,0);
        joueur->cpttir0 = 0;
    }

}

// Dessiner joueur sur la bitmap
void dessinerJoueur(BITMAP *bmp,t_joueur_ballons *joueur){
    draw_sprite(bmp,joueur->img,joueur->x,joueur->y);
}
