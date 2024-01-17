#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SizeOfLine 100
#define SizeOfOrder 3 

typedef char Elementype;

typedef struct node{
    Elementype* Name;
    struct node* NextContent;
}Node;

typedef struct pack{
    Node* Content;
    struct pack* NextCategory;
}Pack;

typedef union pack2{
    Node* Content;
    Pack* Category;
}Pack2;

Pack2* Create(int Select,Elementype* NewName);
void InsertInOrder(Elementype arr[]);


#endif
