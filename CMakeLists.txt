cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET main.c header.h src/Ballons/jeuballons.c src/Snake/Jeux_Snake.c src/Riviere/jeu_riviere.c src/Menu/charger_sprites.c src/Snake/Sous_programme_Snake.c src/Menu/charger_hitboxes.c src/Menu/deplacement_joueurs.c src/Menu/collision_joueur_hitbox.c src/Menu/activation_event.c src/GuitarHero/guitar_hero.c src/GuitarHero/listbox_getter.c src/GuitarHero/charger_musique.c src/GuitarHero/charger_interface.c src/GuitarHero/map.c src/GuitarHero/spawn_cercles.c src/GuitarHero/actualiser_cercles.c src/GuitarHero/actualiser_tab_cercles.c src/GuitarHero/collision_cercles.c src/Riviere/Sous_programme_Riviere.c src/Taupe/jeu_taupe.c src/Taupe/sous_prog_taupe.c)

target_link_libraries(PROJET -lmingw32 -lalleg44 -lwinmm)
