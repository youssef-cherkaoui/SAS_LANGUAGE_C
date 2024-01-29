#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#define MAX_TACHE 100
#define MAX_DESCRIPTION 100

typedef struct {
int jour ;
int mois ;
int annee;
}dateEcheance;

typedef struct {
    char description[MAX_DESCRIPTION];
    dateEcheance dateEcheance;
    char priorite[100];
    int numeroTache;
} Tache;

bool verifierDateValide(dateEcheance date) { // fonction  de verification du date
    if (date.jour < 1 || date.jour > 30 || date.mois < 1 || date.mois > 12 || date.annee > 2024) {
        return false;
    }
    return true;
}

bool numeroTacheExiste(Tache tache[], int NB, int numeroTache) {
    for (int i = 0; i < NB; i++) {
        if (tache[i].numeroTache == numeroTache) {
            return true;
        }
    }
    return false;
}


bool AjouterTache(Tache tache[], int *NB){
    if (*NB<MAX_TACHE) { // succes de trouver espace pour une tache
        Tache Nouvtache;
        printf("numero Tache : ");
        scanf("%d",&Nouvtache.numeroTache);
           if (numeroTacheExiste(tache, *NB, Nouvtache.numeroTache)){ // condition si le numero du tache deja existe affiche une erreur
            printf("Erreur : Le numero de tache existe deja.\n");
            return false;
        }
        printf("Description:");
        scanf(" %[^\n]s",Nouvtache.description);
        printf("Date d'echange:\n");
        printf("Jour:");
        scanf(" %02d",&Nouvtache.dateEcheance.jour);
        printf("mois:");
        scanf(" %02d",&Nouvtache.dateEcheance.mois);
        printf("annee:");
        scanf(" %04d",&Nouvtache.dateEcheance.annee);
        if (!verifierDateValide(Nouvtache.dateEcheance)) {
            printf("Erreur : Date invalide.\n");
            return false;
        }
        printf("Priorite:");
        scanf(" %[^\n]s",Nouvtache.priorite);
        // ajouter la nouvelle tache
        tache[*NB]=Nouvtache;
        (*NB)++;
        printf("Tache ajoutee avec succes.\n");
    } else {
        printf("Erreur d'espace.\n"); // echec de trouver espace pour une tache
    }
}

bool ModifierTache(Tache tache[], int NB) {
    int numeroTache;
    int tacheTrouvee = 0;
    int i;

    printf("Numero de la tache a modifier : ");
    scanf("%d", &numeroTache);

    for (i = 0; i < NB; i++) {
        if (tache[i].numeroTache == numeroTache) {
            printf("Nouvelle description : ");
            scanf(" %[^\n]s", tache[i].description);
            printf("Nouvelle date d'echeance :\n");
            printf("Jour : ");
            scanf("%02d", &tache[i].dateEcheance.jour);
            printf("Mois : ");
            scanf(" %02d", &tache[i].dateEcheance.mois);
            printf("Annee : ");
            scanf(" %04d", &tache[i].dateEcheance.annee);
            if (!verifierDateValide(tache[i].dateEcheance)) {
                printf("Erreur : Date invalide.\n");
                return false;
            }
            printf("Nouvelle priorite : ");
            scanf(" %[^\n]s", tache[i].priorite);
            tacheTrouvee = 1;
            printf("Tache modifiee avec succes.\n");
            break;
        }
    }

    if (!tacheTrouvee) {
        printf("Tache non trouvee.\n");
    }

    return true;
}
void SupprimerTache( Tache tache[], int *NB) {
    if (*NB == 0) {
        printf("aucune tache trouvee.\n");
    } else {
        printf("Entrer le numero du tache (1-%d): ", *NB);
        int Number;
        scanf("%d", &Number);

        if (Number < 1 || Number > *NB) {
            printf("Invalid task number.\n");
        } else {
            // Shift tasks to fill the gap
            for (int i = Number - 1; i < *NB - 1; i++) {
                tache[i] = tache[i + 1];
            }

            (*NB)--;
            printf("tache est supprimer avec succes \n");
        }
    }
}

void AffichageTache(Tache tache[], int NB){
    int i;
    if(NB==0) {
        printf("Aucune tache a afficher.\n");
    } else {
        printf("Liste des taches:\n");
        // afficher les details de chaque tache
        for(i=0;i<NB;i++){
            printf("\n");
            printf("Tache : %d\n",i+1);
            printf("Numero Tache :%d\n",tache[i].numeroTache);
            printf("Description :%s\n",tache[i].description);
            printf("Date d'echange:%02d %02d %04d\n",tache[i].dateEcheance.jour,tache[i].dateEcheance.mois,tache[i].dateEcheance.annee);
            printf("Priorite :%s\n", tache[i].priorite);
        }
    }
}

void echange(Tache *a, Tache *b) {
    Tache temp = *a;
    *a = *b;
    *b = temp;
}

