#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "store.h"
#include "affichage.h"

// ----------------------------
// Fonctions pour les magasins
// ----------------------------

// Fonction pour créer un nouveau magasin
store *creerMagasin(char *nom_magasin) {
    store *nouveau = (store *)malloc(sizeof(store));
    //memset(nouveau, 0, sizeof(store));  // Réinitialiser toute la structure à zéro
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

// ------------------------
// Fonction ajouterProduit
// ------------------------
void ajouterProduit(store *magasin, char *nom_produit, char *nom_categorie, char *nom_marque, char *nom_rayon, int quantite, float prix) {
    product *nouveau = (product *)malloc(sizeof(product));
    memset(nouveau, 0, sizeof(product));  // Réinitialiser toute la structure à zéro

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

// --------------------------
// Fonction supprimer produit
// --------------------------
void supprimerProduit(store *magasin, char *nom_produit, char *nom_marque) {
    if (magasin == NULL || magasin->produits == NULL) {
        printf("\n\033[1;31m[ERREUR] Le magasin est vide ou inexistant.\033[0m\n");
        return;
    }

    product *actuel = magasin->produits;
    product *precedent = NULL;

    printf("\n\033[1;36m----- Suppression du Produit -----\033[0m\n");
    printf("Produit à supprimer : \033[1;32m'%s' (Marque : %s)\033[0m\n", nom_produit, nom_marque);
    printf("----------------------------------\n");

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
            printf("\033[1;31mProduit '%s' de la marque '%s' supprim%c avec succ%cs.\033[0m\n", nom_produit, nom_marque, 130, 138);
            printf("\033[1;36m----------------------------------\033[0m\n");
            return;
        }
        precedent = actuel;
        actuel = actuel->suivant;
    }

    printf("\n\033[1;31m[ERREUR] Produit '%s' (Marque : %s) introuvable dans le magasin.\033[0m\n", nom_produit, nom_marque);
    printf("\033[1;36m----------------------------------\033[0m\n");
}

// --------------------------
// Fonction supprimer produit
// --------------------------
void rechercherProduit(store *debut, char nom_produit[], char nom_marque[]) {
    while(debut != NULL) {
        while(debut->produits != NULL) {
            if(strcmp(debut->produits->nom_produit, nom_produit) == 0) {
                printf("trouv%c\n", 130);
            }
            debut->produits = debut->produits->suivant;
        }
        debut = debut->suivant;
    }
}

// ---------------------------------
// Fonction pour archiver une liste
// ---------------------------------
void archiverListe(store *listeMagasins) {
    FILE *fichier = fopen("archive.txt", "w");  // Utilisation de "w" pour écraser l'ancien fichier
    if (fichier == NULL) {
        printf("\033[1;31mErreur d'ouverture du fichier d'archive.\033[0m\n");
        return;
    }

    store *magasin = listeMagasins;
    while (magasin != NULL) {
        // Afficher le nom du magasin
        fprintf(fichier, "%s\n", magasin->nom_magasin);

        if (magasin->produits == NULL) {
            // Si aucun produit n'est disponible, afficher ce message
            fprintf(fichier, "  Aucun produit disponible.\n");
        } else {
            // Sinon, afficher les produits disponibles
            product *produit = magasin->produits;
            while (produit != NULL) {
                // Afficher les informations du produit avec une indentation
                fprintf(fichier, "	%s\n", produit->nom_produit);  // Nom du produit
                fprintf(fichier, "		%s\n", produit->nom_categorie);  // Catégorie
                fprintf(fichier, "		%s\n", produit->nom_marque);  // Marque
                fprintf(fichier, "		%s\n", produit->nom_rayon);  // Rayon
                fprintf(fichier, "		%d\n", produit->quantite);  // Quantité
                fprintf(fichier, "		%.2f\n", produit->prix);  // Prix unitaire
                produit = produit->suivant;
            }
        }

        magasin = magasin->suivant;
    }

    fclose(fichier);
    printf("\033[1;32mListe archivée avec succès.\033[0m\n");
    Sleep(200);
    printf("Appuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
}

// --------------------------------
// Fonction pour importer une liste
// --------------------------------
void importerListe(store **listeMagasins) {
    FILE *fichier = fopen("archive.txt", "r");
    if (fichier == NULL) {
        printf("\033[1;31mErreur d'ouverture du fichier d'archive.\033[0m\n");
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

    clearScreen();
    printf("\033[1;32mListe import%ce avec succ%cs depuis 'archive.txt'.\033[0m\n", 130, 138);
    printf("Appuyez sur Entr%ce pour confirmer et revenir au menu principal...", 130);
    getchar(); getchar();
}

// ----------------------
// Affichage des données
// ----------------------
void afficherMagasinsEtProduits(store *debut) {
    float total_prix, tmp;

    if (debut == NULL) {
        printf("\nAucun magasin trouv%c.\n\n", 130);  // Utilisation de %c 130 pour "é"
        return;
    }

    while (debut != NULL) {
        printf("\nMagasin : %s\n", debut->nom_magasin);
        printf("---------------------------\n");

        if (debut->produits == NULL) {
            printf("  Aucun produit disponible.\n");
        } else {
            total_prix = 0;
            product *actuel = debut->produits;
            while (actuel != NULL) {
                printf("  Produit : %s\n", actuel->nom_produit);
                printf("    Cat%cgorie : %s\n", 130, actuel->nom_categorie);  // Utilisation de %c 130 pour "é"
                printf("    Marque : %s\n", actuel->nom_marque);
                printf("    Rayon : %s\n", actuel->nom_rayon);
                printf("    Quantit%c : %d\n", 130, actuel->quantite);  // Utilisation de %c 130 pour "é"
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
}