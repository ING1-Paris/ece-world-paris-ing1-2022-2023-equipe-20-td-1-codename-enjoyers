//
// Created by lucie on 11/05/2023.
//


#include "../../header.h"

void traverser_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS], int tab_temps[NOMBRE_JOUEURS]){

   //variable decor
    BITMAP *decor;
    BITMAP *page;
    BITMAP *fond;

    page = create_bitmap(SCREEN_W, SCREEN_H);

    decor=load_bitmap("../assets/maps/MAP_RIVIERE.bmp",NULL);

    if (!decor)
    {
        allegro_message("decor \"MAP_RIVIERE\"  introuvable");
        exit(EXIT_FAILURE);
    }

    fond=load_bitmap("../assets/Item/Riviere/fond_riviere.bmp",NULL);

    if (!fond)
    {
        allegro_message("decor \"fond_riviere\" introuvable");
        exit(EXIT_FAILURE);
    }


    //variable acteur
    t_joueur_riv joueur[NOMBRE_JOUEURS];
    t_rondin *tabl_rondin[NRONDIN];


    // SPRITES
    int innactivite[NOMBRE_JOUEURS]={1,1};
    int animation[NOMBRE_JOUEURS]={0,0};

    //Variable temps
    time_t joueur_tps_parcours[NOMBRE_JOUEURS];


    //Création rondin et joueur
    Remplir_tab_rondin(tabl_rondin);


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        joueur[i] = Creation_joueur(joueur_riv);
    }




    blit(fond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue sur le JEU DE LA RIVIERE !", NULL, NULL, "go !", NULL, 0, 0);





    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        time_t begin = time(NULL);

        alert("Tenez-vous prêt...", NULL, "Vous devez traverser la riviere pour rejoindre Dragonne,", "c'est parti !", NULL, 0, 0);

        joueur[i].temps = 0;
        joueur[i].temps = begin;


        //Début du jeu
        while (joueur[i].y < 640){

            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);



            Afficher_joueur(page, &joueur[i]);

            Afficher_tab_rondin(page, tabl_rondin);

            Deplacement_tab_rondin(tabl_rondin);

            Deplacement_joueur(*tabl_rondin, &joueur[i], &innactivite[NOMBRE_JOUEURS]);


            //arrêt du chrono pour le joueur qui est arrivé à la fin
            if(joueur[i].y < 640) {
                joueur_tps_parcours[i] = time(NULL);
            }


            time_t tps_actuel = time(NULL);
            joueur[i].temps = (unsigned long) difftime(tps_actuel, begin);


            //Affichage score
            rectfill(page, 10, 10, 250, 90, makecol(255, 255, 255));
            rect(page, 10, 10, 250, 90, makecol(0, 0, 0));
            stretch_blit(joueur_riv[i].sprites[12], page, 0, 0, 225, 225, 15, 15, 70, 70);

            textprintf_ex(page, font, 90, 20, makecol(0, 0, 0), -1, "%s", joueur_riv[i].nom);
            textprintf_ex(page, font, 90, 50, makecol(0, 0, 0), -1, "position: %d", joueur[i].y);
            textprintf_ex(page, font, 90, 70, makecol(0, 0, 0), -1, "temps écoulé: %lu", joueur[i].temps);
            masked_blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            rest(15);



        }

        //*Temps = (unsigned long) difftime(joueur_tps_parcours[i],begin);
        //printf("Le joueur %d a traverse la riviere en %lus\n",i+1,*Temps);
    }




    if (joueur[0].temps < joueur[1].temps) {

        alert("Joueur 1, vous avez gagné un ticket ! ", NULL, NULL, "ok!", NULL, 0, 0);
        joueur_riv[0].tickets = joueur_riv[0].tickets + 1;
    }

    else {

        alert("Joueur 2, vous avez gagné un ticket ! ", NULL, NULL, "ok !", NULL, 0, 0);
        joueur_riv[1].tickets = joueur_riv[1].tickets + 1;

    }

}