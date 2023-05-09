//
// Created by Leroy on 08/05/2023.
//
#include "../../header.h"

void Acceuil(){

    BITMAP * page;
    BITMAP * Affiche= NULL;
    int compteur_temporel = 0;

    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    Affiche = load_bitmap("../assets/Item/Menu/Ecran_d_acceuil.bmp",NULL);
    PlaySound(TEXT("../assets/Item/Menu/All-Star.wav"), NULL, SND_ASYNC);

    while (!key[KEY_SPACE]){

        blit(Affiche,page,0,0,0,0,SCREEN_W, SCREEN_H);

        if (compteur_temporel>=500){
            textprintf_ex(page,font,400,700, makecol(255,255,255),-1,"Press Space to Start !");

        }
        if(compteur_temporel==1000){
            compteur_temporel = 0;
        }

        compteur_temporel++;

        blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);

    }

}