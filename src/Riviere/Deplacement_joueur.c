//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(t_rondin * tab_rondins[NRONDIN], t_joueur_riv * joueur_en_train_de_jouer, int Innactivite[NOMBRE_JOUEURS]){


    // Initialisation de la couleur bleue de la riviere
    int bleu = makecol(80, 167, 232) ;

    // Algorithme de déplacement du joueur
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

    // Détection de collisions du joueur avec les rondins
    for (int i=0; i<NRONDIN; i++) {

        if (Collision_joueur_rondin(tab_rondins[i], joueur_en_train_de_jouer)) {

            joueur_en_train_de_jouer->x = tab_rondins[i]->posx + tab_rondins[i]->tx/2;
            joueur_en_train_de_jouer->dx = 5 + tab_rondins[i]->depx;

        } else {

            if ((joueur_en_train_de_jouer->couleur == bleu) && (!(Collision_joueur_rondin(tab_rondins[i], joueur_en_train_de_jouer)))) {

                joueur_en_train_de_jouer->x = 400; // On le fait reculer un peu plus pour qu'il évite de tout de suite foncer dans l'eau
                joueur_en_train_de_jouer->y = 70;
                joueur_en_train_de_jouer->dx = 5;
                joueur_en_train_de_jouer->dy = 5;

            }


        }

    }

}