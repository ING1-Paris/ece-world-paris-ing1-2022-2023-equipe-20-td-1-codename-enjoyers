//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void actualiser_tab_cercles(BITMAP * bmp, t_note * tableau_notes, int taille_tab) {

    int i;

    clear(bmp);

    for (i=0; i<taille_tab; i++) {

        if (tableau_notes[i].affichage == 1) {

            actualiser_cercle(&tableau_notes[i]);
        }
    }



}
