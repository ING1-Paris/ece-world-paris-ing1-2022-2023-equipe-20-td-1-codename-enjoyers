//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void guitar_hero() {

    // INITIALISATION - DECLARATION DES VARIABLES
    int index;
    int alive = 1;
    clock_t begin;
    clock_t end;
    unsigned long millis;
    int tempo_musique;

    char nom_fichier_musique[256];

    BITMAP * page = create_bitmap(SCREEN_W, SCREEN_H);

    t_cercle_fixe tableau_cercles_fixes[5] = {

            {SCREEN_W/2-120, 650, 25, makecol(0, 255, 0)},
            {SCREEN_W/2-60, 650, 25, makecol(255, 0, 0)},
            {SCREEN_W/2, 650, 25, makecol(255, 255, 0)},
            {SCREEN_W/2+60, 650, 25, makecol(0, 0, 255)},
            {SCREEN_W/2+120, 650, 25, makecol(255, 160, 0)}
    };

    DIALOG GUI_guitar_hero[] =

            {
                    // (dialog proc)     (x)   (y)   (w)   (h) (fg)(bg) (key) (flags)     (d1) (d2)    (dp)                   (dp2) (dp3)
                    { d_box_proc,           0, 0, 500, 200, 0, 0, 0,        0,          0,  0,       NULL,               NULL, NULL},
                    { d_text_proc,         4,  10,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Selectionner la musique a jouer (pour les deux joueurs):",  NULL, NULL  },

                    { d_text_list_proc,          4, 30, 280, 100, 0, 0, 0, 0, 0, 0, (void *) listbox_getter, NULL, NULL},


                    { d_button_proc,     160,   190,  160,   16,   0,  0,    0, D_EXIT,       0,   0,    (void*)"Suivant",            NULL, NULL  },
                    { d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
                    { NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
            };

    gui_fg_color = makecol(0, 0, 0);
    gui_mg_color = -1;
    gui_bg_color = makecol(255, 255, 255);
    set_dialog_color (GUI_guitar_hero, gui_fg_color, gui_bg_color);
    centre_dialog(GUI_guitar_hero);

    // On affiche le menu
    do_dialog(GUI_guitar_hero, 3);

    // On remplit le tableau de note avec la chanson selectionnee
    printf("Index du string: %d \n", GUI_guitar_hero[2].d1);
    printf("String en question: %s \n", listbox_getter(GUI_guitar_hero[2].d1, (int *) TAILLE_TAB_CHANSONS));

    int taille_tableau;
    int note_max;
    int note_min;
    int corde;

    t_note * chanson_jouee = charger_musique(listbox_getter(GUI_guitar_hero[2].d1, (int*) TAILLE_TAB_CHANSONS), &taille_tableau);

    // On charge le fichier MIDI/audio de la musique en question
    sprintf(nom_fichier_musique, "../assets/Item/GuitarHero/%s.wav", listbox_getter(GUI_guitar_hero[2].d1, (int*) TAILLE_TAB_CHANSONS));

    // On cherche les notes maximum et minimum
    note_max = chanson_jouee[0].note;
    note_min = chanson_jouee[0].note;

    for (int i=0; i<taille_tableau; i++) {

        //printf("Portee: %d  Millis: %d  Note: %d \n", chanson_jouee[i].portee, chanson_jouee[i].millis, chanson_jouee[i].note); // pour lde debug

        if (chanson_jouee[i].note > note_max) {

            note_max = chanson_jouee[i].note;

        } else if (chanson_jouee[i].note < note_min) {

            note_min = chanson_jouee[i].note;
        }

    }

    // On complete les informations des notes en fonction de leur hauteur
    for (int i=0; i<taille_tableau; i++) {

        corde = map(chanson_jouee[i].note, note_min, note_max, 0, 5);

        if (corde == 0) {

            chanson_jouee[i].x_centre = SCREEN_W/2-120;

            chanson_jouee[i].couleur = makecol(0, 255, 0);

        } else if (corde == 1) {

            chanson_jouee[i].x_centre = SCREEN_W/2-60;

            chanson_jouee[i].couleur = makecol(255, 0, 0);

        } else if (corde == 2) {

            chanson_jouee[i].x_centre = SCREEN_W/2;

            chanson_jouee[i].couleur = makecol(255, 255, 0);

        } else if (corde == 3) {

            chanson_jouee[i].x_centre = SCREEN_W/2+60;

            chanson_jouee[i].couleur = makecol(0, 0, 255);

        } else if (corde == 4) {

            chanson_jouee[i].x_centre = SCREEN_W/2+120;

            chanson_jouee[i].couleur = makecol(255, 155, 0);

        }

        chanson_jouee[i].y_centre = 0;
        chanson_jouee[i].radius = 25;
        chanson_jouee[i].dy = 1;
        chanson_jouee[i].affichage = 0;
    }

    // Update de tous les millis en fonction du tempo
    for (int i = 0; i < taille_tableau; ++i) {

        update_millis(&chanson_jouee[i], tempo_musique);

    }


    // Initialisation des deux portées
    portee_1 = organiser_portees(chanson_jouee, taille_tableau, &taille_portee_1, 1);

    portee_2 = organiser_portees(chanson_jouee, taille_tableau, &taille_portee_2, 2);

    // On charge l'interface fixe
    charger_interface(page, tableau_cercles_fixes);

    // On affiche le tout
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    // On initialise les index
    index_portee_1 = 0;
    index_portee_2 = 0;

    printf("Affichage note 1 portee 1 \n");

    printf("Note : %d, Millis: %d, portee: %d, X: %d, Y: %d, Radius: %d, Dy: %f, Affichage: %d\n", portee_2[0].note, portee_2[0].millis, portee_2[0].portee, portee_2[0].x_centre, portee_2[0].y_centre, portee_2[0].radius, portee_2[0].dy, portee_2[0].affichage);

    // On démarre le chronomètre
    begin = clock();


    // On lance la boucle de jeu
    while (alive) {

        end = clock();

        millis = (end - begin) * 1000 / CLOCKS_PER_SEC;

        //printf("%lu \n", millis);

        if ((millis >= portee_1[index_portee_1].millis)  && index_portee_1 < taille_portee_1) {

            spawn_cercles(page, &portee_1[index_portee_1]);

            printf("La note %d de la portee %d est dessinee. Diff de temps: %d theorique, %lu reel \n", portee_1[index_portee_1].note, portee_1[index_portee_1].portee, portee_1[index_portee_1].millis, millis);

            index_portee_1 = index_portee_1 + 1;
        }


        if ((millis >= portee_2[index_portee_2].millis)  && index_portee_2 < taille_portee_2) {

            spawn_cercles(page, &portee_2[index_portee_2]);

            printf("La note %d de la portee %d est dessinee. Diff de temps: %d theorique, %lu reel \n", portee_2[index_portee_2].note, portee_2[index_portee_2].portee, portee_2[index_portee_2].millis, millis);

            index_portee_2 = index_portee_2 + 1;
        }

        actualiser_tab_cercles(page, chanson_jouee, taille_tableau);

        charger_interface(page, tableau_cercles_fixes);

        for (int i=0; i<taille_portee_1; i++) {

            if (portee_1[i].affichage == 1) {

                circlefill(page, portee_1[i].x_centre, portee_1[i].y_centre, portee_1[i].radius, portee_1[i].couleur);
            }
        }

        for (int i=0; i<taille_portee_2; i++) {

            if (portee_2[i].affichage == 1) {

                circlefill(page, portee_2[i].x_centre, portee_2[i].y_centre, portee_2[i].radius, portee_2[i].couleur);
            }
        }


        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


        if ((portee_1[0].y_centre == 625 || portee_2[0].y_centre == 625) && demarrage_musique) {

            // Lancer la chanson
            PlaySound(TEXT(nom_fichier_musique), NULL, SND_ASYNC);

            demarrage_musique = 0;

        }

    }

}
