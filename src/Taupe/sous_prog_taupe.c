//
// Created by lucie on 06/05/2023.
//

#include "../../header.h"


void generation_Taupe(t_taupe* taupe){

    taupe->x = rand()%(700-100+1)+100;
    taupe->y = rand()%(600-100+1)+100;
}

void actualiserTaupe(t_taupe* taupe_a_actualiser){

}


void actualiserTabTaupe(t_rondin tab[NRONDIN]) {
    int i;
    for (i = 0; i < NRONDIN; i++) {
        actualiserRondin(tab[i]);
    }
}

void remplirTabTaupe(t_rondin MesRondins[NRONDIN]){
    for (int i = 0; i < NRONDIN; ++i) {
        MesRondins[i] = creerRondin("../assets/Item/Riviere/bois1.bmp");
    }
}



void actualiser_taupe(t_taupe * taupe) {

    if ((mouse_b)&& (mouse_x<=taupe->x) &&(mouse_y<=taupe->y)) {
        printf("TAP !\n");

        taupe->affichage = 0;

    } else {

        //printf("laisser afficher taupe\n");
        //taupe->affichage = 1;
        //masked_blit(taupe->skin,decor,0,0,mesTaupes->x,mesTaupes->y,mesTaupes->tx,mesTaupes->ty);

    }

}



void actualiser_tab_taupe(t_taupe * tableau_taupe) {

    int i;

    for (i=0; i<NOMBRE_TAUPE; i++) {
        if ((mouse_b)&& (mouse_x==tableau_taupe[i].x) &&(mouse_y==tableau_taupe[i].y)) {
            printf("TAP !\n");

            tableau_taupe[i].affichage = 0;

        }

    }

}



int verfication(t_taupe tab_taupe){
    for (int i = 0; i < 79; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (mouse_x == tab_taupe.taille[i][j][0])
                if (mouse_y == tab_taupe.taille[i][j][1])
                    return 1;
        }

    }
    return 0;
}