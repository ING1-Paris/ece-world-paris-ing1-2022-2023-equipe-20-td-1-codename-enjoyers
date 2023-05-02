//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void spawn_cercles(BITMAP * bmp, t_note * note_a_jouer) {

    note_a_jouer->affichage = 1;

    circlefill(bmp, note_a_jouer->x_centre, note_a_jouer->y_centre, note_a_jouer->radius, note_a_jouer->couleur);
}