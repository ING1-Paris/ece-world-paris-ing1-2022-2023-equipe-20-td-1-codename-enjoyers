//
// Created by guych on 16/05/2023.
//

#include "../../header.h"

void remplir_tab_sauvegardes(t_entree_sauvegarde tab_donnees[NOMBRE_JOUEURS], t_joueur tab_joueurs[NOMBRE_JOUEURS], int tab_temps[NOMBRE_JOUEURS], int choix_jeu) {

    int i;

    if (choix_jeu == 1) { // Snake

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            tab_donnees[i].jeu = choix_jeu;
            tab_donnees[i].score = tab_joueurs[i].score;
            tab_donnees[i].temps = tab_temps[i];
            tab_donnees[i].date = time(NULL);
            strcpy(tab_donnees[i].map, "!");
            strcpy(tab_donnees[i].nom, tab_joueurs[i].nom);

        }

    } else if (choix_jeu == 2) { // Guitar Hero

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            tab_donnees[i].jeu = choix_jeu;
            tab_donnees[i].score = tab_joueurs[i].score;
            tab_donnees[i].temps = -1;
            tab_donnees[i].date = time(NULL);
            // La map est renseignée a partir du jeu
            strcpy(tab_donnees[i].nom, tab_joueurs[i].nom);

        }

    } else if (choix_jeu == 3) { // Tir aux ballons

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            tab_donnees[i].jeu = choix_jeu;
            tab_donnees[i].score = -1;
            tab_donnees[i].temps = tab_temps[i];
            tab_donnees[i].date = time(NULL);
            strcpy(tab_donnees[i].map, "!");
            strcpy(tab_donnees[i].nom, tab_joueurs[i].nom);

        }

    } else if (choix_jeu == 4) { // Course (de lapins)

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            tab_donnees[i].jeu = choix_jeu;
            tab_donnees[i].score = tab_joueurs[i].score;
            tab_donnees[i].temps = -1;
            tab_donnees[i].date = time(NULL);
            strcpy(tab_donnees[i].map, "!");
            strcpy(tab_donnees[i].nom, tab_joueurs[i].nom);

        }

    } else if (choix_jeu == 5) { // Taupes

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            tab_donnees[i].jeu = choix_jeu;
            tab_donnees[i].score = tab_joueurs[i].score;
            tab_donnees[i].temps = -1;
            tab_donnees[i].date = time(NULL);
            strcpy(tab_donnees[i].map, "!");
            strcpy(tab_donnees[i].nom, tab_joueurs[i].nom);

        }


    } else if (choix_jeu == 6) { // Riviere

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            tab_donnees[i].jeu = choix_jeu;
            tab_donnees[i].score = -1;
            tab_donnees[i].temps = tab_temps[i];
            tab_donnees[i].date = time(NULL);
            strcpy(tab_donnees[i].map, "!");
            strcpy(tab_donnees[i].nom, tab_joueurs[i].nom);

        }
    }

    for (i=0; i<NOMBRE_JOUEURS; i++) {

        tab_joueurs[i].score = 0;
        tab_temps[i] = 0;
    }

}