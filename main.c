#include "header.h"

int main() {

    srand(time(NULL));

    allegro_init();

    install_keyboard();
    install_mouse();

    set_window_title("SHREK MANIA WORLD");





    /// CREATION DU MODE GRAPHIQUE
    // -----------------------------
    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,960,720,0,0) != 0) {

        allegro_message("Probleme de mode graphique :/");

        allegro_exit();
        exit(EXIT_FAILURE);
    }
    /// -----------------------------








    /// INITIALISER LES VARIABLES ICI
    // -----------------------------

    // BITMAPS
    BITMAP * page; // BITMAP de la page (double buffer)
    BITMAP * map_menu; // BITMAP de la carte du menu
    BITMAP * Shrek_Question;
    BITMAP * fond_de_maison;
    BITMAP * Couronne_de_jeu;
    BITMAP * Control_J1;
    BITMAP * Interaction_J1;
    BITMAP * Control_J2;
    BITMAP * Interaction_J2;

    // HITBOXES
    t_hitbox tableau_hitboxes[NOMBRE_HITBOXES] = {
            // Maisons
            {192, 74, 320, 189},
            {592, 48, 710, 200},
            {0, 288, 135, 430},
            {255, 288, 412, 425},
            {780, 240, 893, 379},

            //Nord de la map
            {0, 0, 960, 90},
            {0*48, 0*48, 3*48, 4*48},
            {17*48, 0*48, 20*48, 175},

            //Paneaux
            {11*48, 10*48, 13*48, 12*48},

            //Riviere
            {0*48, 12*48, 9*48, 13*48},
            {11*48, 12*48, 765, 13*48},
            {910,12*48, 20*48, 13*48},
            {400 ,600, 430, 720},
            {525 ,600, 550, 720},
            {770 ,635, 912, 643},
    };

    // EVENTBOXES
    t_hitbox tableau_eventboxes[NOMBRE_EVENTBOXES] = {

            {5*48, 4*48, 6*48, 5*48},
            {13*48, 4*48, 14*48, 5*48},
            {1*48, 9*48, 2*48, 10*48},
            {6*48, 9*48, 7*48, 10*48},
            {17*48, 8*48, 18*48, 9*48},
            {10*48, 9*48, 14*48, 11*48},
            {780, 590, 900, 630},
            {435,677,520,720}
    };

    // JOUEURS
    t_joueur tableau_joueurs[NOMBRE_JOUEURS];
    int tab_temps_epreuves[NOMBRE_JOUEURS];

    // EVENT
    int Personne_qui_choisi = 0;
    int Choix_epreuve = 0;

    // SPRITES
    int Innactivite[NOMBRE_JOUEURS]={1,1};
    int animation[NOMBRE_JOUEURS]={0,0};

    // TABLEAU D'ENTREES DE SAUVEGARDES
    t_entree_sauvegarde tableau_donnees_a_sauvegarder[NOMBRE_JOUEURS];

    // FIN DE PARTIE
    int Fin = 0;
    int Fin_de_partie = 0;


    // OUVERTURE DE LA BOITE DE DIALOGUE
    char chaine_temp[256] = "";

    DIALOG GUI_demarrage[] =
        {
            //(dialog proc)     (x)   (y)  (w)   (h)  (fg)(bg) (key) (flags)     (d1) (d2)    (dp)                                    (dp2)  (dp3)
            { d_box_proc,         0,   0,  500,  200,   0,  0,    0,      0,       0,   0,     NULL                                 ,  NULL, NULL },
            { d_text_proc,        2,  10,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Saisir le pseudo du joueur:"  ,  NULL, NULL  },
            { d_text_proc,        4,  25,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)">>"                           ,  NULL, NULL  },
            { d_edit_proc,       28,  25,  160,    8,   0,  0,    0, D_EXIT,      64,   0,    (void*)chaine_temp                    ,  NULL, NULL  },
            { d_text_proc,        2,  65,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Choisir le personnage:"       ,  NULL, NULL  },

            { d_icon_proc,        4,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL                                  ,  NULL, NULL  },
            { d_icon_proc,       64,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL                                  ,  NULL, NULL  },
            { d_icon_proc,      124,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL                                  ,  NULL, NULL  },
            { d_icon_proc,      184,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL                                  ,  NULL, NULL  },
            { d_icon_proc,      244,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL                                  ,  NULL, NULL  },


            { d_button_proc,    160, 190,  160,   16,   0,  0,    0, D_EXIT,       0,   0,    (void*)"OK"                           ,  NULL, NULL  },
            { d_yield_proc,       0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL                                  ,  NULL, NULL  },
            { NULL,               0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL                                  ,  NULL, NULL  },
        };

    gui_fg_color = makecol(0, 0, 0);
    gui_mg_color = -1;
    gui_bg_color = makecol(255, 255, 255);
    set_dialog_color (GUI_demarrage, gui_fg_color, gui_bg_color);
    centre_dialog(GUI_demarrage);

    /// -----------------------------








    /// CHARGEMENT DES VARIABLES
    // -----------------------------

    // CHARGEMENT DE LA MAP DU MENU
    map_menu = load_bitmap("../assets/maps/menu.bmp", NULL);

    // CHARGEMENT DES SPRITES DU MENU
    Shrek_Question = load_bitmap("../assets/Item/Menu/Shrek_question.bmp",NULL);
    fond_de_maison = load_bitmap("../assets/Item/Menu/Fond_de_maison.bmp",NULL);
    Couronne_de_jeu= load_bitmap("../assets/Item/Menu/Couronne_de_Shrek.bmp",NULL);
    Control_J1 = load_bitmap("../assets/Item/Menu/hgbd.bmp",NULL);
    Interaction_J1 = load_bitmap("../assets/Item/Menu/L.bmp",NULL);
    Control_J2 = load_bitmap("../assets/Item/Menu/zqsd.bmp",NULL);
    Interaction_J2 = load_bitmap("../assets/Item/Menu/f.bmp",NULL);


    // -----------------------------





    /// ZONE DE TEST
    // -----------------------------


    //statistique();

    /*while (1) {

        guitar_hero();
    }*/

    //jeu_riviere(tableau_joueurs, &Temps_d_epreuve);
    //jeuballons();
    //jeu_course();
    //printf("\n\n\n");
    //system("pause");

    // -----------------------------







    /// DEBUT DU JEU

    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    GUI_demarrage[5].dp = load_bitmap("../assets/personnages/Farquaad/Farquaad_12.bmp", NULL);
    GUI_demarrage[6].dp = load_bitmap("../assets/personnages/Shrek/Shrek_12.bmp", NULL);
    GUI_demarrage[7].dp = load_bitmap("../assets/personnages/Chat/Chat_12.bmp", NULL);
    GUI_demarrage[8].dp = load_bitmap("../assets/personnages/Fiona/Fiona_12.bmp", NULL);
    GUI_demarrage[9].dp = load_bitmap("../assets/personnages/Thomas/Thomas_12.bmp", NULL);


    Acceuil();


    for (int i=0; i<NOMBRE_JOUEURS; i++) {

        strcpy(chaine_temp, "");

        for (int j=5; j<10; j++) {

            if (GUI_demarrage[j].flags != D_HIDDEN) {

                GUI_demarrage[j].flags = 0;
            }
        }

        blit(fond_de_maison,page,0,0,0,0,SCREEN_W, SCREEN_H);
        masked_blit(Shrek_Question,page,0,0,0,450,400,533);


        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (i == 0) {

            alert("Remplissez les informations du joueur 1 !", NULL, NULL, "Suivant", NULL, 0, 0);

        }

        do {

            do_dialog(GUI_demarrage, 3);

        } while (strlen(chaine_temp) < 1 || (GUI_demarrage[5].flags != D_SELECTED && GUI_demarrage[6].flags != D_SELECTED && GUI_demarrage[7].flags != D_SELECTED && GUI_demarrage[8].flags != D_SELECTED && GUI_demarrage[9].flags != D_SELECTED));


        strcpy(tableau_joueurs[i].nom, chaine_temp);
        tableau_joueurs[i].score = 0;
        tableau_joueurs[i].dx = 15;
        tableau_joueurs[i].dy = 15;
        tableau_joueurs[i].Sprite_actif = 0;
        tableau_joueurs[i].tickets = 5;


        // Remplir le tableau de sprites de chaque joueur en fonction du perso qu'il a choisi
        if (GUI_demarrage[5].flags == D_SELECTED) { // Farquaad

            GUI_demarrage[5].flags = D_HIDDEN;

            charger_sprites(&tableau_joueurs[i], "Farquaad");

        } else if (GUI_demarrage[6].flags == D_SELECTED) { //Shrek

            GUI_demarrage[6].flags = D_HIDDEN;

            charger_sprites(&tableau_joueurs[i], "Shrek");

        } else if (GUI_demarrage[7].flags == D_SELECTED) { // Le chat potté

            GUI_demarrage[7].flags = D_HIDDEN;

            charger_sprites(&tableau_joueurs[i], "Chat");

        } else if (GUI_demarrage[8].flags == D_SELECTED) { // Fiona

            GUI_demarrage[8].flags = D_HIDDEN;

            charger_sprites(&tableau_joueurs[i], "Fiona");

        } else if (GUI_demarrage[9].flags == D_SELECTED) { // Thomas

            GUI_demarrage[9].flags = D_HIDDEN;

            charger_sprites(&tableau_joueurs[i], "Thomas");
        }

        tableau_joueurs[i].x = 458;
        tableau_joueurs[i].y = 600 + (i*60);
        tableau_joueurs[i].tx = tableau_joueurs[i].sprites[0]->w;
        tableau_joueurs[i].ty = tableau_joueurs[i].sprites[0]->h;


        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (i == 0) {

            alert("Remplissez a present les informations du joueur 2 !", NULL, NULL, "Suivant", NULL, 0, 0);
        }

    }

    PlaySound(NULL, 0, 0);

    blit(map_menu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    alert("Pendant le jeu, appuyez sur 'h' pour ouvrir le menu d'aide!", NULL, NULL, "Compris, merci Shrek my love !", NULL, 0, 0);

    while (!Fin) {


        blit(map_menu, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (key[KEY_H]) {

            //AIDE J1
            rectfill(page,545,600,750,710, makecol(255,255,255));
            rect(page,545,600,750,710, makecol(0,0,0));

            textprintf_ex(page,font,640,610, makecol(0,0,0),-1,"J1:");

            masked_blit(Control_J1,page,0,0,550,625,133,84);
            masked_blit(Interaction_J1,page,0,0,700,630,45,43);

            //AIDE J2
            rectfill(page,195,600,400,710, makecol(255,255,255));
            rect(page,195,600,400,710, makecol(0,0,0));

            textprintf_ex(page,font,290,610, makecol(0,0,0),-1,"J2:");

            masked_blit(Control_J2,page,0,0,200,625,133,84);
            masked_blit(Interaction_J2,page,0,0,350,630,45,43);
        }


        //charger_hitboxes(page, tableau_eventboxes, makecol(0, 255, 0));

        //charger_hitboxes(page, tableau_hitboxes, makecol(0, 0, 255));


        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            Innactivite[i]=1;
        }

        deplacement_joueurs(page, tableau_joueurs, tableau_hitboxes,Innactivite);


        //Event
        if (activation_event(tableau_joueurs, tableau_eventboxes,Personne_qui_choisi) == 1) {

            Choix_epreuve = Recherche_event_le_plus_proche(&tableau_joueurs[Personne_qui_choisi]);

            if (Choix_epreuve < 7) {

                Personne_qui_choisi ++;

                for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

                    tableau_joueurs[i].tickets = tableau_joueurs[i].tickets - 1;

                }
            }



            if(Personne_qui_choisi == 2){
                Personne_qui_choisi = 0;
            }
        }

        if (Choix_epreuve == 1) {

            Snake(tableau_joueurs,tab_temps_epreuves);

        } else if (Choix_epreuve == 2) {

            guitar_hero(tableau_joueurs, tableau_donnees_a_sauvegarder);

        } else if (Choix_epreuve == 3) {

            jeuballons(tableau_joueurs, tab_temps_epreuves);

        } else if (Choix_epreuve == 4) {

            jeu_course(tableau_joueurs);

        } else if (Choix_epreuve == 5){

            jeu_taupe(tableau_joueurs);

        } else if (Choix_epreuve == 6){

           traverser_riviere(tableau_joueurs, tab_temps_epreuves);

        } else if (Choix_epreuve == 7){
            statistique();
            Choix_epreuve = 0;

        } else if(Choix_epreuve == 8){

            Choix_epreuve = 0;
            alert("Au revoir !", NULL, NULL, "Quitter SHREK MANIA WORLD", NULL, 0, 0);
            Fin = 1;

        }

        if (Choix_epreuve > 0 && Choix_epreuve < 7) {

            remplir_tab_sauvegardes(tableau_donnees_a_sauvegarder, tableau_joueurs, tab_temps_epreuves, Choix_epreuve);

            sauvegarder(tableau_donnees_a_sauvegarder);

            Choix_epreuve = 0;
        }

        //Detection de Victoire
        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

            if(tableau_joueurs[i].tickets == 0){

                Fin_du_jeu(page,tableau_joueurs);
                Fin = 1;
            }
        }



        for (int i=0; i<NOMBRE_JOUEURS; i++) {

            //On verifie si le personnage est innactif ou non
            if (Innactivite[i] == 1){

                tableau_joueurs[i].Sprite_actif = tableau_joueurs[i].Sprite_actif +2;
                animation[i] = 0;

            }
            else{

                if (animation[i] == 0)
                    animation[i] = 1;
                else {
                    animation[i] = 0;
                }
            }

            //Affichage du joueur
            masked_blit(tableau_joueurs[i].sprites[tableau_joueurs[i].Sprite_actif+animation[i]],page,0,0,tableau_joueurs[i].x,tableau_joueurs[i].y,tableau_joueurs[i].tx,tableau_joueurs[i].ty);


            //On enleve le sprite d'inactivite
            if (Innactivite[i] == 1)
                tableau_joueurs[i].Sprite_actif = tableau_joueurs[i].Sprite_actif -2;
        }
        //Gestion de L'interface in game

        //J1
        rectfill(page,10,10,250,70,makecol(255,255,255));
        rect(page,10,10,250,70,makecol(0,0,0));
        stretch_blit(tableau_joueurs[0].sprites[12],page,0,0,225,225,15,15,50,50);

        if(Personne_qui_choisi == 0)
            masked_stretch_blit(Couronne_de_jeu,page,0,0,650,366,170,20,70,50);

        textprintf_ex(page,font,70, 30, makecol(0,0,0),-1,"%s",tableau_joueurs[0].nom);
        textprintf_ex(page,font,70, 50, makecol(0,0,0),-1,"Tickets: %d",tableau_joueurs[0].tickets);

        //J2
        rectfill(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(255,255,255));
        rect(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(0,0,0));
        stretch_blit(tableau_joueurs[1].sprites[12],page,0,0,225,225,SCREEN_W-250+5,15,50,50);

        if(Personne_qui_choisi == 1)
            masked_stretch_blit(Couronne_de_jeu,page,0,0,650,366,SCREEN_W-250+160,20,70,50);

        textprintf_ex(page,font,SCREEN_W-250+5+55, 30, makecol(0,0,0),-1,"%s",tableau_joueurs[1].nom);
        textprintf_ex(page,font,SCREEN_W-250+5+55, 50, makecol(0,0,0),-1,"Tickets: %d",tableau_joueurs[1].tickets);


        masked_blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        rest(50);


    }



    destroy_bitmap(page);
    destroy_bitmap(map_menu);
    allegro_exit();

    return 0;

} END_OF_MAIN()