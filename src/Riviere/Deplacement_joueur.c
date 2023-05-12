//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Deplacement_joueur(t_rondin rondin[NRONDIN], t_joueur_riv joueur[NOMBRE_JOUEURS], int innactivite[NOMBRE_JOUEURS]){

    if(Collision_joueur_rondin(rondin, &joueur[0])){
        printf("peu avancer\n");
    }
    else printf("stop\n");


    if (key[KEY_DOWN]){


        if(Collision_joueur_rondin(rondin, &joueur[0])){


            joueur[0].y = joueur[0].y + joueur[0].vit;
            joueur[0].skin_utilise = 0;
            //innactivite[0] = 0;
            printf("c'est bon\n");

        }

        else {

            //dans l'eau = retour à la position initiale
            joueur[0].y = 145;
            joueur[0].x = 500;
            //joueur[0].y = joueur[0].y + joueur[0].vit;
            printf("c'est pas bon\n");
        }



    }

}