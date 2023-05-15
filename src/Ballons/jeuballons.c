#include "../../header.h"

///variables globales///

//compteur de ballons éclatés
int cpt_ballons = 0 ;

int stopBleu = 0;
int stopRose = 0;
int stopVert = 0;
int stopViolet = 0;
int stopRouge = 0;


/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

void jeuballons()
{
    int tmpJ1;
    double performance_temps;
    t_joueur tableau_joueurs[NOMBRE_JOUEURS];
    for(int j=0; j<2; j++) {
        time_t temps_precedent = time(NULL);
        cpt_ballons = 0;
        stopBleu = 0;
        stopRose = 0;
        stopVert = 0;
        stopViolet = 0;
        stopRouge = 0;

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
        while (cpt_ballons < 5) {
            time_t temps_actuel = time(NULL);
            performance_temps = difftime(temps_actuel, temps_precedent);

            // effacer buffer en appliquant décor  (pas de clear_bitmap)
            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // bouger tout le monde
            actualiserJoueur(fusil, acteurs);
            actualiserBallon_bleu(ballon1);
            actualiserBallon_rose(ballon2);
            actualiserBallon_vert(ballon3);
            actualiserBallon_violet(ballon4);
            actualiserBallon_rouge(ballon5);

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
        }
        allegro_message("vous avez éclaté les 5 ballons en %.1f secondes", performance_temps);
        if (j == 0)
            tmpJ1 = performance_temps;
        else {
            if (tmpJ1 < performance_temps) {
                tableau_joueurs[0].tickets = tableau_joueurs[0].tickets + 1;
                allegro_message("Joueur 1, vous avez gagné un ticket !");
            } else {
                tableau_joueurs[1].tickets = tableau_joueurs[1].tickets + 1;
                allegro_message("Joueur 2, vous avez gagné un ticket !");
            }
        }
    }

}




/************************************************/
/*     DEFINITIONS DES SOUS-PROGRAMMES          */
/************************************************/


// Actualiser les ballons (les bouger au hasard)
void actualiserBallon_bleu(t_ballon *ballon_bleu){
    t_ballon *nouv;

        // proba de changement de déplacement : une chance sur 50
        if (rand() % 50 == 0) {
            // Nouveau vecteur déplacement
            ballon_bleu->dx = rand() % 11 - 5;
        }

        // contrôle des bords : ici on décide de rebondir sur les bords
        if ((ballon_bleu->x < 0 && ballon_bleu->dx < 0) ||
            (ballon_bleu->x + ballon_bleu->tx > SCREEN_W && ballon_bleu->dx > 0))
            ballon_bleu->dx = -ballon_bleu->dx;

        // nouvelle position = position actuelle + déplacement
        ballon_bleu->x = ballon_bleu->x + ballon_bleu->dx;
        ballon_bleu->y = ballon_bleu->y + ballon_bleu->dy;

        if (ballon_bleu->y-8*ballon_bleu->dy < 0) {
            if(stopBleu==0) {
                cpt_ballons += 1;
                stopBleu = 1;
            }
        }

}


void actualiserBallon_rose(t_ballon *ballon_rose){

        // proba de changement de déplacement : une chance sur 50
        if (rand() % 50 == 0) {
            // Nouveau vecteur déplacement
            ballon_rose->dx = rand() % 11 - 5;
        }

        // contrôle des bords : ici on décide de rebondir sur les bords
        if ((ballon_rose->x < 0 && ballon_rose->dx < 0) ||
            (ballon_rose->x + ballon_rose->tx > SCREEN_W && ballon_rose->dx > 0))
            ballon_rose->dx = -ballon_rose->dx;

        // calculer nouvelle position
        // nouvelle position = position actuelle + deplacement
        ballon_rose->x = ballon_rose->x + ballon_rose->dx;
        ballon_rose->y = ballon_rose->y + ballon_rose->dy;

    if (ballon_rose->y-8*ballon_rose->dy < 0) {
        if (stopRose == 0) {
            cpt_ballons += 1;
            stopRose = 1;
        }
    }

}

void actualiserBallon_vert(t_ballon *ballon_vert){

        // proba de changement de déplacement : une chance sur 50
        if (rand() % 50 == 0) {
            // Nouveau vecteur déplacement
            ballon_vert->dx = rand() % 11 - 5;
        }

        // contrôle des bords : ici on décide de rebondir sur les bords
        if ((ballon_vert->x < 0 && ballon_vert->dx < 0) ||
            (ballon_vert->x + ballon_vert->tx > SCREEN_W && ballon_vert->dx > 0))
            ballon_vert->dx = -ballon_vert->dx;

        // calculer nouvelle position
        // nouvelle position = position actuelle + deplacement
        ballon_vert->x = ballon_vert->x + ballon_vert->dx;
        ballon_vert->y = ballon_vert->y + ballon_vert->dy;

    if (ballon_vert->y < 0) {
        if (stopVert == 0) {
            cpt_ballons += 1;
            stopVert = 1;
        }
    }
}


void actualiserBallon_violet(t_ballon *ballon_violet){

        // proba de changement de déplacement : une chance sur 50
        if (rand() % 50 == 0) {
            // Nouveau vecteur déplacement
            ballon_violet->dx = rand() % 11 - 5;
        }

        // contrôle des bords : ici on décide de rebondir sur les bords
        if ((ballon_violet->x < 0 && ballon_violet->dx < 0) ||
            (ballon_violet->x + ballon_violet->tx > SCREEN_W && ballon_violet->dx > 0))
            ballon_violet->dx = -ballon_violet->dx;

        // calculer nouvelle position
        // nouvelle position = position actuelle + deplacement
        ballon_violet->x = ballon_violet->x + ballon_violet->dx;
        ballon_violet->y = ballon_violet->y + ballon_violet->dy;

    if (ballon_violet->y-8*ballon_violet->dy < 0) {
        if (stopViolet == 0) {
            cpt_ballons += 1;
            stopViolet = 1;
        }
    }

}

void actualiserBallon_rouge(t_ballon *ballon_rouge){

        // proba de changement de déplacement : une chance sur 50
        if (rand() % 50 == 0) {
            // Nouveau vecteur déplacement
            ballon_rouge->dx = rand() % 11 - 5;
        }

        // contrôle des bords : ici on décide de rebondir sur les bords
        if ((ballon_rouge->x < 0 && ballon_rouge->dx < 0) ||
            (ballon_rouge->x + ballon_rouge->tx > SCREEN_W && ballon_rouge->dx > 0))
            ballon_rouge->dx = -ballon_rouge->dx;

        // calculer nouvelle position
        // nouvelle position = position actuelle + deplacement
        ballon_rouge->x = ballon_rouge->x + ballon_rouge->dx;
        ballon_rouge->y = ballon_rouge->y + ballon_rouge->dy;

        if (ballon_rouge->y-8*ballon_rouge->dy  < 0) {
            if (stopRouge == 0) {
                cpt_ballons += 1;
                stopRouge = 1;
            }
        }
}