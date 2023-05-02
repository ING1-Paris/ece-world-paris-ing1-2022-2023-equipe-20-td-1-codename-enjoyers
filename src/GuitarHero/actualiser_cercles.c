//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void actualiser_cercle(t_note * note_a_jouer) {


    if (note_a_jouer->y_centre >= 675) {

        note_a_jouer->affichage = 0;

    } else {

        note_a_jouer->y_centre = note_a_jouer->y_centre + note_a_jouer->dy;
    }




}