//
// Created by lucie on 13/05/2023.
//

#include "../../header.h"

int Fin_partie_taupe(t_joueur_taupe joueur[NOMBRE_JOUEURS]){

    if ((joueur[0].score == 5) && (joueur[1].score == 5))
        return 1;
    else
        return 0;

}