//
// Created by lucie on 06/05/2023.
//

#include "../../header.h"


int verification(t_taupe tab_taupe){

    //verification si la souris se trouve sur une des taupes
    for (int i = 0; i < 79; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (mouse_x == tab_taupe.taille[i][j][0])
                if (mouse_y == tab_taupe.taille[i][j][1])
                    if (tab_taupe.affichage)
                        return 1;
        }

    }

    return 0;
}