//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void charger_interface(BITMAP * bmp, t_cercle_fixe tab_cercles_fixes[5], t_joueur * tab_joueurs) {

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

    
    
    // Affichage des joueurs
    //J1
    rectfill(bmp,10,10,250,70,makecol(255,255,255));
    rect(bmp,10,10,250,70,makecol(0,0,0));
    stretch_blit(tab_joueurs[0].sprites[12],bmp,0,0,225,225,15,15,50,50);

    textprintf_ex(bmp,font,70, 30, makecol(0,0,0),-1,"%s",tab_joueurs[0].nom);
    textprintf_ex(bmp,font,70, 50, makecol(0,0,0),-1,"Score: %d",tab_joueurs[0].score);

    //J2
    rectfill(bmp,SCREEN_W-250,10,SCREEN_W-10,70,makecol(255,255,255));
    rect(bmp,SCREEN_W-250,10,SCREEN_W-10,70,makecol(0,0,0));
    stretch_blit(tab_joueurs[1].sprites[12],bmp,0,0,225,225,SCREEN_W-250+5,15,50,50);

    textprintf_ex(bmp,font,SCREEN_W-250+5+55, 30, makecol(0,0,0),-1,"%s",tab_joueurs[1].nom);
    textprintf_ex(bmp,font,SCREEN_W-250+5+55, 50, makecol(0,0,0),-1,"Score: %d",tab_joueurs[1].score);
}