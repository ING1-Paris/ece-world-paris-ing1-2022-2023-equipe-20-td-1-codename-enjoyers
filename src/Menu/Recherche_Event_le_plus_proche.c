//
// Created by Leroy on 07/05/2023.
//
#include "../../header.h"



int Recherche_event_le_plus_proche(t_joueur* Joueur){
    int event = 0;

    int Diff_x;
    int Diff_y;
    int tab_de_distance[NOMBRE_EVENTBOXES];

    int min;

    int event_c[NOMBRE_EVENTBOXES][2] ={{265,208},{647,208},{73,448},{313,443},{844,401},{570,510},{840,623},{480,720}};

    for (int i = 0; i < NOMBRE_EVENTBOXES; ++i) {
        if (Joueur->x>=event_c[i][0]){
            Diff_x = Joueur->x-event_c[i][0];
        }
        else {
            Diff_x = event_c[i][0]-Joueur->x;
        }
        if (Joueur->y>=event_c[i][1]){
            Diff_y = Joueur->y-event_c[i][1];
        }
        else {
            Diff_y = event_c[i][1]-Joueur->y;
        }
        tab_de_distance[i]=Diff_x+Diff_y;
    }
    min = tab_de_distance[0];

    for (int i = 0; i < NOMBRE_EVENTBOXES; ++i) {
        if (tab_de_distance[i]<=min){
            min = tab_de_distance[i];
            event=i+1;
        }

    }

    return event;
}