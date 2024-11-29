#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Structure pour repr�senter une cat�gorie
typedef struct {
    int id;
    char nom[50];
} Categorie;

// Structure pour repr�senter un produit
typedef struct {
    int id;
    char nom[50];
    float prix;
    int quantite;
    Categorie categorie;
} Produit;

// Fonction pour v�rifier si une cat�gorie existe d�j� par son ID
int categorieExiste(Categorie categories[], int nbCategories, int id) {
    for (int i = 0; i < nbCategories; i++) {
        if (categories[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour v�rifier si un produit existe d�j� par son ID
int produitExiste(Produit produits[], int nbProduits, int id) {
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour ajouter une cat�gorie
void ajouterCategorie(Categorie categories[], int *nbCategories, int id, char *nom) {
    if (categorieExiste(categories, *nbCategories, id)) {
        printf("Erreur : Une cat�gorie avec cet ID existe d�j�.\n");
        return;
    }
    categories[*nbCategories].id = id;
    strcpy(categories[*nbCategories].nom, nom);
    (*nbCategories)++;
    printf("Cat�gorie ajout�e avec succ�s.\n");
}

// Fonction pour ajouter un produit
void ajouterProduit(Produit produits[], int *nbProduits, int id, char *nom, float prix, int quantite, Categorie categorie) {
    if (produitExiste(produits, *nbProduits, id)) {
        printf("Erreur : Un produit avec cet ID existe d�j�.\n");
        return;
    }
    produits[*nbProduits].id = id;
    strcpy(produits[*nbProduits].nom, nom);
    produits[*nbProduits].prix = prix;
    produits[*nbProduits].quantite = quantite;
    produits[*nbProduits].categorie = categorie;
    (*nbProduits)++;
    printf("Produit ajout� avec succ�s.\n");
}

// Fonction pour afficher toutes les cat�gories
void afficherCategories(Categorie categories[], int nbCategories) {
    printf("\nListe des cat�gories :\n");
    for (int i = 0; i < nbCategories; i++) {
        printf("ID: %d | Nom: %s\n", categories[i].id, categories[i].nom);
    }
    if (nbCategories == 0) {
        printf("Aucune cat�gorie trouv�e.\n");
    }
}

// Fonction pour afficher tous les produits
void afficherProduits(Produit produits[], int nbProduits) {
    printf("\nListe des produits :\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("ID: %d | Nom: %s | Prix: %.2f | Quantit�: %d | Cat�gorie: %s\n",
               produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
    }
    if (nbProduits == 0) {
        printf("Aucun produit trouv�.\n");
    }
}

// Fonction pour supprimer une cat�gorie
void supprimerCategorie(Categorie categories[], int *nbCategories, int id) {
    int trouve = 0;
    for (int i = 0; i < *nbCategories; i++) {
        if (categories[i].id == id) {
            trouve = 1;
            for (int j = i; j < *nbCategories - 1; j++) {
                categories[j] = categories[j + 1];
            }
            (*nbCategories)--;
            printf("Cat�gorie supprim�e avec succ�s.\n");
            break;
        }
    }
    if (!trouve) {
        printf("Erreur : Cat�gorie introuvable.\n");
    }
}

// Fonction pour supprimer un produit
void supprimerProduit(Produit produits[], int *nbProduits, int id) {
    int trouve = 0;
    for (int i = 0; i < *nbProduits; i++) {
        if (produits[i].id == id) {
            trouve = 1;
            for (int j = i; j < *nbProduits - 1; j++) {
                produits[j] = produits[j + 1];
            }
            (*nbProduits)--;
            printf("Produit supprim� avec succ�s.\n");
            break;
        }
    }
    if (!trouve) {
        printf("Erreur : Produit introuvable.\n");
    }
}

// Fonction pour modifier une cat�gorie
void modifierCategorie(Categorie categories[], int nbCategories, int id) {
    for (int i = 0; i < nbCategories; i++) {
        if (categories[i].id == id) {
            printf("Nouveau nom de la cat�gorie : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(categories[i].nom, nom);
            printf("Cat�gorie modifi�e avec succ�s.\n");
            return;
        }
    }
    printf("Erreur : Cat�gorie introuvable.\n");
}

// Fonction pour modifier un produit
void modifierProduit(Produit produits[], int nbProduits, Categorie categories[], int nbCategories, int id) {
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == id) {
            printf("Nouveau nom du produit : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(produits[i].nom, nom);

            printf("Nouveau prix : ");
            scanf("%f", &produits[i].prix);

            printf("Nouvelle quantit� : ");
            scanf("%d", &produits[i].quantite);

            afficherCategories(categories, nbCategories);
            printf("ID de la nouvelle cat�gorie : ");
            int idCategorie;
            scanf("%d", &idCategorie);

            for (int j = 0; j < nbCategories; j++) {
                if (categories[j].id == idCategorie) {
                    produits[i].categorie = categories[j];
                    printf("Produit modifi� avec succ�s.\n");
                    return;
                }
            }

            printf("Erreur : Cat�gorie introuvable.\n");
            return;
        }
    }
    printf("Erreur : Produit introuvable.\n");
}

// Fonction pour afficher le menu principal
void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une cat�gorie\n");
    printf("2. Ajouter un produit\n");
    printf("3. Afficher les cat�gories\n");
    printf("4. Afficher les produits\n");
    printf("5. Supprimer une cat�gorie\n");
    printf("6. Supprimer un produit\n");
    printf("7. Modifier une cat�gorie\n");
    printf("8. Modifier un produit\n");
    printf("9. Quitter\n");
    printf("Choix : ");
}

// Fonction principale
int main() {
    setlocale(LC_ALL, ""); // Configurer l'encodage pour UTF-8

    Produit produits[100];
    Categorie categories[50];
    int nbProduits = 0, nbCategories = 0;

    while (1) {
        afficherMenu();
        int choix;
        scanf("%d", &choix);

        if (choix == 9) break;

        int id;
        char nom[50];
        float prix;
        int quantite, idCategorie;
        switch (choix) {
            case 1:
                printf("ID de la cat�gorie : ");
                scanf("%d", &id);
                printf("Nom de la cat�gorie : ");
                scanf(" %49[^\n]", nom);
                ajouterCategorie(categories, &nbCategories, id, nom);
                break;
            case 2:
                printf("ID du produit : ");
                scanf("%d", &id);
                printf("Nom du produit : ");
                scanf(" %49[^\n]", nom);
                printf("Prix : ");
                scanf("%f", &prix);
                printf("Quantit� : ");
                scanf("%d", &quantite);
                afficherCategories(categories, nbCategories);
                printf("ID de la cat�gorie : ");
                scanf("%d", &idCategorie);

                Categorie cat;
                for (int i = 0; i < nbCategories; i++) {
                    if (categories[i].id == idCategorie) {
                        cat = categories[i];
                        break;
                    }
                }
                ajouterProduit(produits, &nbProduits, id, nom, prix, quantite, cat);
                break;
            case 3:
                afficherCategories(categories, nbCategories);
                break;
            case 4:
                afficherProduits(produits, nbProduits);
                break;
            case 5:
                printf("ID de la cat�gorie � supprimer : ");
                scanf("%d", &id);
                supprimerCategorie(categories, &nbCategories, id);
                break;
            case 6:
                printf("ID du produit � supprimer : ");
                scanf("%d", &id);
                supprimerProduit(produits, &nbProduits, id);
                break;
            case 7:
                printf("ID de la cat�gorie � modifier : ");
                scanf("%d", &id);
                modifierCategorie(categories, nbCategories, id);
                break;
            case 8:
                printf("ID du produit � modifier : ");
                scanf("%d", &id);
                modifierProduit(produits, nbProduits, categories, nbCategories, id);
                break;
            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
