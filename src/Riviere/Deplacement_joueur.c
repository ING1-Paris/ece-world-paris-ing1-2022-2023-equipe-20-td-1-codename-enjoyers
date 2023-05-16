//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(t_rondin *rondin[NRONDIN], t_joueur_riv * joueur_en_train_de_jouer){


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

        if (Collision_joueur_rondin(rondin[i], joueur_en_train_de_jouer)) {

            rondin[i]->indice_ligne = 0;

            joueur_en_train_de_jouer->x = rondin[i]->posx + (rondin[i]->tx / 2);
            joueur_en_train_de_jouer->dx = 5 + rondin[i]->depx;

            rondin[i]->indice_ligne++;


        }

        else if ((joueur_en_train_de_jouer->x>SCREEN_W)||(joueur_en_train_de_jouer->x==0)){

            joueur_en_train_de_jouer->x = 500;
            joueur_en_train_de_jouer->y = 70;

        }
    }


}