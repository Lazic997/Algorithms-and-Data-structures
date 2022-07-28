#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int vrijednost;
    struct lista *next;
}LISTA;

void dodajElementNaKraj(LISTA**, int);
void ispisiListu(LISTA*);
void bubbleSortListe(LISTA*);
void swap(LISTA*, LISTA*);
void obrisiDuplikate(LISTA*);
LISTA* oslobodiMemoriju(LISTA*);

//U programu sam zapoceo sa dodavanjem bubbleSorta ali sam kasnije shvatio kako nije potreban

int main(){

    LISTA *glavaListe = NULL;
    int n;

    printf("Unesite elemente liste, za izlaz iz unosa unesite vrijednost -1: \n");
    do{

        scanf("%d", &n);
        if(n==-1){
            printf("Prekida se unos elemenata!\n");
            break;
        }
        dodajElementNaKraj(&glavaListe,n);
            

    }while(n!=-1);

    //bubbleSortListe(glavaListe);
    printf("\nPrvobitan unos: \n");
    ispisiListu(glavaListe);
    printf("\n");

    obrisiDuplikate(glavaListe);

    printf("\nLista nakon brisanja duplikata: \n");
    ispisiListu(glavaListe);
    printf("\n");

    glavaListe = oslobodiMemoriju(glavaListe);

    return 0;

}

void dodajElementNaKraj(LISTA** glavaListe, int number){

    LISTA* noviCvor = malloc(sizeof(LISTA));
    noviCvor->vrijednost = number;
    noviCvor->next = NULL;

    if(*glavaListe == NULL)
        *glavaListe = noviCvor;
    else{
        LISTA* zadnjiCvor = *glavaListe;

        while(zadnjiCvor->next != NULL){
            zadnjiCvor = zadnjiCvor->next;
        }

        zadnjiCvor->next = noviCvor;
    }
}

void ispisiListu(LISTA* glavaListe){
    LISTA* temp = glavaListe;

    while(temp != NULL){
        printf("%d->", temp->vrijednost);
        temp = temp->next;
    }
    printf("NULL\n");
}

LISTA* oslobodiMemoriju(LISTA* glavaListe){

    LISTA* obrisiCvor = NULL;

    while(glavaListe){
        obrisiCvor = glavaListe;
        glavaListe = glavaListe->next;
        free(obrisiCvor);
    }
    printf("Memorija oslobodjena!\n");
    return NULL;
}

void swap(LISTA* a, LISTA* b){
    int temp = a->vrijednost;
    a->vrijednost = b->vrijednost;
    b->vrijednost = temp;
}

void bubbleSortListe(LISTA* glavaListe){
    
    int swapped, i;
    LISTA* pv1; //pomocni pokazivac na cvor
    LISTA* lastPv = NULL; //pokazivac na zadnji cvor

    if(glavaListe == NULL){
        return;
    }

    do{

        swapped = 0;
        pv1 = glavaListe;

        while(pv1->next != lastPv){
            if(pv1->vrijednost > pv1->next->vrijednost){
                swap(pv1, pv1->next);
                swapped=1;
            }
            pv1 = pv1->next;
        }
        lastPv = pv1;

    }while(swapped);
}

void obrisiDuplikate(LISTA* glavaListe){

    LISTA* ptr1, *ptr2, *duplikat;
    ptr1 = glavaListe;

    while(ptr1 != NULL && ptr1->next != NULL){
        ptr2 = ptr1;

        while(ptr2->next != NULL){
            if(ptr1->vrijednost == ptr2->next->vrijednost){
                duplikat = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(duplikat);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;

    }
}