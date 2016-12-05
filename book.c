#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"book.h"

booktype *creatdata(void){
    unsigned long x = 1;
    booktype *head = (booktype *)malloc(sizeof(booktype));
    head->next = NULL;
    while(x != 0){
        scanf("请输入书的序列号:%lu" &x); 
        booktype *s = (booktype *)malloc(sizeof(booktype));
        s->index = x;
        printf("请输入书的名字\n");
        fgets(s->name, MAXNAME, stdin);
        printf("请输入书的作者\n");
        fgets(s->author, MAXNAME, stdin);
        s->next = head->next;
        head->next = s;
    }
    return head;
}

int searchbook(booktype *head, char *bookname){
    booktype *h = head->next;
    int storge = 0;
    while(h->next == NULL){
        if(strcmp(h->name, bookname) == 0){
            storge++;

        }
    }
}
