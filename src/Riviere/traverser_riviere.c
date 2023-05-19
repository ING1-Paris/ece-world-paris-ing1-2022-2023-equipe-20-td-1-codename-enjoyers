//
// Created by lucie on 11/05/2023.
//


#include "../../header.h"

void traverser_riviere(t_joueur tab_joueurs[NOMBRE_JOUEURS], int tab_temps[NOMBRE_JOUEURS]){

    // Déclaration des BITMAPS
    BITMAP *decor;
    BITMAP *page;
    BITMAP *fond;

    // Déclaration des variables de joueurs et de rondins
    t_joueur_riv * tab_joueurs_riv[NOMBRE_JOUEURS];
    t_rondin * tab_rondins[NRONDIN];

    // Déclaration des variables de gestion d'animation
    int innactivite[NOMBRE_JOUEURS] = {1, 1};
    int animation[NOMBRE_JOUEURS] = {0,0};

    // Déclaration des variables de temps
    time_t begin;
    time_t end;

    // Déclaration des variables de jeu
    int alive = 1;







    // Initialisation des BITMAPS
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




    // Création des rondins et des joueurs
    Remplir_tab_rondin(tab_rondins);
    Remplir_tab_joueur(tab_joueurs_riv);



    // Initialisation des sprites (skins) des joueurs rivieres
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        for (int j = 0; j < 12; ++j) {

            tab_joueurs_riv[i]->skin_perso[j] = tab_joueurs[i].sprites[j];
        }
    }



    // Affichage de l'interface
    blit(fond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue dans la TRAVERSEE DE LA MORT !", NULL, NULL, "Go !", NULL, 0, 0);




    // Boucle de joueurs (joueur 1 puis joueur 2)
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        alert("Tenez-vous prêt...", NULL, "Vous devez traverser la riviere pour rejoindre Dragonne,", "C'est parti !", NULL, 0, 0);

        // Initialisation de la variable de démarrage de la partie
        alive = 1;

        // Démarrage du chronomètre
        begin = time(NULL);


        //Début du jeu
        while (alive) {

            // Affichage du décor sur la page (double buffer)
            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // Gestion de l'inactivité du joueur
            innactivite[i] = 1;

            // Affichage du tableau de rondins
            Afficher_tab_rondin(page, tab_rondins);

            // Calcul des déplacements des rondins sur l'écran
            Deplacement_tab_rondin(tab_rondins);

            // Calcul du déplacement du joueur
            Deplacement_joueur(tab_rondins, tab_joueurs_riv[i], innactivite);


            // Detection de la couleur sur laquelle le joueur se trouve (pour détecter s'il est présent sur l'eau ou pas)
            tab_joueurs_riv[i]->couleur = getpixel(page, tab_joueurs_riv[i]->x + tab_joueurs_riv[i]->tx / 2, tab_joueurs_riv[i]->y + tab_joueurs_riv[i]->ty);



            // Gestion de l'animation des sprites du joueur
            // On vérifie si le personnage est inactif ou non
            if (innactivite[i] == 1) {

                tab_joueurs_riv[i]->skin_utilise = tab_joueurs_riv[i]->skin_utilise + 2;
                animation[i] = 0;

            } else {

                if (animation[i] == 0) {

                    animation[i] = 1;

                } else {

                    animation[i] = 0;
                }

            }


            // Affichage du joueur
            masked_blit(tab_joueurs_riv[i]->skin_perso[(tab_joueurs_riv[i]->skin_utilise + animation[i])],page,0,0,tab_joueurs_riv[i]->x,tab_joueurs_riv[i]->y,tab_joueurs_riv[i]->tx,tab_joueurs_riv[i]->ty);


            // On enlève le sprite d'inactivite
            if (innactivite[i] == 1) {

                tab_joueurs_riv[i]->skin_utilise = tab_joueurs_riv[i]->skin_utilise - 2;
            }



            // Arrêt du chronomètre lorsque le joueur arrive à la fin et fin de la boucle de jeu
            if (tab_joueurs_riv[i]->y >= 640) {

                end = time(NULL);

                alive = 0;
            }


            // Calcul du temps de parcours et stockage de la valeur dans la structure du joueur
            tab_joueurs_riv[i]->temps = (end - begin);


            // Affichage de l'interface de jeu
            rectfill(page, 10, 10, 250, 90, makecol(255, 255, 255));
            rect(page, 10, 10, 250, 90, makecol(0, 0, 0));
            stretch_blit(tab_joueurs[i].sprites[12], page, 0, 0, 225, 225, 15, 15, 70, 70);

            textprintf_ex(page, font, 90, 20, makecol(0, 0, 0), -1, "%s", tab_joueurs[i].nom);
            textprintf_ex(page, font, 90, 50, makecol(0, 0, 0), -1, "Arrivée : %dm ", 640 - tab_joueurs_riv[i]->y);
            textprintf_ex(page, font, 90, 70, makecol(0, 0, 0), -1, "Temps écoulé: %lu", time(NULL) - begin);

            // Affichage de la page sur l'écran (double buffer)
            masked_blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            rest(15);


        }

        // Remplissage du tableau de temps (utilisé ultérieurement pour la sauvegarde) avec le temps de parcours du joueur actuel
        tab_temps[i] = (int) tab_joueurs_riv[i]->temps;
        printf("Le joueur %d est reste en vie pendant %d\n", i+1, tab_temps[i]);

    }



    // Détection de la victoire
    if (tab_joueurs_riv[0]->temps < tab_joueurs_riv[1]->temps) {

        alert("Joueur n°1, vous avez gagné un ticket ! ", NULL, NULL, " Retour au menu ", NULL, 0, 0);
        tab_joueurs[0].tickets = tab_joueurs[0].tickets + 1;

    } else if (tab_joueurs_riv[0]->temps == tab_joueurs_riv[1]->temps) {

        alert("Egalité ! Personne ne gagne de ticket :/", NULL, NULL, " Retour au menu ", NULL, 0, 0);

    } else {

        alert("Joueur n°2, vous avez gagné un ticket ! ", NULL, NULL, " Retour au menu ", NULL, 0, 0);
        tab_joueurs[1].tickets = tab_joueurs[1].tickets + 1;

    }


    // Destruction BITMAP
    destroy_bitmap(decor);
    destroy_bitmap(fond);
    destroy_bitmap(page);


}