#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
    int x;
    struct node_ *left;
    struct node_ *right;
}Node;

void preorderTraversal(Node* root) {

    if (root){
        printf("%c -> ", root->x);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    } 
}

Node* RecConvertToDyn(Node* root, int indexRetka, int B[][3]){

    root = (Node*)malloc(sizeof(Node));
    root->x = B[indexRetka][0];
    int skokNaLeft= B[indexRetka][1];
    int skokNaRight = B[indexRetka][2];

    if(skokNaLeft != 0){
        root->left = RecConvertToDyn(root, skokNaLeft, B);
    }else root->left = NULL;
    
    if(skokNaRight != 0){
        root->right = RecConvertToDyn(root, skokNaRight, B);
    }else root->right = NULL;

    return root;

}

Node* ConvertToDyn(int B[][3]){

    Node* root = NULL;
    root = RecConvertToDyn(root,0,B);
    return root;
}

Node *LoadFromFileDyn(const char *filename) {

    Node* root = NULL;
    FILE *file;
    file = fopen (filename, "r");

    char line[102] = {0};
    int B[16][3];
    int c;
    int i = 0;

    if (file == NULL){
        printf("Datoteka ne postoji!\n");
        return 0;
    }
    else{
            do{
                fscanf(file, "%c %d %d", &B[i][0], &B[i][1], &B[i][2]);
                printf("%c %d %d", B[i][0], B[i][1], B[i][2]);
                printf("\n");
                i +=1;
            }while((c = fgetc(file)) != EOF); 

        }

    fclose(file);
    root = ConvertToDyn(B);


    return root;
}

int main(){

    int B[100][3] = {
'R', 1, 0,
'a', 2, 3,
'e', 4, 5,
'b', 6, 7,
'l', 0, 8,
'f', 0, 0,
'g', 0, 9,
'c', 0, 10,
'm', 0, 0,
'h', 0, 11,
'd', 12, 0,
'i', 0, 0,
'j', 13, 14,
'n', 0, 15,
'k', 0, 0,
'o', 0, 0
};

    Node *root = NULL;
    const char *filename = "BynTreeMatrix.txt";
    root = LoadFromFileDyn(filename);
    preorderTraversal(root);

    return 0;
}