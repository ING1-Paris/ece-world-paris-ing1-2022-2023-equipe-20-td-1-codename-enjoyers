
#include "../../header.h"



double temps_ecoule;
double tmpJ1;



/******************************************/
/*          PROGRAMME PRINCIPAL           */
/******************************************/

void jeu_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS]) {

    t_joueur *joueur_riviere;
    t_rondin *mesRondins[NRONDIN];
    t_joueuur *joueur[NOMBRE_JOUEURS];    // Un joueur (� cr�er)
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;
    BITMAP *perso[13];
    char nomfichier[256];


    page = create_bitmap(SCREEN_W, SCREEN_H);

    remplirTabRondin(mesRondins);

    decor = load_bitmap_check("../assets/maps/MAP_RIVIERE.bmp");



    for (int j = 0; j < NOMBRE_JOUEURS; j++) {

        //Debut du chronometre
        time_t temps_precedent = time(NULL);

        //joueur[j] = creationJoueur(perso);

        joueur[j] = (t_joueuur *)malloc(sizeof(t_joueur));


        for (int i = 0; i < 12; ++i) {
            joueur[j]->skin_perso[i]=joueur_riv[j].sprites[i];
        }

        joueur[j]->vit = 5;
        joueur[j]->tx = 30;
        joueur[j]->ty = 30;
        joueur[j]->y = 400;



        while (joueur[j]->y <= 580) {


            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

            //dessineTerrain(page, terrain);
            AfficherTabRondin(page, mesRondins);
            AfficherJoueur(page, joueur[j]);
            actualiserTabRondin(mesRondins);

            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%d",joueur[j]->y);


            time_t temps_actuel = time(NULL);
            temps_ecoule = difftime(temps_actuel, temps_precedent);


            ActualiserJoueur(decor, joueur[j], mesRondins);


            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            rest(15);


        }

        allegro_message("vous avez traversé la rivière en %.1f secondes", temps_ecoule);
        if (j == 0)
            tmpJ1 = temps_ecoule;
        else {
            if (tmpJ1 < temps_ecoule)
                allegro_message("Joueur 1, vous avez gagné un ticket !");
            else
                allegro_message("Joueur 2, vous avez gagné un ticket !");

        }

    }

    //time_t end = time(NULL);
    //*Temps = (unsigned long) difftime(end,begin);

}

