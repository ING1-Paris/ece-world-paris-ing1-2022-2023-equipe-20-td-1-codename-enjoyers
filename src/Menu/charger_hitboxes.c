//
// Created by guych on 01/05/2023.
//

#include "../../header.h"

void charger_hitboxes(BITMAP * bmp, t_hitbox tab_hitboxes[NOMBRE_HITBOXES], int couleur) {

    // Procédure de chargement des hitboxes des maisons

    int i;


    for (i=0; i<NOMBRE_HITBOXES; i++) {

        rectfill(bmp, tab_hitboxes[i].x1, tab_hitboxes[i].y1, tab_hitboxes[i].x2, tab_hitboxes[i].y2, couleur);
    }

}