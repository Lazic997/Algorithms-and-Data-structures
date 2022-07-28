#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct cvor{

    char x;
    struct cvor *lijevi;
    struct cvor *desni;

}Cvor;

int nadjiP(Cvor*, char, Cvor**);
Cvor* dodajP(Cvor*, char);
void preOrder(Cvor*);
void inOrder(Cvor*);
void postOrder(Cvor*);

int main(){

    Cvor *korijen = NULL;
    char X;
    
    printf("Unesite elemente PBS, za izlaz iz unosa unesite vrijednost q: \n");
    do{

        scanf(" %c", &X);
        if(X=='q'){
            printf("Prekida se unos elemenata!\n");
            break;
        }
        if(korijen == NULL) korijen = dodajP(korijen, X);
        else dodajP(korijen, X);
            

    }while(X!='q');

    printf("\nPreOrder: \n");
    preOrder(korijen);
    printf("\nInOrder: \n");
    inOrder(korijen);
    printf("\nPostOrder: \n");
    postOrder(korijen);
    
    return 0;
}

int nadjiP(Cvor *cvor, char X, Cvor **nadredjeni){

    if(cvor == NULL) return 0;
    if(cvor->x == X) return 1;
    *nadredjeni = cvor;
    if(cvor->x > X) return nadjiP(cvor->lijevi,X,nadredjeni);
    else return nadjiP(cvor->desni,X,nadredjeni);
}

Cvor* dodajP(Cvor *cvor, char X){

    Cvor* nadredjeni = NULL , *noviCvor;

    if(nadjiP(cvor,X,&nadredjeni)){
        printf("\nElement vec postoji!\n");
        return cvor;
    }
    else{
        noviCvor = (Cvor*)malloc(sizeof(Cvor));
        noviCvor->x = X;
        noviCvor->lijevi = noviCvor->desni = NULL;
        if(nadredjeni == NULL) return noviCvor;
        else
            if(X<nadredjeni->x) nadredjeni->lijevi = noviCvor;
            else nadredjeni->desni = noviCvor;
    }
}

void preOrder(Cvor* cvor){
    if(cvor==NULL)  return;
    printf("%c ", cvor->x);
    if(cvor->lijevi!=NULL) preOrder(cvor->lijevi);
    if(cvor->desni!=NULL) preOrder(cvor->desni);
}

void inOrder(Cvor* cvor){
    if(cvor==NULL) return;
    if(cvor->lijevi!=NULL) inOrder(cvor->lijevi);
    printf("%c ", cvor->x);
    if(cvor->desni!=NULL) inOrder(cvor->desni);
}

void postOrder(Cvor* cvor){
    if(cvor==NULL)return;
    if(cvor->lijevi!=NULL)postOrder(cvor->lijevi);
    if(cvor->desni!=NULL) postOrder(cvor->desni);
    printf("%c ", cvor->x);
}