#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen_arr(float* , int, float, float);
int sekv_pret (float* , int, float);
void selectionSort(float* ,int);
void insertionSort(float*, int);
void bubbleSort(float*, int);
void quickSort(float*, int, int);
int bin_pret(float* , int, float);
void zamjena(float* , float*);
int partition(float*, int, int); //podjela niza za quick sort

int main(){

    int n,i;
    float DG,GG,x;
    srand (( unsigned) time ( NULL ));
    time_t t1, t2;
    
    printf("Unesite velicinu n za velicinu vektora: \n");

    scanf("%d", &n);
    float* V = (float *) malloc (n * sizeof(float));

    printf("Unesite velicinu za DG: \n");
    scanf("%f" , &DG);

    printf("Unesite velicinu za GG: \n");
    scanf("%f" , &GG);

    printf("\n");

    gen_arr(V,n,DG,GG);

    /*for(i = 0; i<n ; i++){
        printf("%.2f ", V[i]);
    }*/

    printf("Sekvencijalno pretrazi element: \n");
    scanf("%f" , &x);

    t1 = clock();
    i = sekv_pret(V,n,x);
    t2 = clock();
    printf("Vrijeme trajanja sekvencijalnog pretrazivanja je %dms\n",t2-t1 );


    if(i == -1)
        printf("Element ne postoji u vektoru!\n\n");
    else
        printf("Element se nalazi na poziciji: %d\n", i);

    t1=clock();
    insertionSort(V,n);
    t2=clock();
    printf("Vrijeme trajanja insertion sorta je %dms\n", t2-t1);

    /*for(i = 0; i<n ; i++){
        printf("%.2f ", V[i]);
    }*/

    printf("\nBinarno pretrazi element: \n");
    scanf("%f" , &x);

    t1=clock();
    i = bin_pret(V,n,x);
    t2=clock();
    printf("Vrijeme trajanja binarnog pretrazivanja je %dms\n", t2-t1);
    

    if(i == -1)
        printf("Element ne postoji u vektoru!\n");
    else
        printf("Element se nalazi na poziciji: %d\n", i);

    free(V);
    return 0;
}

void gen_arr(float* V, int n, float DG, float GG){

    for(int i = 0; i<n ; i++){
        V[i] = DG + (float) rand () / RAND_MAX * (GG - DG );
    }

}

int sekv_pret(float* V, int n, float x){

    for(int i = 0; i<n ; i++){
        if(V[i] == x){
            return i;
        }
    }
    return -1;
}

void zamjena (float* manji, float* veci){

   float temp = *manji;
    *manji = *veci;
    *veci = temp;
}

int partition(float* V, int dg, int gg){
    
    int pivot = V[gg]; //pivot mi je zadnji element u nizu
    int i = (dg-1); //stavljam pokazivac na veci element

    for(int j = dg; j<gg; j++){ //prodji kroz cijeli niz i usporedi s pivotom
        if(V[j] <= pivot){ //ako je element na j manji od pivota
            i++;
            zamjena(&V[i], &V[j]); //zamjeni ga s vecim elementom na koji pokazuje i
        }
    }

    zamjena(&V[i+1], &V[gg]); //zamjeni pivot s vecim elementom na i

    return(i+1); //vrati poziciju podjele
}

void quickSort(float* V, int dg, int gg){

    if(dg<gg){
        int pivot = partition(V,dg,gg); //pronadji takav pivot da su svi manji ljevo od njega, a svi veci desno od njega
        quickSort(V,dg,pivot-1); //rekurzivni poziv na ljevu polovicu
        quickSort(V,pivot+1,gg); //rekurzivni poziv na desnu polovicu
    }
}

void selectionSort(float* V, int n){

    int min = -1;

    for (int i = 0; i < n - 1; i++){

        min = i;

        for (int j = i + 1; j < n; j++){
            if (V[j] < V[min])
                min = j;
        }
        zamjena(&V[i], &V[min]);
    }
}

void insertionSort(float* V, int n){

    int i,j,key=0;
    for(i = 1; i<n; i++){

        key = V[i];
        j = i - 1;

        while(key < V[i] && j>=0){
            V[j+1] = V[j];
            --j;
        }
        V[j+1] = key;
    }
}

void bubbleSort(float* V, int n){

    for(int i = 0; i<n-1 ; i++){
        for(int j = 0; j<n-1;j++){
            if(V[j+1]<V[j])
                zamjena(&V[j+1], &V[j]);
        }
    }
}

int bin_pret(float* V, int n, float x){

    int dg = 0;
    int gg = n-1;
    int s = -1;

    while(dg <= gg) {
        s = (dg + gg) / 2;

        if(V[s] == x){
            return s;
        }
        else if(V[s] > x){
            gg = s - 1;
        }
        else{
            dg = s + 1;
        }
    }

    return -1;
}

