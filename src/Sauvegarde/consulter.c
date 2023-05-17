//
// Created by guych on 12/05/2023.
//

#include "../../header.h"

int consulter(t_entree_sauvegarde * tab_de_sauvegarde, int taille_tab) {

    // Initialisation des séparateurs
    char * strToken;
    char * separateur = ">";

    // Initialisation des variables de lecture de donnees
    char ligne[1000];
    int i;
    int j;
    int compteur_entrees = 0;

    // Ouverture du fichier des scores
    FILE * pf = NULL;

    pf = fopen("../saves/hscores.txt", "r");


    if (pf == NULL) {

        return 0;

    } else {

        if (taille_tab == 0) {

            return 0;
        }

        i = 0;

        // Lecture des données et remplissage du tableau
        while (fgets(ligne, 999, pf) && i < taille_tab) {

            j = 0;

            strToken = strtok(ligne, separateur);

            while (strToken != NULL) {

                if (j == 0) { //Jeu

                    tab_de_sauvegarde[i].jeu = atoi(strToken);

                } else if (j == 1) { //Score (pas d'info ? var = '!')

                    tab_de_sauvegarde[i].score = atoi(strToken);

                } else if (j == 2) { //Temps (pas d'info ? var = '!')

                    tab_de_sauvegarde[i].temps = atoi(strToken);

                } else if (j == 3) { //Date

                    tab_de_sauvegarde[i].date = atoi(strToken);

                } else if (j == 4) { //Map (pas d'info ? var = '!')

                    strcpy(tab_de_sauvegarde[i].map, strToken);

                } else if (j == 5){ //Nom

                    strToken[strcspn(strToken, "\n")] = 0;

                    strcpy(tab_de_sauvegarde[i].nom, strToken);

                }

                j = j + 1;

                strToken = strtok(NULL, separateur);
            }

            i = i + 1;
        }

        for (i=0; i<taille_tab; i++) {

            printf("%d %d %d %d %s %s \n", tab_de_sauvegarde[i].jeu, tab_de_sauvegarde[i].score, tab_de_sauvegarde[i].temps, tab_de_sauvegarde[i].date, tab_de_sauvegarde[i].map, tab_de_sauvegarde[i].nom);
        }

        fclose(pf);


        return 1;
    }
}