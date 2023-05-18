#include "../../header.h"

/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

void jeuballons(t_joueur joueur_ballons[NOMBRE_JOUEURS])
{
    unsigned long tmpJ1;
    t_joueur_tir_aux_ballons Joueur_actuel[NOMBRE_JOUEURS];


    for(int j=0; j<NOMBRE_JOUEURS; j++) {

        Joueur_actuel[j].temps = 0;
        Joueur_actuel[j].score = 0;

        time_t temps_initial = time(NULL);

        int stopBleu = 0;
        int stopRose = 0;
        int stopVert = 0;
        int stopViolet = 0;
        int stopRouge = 0;

        // Buffer
        BITMAP *page;

        // Image de fond
        BITMAP *decor;

        // La collection des acteurs (les tirs)
        t_listeActeurs *acteurs;

        // Le fusil manipulé par le joueur
        t_joueur_ballons *fusil;

        t_ballon *ballon1;
        t_ballon *ballon2;
        t_ballon *ballon3;
        t_ballon *ballon4;
        t_ballon *ballon5;


        // buffer
        page = create_bitmap(SCREEN_W, SCREEN_H);

        // charger image de fond
        decor = load_bitmap("../assets/maps/map_ballons.bmp", NULL);
        if (!decor) {
            allegro_message("pas pu trouver map_ballons.bmp");
            exit(EXIT_FAILURE);
        }

        // créer le fusil et les ballons
        fusil = creerJoueur("../assets/Item/TirBallons/fusil.bmp");
        ballon1 = creerBallon_bleu("../assets/Item/TirBallons/ballon_bleu.bmp");
        ballon2 = creerBallon_rose("../assets/Item/TirBallons/ballon_rose.bmp");
        ballon3 = creerBallon_vert("../assets/Item/TirBallons/ballon_vert.bmp");
        ballon4 = creerBallon_violet("../assets/Item/TirBallons/ballon_violet.bmp");
        ballon5 = creerBallon_rouge("../assets/Item/TirBallons/ballon_rouge.bmp");

        // préparer la liste des acteurs (100 maxi)
        // mais vide initialement
        acteurs = creerListeActeurs(100);

        // BOUCLE DE JEU
        while (Joueur_actuel[j].score < 5) {
            time_t temps_actuel = time(NULL);

            // effacer buffer en appliquant le décor
            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // bouger tout le monde
            actualiserJoueur(fusil, acteurs);
            actualiserBallon_bleu(ballon1);
            actualiserBallon_rose(ballon2);
            actualiserBallon_vert(ballon3);
            actualiserBallon_violet(ballon4);
            actualiserBallon_rouge(ballon5);

            if (ballon1->y-8*ballon1->dy < 0) {
                if(stopBleu==0) {
                    Joueur_actuel[j].score += 1;
                    stopBleu = 1;
                }
            }

            if (ballon2->y-8*ballon2->dy < 0) {
                if (stopRose == 0) {
                    Joueur_actuel[j].score += 1;
                    stopRose = 1;
                }
            }

            if (ballon3->y-8*ballon3->dy < 0) {
                if (stopVert == 0) {
                    Joueur_actuel[j].score += 1;
                    stopVert = 1;
                }
            }

            if (ballon4->y-8*ballon4->dy < 0) {
                if (stopViolet == 0) {
                    Joueur_actuel[j].score += 1;
                    stopViolet = 1;
                }
            }

            if (ballon5->y-8*ballon5->dy  < 0) {
                if (stopRouge == 0) {
                    Joueur_actuel[j].score += 1;
                    stopRouge = 1;
                }
            }

            actualiserListeActeurs(acteurs);

            // gérer les collisions
            collisionListeActeursBleu(ballon1, acteurs);
            collisionListeActeursRose(ballon2, acteurs);
            collisionListeActeursVert(ballon3, acteurs);
            collisionListeActeursViolet(ballon4, acteurs);
            collisionListeActeursRouge(ballon5, acteurs);

            // afficher tout le monde
            dessinerJoueur(page, fusil);
            dessinerBallon_bleu(page, ballon1);
            dessinerBallon_rose(page, ballon2);
            dessinerBallon_vert(page, ballon3);
            dessinerBallon_violet(page, ballon4);
            dessinerBallon_rouge(page, ballon5);

            dessinerListeActeurs(page, acteurs);

            // afficher tout ça à l'écran
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // petite temporisation
            rest(10);

            Joueur_actuel[j].temps = (unsigned long)difftime(temps_actuel, temps_initial);
        }
        allegro_message("vous avez éclaté les 5 ballons en %.lu secondes", Joueur_actuel[j].temps);
        if (j == 0)
            tmpJ1 = Joueur_actuel[j].temps;
        else {
            if (tmpJ1 < Joueur_actuel[j].temps) {
                joueur_ballons[0].tickets = joueur_ballons[0].tickets + 1;
                allegro_message("Joueur 1, vous avez gagné un ticket !");
            } else {
                joueur_ballons[1].tickets = joueur_ballons[1].tickets + 1;
                allegro_message("Joueur 2, vous avez gagné un ticket !");
            }
        }
    }

}