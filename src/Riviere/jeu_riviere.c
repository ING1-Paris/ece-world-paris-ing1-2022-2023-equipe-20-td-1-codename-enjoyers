
#include "../../header.h"



double temps_ecoule;
double tmpJ1;



/******************************************/
/*          PROGRAMME PRINCIPAL           */
/******************************************/

void jeu_riviere(t_joueur Joueur[NOMBRE_JOUEURS]) {

    t_rondin *mesRondins[NRONDIN];
    t_joueuur *joueur;    // Un joueur (� cr�er)
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;


    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 700, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    //tableTuiles = load_bitmap_check("images/tilemapZelda/tableTuiles.bmp");


    remplirTabRondin(mesRondins);

    decor = load_bitmap_check("MAP_RIVIERE_TEST2.bmp");



    for (int j = 0; j < NOMBRE_JOUEURS; j++) {
        time_t temps_precedent = time(NULL);

        joueur = creationJoueur("shrek4.bmp");


        while (joueur->y <= 580) {


            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

            //dessineTerrain(page, terrain);
            AfficherTabRondin(page, mesRondins);
            AfficherJoueur(page, joueur);
            actualiserTabRondin(mesRondins);

            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%d",joueur->y);


            time_t temps_actuel = time(NULL);
            temps_ecoule = difftime(temps_actuel, temps_precedent);


            ActualiserJoueur(decor, mesRondins, joueur, mesRondins);


            /*if (typeTerrain(joueur, 0, 0, 2)) { // dans l'eau ?
                joueur->x = 32;
                joueur->y = 200;
                //acteur->x+=1;
                textprintf_centre_ex(page, font, 400, 570, makecol(255, 255, 255), 0, " COULE ");
            } else
                textprintf_centre_ex(page, font, 400, 570, makecol(255, 255, 255), 0, "MARCHE");*/



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
}

