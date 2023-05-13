//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(t_rondin * rondin, t_joueur_riv * joueur_en_train_de_jouer, int innactivite[NOMBRE_JOUEURS]){


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


}