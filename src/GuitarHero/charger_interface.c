//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void charger_interface(BITMAP * bmp, t_cercle_fixe tab_cercles_fixes[5]) {

    int x1_jaune = SCREEN_W / 2 - 25;
    int x2_jaune = SCREEN_W / 2 + 25;

    int x1_bleu = x2_jaune + 10;
    int x2_bleu = x1_bleu + 50;

    int x1_orange = x2_bleu + 10;
    int x2_orange = x1_orange + 50;

    int x1_rouge = x1_jaune - 60;
    int x2_rouge = x1_rouge + 50;

    int x1_vert = x1_rouge - 60;
    int x2_vert = x1_vert + 50;


    // Affichage du rectangle jaune au milieu
    rectfill(bmp, x1_jaune, 700, x2_jaune, 710, makecol(255, 255, 0));

    // Affichage du rectangle bleu
    rectfill(bmp, x1_bleu, 700, x2_bleu, 710, makecol(0, 0, 255));

    // Affichage du rectangle orange
    rectfill(bmp, x1_orange, 700, x2_orange, 710, makecol(255, 155, 0));

    // Affichage du rectangle rouge
    rectfill(bmp, x1_rouge, 700, x2_rouge, 710, makecol(255, 0, 0));

    // Affichage du rectangle vert
    rectfill(bmp, x1_vert, 700, x2_vert, 710, makecol(0, 255, 0));




    // Affichage des cercles fixes

    for (int i=0; i<5; i++) {

        circle(bmp, tab_cercles_fixes[i].x_centre, tab_cercles_fixes[i].y_centre, tab_cercles_fixes[i].radius, tab_cercles_fixes[i].couleur);
    }

}