//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(t_rondin rondin[NRONDIN], t_joueur_riv joueur[NOMBRE_JOUEURS], int innactivite[NOMBRE_JOUEURS]){


    if (key[KEY_UP]) {

        joueur_en_train_de_jouer->y = joueur_en_train_de_jouer->y - joueur_en_train_de_jouer->dy;


    }

    if (key[KEY_DOWN]) {

        joueur_en_train_de_jouer->y = joueur_en_train_de_jouer->y + joueur_en_train_de_jouer->dy;

    }

    if (key[KEY_LEFT]) {

        joueur_en_train_de_jouer->x = joueur_en_train_de_jouer->x - joueur_en_train_de_jouer->dx;

    }

    if (key[KEY_RIGHT]) {

        joueur_en_train_de_jouer->x = joueur_en_train_de_jouer->x + joueur_en_train_de_jouer->dx;

    }

    for (int i=0; i<NRONDIN; i++) {

        if (Collision_joueur_rondin(&rondin[i], joueur_en_train_de_jouer)) {

            joueur_en_train_de_jouer->x = rondin[i].posx + (rondin[i].tx / 2);

            joueur_en_train_de_jouer->dx = 10 + rondin[i].depx;

        }
    }



    if(Collision_joueur_rondin(rondin, &joueur[0])){

        if (key[KEY_DOWN])
        {
            joueur[0].y = joueur[0].y + joueur[0].vit;
            joueur[0].skin_utilise = 0;

            //innactivite[0] = 0;
            printf("sur un rondin\n");
        }

        joueur[0].x = rondin->posx;
        joueur[0].y = rondin->posy;
    }

    else {

        //dans l'eau = retour à la position initiale
        joueur[0].y = 145;
        joueur[0].x = 500;

        printf("dans l'eau\n");
    }

}