//
// Created by guych on 01/05/2023.
//

#include "../../header.h"

void deplacement_joueurs(t_joueur tableau_joueurs[NOMBRE_JOUEURS],int innactivite[NOMBRE_JOUEURS]) {
    //Inactivite permet de savoir quand le Joueur est immobile


    // DEPLACEMENTS DU JOUEUR 1

    if (key[KEY_UP]) {

        // Controle des bords de la fenetre
        if (tableau_joueurs[0].y < 0) {

            // on bloque

        } else {

            tableau_joueurs[0].y = tableau_joueurs[0].y - tableau_joueurs[0].dy;
            tableau_joueurs[0].Sprite_actif = 9;
            innactivite[0] = 0;
        }

    }


    if (key[KEY_DOWN]) {

        if (tableau_joueurs[0].y + tableau_joueurs[0].ty >= SCREEN_H) {

            // on bloque

        } else {

            tableau_joueurs[0].y = tableau_joueurs[0].y + tableau_joueurs[0].dy;
            tableau_joueurs[0].Sprite_actif = 0;
            innactivite[0] = 0;
        }

    }


    if (key[KEY_RIGHT]) {

        if (tableau_joueurs[0].x + tableau_joueurs[0].tx >= SCREEN_W) {

            // on bloque

        } else {

            tableau_joueurs[0].x = tableau_joueurs[0].x + tableau_joueurs[0].dx;
            tableau_joueurs[0].Sprite_actif = 6;
            innactivite[0] = 0;

        }


    }


    if (key[KEY_LEFT]) {

        if (tableau_joueurs[0].x < 0) {

            // on bloque

        } else {

            tableau_joueurs[0].x = tableau_joueurs[0].x - tableau_joueurs[0].dx;
            tableau_joueurs[0].Sprite_actif = 3;
            innactivite[0] = 0;
        }

    }














    // DEPLACEMENTS DU JOUEUR 2 (attention les touches sont mappées en qwerty)
    if (key[KEY_W]) {

        // Controle des bords de la fenetre
        if (tableau_joueurs[1].y < 0) {

            // on bloque

        } else {

            tableau_joueurs[1].y = tableau_joueurs[1].y - tableau_joueurs[1].dy;
            tableau_joueurs[1].Sprite_actif = 9;
            innactivite[1] = 0;
        }

    }


    if (key[KEY_S]) {

        if (tableau_joueurs[1].y + tableau_joueurs[1].ty >= SCREEN_H) {

            // on bloque

        } else {

            tableau_joueurs[1].y = tableau_joueurs[1].y + tableau_joueurs[1].dy;
            tableau_joueurs[1].Sprite_actif = 0;
            innactivite[1] = 0;
        }

    }


    if (key[KEY_D]) {

        if (tableau_joueurs[1].x + tableau_joueurs[1].tx >= SCREEN_W) {

            // on bloque

        } else {

            tableau_joueurs[1].x = tableau_joueurs[1].x + tableau_joueurs[1].dx;
            tableau_joueurs[1].Sprite_actif = 6;
            innactivite[1] = 0;

        }


    }


    if (key[KEY_A]) {

        if (tableau_joueurs[1].x < 0) {

            // on bloque

        } else {

            tableau_joueurs[1].x = tableau_joueurs[1].x - tableau_joueurs[1].dx;
            tableau_joueurs[1].Sprite_actif = 3;
            innactivite[1] = 0;
        }

    }



}