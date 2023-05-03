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

    SAMPLE * musique;
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

    musique = load_sample(nom_fichier_musique);

    if (!musique) {

        allegro_message("Impossible de trouver le fichier %s :/", nom_fichier_musique);
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    // On cherche les notes maximum et minimum
    note_max = chanson_jouee[0].note;
    note_min = chanson_jouee[0].note;

    for (int i=0; i<taille_tableau; i++) {

        printf("Portee: %d  Millis: %d  Note: %d \n", chanson_jouee[i].portee, chanson_jouee[i].millis, chanson_jouee[i].note); // pour lde debug

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

        chanson_jouee[i].y_centre = 30;
        chanson_jouee[i].radius = 25;
        chanson_jouee[i].dy = 1;
        chanson_jouee[i].affichage = 0;
    }

    // On charge l'interface fixe
    charger_interface(page, tableau_cercles_fixes);

    // On affiche le tout
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    // On démarre le chronomètre
    begin = clock();

    // On lance la boucle de jeu
    while (alive) {

        end = clock();

        millis = (end - begin) * 1000 / CLOCKS_PER_SEC;

        for (index=0; index < taille_tableau; index++) {

            if (chanson_jouee[index].millis == millis) {

                printf("La note %d est jouee. Diff de temps: %d theorique, %lu reel \n", chanson_jouee[index].note, chanson_jouee[index].millis, millis);

                spawn_cercles(page, &chanson_jouee[index]);
            }
        }

        actualiser_tab_cercles(page, chanson_jouee, taille_tableau);

        charger_interface(page, tableau_cercles_fixes);


        for (int i=0; i<taille_tableau; i++) {

            if (chanson_jouee[i].affichage == 1) {

                circlefill(page, chanson_jouee[i].x_centre, chanson_jouee[i].y_centre, chanson_jouee[i].radius, chanson_jouee[i].couleur);
            }
        }

        if (chanson_jouee[0].y_centre == 640 && chanson_jouee[0].affichage == 1) {

            PlaySound(TEXT(nom_fichier_musique), NULL, SND_ASYNC);

            //allegro_message("Musique on !");
        }

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    }

}
