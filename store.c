#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// ------------------------
// Fonction ajouterProduit
// ------------------------
void ajouterProduit(store *magasin, char *nom_produit, char *nom_categorie, char *nom_marque, char *nom_rayon, int quantite, float prix) {
    product *nouveau = (product *)malloc(sizeof(product));

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
    printf("\nProduit '%s' ajout%c au magasin '%s' avec succ%cs.\n", nom_produit, 130, magasin->nom_magasin, 130);
}

// --------------------------
// Fonction supprimer produit
// --------------------------

// Fonction pour supprimer un produit
void supprimerProduit(store *magasin, char *nom_produit, char *nom_marque) {
    if (magasin == NULL || magasin->produits == NULL) {
        printf("\nLe magasin est vide ou inexistant.\n");
        return;
    }

    product *actuel = magasin->produits;
    product *precedent = NULL;

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
            printf("\nProduit '%s' (Marque : %s) supprim%c avec succ%cs.\n", nom_produit, nom_marque, 130, 130);
            return;
        }
        precedent = actuel;
        actuel = actuel->suivant;
    }
    printf("\nProduit '%s' (Marque : %s) introuvable dans le magasin.\n", nom_produit, nom_marque);
}

// ----------------------
// Affichage des données
// ----------------------

// Fonction pour afficher les magasins et leurs produits
void afficherMagasinsEtProduits(store *debut) {
    if (debut == NULL) {
        printf("\nAucun magasin trouv%c.\n", 130);
        return;
    }

    while (debut != NULL) {
        printf("\nMagasin : %s\n", debut->nom_magasin);
        printf("---------------------------\n");

        if (debut->produits == NULL) {
            printf("\n  Aucun produit disponible.\n");
        } else {
            product *tmp = debut->produits;
            while (tmp != NULL) {
                printf("  Produit : %s\n", tmp->nom_produit);
                printf("    Cat%cgorie : %s\n", 130, tmp->nom_categorie);
                printf("    Marque : %s\n", tmp->nom_marque);
                printf("    Rayon : %s\n", tmp->nom_rayon);
                printf("    Quantit%c : %d\n", 130, tmp->quantite);
                printf("    Prix : %.2f\n", tmp->prix);
                tmp = tmp->suivant;
            }
        }

        debut = debut->suivant;
    }
}
