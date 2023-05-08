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


void actualiserTabTaupe(t_rondin * tab[NRONDIN]) {
    int i;
    for (i = 0; i < NRONDIN; i++) {
        actualiserRondin(tab[i]);
    }
}

void remplirTabTaupe(t_rondin* MesRondins[NRONDIN]){
    for (int i = 0; i < NRONDIN; ++i) {
        MesRondins[i] = creerRondin("../assets/Item/Riviere/bois1.bmp");
    }
}