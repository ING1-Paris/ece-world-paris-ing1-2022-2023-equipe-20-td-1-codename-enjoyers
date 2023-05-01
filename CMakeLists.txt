cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET main.c header.h src/Ballons/jeuballons.c src/Snake/Jeux_Snake.c src/Riviere/jeu_riviere.c src/Menu/charger_sprites.c src/Snake/Sous_programme_Snake.c src/Menu/charger_hitboxes.c src/Menu/deplacement_joueurs.c src/Menu/collision_joueur_hitbox.c)

target_link_libraries(PROJET -lmingw32 -lalleg44)
