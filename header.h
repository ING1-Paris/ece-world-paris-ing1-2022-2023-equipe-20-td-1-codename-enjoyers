//
// Created by guych on 24/04/2023.
//

#ifndef PROJET_HEADER_H
#define PROJET_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <allegro.h>
#include <winalleg.h>
#include <mmsystem.h>
#include <math.h>

#define NOMBRE_JOUEURS 2
#define NOMBRE_HITBOXES 15
#define NOMBRE_EVENTBOXES 8



// MENU ET POUR TOUT EN GENERAL
typedef struct joueur {

    char nom[64];
    int tickets;
    int score;
    int x,y;     // position
    int tx,ty;   // taille
    int dx, dy;     // vitesse des déplacements (nombre de pixels)
    int Sprite_actif;
    BITMAP * sprites[13];


} t_joueur;

typedef struct hitbox {

    int x1, y1;
    int x2, y2;

} t_hitbox;

void charger_sprites(t_joueur * joueur_actuel, char nom_perso[256]);
void charger_hitboxes(BITMAP * bmp, t_hitbox tab_hitboxes[NOMBRE_HITBOXES], int couleur);
void deplacement_joueurs(BITMAP * bmp, t_joueur tableau_joueurs[NOMBRE_JOUEURS], t_hitbox tab_hitboxes[NOMBRE_HITBOXES],int innactivite[NOMBRE_JOUEURS]);
int collision_joueur_hitbox(t_hitbox * hitbox, t_joueur * joueur_actuel);
int activation_event(t_joueur tab_joueurs[NOMBRE_JOUEURS], t_hitbox tab_eventboxes[NOMBRE_EVENTBOXES]);
int Recherche_event_le_plus_proche(t_joueur* Joueur);
void Acceuil();
void Fin_du_jeu(BITMAP * page,t_joueur tableau_joueurs[NOMBRE_JOUEURS]);








// SAUVEGARDE

typedef struct entree_sauvegarde {

    int jeu; //SNAKE/GUITAR HERO/TIR-BALLON/COURSE/TAUPE/RIVIERE  (1 à 6)
    int score;
    int temps;
    int date;
    char map[128];
    char nom[128];

} t_entree_sauvegarde;

int consulter(t_entree_sauvegarde * tab_de_sauvegarde, int * taille_tab);
void triInsertion(t_entree_sauvegarde * tableau, int taille_tab);








// GUITAR HERO
#define TAILLE_TAB_CHANSONS 3
#define TEMPO_DE_BASE 480000

typedef struct note_musique {

    int note;
    int millis;
    int portee;
    int x_centre;
    int y_centre;
    int radius;
    int couleur;
    float dy;
    int affichage;

} t_note;

typedef struct cercle_fixe {

    int x_centre;
    int y_centre;
    int radius;
    int couleur;


} t_cercle_fixe;


void guitar_hero();
char *listbox_getter(int index, int *list_size);
t_note * charger_musique(char nom_musique[256], int * taille_tab, int * tempo);
void charger_interface(BITMAP * bmp, t_cercle_fixe tab_cercles_fixes[5]);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void spawn_cercles(BITMAP * bmp, t_note * note_a_jouer);
void actualiser_cercle(t_note * note_a_jouer);
void actualiser_tab_cercles(BITMAP * bmp, t_note * tableau_notes, int taille_tab);
int collision_cercles(t_cercle_fixe *a1, t_note *a2);
t_note * organiser_portees(t_note * tab_notes, int taille_tab_notes, int * taille_portee, int portee);
void update_millis(t_note * note_a_update, int tempo);
void detection_touches(t_note * portee_1, int index_1, int * index_note_jouee_1, t_note * portee_2, int index_2, int * index_note_jouee_2, t_cercle_fixe * tab_cercles_fixes, int * alive, int mono_portee);











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

typedef struct Pomme{
    int x,y;
    BITMAP* Skin;

}t_Pomme;

void Snake(t_joueur* Joueur,unsigned long* Temps);
t_corp_de_snake* Creer_maillon(BITMAP* tab_de_Skin[12]);
void Actualisation_Snake(t_corp_de_snake* head);
void Deplacement_Snake_1(t_corp_de_snake * head);
void Deplacement_Snake_2(t_corp_de_snake * head);
void Ajout_de_Longueur(t_corp_de_snake* Head,BITMAP* Tab_de_sprites[12],int* Longueur);
void Invertion(t_corp_de_snake* Liste_init,BITMAP* page,int Animation);
int Collision_Acteur(t_corp_de_snake* head,t_corp_de_snake* corp);
void generation_Pomme(t_Pomme* Pomme);
int actualistation_Pomme(t_corp_de_snake* head,t_Pomme* Pomme);
void Interaction_Pomme(t_corp_de_snake* head,t_Pomme* Pomme,int *Longeur,BITMAP* tab_de_Skin[12]);
void Mort_de_serpent(t_corp_de_snake * head);
int Fin_de_partie(int serpent_en_vie[2]);

















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

void jeuballons();

// ----------------------------------------



//COURSE DE LAPIN
void jeu_course();




//LA RIVIERE

#define NRONDIN 15

typedef struct rondin{

    int tx,ty;   // taille
    BITMAP *img;
    int posx,posy;
    int depx;
    int indice_ligne;
    int taille[109][50][2];
    int affichage;

}t_rondin;



typedef struct joueur_riv
{
    int tx, ty;
    unsigned long temps;
    int x, y;
    int vit;
    int skin_utilise;
    BITMAP *skin_perso[13];
    int affichage;

} t_joueur_riv;



void traverser_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS], unsigned long* Temps);

t_rondin * Creation_rondin(int nb);
void Remplir_tab_rondin(t_rondin * tableau_de_rondin[NRONDIN]);
void Afficher_rondin(BITMAP *bmp, t_rondin *rondin_a_afficher);
void Afficher_tab_rondin(BITMAP *bmp, t_rondin *tab_rondin[NRONDIN]);
void Deplacement_rondin(t_rondin *le_rondin);
void Deplacement_tab_rondin(t_rondin *le_rondin[NRONDIN]);


t_joueur_riv Creation_joueur(t_joueur joueur[NOMBRE_JOUEURS]);
void Afficher_joueur(BITMAP *bmp, t_joueur_riv joueur_a_afficher[NOMBRE_JOUEURS]);

int Collision_joueur_rondin(t_rondin *rondin, t_joueur_riv *joueur);
void Deplacement_joueur(t_rondin rondin[NRONDIN], t_joueur_riv joueur[NOMBRE_JOUEURS], int innactivite[NOMBRE_JOUEURS]);


int Fin_partie_riv(t_joueur_riv joueur[NOMBRE_JOUEURS]);












//JEU DE LA TAUPE

#define NOMBRE_TAUPE 10
void jeu_taupe(t_joueur joueur_riv[NOMBRE_JOUEURS]);


typedef struct taupe{

    int tx,ty;
    BITMAP *skin;
    int affichage;
    int taille[79][100][2];
    int x,y;

}t_taupe;



typedef struct joueur_taupe
{
    int tx, ty;
    unsigned long temps;
    int score;
} t_joueur_taupe;



int verfication(t_taupe tab_taupe);
int Fin_partie_taupe(t_joueur_taupe joueur[NOMBRE_JOUEURS]);









#endif //PROJET_HEADER_H
