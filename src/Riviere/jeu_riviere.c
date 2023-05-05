
#include "../../header.h"




double tmpJ1;



/******************************************/
/*          PROGRAMME PRINCIPAL           */
/******************************************/

void jeu_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS], unsigned long* Temps) {

    t_rondin *mesRondins[NRONDIN];
    t_joueuur *joueur[NOMBRE_JOUEURS];    // Un joueur (� cr�er)
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;
    int animation_perso_riv = 0;
    int attente_riv = 0;
    double temps_ecoule_riv;

    page = create_bitmap(SCREEN_W, SCREEN_H);

    remplirTabRondin(mesRondins);

    decor = load_bitmap_check("../assets/maps/MAP_RIVIERE.bmp");



    for (int j = 0; j < NOMBRE_JOUEURS; j++) {

        //Debut du chronometre
        time_t temps_precedent = time(NULL);

        //joueur[j] = creationJoueur(perso);

        joueur[j] = (t_joueuur *) malloc(sizeof(t_joueur));

        joueur[j]->skin_utilise = 6;
        joueur[j]->vit = 5;
        joueur[j]->tx = 48;
        joueur[j]->ty = 48;
        joueur[j]->y = 400;
        joueur[j]->x = 400;

        for (int i = 0; i < 12; ++i) {
            joueur[j]->skin_perso[i] = joueur_riv[j].sprites[i];
        }

    }

        time_t begin = time(NULL);

    for (int j = 0; j < NOMBRE_JOUEURS; ++j) {

        while (joueur[j]->y <= 580) {


            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            //dessineTerrain(page, terrain);
            AfficherTabRondin(page, mesRondins);
            AfficherJoueur(joueur[j], page, animation_perso_riv);
            actualiserTabRondin(mesRondins);

            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%d", joueur[j]->y);


            ActualiserJoueur(decor, joueur[j], mesRondins);

            if (attente_riv == 4) {
                if (animation_perso_riv == 1)
                {
                    animation_perso_riv = 0;
                } else
                {
                    animation_perso_riv = 1;
                }
                attente_riv = 0;
            }
            attente_riv++;


            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            rest(15);


        }

        /*allegro_message("vous avez traversé la rivière en %.1f secondes", temps_ecoule_riv);
        if (j == 0)
            tmpJ1 = temps_ecoule;
        else {
            if (tmpJ1 < temps_ecoule)
                allegro_message("Joueur 1, vous avez gagné un ticket !");
            else
                allegro_message("Joueur 2, vous avez gagné un ticket !");

        }*/

    }
    time_t end = time(NULL);
    *Temps = (unsigned long) difftime(end,begin);
}

