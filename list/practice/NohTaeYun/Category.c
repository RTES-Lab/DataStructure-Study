#include "Category.h"

Node* CreateContent(Elementtype* Newname){
    Node* Content = (Node*)malloc(sizeof(Node));
    Content->Name = (Elementtype*)malloc(strlen(Newname)+1);
    strcpy(Content->Name,Newname);
    Content->NextContent = (Node*)malloc(sizeof(Node));
    Content->NextContent = NULL;
    return Content;
}

Tag* CreateCategory(Elementtype* Newname){
    Tag* Category = (Tag*)malloc(sizeof(Tag));
    Category->Name = (Elementtype*)malloc(strlen(Newname)+1);
    strcpy(Category->Name,Newname);
    Category->NextContent = (Node*)malloc(sizeof(Node));
    Category->NextContent = NULL;
    Category->NextCategory = (Tag*)malloc(sizeof(Tag));
    Category->NextCategory = NULL;
    return Category;
}

void InsertContent(Elementtype* Categoryname,Tag* Category, Node* NewContent){
    Tag* Current = Category;
    while(Current->NextCategory != NULL){
        if(strcmp(Categoryname,Current->Name) < 0)
            Current = Current->NextCategory;
        else if(strcmp(Current->Name,Current->Name) == 0){
            break;
        }
        else
            break;
    }
    if(Category->NextContent == NULL){
        Category->NextContent = (Node*)malloc(sizeof(Node));
        Category->NextContent = NewContent;
    }
    else{
        Node* Current = Category->NextContent;
        while(Current->NextContent != NULL){
            if(strcmp(Current->Name,Current->NextContent->Name) < 0)
                Current = Current->NextContent;
            else if(strcmp(Current->Name,Current->NextContent->Name) == 0){
                printf("이미 존재하는 카테고리입니다.");
                puts("");
                exit(0);
            }
            else
                break;
        }
        Current->NextContent = NewContent;
    }
}

void InsertCategory(Tag* Category, Tag* NewCategory){
    if(Category->NextCategory == NULL){
        Category->NextCategory = (Tag*)malloc(sizeof(Tag));
        Category->NextCategory = NewCategory;
    }
    else{
        Tag* Current = Category->NextCategory;
        while(Current->NextCategory != NULL){
            if(strcmp(Current->Name,Current->NextCategory->Name) < 0)
                Current = Current->NextCategory;
            else if(strcmp(Current->Name,Current->NextCategory->Name) == 0){
                printf("이미 존재하는 항목입니다.");
                puts("");
                break;
            }
            else
                break;
        }
        Current->NextCategory = NewCategory;
    }
}

void PrintAll(Tag *Category){
    Tag* CurCategory = Category;
    while(CurCategory != NULL){
        printf("%s: ",CurCategory->Name);
        Node* CurContent = CurCategory->NextContent;
        while(CurContent != NULL){
            printf("%s ",CurContent->Name);
            CurContent = CurContent->NextContent;
            if(CurContent != NULL){
                printf("-> ");
            }
            else{
                puts("");
            }
        }
        CurCategory = CurCategory->NextCategory;
    }
}
