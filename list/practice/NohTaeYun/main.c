#include "Category.h"

int main(void){
    int Select = 0;
    char Line[70] = {};
    char * ptr;
    Tag * FirstCategory = NULL;
    Elementtype CategoryName[31] = {};
    Elementtype ContentName[31] = {};

    while(Select != -1){
        fgets(Line,70,stdin);
        ptr = strtok(Line,"/");
        Select = atoi(ptr);
        if(ptr != NULL){
            ptr = strtok(NULL,"/\n");
            strcpy(CategoryName,ptr);
        }
        if(ptr != NULL){
            ptr = strtok(NULL,"/\n");
            strcpy(ContentName,ptr);
        }
        if(Select == 0){
            if(FirstCategory == NULL){
                FirstCategory = CreateCategory(CategoryName);
            }
            else{
                Tag* NewCategory = (Tag*)malloc(sizeof(Tag));
                NewCategory = CreateCategory(CategoryName);
                InsertCategory(FirstCategory,NewCategory);
            }
        }
        else if(Select == 1){
            Node* NewContent = (Node*)malloc(sizeof(Node));
            strcpy(NewContent->Name,ContentName);
            InsertContent(CategoryName, FirstCategory, NewContent);
        }
        else if(Select == 2)
            PrintAll(FirstCategory);
        else if(Select == -1)
            exit(0);
        else{
            printf("잘못된 명령어입니다.");
            puts("");
        }
    }    
    return 0;
}
