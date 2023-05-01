//
// Created by guych on 24/04/2023.
//

#ifndef PROJET_HEADER_H
#define PROJET_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>

#define NOMBRE_JOUEURS 2
#define NOMBRE_HITBOXES 12



// MENU ET POUR TOUT EN GENERAL
typedef struct joueur {

    char nom[64];
    int score;
    int x,y;     // position
    int tx,ty;   // taille
    int dx, dy;     // vitesse des déplacements (nombre de pixels)
    BITMAP * sprites[13];

} t_joueur;

typedef struct hitbox {

    int x1, y1;
    int x2, y2;

} t_hitbox;

void charger_sprites(t_joueur * joueur_actuel, char nom_perso[256]);
void charger_hitboxes(BITMAP * bmp, t_hitbox tab_hitboxes[NOMBRE_HITBOXES]);
void deplacement_joueurs(BITMAP * bmp, t_joueur tableau_joueurs[NOMBRE_JOUEURS], t_hitbox tab_hitboxes[NOMBRE_HITBOXES]);
int collision_joueur_hitbox(t_hitbox * hitbox, t_joueur * joueur_actuel);













//LE SNAKE

#define TAILLE_TAB 6

typedef struct Maillon {
    BITMAP* Skin[12];
    int skin_used;
    int x,y;
    int last_x[TAILLE_TAB],last_y[TAILLE_TAB];
    int tx,ty;
    int dx,dy;
    struct Maillon* next_corp;
}t_corp_de_snake;

void Snake(t_joueur Joueur[NOMBRE_JOUEURS]);
t_corp_de_snake* Creer_maillon(t_corp_de_snake* maillon_precedent,BITMAP* tab_de_Skin[12]);
void Actualisation_Snake(t_corp_de_snake* head);
void Invertion(t_corp_de_snake* Liste_init,BITMAP* page,int Animation);

















// JEU DE TIR AUX BALLONS
// ----------------------------------------
typedef struct acteur
{

    // position du coin sup. gauche
    int x,y;

    // vecteur deplacement
    int dx,dy;

    // largeur hauteur
    int tx,ty;

    // couleur (ne sera plus pertinent avec des sprites importés...)
    int couleur;

    // type (ici 2 types mais on peut en mettre plus):
    //   0 laser
    //   1 missile (accélération horizontale)
    int type;

    // comportement :
    //   0 normal déplacement
    //   1 explosion
    int comportement;
    int cptexplo; // temps depuis l'explosion

    // vivant :
    //   0 mort (doit disparaitre de la liste)
    //   1 vivant
    int vivant;

} t_acteur;

// Une collection de acteurs
typedef struct listeActeurs
{
    // nombre maxi d'éléments
    // =taille du tableau de pointeurs
    int max;

    // nombre effectif de pointeurs utilisés
    // (les autres sont à NULL)
    int n;

    // le tableau de pointeurs (alloué dynamiquement)
    t_acteur **tab;

} t_listeActeurs;


// Spécifique à cet exemple : un fusil et un ballon
// Un élément à déplacement interactif
typedef struct joueur_ballons {
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des déplacements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image chargée)
} t_joueur_ballons;

// Un élément à déplacement automatique aléatoire
typedef struct ballon {
    int x,y;     // position
    int dx;      // vecteur déplacement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image chargée)
} t_ballon;

// ----------------------------------------



#endif //PROJET_HEADER_H
