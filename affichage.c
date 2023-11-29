#include "affichage.h"

void afficherMenu() {
    printf("====== Menu du Jeu de Dames ======\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger partie\n");
    printf("3. Options\n");
    printf("4. Aide\n");
    printf("0. Quitter\n");
    printf("===================================\n");
}

void afficherOptions() {
    printf("\n====== Options du Jeu de Dames ======\n");
    printf("1. Niveau facile\n");
    printf("2. Niveau Moyen\n");
    printf("3. Niveau difficile\n");
}

void afficherTypeJoeur() {
    printf("====== Type de joeurs du Jeu de Dames ======\n");
    printf("1. Humain VS Machine\n");
    printf("2. Humain VS Humain\n");
    printf("3. Retour au menu principal\n");
    printf("0. Quitter\n");
}


/* 
    Securise la saisie
    1: tout s'est bien passe
    0: une erreur
 */ 
int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;

    if(fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        } else {
            viderBuffer();
        }

        return 1;
    } else {
        viderBuffer();
    
        return 0;
    }
}

/* Vide le buffer si on entre trop de caractere */ 
void viderBuffer() {
    int c = 0;

    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void enregistrerJoeur(int typeJoeur, Joueur joueur1, Joueur joueur2) {
    switch (typeJoeur) {
        case 1:
            // Enregistrement du Joueur Humain
            printf("====== Enregistrement du Joueur ======\n");
            printf("Surnom: \t");
            lire(joueur1.surnom, 25);
            printf("\nNom: \t");
            lire(joueur1.nom, 25);
            printf("\nPrenom: \t");
            lire(joueur1.prenom, 25);
            printf("\nEmail: \t");
            lire(joueur1.email, 25);
            joueur1.type = HUMAIN;

            // Enregistrement du Joueur Machine
            char cpu[30];
            snprintf(cpu, sizeof(cpu), "%s_%d", "CPU", genererNombre(1, 100)); // concatene une chaine avec un nombre
            strcpy(joueur2.surnom, cpu);
            strcpy(joueur2.nom, cpu);
            strcpy(joueur2.prenom, cpu);
            strcpy(joueur2.email, cpu);
            joueur2.type = CPU;
        break; 
        case 2: 
            // Enregistrement du Joueur Humain 1
            printf("====== Enregistrement du Joueur 1 ======\n");
            printf("Surnom: \t");
            lire(joueur1.surnom, 25);
            printf("\nNom: \t");
            lire(joueur1.nom, 25);
            printf("\nPrenom: \t");
            lire(joueur1.prenom, 25);
            printf("\nEmail: \t");
            lire(joueur1.email, 25);
            joueur1.type = HUMAIN;

            // Enregistrement du Joueur Humain 2
            printf("====== Enregistrement du Joueur 2 ======\n");
            printf("Surnom: \t");
            lire(joueur2.surnom, 25);
            printf("\nNom: \t");
            lire(joueur2.nom, 25);
            printf("\nPrenom: \t");
            lire(joueur2.prenom, 25);
            printf("\nEmail: \t");
            lire(joueur2.email, 25);
            joueur2.type = HUMAIN;
        break;
    }
}

int genererNombre(int minimum, int maximum) {
    static int limit = 0;

    if(limit == 0) {
        srand(time(NULL));
        limit = 1;
    }

    return (rand() % (maximum - minimum + 1)) + minimum;
}

void afficherAide() {
    printf("\n====== Aide du Jeu de Dames ======\n");
    printf("Le jeu de dames est un jeu de plateau pour deux joueurs.\n");

    printf("Commandes :\n");
    printf("- Utilisez les coordonnées pour déplacer vos pions.\n");
    printf("- Exemple : '(1, 3) au (0, 4)' pour déplacer une pion de (1, 3) au (0, 4).\n");

    printf("=================================\n");
}

void tabuler(int nombre) {
    for(int i = 0; i < nombre; i++) {
        printf("\t");
    }
}

void initialiserDamier(Damier *damier) {
    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if ((i + j) % 2 == 0 && i < 4) { // Selection des cases blanches de la ligne 0 a 3 : Pion vert
                damier->plateau[i][j] = PION_VERT;
            } else if ((i + j) % 2 == 0 && i > 5) { // Selection des cases blanches de la ligne 6 a 9 : Pion rouge
                damier->plateau[i][j] = PION_ROUGE; 
            } // Les cases comprises entre 4 et 5 sont vides
        }
    }
}

void afficherDamier(Damier *damier, Rafle *rafle) {
    printf("\t\t   0  1  2  3  4  5  6  7  8  9\n");
    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        tabuler(2);
        printf("%d ", i);

        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if ((i + j) % 2 == 0) { // Selection et Affichage des cases blanches
                if (damier->plateau[i][j] == PION_VERT) { // Affichage des pions verts
                    if(rafle == NULL){
                        printf("\033[47m\033[32m X ");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[41m\033[37m X ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[32m X ");
                        }
                    }
                } else if(damier->plateau[i][j] == PION_ROUGE) { // Affichage des pions rouges
                    if(rafle == NULL){
                        printf("\033[47m\033[31m O ");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[41m\033[37m O ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[31m O ");
                        }
                    }
                } else { // Affichages des cases vides
                    if(rafle == NULL){
                        printf("\033[47m\033[31m   ");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[41m\033[37m   ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[31m   ");
                        }
                    }
                }
            } else { // Selection et Affichage des cases noires
                printf("\033[40m   ");
            }
        }
        printf("\033[0m %d\n", i);
    }
    printf("\t\t   0  1  2  3  4  5  6  7  8  9\n");
}


