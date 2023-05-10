//
// Created by guych on 08/05/2023.
//

#include "../../header.h"

void detection_touches(t_note * portee_1, int index_1, int * index_note_jouee_1, t_note * portee_2, int index_2, int * index_note_jouee_2, t_cercle_fixe * tab_cercles_fixes, int * alive, int mono_portee) {

    // Touches de jeu D F  J K

    int i;

    if (!mono_portee) {


        if (key[KEY_D]) {


            if (collision_cercles(&tab_cercles_fixes[0], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(0, 255, 0))) {

                portee_2[*index_note_jouee_2].affichage = 0;

                *index_note_jouee_2 = *index_note_jouee_2 + 1;

                printf("Collision D ! \t");

            } /*else if (!collision_cercles(&tab_cercles_fixes[0], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(0, 255, 0))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_F]) {


            if (collision_cercles(&tab_cercles_fixes[1], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(255, 0, 0))) {

                portee_2[*index_note_jouee_2].affichage = 0;

                *index_note_jouee_2 = *index_note_jouee_2 + 1;

                printf("Collision F ! \n");

            } /*else if (!collision_cercles(&tab_cercles_fixes[1], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(255, 0, 0))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_J]) {


            if (collision_cercles(&tab_cercles_fixes[2], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(255, 255, 0))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

            } else if (collision_cercles(&tab_cercles_fixes[2], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(255, 255, 0))) {

                portee_2[*index_note_jouee_2].affichage = 0;

                *index_note_jouee_2 = *index_note_jouee_2 + 1;
            }



            /*else if (!collision_cercles(&tab_cercles_fixes[2], &portee_2[*index_note_jouee_1]) && (portee_2[*index_note_jouee_1].affichage) && (portee_2[*index_note_jouee_1].couleur == makecol(255, 255, 0))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_K]) {


            if (collision_cercles(&tab_cercles_fixes[3], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(0, 0, 255))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

            } /*else if (!collision_cercles(&tab_cercles_fixes[3], &portee_2[*index_note_jouee_1]) && (portee_2[*index_note_jouee_1].affichage) && (portee_2[*index_note_jouee_1].couleur == makecol(0, 0, 255))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_L]) {

            if (collision_cercles(&tab_cercles_fixes[4], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(255, 160, 0))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

            } /*else if (!collision_cercles(&tab_cercles_fixes[4], &portee_2[*index_note_jouee_1]) && (portee_2[*index_note_jouee_1].affichage) && (portee_2[*index_note_jouee_1].couleur == makecol(255, 160, 0))) {

                *alive = 0;
            }*/


        }








        for (i=0; i<= index_2; i++) {

            if (portee_2[i].y_centre >= 690 && (portee_2[i].affichage)) {

                *alive = 0;
            }
        }

        for (i=0; i<= index_1; i++) {

            if (portee_1[i].y_centre >= 690 && (portee_1[i].affichage)) {

                *alive = 0;
            }
        }





    } else if (mono_portee) {


        if (key[KEY_D]) {


            if (collision_cercles(&tab_cercles_fixes[0], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(0, 255, 0))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

                printf("Collision D ! \t");

            } /*else if (!collision_cercles(&tab_cercles_fixes[0], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(0, 255, 0))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_F]) {


            if (collision_cercles(&tab_cercles_fixes[1], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(255, 0, 0))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

                printf("Collision F ! \n");

            } /*else if (!collision_cercles(&tab_cercles_fixes[1], &portee_2[*index_note_jouee_2]) && (portee_2[*index_note_jouee_2].affichage) && (portee_2[*index_note_jouee_2].couleur == makecol(255, 0, 0))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_J]) {


            if (collision_cercles(&tab_cercles_fixes[2], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(255, 255, 0))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

            }


            /*else if (!collision_cercles(&tab_cercles_fixes[2], &portee_2[*index_note_jouee_1]) && (portee_2[*index_note_jouee_1].affichage) && (portee_2[*index_note_jouee_1].couleur == makecol(255, 255, 0))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_K]) {


            if (collision_cercles(&tab_cercles_fixes[3], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(0, 0, 255))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

            } /*else if (!collision_cercles(&tab_cercles_fixes[3], &portee_2[*index_note_jouee_1]) && (portee_2[*index_note_jouee_1].affichage) && (portee_2[*index_note_jouee_1].couleur == makecol(0, 0, 255))) {

                *alive = 0;
            }*/


        }


        if (key[KEY_L]) {

            if (collision_cercles(&tab_cercles_fixes[4], &portee_1[*index_note_jouee_1]) && (portee_1[*index_note_jouee_1].affichage) && (portee_1[*index_note_jouee_1].couleur == makecol(255, 160, 0))) {

                portee_1[*index_note_jouee_1].affichage = 0;

                *index_note_jouee_1 = *index_note_jouee_1 + 1;

            } /*else if (!collision_cercles(&tab_cercles_fixes[4], &portee_2[*index_note_jouee_1]) && (portee_2[*index_note_jouee_1].affichage) && (portee_2[*index_note_jouee_1].couleur == makecol(255, 160, 0))) {

                *alive = 0;
            }*/


        }





        for (i=0; i<= index_1; i++) {

            if (portee_1[i].y_centre >= 690 && (portee_1[i].affichage)) {

                *alive = 0;
            }
        }



    }



}