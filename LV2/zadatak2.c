#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct lista{
    int x;
    struct lista *next;
}LISTA;

void gen_arr(int*, int, int, int);
void dodajElementNaKraj(LISTA**, LISTA**, int);
void ispisiListu(LISTA*);
int sekv_pret_arr(int*, int, int);
int sekv_pret_pp(LISTA*, int);
LISTA* oslobodiMemoriju(LISTA*);

int main(){

    LISTA *glavaListe = NULL;
    LISTA *zadnjiElementListe = NULL;

    printf("%d ", sizeof(int));
    printf("%d ", sizeof(LISTA));

    int N,DG,GG,index,x;
    srand((unsigned) time (NULL));
    time_t start, end;

    printf("Unesite velicinu vektora koji zelite koristiti: \n");
    scanf("%d", &N);

    int *V = (int*) malloc (N*sizeof(int));

    printf("Unesite velicinu za DG za generiranje polja: \n");
    scanf("%d", &DG);

    printf("Unesite velicinu za GG za generiranje polja: \n");
    scanf("%d", &GG);

    start = clock();
    gen_arr(V,N,DG,GG);
    end = clock();
    printf("\nVrijeme trajanja generiranja niza je %dms\n", end-start);

    start = clock();
    for(int i = 0; i<N; i++){ //pretvorba niza u povezani popis
        dodajElementNaKraj(&glavaListe,&zadnjiElementListe,V[i]);
    }
    end = clock();
    
    printf("\n");
    //ispisiListu(glavaListe);
    printf("\nVrijeme trajanja generiranja PP je %dms\n", end-start);

    printf("\nSekvencijalno pretrazi niz i PP za element: \n");
    scanf("%d", &x);
    start = clock();
    index = sekv_pret_arr(V,N,x);
    end = clock();
    printf("\nVrijeme trajanja pretrazivanja niza je %dms\n", end-start);

    if(index == -1)
        printf("Element ne postoji u nizu!\n");
    else
        printf("Element se nalazi na poziciji: %d\n", index);

    start = clock();
    index = sekv_pret_pp(glavaListe, x);
    end = clock();
    printf("\nVrijeme trajanja pretrazivanja PP je %dms\n", end-start);

    if(index == -1)
        printf("Element ne postoji u PP!\n");
    else
        printf("Element se nalazi na poziciji: %d\n", index);

    free(V);
    glavaListe = oslobodiMemoriju(glavaListe);
    return 0;
}

void gen_arr(int *V, int N, int DG, int GG){

    for(int i = 0; i<N; i++){
        V[i] = DG + (float) rand() / RAND_MAX * (GG-DG);
        //printf("%d ", V[i]);
    }
}

void dodajElementNaKraj(LISTA** glavaListe, LISTA** zadnjiElementListe, int x){

    LISTA* noviCvor = (LISTA*) malloc(sizeof(LISTA));
    noviCvor->x = x;
    noviCvor->next = NULL;

    if(*glavaListe == NULL){
        *glavaListe = noviCvor;
        *zadnjiElementListe = noviCvor;
    }
    else{
        (*zadnjiElementListe)->next = noviCvor;
        *zadnjiElementListe=(*zadnjiElementListe)->next;
    }

    return;
}

void ispisiListu(LISTA* glavaListe){
    
    LISTA* temp = glavaListe;

    while(temp != NULL){
        printf("%d->", temp->x);
        temp = temp->next;
    }
    printf("NULL\n");
}

int sekv_pret_arr(int* V, int N, int x){

    for(int i = 0; i<N ;i++){
        if(V[i] == x)
            return i;
    }
    return -1;
}

int sekv_pret_pp(LISTA* glavaListe, int x){

    LISTA* temp = glavaListe;
    int i=0;

    while(temp != NULL){
        if(temp->x == x)
            return i;

        i++;
        temp=temp->next;
    }
    return -1;
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