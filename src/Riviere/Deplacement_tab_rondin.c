//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_tab_rondin(t_rondin * tab_rondin[NRONDIN]) {

    for (int i = 0; i < NRONDIN; ++i) {

        if((tab_rondin[i]->posx < 0)||(tab_rondin[i]->posx + tab_rondin[i]->tx > SCREEN_W )){

            tab_rondin[i]->depx = -tab_rondin[i]->depx;
            //le_rondin->posx = le_rondin->posx + le_rondin->depx;

        }

        tab_rondin[i]->posx = tab_rondin[i]->posx + tab_rondin[i]->depx;



    }

}

