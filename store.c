// Library privé
#include "store.h"

// ----------------------------
// Fonctions pour les magasins
// ----------------------------

// Fonction pour créer un nouveau magasin
store *creerMagasin(char *nom_magasin) {
    store *nouveau = (store *)malloc(sizeof(store));
    strcpy(nouveau->nom_magasin, nom_magasin);
    nouveau->produits = NULL; // Liste de produits vide
    nouveau->suivant = NULL;
    return nouveau;
}

// Fonction pour rechercher un magasin dans la liste
store *rechercherMagasin(store *head, char *nom_magasin) {
    while (head != NULL) {
        if (strcmp(head->nom_magasin, nom_magasin) == 0) {
            return head;
        }
        head = head->suivant;
    }
    return NULL;
}

// Fonction pour rechercher un produit dans un magasin
int rechercherProduitMagasin(store *liste, char *nom_magasin, char *nom_produit, char *nom_marque) {
    store *magasin = rechercherMagasin(liste, nom_magasin);

    if (magasin == NULL) {  // Vérification avant d'accéder à magasin->produits
        traitement();
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        printf(">>         \033[1;36mModifier un Produit\033[0m         <<\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

        printf("\033[1;31mMagasin '%s' introuvable.\033[0m\n", nom_magasin);

        printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
        getchar(); getchar();
        return 0;
    }

    product *actuel = magasin->produits;

    while (actuel != NULL) {
        if (strcmp(actuel->nom_produit, nom_produit) == 0 && strcmp(actuel->nom_marque, nom_marque) == 0) {
            return 1;
        }
        actuel = actuel->suivant;
    }

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>         \033[1;36mModifier un Produit\033[0m         <<\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

    printf("\033[1;31mProduit '%s' (Marque : %s) introuvable dans le magasin '%s'.\033[0m\n", nom_produit, nom_magasin);
    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
    return 0;
}

// ------------------------
// Fonction ajouterProduit
// ------------------------
void ajouterProduit(store *magasin, char *nom_produit, char *nom_categorie, char *nom_marque, char *nom_rayon, int quantite, float prix) {
    product *nouveau = (product *)malloc(sizeof(product));
    memset(nouveau, 0, sizeof(product));

    // Initialiser les valeurs du nouveau produit
    strcpy(nouveau->nom_produit, nom_produit);
    strcpy(nouveau->nom_categorie, nom_categorie);
    strcpy(nouveau->nom_marque, nom_marque);
    strcpy(nouveau->nom_rayon, nom_rayon);

    nouveau->quantite = quantite;
    nouveau->prix = prix;
    nouveau->suivant = NULL;

    // Ajouter le produit à la liste du magasin
    if (magasin->produits == NULL) {
        magasin->produits = nouveau;
    } else {
        product *tmp = magasin->produits;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = nouveau;
    }
}

// -------------------------
// Fonction modifier produit
// -------------------------
void modifierProduit(store *magasin, char *old_nom_produit, char *old_nom_marque, char *new_nom_produit, char *new_nom_categorie, char *new_nom_marque, char *new_nom_rayon, int new_quantite, float new_prix) {
    int tmp = 0;

    product *actuel = magasin->produits;
    while(actuel != NULL) {
        if(strcmp(actuel->nom_produit, old_nom_produit) == 0 && strcmp(actuel->nom_marque, old_nom_marque) == 0) {
            strcpy(actuel->nom_produit, new_nom_produit);
            strcpy(actuel->nom_categorie, new_nom_categorie);
            strcpy(actuel->nom_marque, new_nom_marque);
            strcpy(actuel->nom_rayon, new_nom_rayon);
            actuel->quantite = new_quantite;
            actuel->prix = new_prix;
            tmp++;
            break;
        }
        actuel = actuel->suivant;
    }

    if(tmp == 0) {
        printf("\n\033[1;31mProduit '%s' (Marque : %s) introuvable dans le magasin.\033[0m\n", old_nom_produit, old_nom_marque);
    } else {
        printf("\033[1;32mProduit '%s' modifi%c avec succ%cs.\033[0m\n", new_nom_produit, 130, 138, new_nom_marque);
    }

    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}

// --------------------------
// Fonction supprimer produit
// --------------------------
void supprimerProduit(store *magasin, char *nom_produit, char *nom_marque) {
    product *actuel = magasin->produits;
    product *precedent = NULL;
    int tmp = 0;

    while (actuel != NULL) {
        if (strcmp(actuel->nom_produit, nom_produit) == 0 && strcmp(actuel->nom_marque, nom_marque) == 0) {
            if (precedent == NULL) {
                // Le produit à supprimer est le premier de la liste
                magasin->produits = actuel->suivant;
            } else {
                // Supprimer le produit du milieu ou de la fin
                precedent->suivant = actuel->suivant;
            }

            free(actuel);
            tmp++;
            break;
        }
        precedent = actuel;
        actuel = actuel->suivant;
    }

    clearScreen();

    if(tmp != 0) {
        printf("\033[1;31mProduit '%s' de la marque '%s' supprim%c avec succ%cs.\033[0m\n", nom_produit, nom_marque, 130, 138);
    } else {
        printf("\n\033[1;31mProduit '%s' (Marque : %s) introuvable dans le magasin.\033[0m\n", nom_produit, nom_marque);
    }
    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}

// ---------------------------
// Fonction rechercher produit
// ---------------------------
void rechercherProduit(store *debut, char nom_produit[], char nom_marque[]) {
    int tmp = 0;

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>      \033[1;36mRechercher un Produit\033[0m      <<\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

    while(debut != NULL) {
        product *actuel = debut->produits;  // Pointeur temporaire
        while(actuel != NULL) {
            if(strcmp(actuel->nom_produit, nom_produit) == 0 && strcmp(actuel->nom_marque, nom_marque) == 0) {
                printf("\nMagasin : %-s\n", debut->nom_magasin);
                printf("---------------------------\n");
                printf("  Produit : %-s\n", actuel->nom_produit);
                printf("    Cat%cgorie : %-s\n", 130, actuel->nom_categorie);
                printf("    Marque : %-s\n", actuel->nom_marque);
                printf("    Rayon : %-s\n", actuel->nom_rayon);
                printf("    Quantit%c : %d\n", 130, actuel->quantite);
                printf("    Prix/u : %.2f euro\n", actuel->prix);
                tmp++;
            }
            actuel = actuel->suivant;  // Avancer sans modifier debut->produits
        }
        debut = debut->suivant;
    }

    if(tmp == 0) {
        printf("\033[1;31mProduit '%s' (Marque : %s) introuvable dans le magasin.\033[0m\n", nom_produit, nom_marque);
    }

    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}

// ---------------------------------
// Fonction pour archiver une liste
// ---------------------------------
void archiverListe(store *listeMagasins) {
    traitement();

    FILE *fichier = fopen("archive.txt", "w");  // Utilisation de "w" pour écraser l'ancien fichier
    if (fichier == NULL) {
        printf("\033[1;31mErreur d'ouverture du fichier d'archive.\033[0m\n");

        printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
        getchar(); getchar();
        return;
    }

    store *magasin = listeMagasins;
    while (magasin != NULL) {
        // Afficher le nom du magasin
        fprintf(fichier, "%s\n", magasin->nom_magasin);

        if (magasin->produits == NULL) {
            // Si aucun produit n'est inscrit dans la liste
            fprintf(fichier, "  Aucun produit dans la liste.\n");
        } else {
            // Sinon, afficher les produits disponibles
            product *produit = magasin->produits;
            while (produit != NULL) {
                // Afficher les informations du produit avec une indentation
                fprintf(fichier, "	%-s\n", produit->nom_produit);  // Nom du produit
                fprintf(fichier, "		%-s\n", produit->nom_categorie);  // Catégorie
                fprintf(fichier, "		%-s\n", produit->nom_marque);  // Marque
                fprintf(fichier, "		%-s\n", produit->nom_rayon);  // Rayon
                fprintf(fichier, "		%d\n", produit->quantite);  // Quantité
                fprintf(fichier, "		%.2f\n", produit->prix);  // Prix unitaire
                produit = produit->suivant;
            }
        }

        magasin = magasin->suivant;
    }

    fclose(fichier);
    printf("\033[1;32mListe archiv%ce avec succ%cs.\033[0m\n", 130, 130);
    Sleep(800);

    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}

// --------------------------------
// Fonction pour importer une liste
// --------------------------------
void importerListe(store **listeMagasins) {
    traitement();
    FILE *fichier = fopen("archive.txt", "r");
    if (fichier == NULL) {
        printf("\033[1;31mErreur d'ouverture du fichier d'archive.\033[0m\n");

        printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
        getchar(); getchar();
        return;
    }

    char ligne[256], nomMagasin[100], nomProduit[80], nomCategorie[80], nomMarque[80], nomRayon[80];
    int quantiteProduit;
    float prixProduit;

    store *magasinActuel = NULL;
    product *produitActuel = NULL;

    // Lecture ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Retirer le saut de ligne à la fin
        ligne[strcspn(ligne, "\n")] = 0;

        if (strlen(ligne) == 0) {
            continue;  // Sauter les lignes vides
        }

        // Si la ligne contient le nom du magasin
        if (ligne[0] != '\t') {
            // Si un magasin est déjà ouvert, l'ajouter à la liste
            if (magasinActuel != NULL) {
                magasinActuel->suivant = *listeMagasins;
                *listeMagasins = magasinActuel;
            }

            // Créer un nouveau magasin
            strcpy(nomMagasin, ligne);
            magasinActuel = creerMagasin(nomMagasin);
            magasinActuel->produits = NULL;  // Initialiser la liste des produits à NULL
            continue;
        }

        // Si la ligne commence par une tabulation, c'est un produit à ajouter
        sscanf(ligne, "%s", nomProduit);  // Lire le nom du produit

        fgets(ligne, sizeof(ligne), fichier);  // Lire la catégorie
        sscanf(ligne, "%s", nomCategorie);

        fgets(ligne, sizeof(ligne), fichier);  // Lire la marque
        sscanf(ligne, "%s", nomMarque);

        fgets(ligne, sizeof(ligne), fichier);  // Lire le rayon
        sscanf(ligne, "%s", nomRayon);

        fgets(ligne, sizeof(ligne), fichier);  // Lire la quantité
        sscanf(ligne, "%d", &quantiteProduit);

        fgets(ligne, sizeof(ligne), fichier);  // Lire le prix
        sscanf(ligne, "%f", &prixProduit);

        // Ajouter le produit au magasin
        ajouterProduit(magasinActuel, nomProduit, nomCategorie, nomMarque, nomRayon, quantiteProduit, prixProduit);
    }

    // Ajouter le dernier magasin à la liste
    if (magasinActuel != NULL) {
        magasinActuel->suivant = *listeMagasins;
        *listeMagasins = magasinActuel;
    }

    fclose(fichier);

    printf("\033[1;32mListe import%ce avec succ%cs.\033[0m\n", 130, 138);

    printf("\nAppuyez sur Entr%ce pour confirmer et revenir au menu principal...", 130);
    getchar(); getchar();
}

// -------------------------------------------
// Affichage des produits de tous les magasins
// -------------------------------------------
void afficherMagasinsEtProduits(store *debut) {
    traitement();
    float total_prix, tmp;

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>   \033[1;36mListe des magasins et des produits\033[0m   <<\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

    if (debut == NULL) {
        printf("Aucun magasin trouv%c.\n\n", 130);

        printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
        getchar(); getchar();
        return;
    }

    while (debut != NULL) {
        printf("Magasin : %s\n", debut->nom_magasin);
        printf("---------------------------\n");

        if (debut->produits == NULL) {
            printf("  Aucun produit disponible.\n");
        } else {
            total_prix = 0;
            product *actuel = debut->produits;
            while (actuel != NULL) {
                printf("  Produit : %s\n", actuel->nom_produit);
                printf("    Cat%cgorie : %s\n", 130, actuel->nom_categorie);
                printf("    Marque : %s\n", actuel->nom_marque);
                printf("    Rayon : %s\n", actuel->nom_rayon);
                printf("    Quantit%c : %d\n", 130, actuel->quantite);
                printf("    Prix/u : %.2f euro\n", actuel->prix);

                tmp = actuel->prix * (float)(actuel->quantite);
                printf("    Prix total : %.2f euro\n", tmp);

                total_prix += tmp;
                actuel = actuel->suivant;
            }
            printf("Montant total : %.2f euro\n\n", total_prix);
        }
        debut = debut->suivant;
    }
    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}

// ----------------------------------------
// Affichage des produits d'un seul magasin
// ----------------------------------------
void afficherMagasin(store *debut) {
    traitement();
    float total_prix = 0, tmp;
    char nom_magasin[100];
    int find = 0;

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>   \033[1;36mListe des produits du magasin\033[0m   <<\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

    printf("\033[1;33mNom du magasin\033[0m > ");
    scanf("%99s", nom_magasin);

    traitement();

    while(debut != NULL) {
        if(strcmp(debut->nom_magasin, nom_magasin) == 0) {
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            printf(">>   \033[1;36mListe des produits du magasin\033[0m   <<\n");
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
            printf("Magasin : %s\n", debut->nom_magasin);
            printf("---------------------------\n");
            product *actuel = debut->produits;
            while(actuel != NULL) {
                printf("  Produit : %s\n", actuel->nom_produit);
                printf("    Cat%cgorie : %s\n", 130, actuel->nom_categorie);
                printf("    Marque : %s\n", actuel->nom_marque);
                printf("    Rayon : %s\n", actuel->nom_rayon);
                printf("    Quantit%c : %d\n", 130, actuel->quantite);
                printf("    Prix/u : %.2f euro\n", actuel->prix);

                tmp = actuel->prix * (float)(actuel->quantite);
                printf("    Prix total : %.2f euro\n", tmp);

                total_prix += tmp;
                actuel = actuel->suivant;
            }

            printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
            getchar(); getchar();
            return;
        }
        debut = debut->suivant;
    }

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>  \033[1;36mListe des produits du magasin\033[0m  <<\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    printf("Aucun magasin trouv%c avec le nom %-s.\n\n", 130, nom_magasin);

    printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}