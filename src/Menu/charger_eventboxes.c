//
// Created by guych on 01/05/2023.
//

#include "../../header.h"

void charger_eventboxes(BITMAP * bmp, t_hitbox tab_eventboxes[NOMBRE_EVENTBOXES]) {

    // Procédure de chargement des eventboxes

    int i;
    int couleur = makecol(0, 255, 0);


    for (i=0; i<NOMBRE_EVENTBOXES; i++) {

        rectfill(bmp, tab_eventboxes[i].x1, tab_eventboxes[i].y1, tab_eventboxes[i].x2, tab_eventboxes[i].y2, couleur);
    }
}