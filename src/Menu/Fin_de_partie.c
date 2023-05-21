//
// Created by leroy on 11/05/2023.
//
#include "../../header.h"

void Fin_du_jeu(BITMAP * page,t_joueur tableau_joueurs[NOMBRE_JOUEURS]){

    PlaySound(TEXT("../assets/Item/Menu/Kiss.wav"), NULL, SND_ASYNC);

    BITMAP *ecran_de_fin = load_bitmap("../assets/Item/Menu/Fin_de_Partie.bmp", NULL);


    stretch_blit(ecran_de_fin, page, 0,0,960,671,0,0, SCREEN_W, SCREEN_H);

    rectfill(page,SCREEN_W / 2 - 200,60,SCREEN_W / 2 +200,100, makecol(255,255,255));
    rect(page,SCREEN_W / 2 - 200,60,SCREEN_W / 2 +200,100, makecol(0,0,0));
    if (tableau_joueurs[0].tickets == 0) {

        stretch_blit(tableau_joueurs[1].sprites[12], page, 0, 0, 225, 225, SCREEN_W / 2 - 75, 125, 150, 150);
        textprintf_ex(page,font,SCREEN_W / 2 - 190, 75, makecol(0,0,0),-1,"%s gagne le jeu, felicitations !",tableau_joueurs[1].nom);

    } else {

        stretch_blit(tableau_joueurs[0].sprites[12], page, 0, 0, 225, 225, SCREEN_W / 2 - 75, 125, 150, 150);
        textprintf_ex(page,font,SCREEN_W / 2 - 190, 75, makecol(0,0,0),-1,"%s gagne le jeu, felicitations !",tableau_joueurs[0].nom);
    }

    rect(page, SCREEN_W / 2 - 75, 125, SCREEN_W / 2 - 75 + 150, 275, makecol(0, 0, 0));

    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    statistique();


    PlaySound(NULL, 0, 0);

}