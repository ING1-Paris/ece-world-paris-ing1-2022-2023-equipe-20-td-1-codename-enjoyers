//
// Created by guych on 30/04/2023.
//

#include "../../header.h"

void charger_sprites(t_joueur * joueur_actuel, char nom_perso[256]) {

    int k;

    char nom_fichier[256];

    for (k=0; k<13; k++) {

        sprintf(nom_fichier, "../assets/personnages/%s/%s_%d.bmp", nom_perso, nom_perso, k);

        joueur_actuel->sprites[k] = load_bitmap(nom_fichier, NULL);

    }
}