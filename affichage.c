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

Deplacement afficherTourJoueur(Joueur joueur, Rafle *rafle) {
    int ligneInitiale, colonneInitiale;
    int ligneFinale, colonneFinale;
    int x = 0;
    Deplacement deplacement;

    printf("====== Tour de %s ======\n", joueur.surnom);

    do {
        printf("Entrer la ligne initiale:\t");
        scanf("%d", &ligneInitiale);
        printf("\nEntrer la colonne initiale:\t");
        scanf("%d", &colonneInitiale);

        if(verifierCaseVide(ligneInitiale, colonneInitiale)) {
            printf("\nLa case est vide.Reessayer\n"); 
            x = 1;
        } else if(!verifierCaseValide(ligneInitiale, colonneInitiale)) {
            printf("\nLa case n'est pas valide.Reessayer\n"); 
            x = 1;
        } else if(rechercherRafle(rafle, ligneFinale, colonneFinale) == NULL) {
            printf("Deplacement incorrect");
            x = 1;
        }
    } while(x == 0);

    do {
        printf("\nEntrer la ligne finale:\t");
        scanf("%d", &ligneFinale);
        printf("\nEntrer la colonne finale:\t");
        scanf("%d", &colonneFinale);

        if(verifierCaseValide(ligneFinale, colonneFinale)) {
            printf("\nLa case est vide.Reessayer\n"); 
            x = 2;
        } else if(!verifierCaseValide(ligneFinale, colonneFinale)) {
            printf("\nLa case n'est pas valide.Reessayer\n"); 
            x = 2;
        } else if(rechercherRafle(rafle, ligneFinale, colonneFinale) == NULL) {
            printf("Deplacements incorrectes");
            x = 2;
        }


    } while(x == 1);

    deplacement.caseInitiale.ligne = ligneInitiale;
    deplacement.caseInitiale.colonne = colonneInitiale;
    deplacement.caseFinale.ligne = ligneFinale;
    deplacement.caseFinale.colonne = colonneFinale;

    return deplacement;
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
    system("clear");
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
            joueur1.tour = 0;

            // Enregistrement du Joueur Machine
            char cpu[30];
            snprintf(cpu, sizeof(cpu), "%s_%d", "CPU", genererNombre(1, 100)); // concatene une chaine avec un nombre
            strcpy(joueur2.surnom, cpu);
            strcpy(joueur2.nom, cpu);
            strcpy(joueur2.prenom, cpu);
            strcpy(joueur2.email, cpu);
            joueur2.type = CPU;
            joueur2.tour = 0;
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
            joueur1.tour = 0;

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
            joueur2.tour = 0;
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
    system("cls");
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
                                printf("\033[43m\033[37m X ");
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
                                printf("\033[44m\033[37m   ");
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

void nouvellePartie(Damier *damier) {
    int choix, typeJoeur;

    system("clear");
    printf("\nLancer une nouvelle partie...\n");

    do {
        afficherTypeJoeur();
        printf("Entrez le numéro du type de joueur : ");
        scanf("%d", &typeJoeur);

        switch (typeJoeur) {
            case 1: // Humain VS Machine
                Joueur humain, machine;
                enregistrerJoeur(1, humain, machine);
                humain.tour = 1;
                jouerPartie(damier, humain, machine, choix);
            break;
            case 2: // Humain VS Humain
                Joueur humain1, humain2;
                enregistrerJoeur(2, humain1, humain2);
                humain1.tour = 1;
                jouerPartie(damier, humain1, humain2, choix);
            break;
            case 3:
                printf("Retour au menu principal!\n");
            break;
            case 0:
                choix = 0;
                printf("Quitter le jeu de dames. Au revoir!\n");
            break;
            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 2.\n");
            break;
        }

    } while(typeJoeur != 3 && typeJoeur != 0);
}

void choisirOptions(int *option) {
    do {
        afficherOptions();
        printf("Entrez le numéro de l'option : \n");
        scanf("%d", option);
    } while(*option != 1 && *option != 2 && *option != 3);
}


void jouerPartie(Damier *damier, Joueur joueur1, Joueur joueur2, int quitter) {
    Rafle *deplacementPossible = NULL, *raflePossible = NULL;
    Deplacement deplacementJoeur;

    system("clear");
    initialiserDamier(damier);

    while(verifierFinPartie(damier, joueur1, quitter) && verifierFinPartie(damier, joueur2, quitter)) {
        if(joueur1.tour) {
            deplacementPossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 1);
            raflePossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 2);

            if(raflePossible == NULL) {
                afficherDamier(damier, deplacementPossible);
                deplacementJoeur = afficherTourJoueur(joueur1, deplacementPossible);
            } else {
                afficherDamier(damier, raflePossible);
                deplacementJoeur = afficherTourJoueur(joueur1, raflePossible);
            }

            deplacerPion(damier, deplacementJoeur, raflePossible, joueur1.couleur);
            joueur1.tour = 0;
        } else if(joueur2.tour) {
            deplacementPossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 1);
            raflePossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 2);

            if(raflePossible == NULL) {
                afficherDamier(damier, deplacementPossible);
                deplacementJoeur = afficherTourJoueur(joueur2, deplacementPossible);
            } else {
                afficherDamier(damier, raflePossible);
                deplacementJoeur = afficherTourJoueur(joueur2, raflePossible);
            }

            deplacerPion(damier, deplacementJoeur, raflePossible, joueur2.couleur);
            joueur2.tour = 0;
        }
    }
    
}

