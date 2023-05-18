//
// Created by guych on 12/05/2023.
//

#include "../../header.h"

void sauvegarder(t_entree_sauvegarde tab_sauvegardes_session[NOMBRE_JOUEURS]) {

    // Creation du tableau de sauvegardes
    t_entree_sauvegarde * tableau_sauvegardes = NULL;
    int taille_tableau_sauvegardes;

    // Ouverture ou création du fichier des scores
    FILE * pf = NULL;

    pf = fopen("../saves/hscores.txt", "r");

    if (pf == NULL) {

        pf = fopen("../saves/hscores.txt", "w+");

        if (pf == NULL) {

            allegro_message("Impossible de créer le fichier de sauvegarde :/ Vérifier les permissions et le dossier d'installation du jeu !");
            allegro_exit();
            exit(EXIT_FAILURE);

        }

    }

    // On compte les lignes du fichier afin de determiner la taille du tableau
    taille_tableau_sauvegardes = compter_lignes_fichier();

    // On alloue la taille du tableau
    tableau_sauvegardes = malloc(taille_tableau_sauvegardes * sizeof(t_entree_sauvegarde));

    // Si il y a présence de scores enregistrés, on récupère les donnéees puis on écrase le fichier ; sinon, on les écrit simplement
    if (consulter(tableau_sauvegardes, taille_tableau_sauvegardes)) {

        //Rajout des 2 valeurs en train d'etre save
        taille_tableau_sauvegardes = taille_tableau_sauvegardes + 2;

        printf("%d", taille_tableau_sauvegardes);

        // On realloue la taille du tableau en ajoutant 2 places pour les deux nouvelles donnéees
        tableau_sauvegardes = realloc(tableau_sauvegardes, taille_tableau_sauvegardes * sizeof(t_entree_sauvegarde));

        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

            tableau_sauvegardes[taille_tableau_sauvegardes-(i+1)] = tab_sauvegardes_session[i];

        }

        // On trie le tableau
        triInsertion(tableau_sauvegardes, taille_tableau_sauvegardes);

        // On remplit le tableau
        pf = fopen("../saves/hscores.txt", "w+");

        // On écrit les donnéees sur le fichier
        for (int i=0; i<taille_tableau_sauvegardes; i++) {

            fprintf(pf, "%d>%d>%d>%d>%s>%s", tableau_sauvegardes[i].jeu, tableau_sauvegardes[i].score, tableau_sauvegardes[i].temps, tableau_sauvegardes[i].date, tableau_sauvegardes[i].map, tableau_sauvegardes[i].nom);

            fprintf(pf, "\n");
        }

        // On ferme le fichier
        fclose(pf);


    } else { // Fichier existant, mais vide de données

        // On trie juste les deux données que l'on a
        triInsertion(tab_sauvegardes_session, NOMBRE_JOUEURS);

        // On remplit le tableau
        pf = fopen("../saves/hscores.txt", "w+");

        // On écrit ces données sur le fichier
        for (int i=0; i<NOMBRE_JOUEURS; i++) {

            fprintf(pf, "%d>%d>%d>%d>%s>%s\n", tab_sauvegardes_session[i].jeu, tab_sauvegardes_session[i].score, tab_sauvegardes_session[i].temps, tab_sauvegardes_session[i].date, tab_sauvegardes_session[i].map, tab_sauvegardes_session[i].nom);
        }

        // On ferme le fichier
        fclose(pf);

    }

}