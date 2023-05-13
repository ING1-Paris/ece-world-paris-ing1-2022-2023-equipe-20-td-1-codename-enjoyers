//
// Created by lucie on 11/05/2023.
//


#include "../../header.h"

void traverser_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS], unsigned long* Temps){

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
    t_joueur_riv joueur[NOMBRE_JOUEURS];
    t_rondin *tabl_rondin[NRONDIN];

    //Variable temps
    time_t joueur_mort[NOMBRE_JOUEURS];



    int innactivite[NOMBRE_JOUEURS];


    //initialisation acteur
    Remplir_tab_rondin(tabl_rondin);


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        joueur[i] = Creation_joueur(joueur_riv);

    }



    blit(decor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue sur le JEU DE LA RIVIERE !", NULL, NULL, "go !", NULL, 0, 0);


    time_t begin = time(NULL);


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
    //Boucle de jeu

        joueur[i].temps = begin;

        while (Fin_partie_riv(&joueur[i])!=1){

            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);



            Afficher_tab_rondin(page, tabl_rondin);
            Deplacement_tab_rondin(tabl_rondin);

            Afficher_joueur(page, joueur);
            Deplacement_joueur(*tabl_rondin, joueur, &innactivite[NOMBRE_JOUEURS]);


            if(joueur[i].y == 690){
                joueur_mort[i] = time(NULL);
            }


            time_t temps_actuel = time(NULL);

            joueur[i].temps = difftime(temps_actuel, begin);

            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%lu", joueur[i].temps);

            masked_blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            rest(15);


        }
    }

    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        *Temps = (unsigned long) difftime(joueur_mort[i],begin);
        printf("Le joueur %d est reste en vie pendant %lus\n",i+1,*Temps);
    }


    if (joueur[0].temps < joueur[1].temps)

        alert("Joueur 1, vous avez gagné un ticket ! ", NULL, NULL, "go!", NULL, 0, 0);

    else

        alert("Joueur 2, vous avez gagné un ticket ! ", NULL, NULL, "go !", NULL, 0, 0);
}