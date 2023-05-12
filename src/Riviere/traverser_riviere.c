//
// Created by lucie on 11/05/2023.
//


#include "../../header.h"

void traverser_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS]){

   //variable decor
    BITMAP *decor;
    BITMAP *page;

    page = create_bitmap(SCREEN_W, SCREEN_H);

    decor=load_bitmap("../assets/maps/MAP_RIVIERE.bmp",NULL);

    if (!decor)
    {
        allegro_message("decor introuvable");
        exit(EXIT_FAILURE);
    }


    //variable acteur
    t_joueur_riv *joueur[NOMBRE_JOUEURS];
    t_rondin *tabl_rondin[NRONDIN];

    int innactivite[NOMBRE_JOUEURS];


    //initialisation acteur
    Remplir_tab_rondin(tabl_rondin);


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        joueur[i] = Creation_joueur(joueur_riv);

    }


    time_t begin = time(NULL);


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
    //Boucle de jeu

        joueur[i]->temps = begin;

        while (joueur[i]->y <= 680)

        {

            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);



            Afficher_tab_rondin(page, tabl_rondin);
            Deplacement_tab_rondin(tabl_rondin);

            Afficher_joueur(page, joueur);
            Deplacement_joueur(*tabl_rondin, joueur[i], &innactivite[NOMBRE_JOUEURS]);

            masked_blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            rest(15);

            time_t temps_actuel = time(NULL);

            joueur[i]->temps = (unsigned long) difftime(temps_actuel, begin);

            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%lu", joueur[i]->temps);

        }
    }
}