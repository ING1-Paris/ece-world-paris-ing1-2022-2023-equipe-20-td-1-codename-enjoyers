//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Afficher_tab_rondin(BITMAP *bmp, t_rondin *tab_rondin[NRONDIN]){

    for (int i = 0; i < NRONDIN; ++i) {

        Afficher_rondin(bmp,tab_rondin[i]);

    }

}