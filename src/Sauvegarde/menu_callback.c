//
// Created by Leroy on 17/05/2023.
//

#include "../../header.h"

int menu_callback() {

    char str[256];
    char jeu_selectionne[256];
    char affichage_scores[256000];
    char chaine_temp[256000];
    int save_trouvee = 0;

    int taille_tableau_sauvegardes;
    t_entree_sauvegarde * tableau_sauvegardes = NULL;


    // On stocke le jeu selectionne
    ustrzcpy(str, sizeof str, active_menu->text);
    strcpy(jeu_selectionne, ustrtok(str, "\t"));

    // On compte les lignes du fichier afin de determiner la taille du tableau
    taille_tableau_sauvegardes = compter_lignes_fichier();

    if (taille_tableau_sauvegardes == 0) {

        strcpy(affichage_scores, "Il n'y aucun fichier de sauvegarde :/");

    } else {

        // On alloue la taille du tableau
        tableau_sauvegardes = malloc(taille_tableau_sauvegardes * sizeof(t_entree_sauvegarde));

        // On remplit le tableau avec les donnees de sauvegarde
        consulter(tableau_sauvegardes, taille_tableau_sauvegardes);

        // On convertit les entrées de sauvegardes en chaine de caracteres
        // Avant ça, on réinitialise la chaine de caractere contenant les entrees de sauvegarde
        strcpy(affichage_scores, "");

        strcpy(affichage_scores, "  Pseudo:\t\t      Score:\t\t    Temps:\t       Date:\n\n");

        // On affiche les scores en fonction du jeu selectionne
        //SNAKE D EPICES (1)
        if (strcmp(jeu_selectionne, "Snake d'epices") == 0) {


            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 1) {

                    // On reinitialise la chaine temp
                    strcpy(chaine_temp, "");

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    //PROBLEME
                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    printf("%s",chaine_temp);

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }


        }

            //GUY TAHAR NEGRO (2)
        else if (strcmp(jeu_selectionne, "Cupid") == 0){


            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 2 && strcmp(tableau_sauvegardes[i].map, "Cupid (facile)") == 0) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }

        }
        else if (strcmp(jeu_selectionne, "Megalovania") == 0){

            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 2 && strcmp(tableau_sauvegardes[i].map, "Megalovania (difficile)") == 0) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }


        }
        else if (strcmp(jeu_selectionne, "Pirates des Caraibes") == 0){

            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 2 && strcmp(tableau_sauvegardes[i].map, "Pirates des Caraibes (intermediaire)") == 0) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }



        }
            //JEU BALLON (3)
        else if (strcmp(jeu_selectionne, "Explose Ballons") == 0){

            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 3) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }

        }
            //JEU COURSE (4)
        else if (strcmp(jeu_selectionne, "Course de Lapin") == 0){


            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 4) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }

        }
            //JEU TAUPE (5)
        else if (strcmp(jeu_selectionne, "Deratisation") == 0){


            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 5) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }

        }
            //JEU RIVIERE (6)
        else if (strcmp(jeu_selectionne, "La traversee de la mort") == 0){


            for (int i=0; i<taille_tableau_sauvegardes; i++) {

                if (tableau_sauvegardes[i].jeu == 6) {

                    //il existe une save de ce jeu
                    save_trouvee = 1;

                    sprintf(chaine_temp, "%8s\t\t%8d pts\t\t%8d s\t\t%8s \n",tableau_sauvegardes[i].nom,tableau_sauvegardes[i].score,tableau_sauvegardes[i].temps, ctime(&tableau_sauvegardes[i].date));

                    strcat(affichage_scores, chaine_temp);
                }
            }


            if (!save_trouvee) {

                strcpy(affichage_scores, "Il n'y aucune sauvegarde de ce jeu :/");
            }

        }

        strcpy(active_dialog[6].dp, affichage_scores);

        free(tableau_sauvegardes);

    }


    return D_REDRAW;
}
