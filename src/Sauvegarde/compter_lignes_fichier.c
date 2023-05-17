//
// Created by guych on 16/05/2023.
//

#include "../../header.h"

int compter_lignes_fichier() {

    char ligne[1000];
    int taille = 0;

    FILE * pf;

    pf = fopen("../saves/hscores.txt", "r");

    if (pf == NULL) {

        return 0;
    }

    // On compte le nombre d'entrées de sauvegarde dans le fichier
    while (fgets(ligne, 999, pf)) {

        taille = taille + 1;
    }

    return taille;
}