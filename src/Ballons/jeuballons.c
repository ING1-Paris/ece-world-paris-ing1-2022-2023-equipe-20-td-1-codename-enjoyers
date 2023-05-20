#include "../../header.h"

/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

void jeuballons(t_joueur joueur_ballons[NOMBRE_JOUEURS], int tab_tmp[NOMBRE_JOUEURS])
{
    unsigned long tmpJ1;
    t_joueur_tir_aux_ballons Joueur_actuel[NOMBRE_JOUEURS];

    // Buffer
    BITMAP *page;
    page = create_bitmap(SCREEN_W, SCREEN_H);

    // Image de fond
    BITMAP *decor;
    BITMAP *fond;


    fond = load_bitmap("../assets/maps/map_ballons.bmp", NULL);

    if (!fond)
    {
        allegro_message("pas pu trouver map_ballons.bmp");
        exit(EXIT_FAILURE);
    }

    blit(fond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Vous venez d'entrer dans le jeu du TIR AU BALLONS !", NULL, "Vous devez éclater tous les ballons le plus rapidement possible.", "Suivant", NULL, 0, 0);
    alert("Tenez-vous prêt...", NULL, "Appuyer sur la barre d'espace pour tirer et déplacez-vous avec les flèches droite et gauche", "C'est partiiiii !", NULL, 0, 0);


    decor = load_bitmap("../assets/maps/map_ballons.bmp", NULL);
    if (!decor) {

        allegro_message("pas pu trouver map_ballons.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Création du tableau de ballons
    t_ballon * tab_ballons[NBALLONS];

    // Nom fichier
    char nom_fichier[64];

    // Tableau d'indicateurs d'arret des ballons permettant de ne les comptabiliser qu'une seule fois
    int tab_stops[NBALLONS] = {0, 0, 0, 0, 0};

    // La collection des acteurs (les tirs)
    t_listeActeurs *acteurs;

    // Le fusil manipulé par le joueur
    t_joueur_ballons *fusil;



    // préparer la liste des acteurs (100 maxi)
    // mais vide initialement
    acteurs = creerListeActeurs(100);


    for (int j=0; j<NOMBRE_JOUEURS; j++) {

        // Création du fusil et des ballons
        fusil = creerJoueur("../assets/Item/TirBallons/fusil.bmp");

        for (int i=0; i<NBALLONS; i++) {

            sprintf(nom_fichier, "../assets/Item/TirBallons/ballon_%d.bmp", i);

            tab_ballons[i] = creerBallon(nom_fichier);
        }


        Joueur_actuel[j].temps = 0;
        Joueur_actuel[j].score = 0;

        // Stockage du temps initial
        time_t temps_initial = time(NULL);

        // Initialisation du tableau d'arrets de ballons
        for (int i = 0; i < NBALLONS; ++i) {

            tab_stops[i] = 0;
        }


        // BOUCLE DE JEU
        while (Joueur_actuel[j].score < 5) {

            // Demarrage du chronomètre
            time_t temps_actuel = time(NULL);

            // Effacer buffer en appliquant le décor
            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // Actualisation des positions des joueurs et des ballons
            actualiserJoueur(fusil, acteurs);

            for (int i = 0; i < NBALLONS; ++i) {

                actualiserBallon(tab_ballons[i]);
            }


            // Detection du score
            for (int i = 0; i < NBALLONS; ++i) {

                if (tab_ballons[i]->y - 8 * tab_ballons[i]->dy < 0) {

                    if (tab_stops[i] == 0) {

                        tab_stops[i] = 1;
                        Joueur_actuel[j].score += 1;

                    }

                }
            }

            // Actualisation de la liste des acteurs
            actualiserListeActeurs(acteurs);

            // gérer les collisions
            for (int i = 0; i < NBALLONS; ++i) {

                collisionListeActeurs(tab_ballons[i], acteurs);
            }


            // Affichage du joueur et des ballons
            dessinerJoueur(page, fusil);

            dessinerListeActeurs(page, acteurs);

            for (int i = 0; i < NBALLONS; ++i) {

                dessinerBallon(page, tab_ballons[i]);
            }



            // Affichage général à l'écran
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // Petite temporisation
            rest(10);

            Joueur_actuel[j].temps = (unsigned long)difftime(temps_actuel, temps_initial);

            // Remplissage du tableau de temps (utilisé ultérieurement pour la sauvegarde) avec le temps de parcours du joueur actuel
            tab_tmp[j] = (int) Joueur_actuel[j].temps;
        }

        allegro_message("Vous avez éclaté les 5 ballons en %d secondes", tab_tmp[j]);


        if (j == 0)
            tmpJ1 = tab_tmp[j];
        else {
            if (tmpJ1 < tab_tmp[j]) {

                joueur_ballons[0].tickets = joueur_ballons[0].tickets + 1;
                alert("Joueur 1, vous avez gagné un ticket !", NULL, NULL, "Retour", NULL, 0, 0);

            } else if (tmpJ1 == tab_tmp[j]) {

                alert("Egalité ! Personne ne gagne de ticket :(", NULL, NULL, "Retour", NULL, 0, 0);

            } else {

                joueur_ballons[1].tickets = joueur_ballons[1].tickets + 1;
                alert("Joueur 2, vous avez gagné un ticket !", NULL, NULL, "Retour", NULL, 0, 0);
            }
        }
    }


    for (int i = 0; i < NBALLONS; ++i) {

        destroy_bitmap(tab_ballons[i]->img);
    }

    destroy_bitmap(fusil->img);
    destroy_bitmap(page);

}