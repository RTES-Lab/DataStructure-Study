#include <stdio.h>
#include "SLL.h"
#include <string.h>

int main(){
    char input[100];    
    char* token;

    Node* List = NULL;
    Node* CategoryList = NULL;
    Node* NewNode = NULL;

    while(scanf("%s", input)){
        token = strtok(input,"/");
        if( strlen(token) == 2 && token[0] == '-' && token[1] == '1'){
            printf("종료\n");
            break;
        } 

        else if( strlen(token) == 1 && token[0] == '0' ){
            char* category = strtok(NULL,"/");
            char* node = strtok(NULL,"/");

            // category 이미 존재
            if(SLL_GetNodeAt(CategoryList, category))

            NewNode = SLL_CreateNode(token);
            break;
        }         

        else if( strlen(token) == 1 && token[0] == '1' ){
            token = strtok(NULL,"/");
            break;
        }         
    }
    return 0;
}