//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Remplir_tab_rondin(t_rondin * tableau_de_rondin[NRONDIN]) {

    for (int i = 0; i < NRONDIN; ++i) {

        tableau_de_rondin[i] = Creation_rondin(i);
    }


}

