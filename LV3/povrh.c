#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 1000

typedef struct stack_ {
    int SP;
    int data[MAXSIZE];
}Stack;

typedef struct node_ { //Stack prikazan povezanom listom
    int x;
    struct node_ *next;
}Node;
Node *firstNode = NULL; //globalno deklariran pocetak liste

void Clear(Stack *s) {
    s->SP = 0;
}

void Push(Stack *s, int x) {
    if (s->SP==MAXSIZE) {
        puts("Stack overflow... Aborting...");
        exit(1);
    }
    s->data[s->SP] = x;
    s->SP++;
}

int Pop(Stack *s) {
    if (s->SP==0) {
        puts("Illegal pop... Aborting...");
        exit(2);
    }
    s->SP--;
    return s->data[s->SP];
}

int Is_empty(Stack s) {
    if (s.SP==0) return 1;
    return 0;
}

void PushN(int x){
    Node *newNode = (Node*) malloc (sizeof(Node));
    if(newNode == NULL){
        printf("Stack overflow. Aborting...");
        exit(1);
    }
    newNode->x = x;
    newNode->next = firstNode;
    firstNode = newNode;
}

int PopN(){
    if(firstNode == NULL){
        printf("Illegal POP. Aborting...");
        exit(2);
    }

    Node *temp = (Node*) malloc (sizeof(Node));

    int x = firstNode->x;
    temp = firstNode;
    firstNode = firstNode->next;
    free(temp);

    return x;
}

int Is_emptyN(){
    if(firstNode==NULL)
        return 1;
    return 0;
}

void ClearN(){
    while(firstNode != NULL)
        PopN();
}


long long povrhRec(int, int);
long long povrhStack(int, int);
long long povrhStackN(int, int);

int main(){

    int n,m;
    long long rezultat;
    time_t start, end;
    
    printf("Unesite velicinu n: \n");
    scanf("%d", &n);
    m = n/2;
    printf("m=n/2: %d", m);
    
    
    start = clock();
    rezultat = povrhRec(n,m);
    end = clock();
    printf("\nVrijeme trajanja Rec: %dms\n", end-start);
    printf("\nRezultatRec: %ld", rezultat);

    start = clock();
    rezultat = povrhStack(n,m);
    end = clock();
    printf("\nVrijeme trajanja Stack: %dms\n", end-start);
    printf("\nRezultatStack: %ld", rezultat);

    start = clock();
    rezultat = povrhStackN(n,m);
    end = clock();
    printf("\nVrijeme trajanja StackN: %dms\n", end-start);
    printf("\nRezultatStackN: %ld", rezultat);

   return 0; 
}

long long povrhRec (int n, int m){
    if(n == m || m == 0)
        return 1;
    return povrhRec(n-1,m-1) + povrhRec(n-1,m);
}

long long povrhStack(int n, int m){

    Stack stack;
    Clear(&stack);

    Push(&stack, m);
    Push(&stack, n);
    long long povrh = 0;

    do{
        n = Pop(&stack);
        m = Pop(&stack);

        if(m == n || m==0){
            povrh = povrh + 1;
        }
        else{
            Push(&stack, m-1);
            Push(&stack, n-1);
            Push(&stack, m);
            Push(&stack, n-1);
        }

    }while(!Is_empty(stack));

    return povrh;
}

long long povrhStackN(int n, int m){

    ClearN(); //ocisti stack kao listu

    PushN(m);
    PushN(n);
    long long povrh = 0;

    do{
        n = PopN();
        m = PopN();

        if(m == n || m==0){
            povrh = povrh + 1;
        }
        else{
            PushN(m-1);
            PushN(n-1);
            PushN(m);
            PushN(n-1);
        }

    }while(!Is_emptyN());

    return povrh;
}