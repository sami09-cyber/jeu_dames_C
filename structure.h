#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <time.h>

/* Constantes representants l'etat d'une case et le type de joueur */ 
#define CASE_VIDE 0
#define CASE_BLANCHE 1 
#define CASE_NOIRE 2
#define PION_ROUGE 31
#define PION_VERT 32 
#define CPU 1
#define HUMAIN 2
#define DIMENSION_PLATEAU 10
#define NOMBRE_PION_BLANC 20
#define NOMBRE_PION_NOIR 20

/* Representation d'une case */ 
typedef struct CASE {
    int ligne;
    int colonne;
} Case;

/* Representation d'un deplacement */ 
typedef struct DEPLACEMENT {
    Case caseInitiale; 
    Case caseFinale;
} Deplacement;

/* Representation des rafles: Les rafles sont une liste de case*/ 
typedef struct RAFLE {
    Case cases;
    struct RAFLE *suivante;
} Rafle;

/* Representation d'un joueur: Le type de joueur est soit HUMAIN ou CPU*/ 
typedef struct JOUEUR {
    char surnom[25];
    char nom[25];
    char prenom[25];
    char email[25];
    int type;
    int couleur;
} Joueur;

/* Representation du damier: Le damier est le plateau contenant les pions */ 
typedef struct DAMIER {
    int plateau[DIMENSION_PLATEAU][DIMENSION_PLATEAU]; // Représente l’état du plateau
    int nombrePionNoir; // Représente le nombre de pion noir
    int nombrePionBlanc; // Représente le nombre de pion blanc
} Damier;


Damier * creerDamier();

Rafle * creerRafle(int ligne, int colonne);

Rafle * insererRafle(Rafle *rafle, Rafle *c);

Rafle * supprimerRafle(Rafle *rafle, int position);
