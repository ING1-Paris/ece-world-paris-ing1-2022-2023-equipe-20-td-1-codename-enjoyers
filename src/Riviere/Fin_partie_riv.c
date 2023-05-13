//
// Created by lucie on 13/05/2023.
//

#include "../../header.h"

int Fin_partie_riv(t_joueur_riv joueur[NOMBRE_JOUEURS]){

    if ((joueur[0].y == 690) && (joueur[1].y == 690))
        return 1;
    else
        return 0;

}