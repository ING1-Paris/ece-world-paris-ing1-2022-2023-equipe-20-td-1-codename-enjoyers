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
int activation_event(t_joueur tab_joueurs[NOMBRE_JOUEURS], t_hitbox tab_eventboxes[NOMBRE_EVENTBOXES],int joueur_leader);
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


void guitar_hero(t_joueur * tab_joueurs);
char *listbox_getter(int index, int *list_size);
t_note * charger_musique(char nom_musique[256], int * taille_tab, int * tempo);
void charger_interface(BITMAP * bmp, t_cercle_fixe tab_cercles_fixes[5], t_joueur * tab_joueurs);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void spawn_cercles(BITMAP * bmp, t_note * note_a_jouer);
void actualiser_cercle(t_note * note_a_jouer);
void actualiser_tab_cercles(BITMAP * bmp, t_note * tableau_notes, int taille_tab);
int collision_cercles(t_cercle_fixe *a1, t_note *a2);
t_note * organiser_portees(t_note * tab_notes, int taille_tab_notes, int * taille_portee, int portee);
void update_millis(t_note * note_a_update, int tempo);
void detection_touches(t_note * portee_1, int index_1, int * index_note_jouee_1, t_note * portee_2, int index_2, int * index_note_jouee_2, t_cercle_fixe * tab_cercles_fixes, int * alive, int mono_portee, t_joueur * joueur_actuel);











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
    int x,y; // position du coin supérieur gauche
    int dx,dy; // vecteur déplacement
    int tx,ty; // largeur hauteur de l'image

    int couleur;

    int comportement; // comportement : 0 normal et 1 explosion
    int cptexplo; // temps depuis l'explosion

    int vivant; // vivant : 0 mort (doit disparaitre de la liste) et 1 vivant

} t_acteur;

// Une collection de acteurs
typedef struct listeActeurs
{
    int max; // nombre maxi d'éléments =taille du tableau de pointeurs
    int n; // nombre effectif de pointeurs utilisés
    t_acteur **tab; // le tableau de pointeurs (alloué dynamiquement)

} t_listeActeurs;


typedef struct joueur_ballons {
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des déplacements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image chargée)
} t_joueur_ballons;

typedef struct ballon {
    int x,y;     // position
    int dx, dy;      // vecteur déplacement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image chargée)
} t_ballon;

void jeuballons();

t_acteur * creerActeur(int x,int y,int type);
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type);
t_listeActeurs * creerListeActeurs(int maxacteurs);
void enleverActeur(t_listeActeurs *la,int i);
void actualiserActeur(t_acteur *acteur);
void actualiserListeActeurs(t_listeActeurs *la);
void dessinerActeur(BITMAP *bmp,t_acteur *acteur);
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la);
int libreListeActeurs(t_listeActeurs *la);

//gérer le fusil et le ballon
t_joueur_ballons * creerJoueur(char *nomimage);
void actualiserJoueur(t_joueur_ballons *joueur,t_listeActeurs *la);
void dessinerJoueur(BITMAP *bmp,t_joueur_ballons *joueur);
void destinActeur(t_acteur *acteur);
// Gérer collision (éventuelle) entre un acteur (un tir) et un ballon_bleu
void collisionActeurBleu(t_ballon *ballon_bleu, t_acteur *acteur);
void collisionActeurRose(t_ballon *ballon_rose, t_acteur *acteur);
void collisionActeurVert(t_ballon *ballon_vert, t_acteur *acteur);
void collisionActeurViolet(t_ballon *ballon_violet, t_acteur *acteur);
void collisionActeurRouge(t_ballon *ballon_rouge, t_acteur *acteur);

// Gérer les collisions entre les acteurs (tous les tirs) et un ballon_bleu
void collisionListeActeursBleu(t_ballon *ballon_bleu,t_listeActeurs *la);
void collisionListeActeursRose(t_ballon *ballon_rose,t_listeActeurs *la);
void collisionListeActeursVert(t_ballon *ballon_vert,t_listeActeurs *la);
void collisionListeActeursViolet(t_ballon *ballon_violet,t_listeActeurs *la);
void collisionListeActeursRouge(t_ballon *ballon_rouge,t_listeActeurs *la);

// Allouer et initialiser les ballons
t_ballon * creerBallon_bleu(char *nomimage);
t_ballon * creerBallon_rose(char *nomimage);
t_ballon * creerBallon_vert(char *nomimage);
t_ballon * creerBallon_violet(char *nomimage);
t_ballon * creerBallon_rouge(char *nomimage);

// Actualiser les ballons (bouger automatiquement au hasard...)
void actualiserBallon_bleu(t_ballon *ballon_bleu);
void actualiserBallon_rose(t_ballon *ballon_rose);
void actualiserBallon_vert(t_ballon *ballon_vert);
void actualiserBallon_violet(t_ballon *ballon_violet);
void actualiserBallon_rouge(t_ballon *ballon_rouge);

// Dessiner les ballons sur la bitmap bmp
void dessinerBallon_bleu(BITMAP *bmp,t_ballon *ballon_bleu);
void dessinerBallon_rose(BITMAP *bmp,t_ballon *ballon_rose);
void dessinerBallon_vert(BITMAP *bmp,t_ballon *ballon_vert);
void dessinerBallon_violet(BITMAP *bmp,t_ballon *ballon_violet);
void dessinerBallon_rouge(BITMAP *bmp,t_ballon *ballon_rouge);

// ----------------------------------------



//COURSE DE LAPIN
void jeu_course();


typedef struct sequence
{
    char *nomSource; // nom du fichier image contenant la séquence
    int nimg;        // nombre d'images dans la séquence
    int tx,ty;       // largeur et hauteur des images de la séquence
    int ncol;        // nbr images cotes à cotés horizontalement dans le fichier image
    BITMAP **img;    // tableau de pointeurs pour indiquer les images
} t_sequence;

typedef struct lapin
{
    int x,y;         // position du coin supérieur gauche
    int dx;          // déplacement
    int tmpdx;       // ralentir déplacements en x (1 pour ne pas ralentir)
    int cptdx;       // compteur pour ralentir déplacement
    int tx,ty;       // largeur hauteur


    int imgcourante; // indice de l'image courante
    int tmpimg;      // ralentir séquence (image suivante 1 fois sur tmpimg)
    int cptimg;      // compteur pour ralentir séquence

    int type; //numéro du lapin (de 0 à 5)

} t_lapin;

#define Nlapin 6
#define NSEQUENCE 6
t_lapin * creerlapin(int type, int x, int y, int dx, int tmpdx, int tmpimg);
void remplirTablapins(t_lapin * tab[Nlapin]);
void actualiserlapin(t_lapin *lapin, int tabParis[2], int *alive, BITMAP *page, t_joueur tableau_joueurs[NOMBRE_JOUEURS]);
void actualiserTablapins(t_lapin * tab[Nlapin], int tabParis[2], int *alive, BITMAP *page, t_joueur tableau_joueurs[NOMBRE_JOUEURS]);
void dessinerlapin(BITMAP *bmp, t_lapin *lapin);
void dessinerTablapins(BITMAP *bmp,t_lapin * tab[Nlapin]);
void chargerSequence(t_sequence * seq);
void chargerTabSequences();




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
    int dx,dy;
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
void Deplacement_joueur(t_rondin rondin[NRONDIN], t_joueur_riv * joueur_en_train_de_jouer, int innactivite[NOMBRE_JOUEURS]);


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
