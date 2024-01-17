#include "classification.h"

Pack2* Create(int Select,Elementype* NewName){
    Pack *pack = (Pack*)malloc(sizeof(Pack));
    Pack2 * pack2 = (Pack2*)malloc(sizeof(Pack2));

    if(Select == 0 || Select == 1){
        if(Select == 0){
            pack->NextCategory = (Pack*)malloc(sizeof(Pack));
            pack->NextCategory = NULL;
            printf("카테고리 생성 중..\n");
        }
        pack->Content = (Node*)malloc(sizeof(Node));
        pack->Content->Name = (Elementype*)malloc(strlen(NewName)+1);
        strcpy(pack->Content->Name,NewName);
        pack->Content->NextContent = (Node*)malloc(sizeof(Node));
        pack->Content->NextContent = NULL;
        printf("카테고리/항목 생성 완료..\n"); 
    }

    if(Select == 0){
        pack2->Content = pack->Content;
    }
    // else if(Select == 1){
    //     pack2->Category = pack;
    // }

    return pack2;
}
