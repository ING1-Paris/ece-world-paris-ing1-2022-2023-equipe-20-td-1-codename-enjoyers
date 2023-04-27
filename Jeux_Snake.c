//
// Created by Leroy on 27/04/2023.
//
#include "header.h"

void Snake(){
    BITMAP* page;
    BITMAP* decor;
    BITMAP* SNAKE1[4];
    char nomfichier[256];

    page = create_bitmap(1000,800);
    clear(page);

    decor = load_bitmap("images/Snake/Map_Snake.bmp",NULL);
    if (!decor){
        allegro_message("Impossible de charger le decor de Snake");
        exit(EXIT_FAILURE);
    }
    // charger les images de la séquence d'animation
    for (int i=0;i<4;i++) {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier, "images/Snake/Snake_1%d.bmp", i+1);

        SNAKE1[i] = load_bitmap(nomfichier, NULL);
        if (!SNAKE1[i]) {
            allegro_message("pas pu trouver %s", nomfichier);
            exit(EXIT_FAILURE);
        }
    }


    while (!key[KEY_ESC]){
        blit(decor,page,0,0,0,0,1000,800);
        blit(page,screen,0,0,0,0,1000,800);
    }

}