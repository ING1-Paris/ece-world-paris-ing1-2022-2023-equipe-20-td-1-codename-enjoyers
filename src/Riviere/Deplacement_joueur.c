//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(t_rondin rondin[NRONDIN], t_joueur_riv joueur[NOMBRE_JOUEURS], int innactivite[NOMBRE_JOUEURS]){


    if (key[KEY_UP]) {



    } else if (key[KEY_DOWN]) {


    } else if (key[KEY_LEFT]) {



    } else if (key[KEY_RIGHT]) {



    }



    if(Collision_joueur_rondin(rondin, &joueur[0])){

        if (key[KEY_DOWN])
        {
            joueur[0].y = joueur[0].y + joueur[0].vit;
            joueur[0].skin_utilise = 0;

            //innactivite[0] = 0;
            printf("sur un rondin\n");
        }

        joueur[0].x = rondin->posx;
        joueur[0].y = rondin->posy;
    }

    else {

        //dans l'eau = retour à la position initiale
        joueur[0].y = 145;
        joueur[0].x = 500;

        printf("dans l'eau\n");
    }

}