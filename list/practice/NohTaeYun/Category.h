#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Elementtype char

typedef struct node{
    Elementtype* Name;
    struct node* NextContent;
}Node;

typedef struct tag{
    Elementtype* Name;
    Node* NextContent;
    struct tag* NextCategory;
}Tag;

Node* CreateContent(Elementtype* Newname);
Tag* CreateCategory(Elementtype* Newname);
void InsertContent(Elementtype* Categoryname, Tag* Category, Node* NewContent);
void InsertCategory(Tag* Category, Tag* NewCategory);
void PrintAll(Tag *Category);
