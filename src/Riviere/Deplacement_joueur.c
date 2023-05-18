//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(int Couleur[NOMBRE_JOUEURS], t_rondin *rondin[NRONDIN], t_joueur_riv * joueur_en_train_de_jouer, int Innactivite[NOMBRE_JOUEURS]){


    int bleu;
    bleu = makecol(80, 167, 232);


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        if (Couleur[i] == bleu) {
            joueur_en_train_de_jouer->x = 500;
            joueur_en_train_de_jouer->y = 70;
        }
    }




    if (key[KEY_UP]) {

        joueur_en_train_de_jouer->y = joueur_en_train_de_jouer->y - joueur_en_train_de_jouer->dy;
        joueur_en_train_de_jouer->skin_utilise = 9;

        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            Innactivite[i] = 0;

        }

    }

    if (key[KEY_DOWN]) {

        joueur_en_train_de_jouer->y = joueur_en_train_de_jouer->y + joueur_en_train_de_jouer->dy;
        joueur_en_train_de_jouer->skin_utilise = 0;

        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            Innactivite[i] = 0;

        }
    }

    if (key[KEY_LEFT]) {

        joueur_en_train_de_jouer->x = joueur_en_train_de_jouer->x - joueur_en_train_de_jouer->dx;
        joueur_en_train_de_jouer->skin_utilise = 3;

        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            Innactivite[i] = 0;

        }
    }

    if (key[KEY_RIGHT]) {

        joueur_en_train_de_jouer->x = joueur_en_train_de_jouer->x + joueur_en_train_de_jouer->dx;
        joueur_en_train_de_jouer->skin_utilise = 6;

        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            Innactivite[i] = 0;

        }
    }

    for (int i=0; i<NRONDIN; i++) {

        if (Collision_joueur_rondin(rondin[i], joueur_en_train_de_jouer)) {

            rondin[i]->indice_ligne = 0;

            joueur_en_train_de_jouer->x = rondin[i]->posx + rondin[i]->tx / 3;

            joueur_en_train_de_jouer->dx = 5 + rondin[i]->depx;

            rondin[i]->indice_ligne++;


        }

    }
}