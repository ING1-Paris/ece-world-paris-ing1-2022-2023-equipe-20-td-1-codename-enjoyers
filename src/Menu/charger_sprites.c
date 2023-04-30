//
// Created by guych on 30/04/2023.
//

#include "../../header.h"

void charger_sprites(t_joueur jouer_actuel, char nom_perso[256]) {

    int i;

    char nom_fichier[256];

    for (i=0; i<13; i++) {

        sprintf(nom_fichier, "../assets/personnages/%s/%s_%d.bmp", nom_perso, nom_perso, i);

        jouer_actuel.sprites[i] = load_bitmap(nom_fichier, NULL);

    }
}