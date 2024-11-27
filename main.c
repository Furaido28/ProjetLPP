//  Nom     :   Flipo       Makhloufi
//  Prénom  :   Ethan       Olivia
//  Classe  :   2BIA1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------
// Déclaration des structures
// --------------------------

typedef struct product {
    char nom_produit[80], nom_categorie[80], nom_marque[80], nom_rayon[80];
    int quantite;
    float prix;
    struct product *suivant;
} product;

typedef struct store {
    char nom_magasin[100];
    product *produits; // Pointeur vers une liste de produits
    struct store *suivant;
} store;

// ---------------------------------
// Prototypes des fonctions
// ---------------------------------
store *creerMagasin(char *nom_magasin);
store *rechercherMagasin(store *head, char *nom_magasin);
void ajouterProduit(store *magasin, char *nom_produit, char *nom_categorie, char *nom_marque, char *nom_rayon, int quantite, float prix);
void afficherMagasinsEtProduits(store *head);

// -------------
// Fonction main
// -------------

int main() {
    store *listeMagasins = NULL;
    char nomMagasin[100], nomProduit[80], nomCategorie[80], nomMarque[80], nomRayon[80];
    int quantiteProduit, input;
    float prixProduit;

    do {
        printf("\nFaites un choix\n");
        printf("1. Ajouter un produit\n");
        printf("2. Afficher les magasins et produits\n");
        printf("   ------\n");
        printf("3. Fermer le programme\n");
        printf("> ");
        scanf("%d", &input);

        switch (input) {
            case 1: {
                printf("\nNom du magasin > ");
                scanf("%s", nomMagasin);

                // Rechercher ou créer le magasin
                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                if (magasin == NULL) {
                    magasin = creerMagasin(nomMagasin);
                    magasin->suivant = listeMagasins;
                    listeMagasins = magasin;
                }

                // Saisir les d�tails du produit
                printf("Nom du produit > ");
                scanf("%s", nomProduit);
                printf("Nom de la cat%cgorie > ", 130);
                scanf("%s", nomCategorie);
                printf("Nom de la marque > ");
                scanf("%s", nomMarque);
                printf("Nom du rayon > ");
                scanf("%s", nomRayon);
                printf("Quantit%c > ", 130);
                scanf("%d", &quantiteProduit);
                printf("Prix > ");
                scanf("%f", &prixProduit);

                // Ajouter le produit au magasin
                ajouterProduit(magasin, nomProduit, nomCategorie, nomMarque, nomRayon, quantiteProduit, prixProduit);
                break;
            }
            case 2:
                afficherMagasinsEtProduits(listeMagasins);
                break;

            case 3:
                printf("\nFermeture du programme...\n");
                break;

            default:
                printf("Erreur - Veuillez s%clectionner une option valide.\n", 130);
        }
    } while (input != 3);

    return 0;
}

// ----------------------------
// Fonctions pour les magasins
// ----------------------------

// Fonction pour cr�er un nouveau magasin
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

// -----------------------------
// Fonctions pour les produits
// -----------------------------

// Fonction pour ajouter un produit � un magasin
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

    // Ajouter le produit � la liste cha�n�e du magasin
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

// ----------------------------
// Affichage des donn�es
// ----------------------------

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

