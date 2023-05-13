//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_rondin(t_rondin *le_rondin){


    if((le_rondin->posx < 0)||(le_rondin->posx + le_rondin->tx > SCREEN_W )){

        le_rondin->depx = -le_rondin->depx;
        //le_rondin->posx = le_rondin->posx + le_rondin->depx;



    }

    le_rondin->posx = le_rondin->posx + le_rondin->depx;



}