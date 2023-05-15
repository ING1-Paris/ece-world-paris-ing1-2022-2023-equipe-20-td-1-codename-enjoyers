//
// Created by guych on 01/05/2023.
//

#include "../../header.h"

int activation_event(t_joueur tab_joueurs[NOMBRE_JOUEURS], t_hitbox tab_eventboxes[NOMBRE_EVENTBOXES]) {

    int i;
    int j;

    if (key[KEY_E]) {

        for (i=0; i<NOMBRE_JOUEURS; i++) {

            for (j=0; j<NOMBRE_EVENTBOXES; j++) {

                if (collision_joueur_hitbox(&tab_eventboxes[j], &tab_joueurs[i])) {

                    return 1;
                }

            }
        }


    }
    return 0;

}