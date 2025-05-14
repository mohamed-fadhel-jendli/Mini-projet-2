#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Materiel
{
    char nom[50];
    int quantite;
    float prix_unitaire;
    struct Materiel *suivant;
} Materiel;

Materiel *tete=NULL;

void ajouterMateriel(char *nom,int quantite,float prix_unitaire)
{
    Materiel *nouveau_materiel=(Materiel *)malloc(sizeof(Materiel));
    strcpy(nouveau_materiel->nom,nom);
    nouveau_materiel->quantite=quantite;
    nouveau_materiel->prix_unitaire=prix_unitaire;
    nouveau_materiel->suivant=tete;
    tete=nouveau_materiel;
    printf("Materiel ajoute avec succes.\n");
}

void supprimerMateriel(char *nom)
{
    Materiel *temp=tete;
    Materiel *precedent=NULL;
    while((temp!=NULL)&&(strcmp(temp->nom, nom) != 0))
    {
        precedent=temp;
        temp=temp->suivant;
    }
    if(temp==NULL)
    {
        printf("Materiel non trouve.\n");
        return;
    }
    if(precedent==NULL)
    {
        tete=temp->suivant;
    }
    else
    {
        precedent->suivant=temp->suivant;
    }
    free(temp);
    printf("Materiel supprime avec succes.\n");
}

void afficherMateriels()
{
    Materiel *temp=tete;
    if(temp==NULL)
    {
        printf("Aucun materiel trouve.\n");
        return;
    }
    printf("Materiels:\n");
    while(temp!=NULL)
    {
        printf("Nom: %s, Quantite: %d, Prix Unitaire: %.2f\n",temp->nom,temp->quantite,temp->prix_unitaire);
        temp=temp->suivant;
    }
}

void mettreAJourMateriel(char *nom,int quantite,float prix_unitaire)
{
    Materiel *temp=tete;
    while(temp!=NULL)
    {
        if(strcmp(temp->nom, nom)==0)
        {
            temp->quantite=quantite;
            temp->prix_unitaire=prix_unitaire;
            printf("Materiel mis a jour avec succes.\n");
            return;
        }
        temp=temp->suivant;
    }
    printf("Materiel non trouve.\n");
}

void enregistrerMaterielsCSV(char *nom_fichier)
{
    FILE *fichier=fopen(nom_fichier,"w");
    if(fichier==NULL)
    {
        printf("Erreur : ouverture du fichier %s\n",nom_fichier);
        return;
    }
    Materiel *temp=tete;
    while(temp!=NULL)
    {
        fprintf(fichier,"%s,%d,%.2f\n",temp->nom,temp->quantite,temp->prix_unitaire);
        temp=temp->suivant;
    }
    fclose(fichier);
    printf("Materiels sauvegardes dans %s\n",nom_fichier);
}

void afficherOperationsJournalieres()
{
    printf("Operations journalieres:\n");
    Materiel *temp=tete;
    while(temp!=NULL)
    {
        printf("Vente: Nom: %s, Quantite Vendue: %d, Revenu: %.2f\n",temp->nom,temp->quantite,(temp->quantite * temp->prix_unitaire));
        temp=temp->suivant;
    }
}

float calculerRevenuJournalier()
{
    float revenu_total=0.0;
    Materiel *temp=tete;
    while(temp!=NULL)
    {
        revenu_total+=(temp->quantite * temp->prix_unitaire);
        temp=temp->suivant;
    }
    return revenu_total;
}

void enregistrerRevenuTotalCSV(char *nom_fichier)
{
    FILE *fichier=fopen(nom_fichier,"w");
    if(fichier==NULL)
    {
        printf("Erreur : ouverture du fichier %s\n",nom_fichier);
        return;
    }
    float revenu_total=calculerRevenuJournalier();
    fprintf(fichier,"Revenu Total,%.2f\n",revenu_total);
    fclose(fichier);
    printf("Revenu total sauvegarde dans %s\n",nom_fichier);
}

int main()
{
    int choix=0;
    char nom[50];
    int quantite;
    float prix_unitaire;
    while(choix!=7)
    {
        printf("Menu:\n");
        printf("1. Ajouter Materiel\n");
        printf("2. Supprimer Materiel\n");
        printf("3. Afficher Materiels\n");
        printf("4. Mettre a jour Materiel\n");
        printf("5. Enregistrer Materiels en CSV\n");
        printf("6. Afficher Operations Journalieres\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                printf("Entrez le nom: ");
                scanf("%s",nom);
                printf("Entrez la quantite: ");
                scanf("%d",&quantite);
                printf("Entrez le prix unitaire: ");
                scanf("%f",&prix_unitaire);
                ajouterMateriel(nom,quantite,prix_unitaire);
                break;
            case 2:
                printf("Entrez le nom du materiel a supprimer: ");
                scanf("%s",nom);
                supprimerMateriel(nom);
                break;
            case 3:
                afficherMateriels();
                break;
            case 4:
                printf("Entrez le nom du materiel a mettre a jour: ");
                scanf("%s",nom);
                printf("Entrez la nouvelle quantite: ");
                scanf("%d",&quantite);
                printf("Entrez le nouveau prix unitaire: ");
                scanf("%f",&prix_unitaire);
                mettreAJourMateriel(nom,quantite,prix_unitaire);
                break;
            case 5:
                enregistrerMaterielsCSV("materiels.csv");
                break;
            case 6:
                afficherOperationsJournalieres();
                break;
            case 7:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Choix invalide, Veuillez reessayer.\n");
        }
    }
    return 0;
}