void tribulleCroissant(Tache taches[], int NB){
    int i, j;
    for (i = 0; i < NB - 1; i++) {
        for (j = 0; j < NB - i - 1; j++) {
            if (taches[j].dateEcheance.annee > taches[j + 1].dateEcheance.annee ||
                (taches[j].dateEcheance.annee == taches[j + 1].dateEcheance.annee && taches[j].dateEcheance.mois > taches[j + 1].dateEcheance.mois) ||
                (taches[j].dateEcheance.annee == taches[j + 1].dateEcheance.annee && taches[j].dateEcheance.mois == taches[j + 1].dateEcheance.mois &&
                 taches[j].dateEcheance.jour > taches[j + 1].dateEcheance.jour)) {
                echange(&taches[j], &taches[j + 1]);
            }
        }
    }
}

void tribulleDecroissant(Tache tache[], int NB){
    int i, j;
    for(i=0;i<NB-1;i++){
        for(j=0;j<NB-i-1;j++) {
            if (tache[j].dateEcheance.annee < tache[j + 1].dateEcheance.annee ||
                (tache[j].dateEcheance.annee == tache[j + 1].dateEcheance.annee && tache[j].dateEcheance.mois < tache[j + 1].dateEcheance.mois) ||
                (tache[j].dateEcheance.annee == tache[j + 1].dateEcheance.annee && tache[j].dateEcheance.mois == tache[j + 1].dateEcheance.mois &&
                 tache[j].dateEcheance.jour < tache[j + 1].dateEcheance.jour)) {
                echange(&tache[j],&tache[j + 1]);
            }
        }
    }
}


void TrierTache(Tache tache[], int *NB) {
    int i;
    for (i = 0; i < *NB; i++) {
        printf("Date:  %02d %02d %04d\n- Priorite: %s\n", tache[i].dateEcheance.jour, tache[i].dateEcheance.mois, tache[i].dateEcheance.annee, tache[i].priorite);
    }
    printf("\n");
    tribulleCroissant(tache, *NB); // appel de la fonction TriBulle croissant
    printf("Taches triees par date en ordre croissant :\n");
    for (i = 0; i < *NB; i++) {
        printf("Date:  %02d %02d %04d\n- Priorite: %s\n", tache[i].dateEcheance.jour, tache[i].dateEcheance.mois, tache[i].dateEcheance.annee, tache[i].priorite);
    }
    printf("\n");
    tribulleDecroissant(tache, *NB); // appel de la fonction triBulle decroissant
    printf("Taches triees par date en ordre decroissant :\n");
    for (i = 0; i < *NB; i++) {
        printf("Date:  %02d %02d %04d\n- Priorite: %s\n", tache[i].dateEcheance.jour, tache[i].dateEcheance.mois, tache[i].dateEcheance.annee, tache[i].priorite);
    }
}
int DateProche(dateEcheance date1,dateEcheance date2){
    if(date1.annee < date2.annee)
        return 1;
    else if(date1.annee > date2.annee)
        return 0;
    if(date1.mois < date2.mois)
        return 1;
    else if (date1.mois > date2.mois)
        return 0;
    if(date1.jour < date2.jour)
        return 1;
    else if(date1.jour > date2.jour)
        return 0;
    return 0;

}

void FiltrerUneTache(Tache tache[], int NB) {
    int i;
    char priorite[10];
    printf("Entrez la priorite (haute, moyenne ou basse) : ");
    scanf(" %9s", priorite);

    printf("Taches avec priorite %s:\n", priorite);
    int tacheTrouvee = 0;
    for (i = 0; i < NB; i++) {
        if (strcmp(tache[i].priorite, priorite) == 0) {
            printf("Tache %d\n", i + 1);
            printf("Description : %s\n", tache[i].description);
            printf("Priorite : %s\n", tache[i].priorite);
            printf("Date d'echeance : %02d %02d %04d\n", tache[i].dateEcheance.jour, tache[i].dateEcheance.mois, tache[i].dateEcheance.annee);
            printf("\n");
            tacheTrouvee = 1;
        }
    }
    if (!tacheTrouvee) {
        printf("Aucune tache avec la priorite %s n'a ete trouvee.\n", priorite);
    }
}


int main() {
    Tache tache[MAX_TACHE];
    int NB = 0;
    int choix;

    do {
        printf("---------MENU---------\n");
        printf("Choix :\n");
        printf("1-Ajouter une tache\n");
        printf("2-modifier les taches\n");
        printf("3-Afficher les taches\n");
        printf("4-Supprimer les taches\n");
        printf("5-Trier les taches\n");
        printf("6-Filtrer une tache par priorite\n");
        printf("7-Quitter\n");
        scanf("%d",&choix);

        switch(choix){
            case 1:
                printf("Ajouter une tache :\n");
                AjouterTache(tache, &NB);
                break;
            case 2:
                printf("modifier les taches :\n");
                ModifierTache(tache,NB);
                break;
            case 3:
                printf("afficher les taches :\n");
                AffichageTache(tache, NB);
                break;
            case 4:
                printf("Supprimer les taches :\n");
                SupprimerTache(tache,&NB);
                break;
            case 5:
                printf("Trier les taches :\n");
                TrierTache(tache,&NB);
                break;
            case 6 :
                printf("Filtrer une tache :\n");
                FiltrerUneTache(tache,NB);
                break;
            case 7:
                printf("Quitter :\n");
                break;
            default:
                printf("ERREUR. Choix invalide.\n");
                break;
        }
    } while(choix!=7);

    return 0;
}

