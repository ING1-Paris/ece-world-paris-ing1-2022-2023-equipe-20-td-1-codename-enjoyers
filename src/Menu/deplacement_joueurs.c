//
// Created by guych on 01/05/2023.
//

#include "../../header.h"

void deplacement_joueurs(BITMAP * bmp, t_joueur tableau_joueurs[NOMBRE_JOUEURS], t_hitbox tab_hitboxes[NOMBRE_HITBOXES]) {

    int compteur = 0;
    int i;

    // DEPLACEMENTS DU JOUEUR 1
    if (key[KEY_UP]) {

        // Controle des bords de la fenetre
        if (tableau_joueurs[0].y < 0) {

            // on bloque

        } else {

            tableau_joueurs[0].y = tableau_joueurs[0].y - tableau_joueurs[0].dy;

        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[0])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[0].y = tableau_joueurs[0].y + tableau_joueurs[0].dy;

            }


        }


    }


    if (key[KEY_DOWN]) {

        if (tableau_joueurs[0].y + tableau_joueurs[0].ty >= SCREEN_H) {

            // on bloque

        } else {

            tableau_joueurs[0].y = tableau_joueurs[0].y + tableau_joueurs[0].dy;
        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[0])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[0].y = tableau_joueurs[0].y - tableau_joueurs[0].dy;

            }

        }



    }


    if (key[KEY_RIGHT]) {

        if (tableau_joueurs[0].x + tableau_joueurs[0].tx >= SCREEN_W) {

            // on bloque

        } else {

            tableau_joueurs[0].x = tableau_joueurs[0].x + tableau_joueurs[0].dx;

        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[0])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[0].x = tableau_joueurs[0].x - tableau_joueurs[0].dx;

            }

        }




    }


    if (key[KEY_LEFT]) {

        if (tableau_joueurs[0].x < 0) {

            // on bloque

        } else {

            tableau_joueurs[0].x = tableau_joueurs[0].x - tableau_joueurs[0].dx;
        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[0])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[0].x = tableau_joueurs[0].x + tableau_joueurs[0].dx;

            }

        }



    }














    // DEPLACEMENTS DU JOUEUR 2 (attention les touches sont mappées en qwerty)
    if (key[KEY_W]) {

        // Controle des bords de la fenetre
        if (tableau_joueurs[1].y < 0) {

            // on bloque

        } else {

            tableau_joueurs[1].y = tableau_joueurs[1].y - tableau_joueurs[1].dy;
        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[1])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[1].y = tableau_joueurs[1].y + tableau_joueurs[1].dy;

            }

        }



    }


    if (key[KEY_S]) {

        if (tableau_joueurs[1].y + tableau_joueurs[1].ty >= SCREEN_H) {

            // on bloque

        } else {

            tableau_joueurs[1].y = tableau_joueurs[1].y + tableau_joueurs[1].dy;
        }


        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[1])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[1].y = tableau_joueurs[1].y - tableau_joueurs[1].dy;

            }


        }



    }


    if (key[KEY_D]) {

        if (tableau_joueurs[1].x + tableau_joueurs[1].tx >= SCREEN_W) {

            // on bloque

        } else {

            tableau_joueurs[1].x = tableau_joueurs[1].x + tableau_joueurs[1].dx;

        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[1])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[1].x = tableau_joueurs[1].x - tableau_joueurs[1].dx;

            }

        }


    }


    if (key[KEY_A]) {

        if (tableau_joueurs[1].x < 0) {

            // on bloque

        } else {

            tableau_joueurs[1].x = tableau_joueurs[1].x - tableau_joueurs[1].dx;
        }

        for (i=0; i<NOMBRE_HITBOXES; i++) {

            if (collision_joueur_hitbox(&tab_hitboxes[i], &tableau_joueurs[1])) {

                // on bloque

                printf("Collision ! \n");

                tableau_joueurs[1].x = tableau_joueurs[1].x + tableau_joueurs[1].dx;

            }

        }



    }



}