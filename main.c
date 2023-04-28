#include "header.h"

int main() {

    srand(time(NULL));

    allegro_init();

    install_keyboard();
    install_mouse();

    set_window_title("SHREK MANIA WORLD");


    // CREATION DU MODE GRAPHIQUE
    // -----------------------------
    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,960,720,0,0) != 0) {

        allegro_message("Probleme de mode graphique :/");

        allegro_exit();
        exit(EXIT_FAILURE);
    }
    // -----------------------------


    // INITIALISER LES VARIABLES ICI
    // -----------------------------

    BITMAP * page; // BITMAP de la page (double buffer)
    BITMAP * menu;

    // -----------------------------





    // CHARGEMENT DES VARIABLES
    // -----------------------------

    menu = load_bitmap("../assets/maps/menu.bmp", NULL);

    // -----------------------------





    // DEBUT DU JEU
    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    blit(menu, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    readkey();


    destroy_bitmap(page);
    destroy_bitmap(menu);

    allegro_exit();

    return 0;

} END_OF_MAIN()
