#include "header.h"

int main() {

    allegro_init();

    install_keyboard();
    install_mouse();

    set_window_title("SHREK MANIA WORLD");

    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,800,0,0) != 0) {

        allegro_message("Probleme de mode graphique :/");

        allegro_exit();
        exit(EXIT_FAILURE);
    }


    allegro_message("Allegro marche !");

    allegro_exit();

    return 0;

} END_OF_MAIN()
