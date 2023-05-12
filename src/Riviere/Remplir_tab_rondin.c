//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Remplir_tab_rondin(t_rondin * tableau_de_rondin[NRONDIN]) {


    for (int i = 0; i < NRONDIN; ++i) {

        tableau_de_rondin[i] = Creation_rondin(i);
    }




/*tableau_de_rondin[2] = Creation_rondin(180, rand()%(SCREEN_W), 1, 1, 4);
tableau_de_rondin[3] = Creation_rondin(220, rand()%(SCREEN_W),-1, 1, 6);
tableau_de_rondin[4] = Creation_rondin(240, rand()%(SCREEN_W),1, 2, 4);
tableau_de_rondin[5] = Creation_rondin(280, rand()%(SCREEN_W),-1, 1, 4);
tableau_de_rondin[6] = Creation_rondin(320, rand()%(SCREEN_W),1, 1, 4);
tableau_de_rondin[7] = Creation_rondin(340, rand()%(SCREEN_W),-1, 1, 4);
tableau_de_rondin[8] = Creation_rondin(380, rand()%(SCREEN_W),1, 2, 4);
tableau_de_rondin[9] = Creation_rondin(420, rand()%(SCREEN_W),-1, 1, 4);
tableau_de_rondin[10] = Creation_rondin(460, rand()%(SCREEN_W),1, 1, 4);*/


}

