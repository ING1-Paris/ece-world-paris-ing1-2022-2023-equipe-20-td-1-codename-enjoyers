//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

t_note * charger_musique(char nom_musique[256], int * taille_tab, int * tempo) {

    FILE * pf;
    t_note * tableau_notes = NULL;
    char nom_fichier[256];

    char ligne[1000];
    char * strToken;

    int compteur_notes = 0;
    int i = 0;
    int j = 0;

    sprintf(nom_fichier, "../assets/Item/GuitarHero/%s.csv", nom_musique);

    pf = fopen(nom_fichier, "r");

    if (pf == NULL) {

        allegro_message("Impossible d'ouvrir le fichier %s. Le fichier est introuvable ?", nom_fichier);

        allegro_exit();
        exit(EXIT_FAILURE);
    }


    while (fgets(ligne, 255, pf)) {

        if (strstr(ligne, "Note_on_c") != NULL) {

            compteur_notes = compteur_notes + 1;

        } else if (strstr(ligne, "Tempo") != NULL) {

            strToken = strtok(ligne, ",");

            while (strToken != NULL) {

                if (j == 3) {

                    *tempo = atoi(strToken);
                }

                j = j + 1;

                strToken = strtok(NULL, ",");
            }
        }

    }

    rewind(pf);

    tableau_notes = malloc(compteur_notes * (sizeof (t_note)));


    while (fgets(ligne, 1000, pf)) {

        if (strstr(ligne, "Note_on_c") != NULL) {

            strToken = strtok(ligne, ",");

            while (strToken != NULL) {

                if (j == 0) {

                    tableau_notes[i].portee = atoi(strToken);

                } else if (j == 1) {

                    tableau_notes[i].millis = atoi(strToken);

                } else if (j == 4) {

                    tableau_notes[i].note = atoi(strToken);
                }

                j = j + 1;

                strToken = strtok(NULL, ",");

            }

            i = i + 1;
        }

        j = 0;

    }

    *taille_tab = compteur_notes;

    fclose(pf);

    return tableau_notes;

}