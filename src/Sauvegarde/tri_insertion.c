//
// Created by guych on 12/05/2023.
//

#include "../../header.h"

void triInsertion(t_entree_sauvegarde * tableau, int taille_tab) {

    int i;
    int j;
    t_entree_sauvegarde tmp;


    // On commence par trier par jeu
    for (i=1 ; i <= taille_tab-1; i++) {

        j = i;

        while (j > 0 && tableau[j-1].jeu < tableau[j].jeu) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }
    }

    // Puis on trie temps, scores en fonction du jeu en question
    for (i=1 ; i <= taille_tab-1; i++) {

        j = i;

        // Snake
        while (j > 0 && tableau[j-1].score < tableau[j].score && tableau[j].jeu == 1) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }

        // Guitar Hero
        while (j > 0 && tableau[j-1].score < tableau[j].score && tableau[j].jeu == 2) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }

        // Ballons
        while (j > 0 && tableau[j-1].temps < tableau[j].temps && tableau[j].jeu == 3) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }

        // Course
        while (j > 0 && tableau[j-1].score < tableau[j].score && tableau[j].jeu == 4) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }

        // Taupe
        while (j > 0 && tableau[j-1].score < tableau[j].score && tableau[j].jeu == 5) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }

        // Riviere
        while (j > 0 && tableau[j-1].temps < tableau[j].temps && tableau[j].jeu == 6) {

            tmp = tableau[j];
            tableau[j] = tableau[j-1];
            tableau[j-1] = tmp;

            j--;
        }


    }




}