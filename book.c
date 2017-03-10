#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"book.h"

booktype *creatdata(void)
{
    char ch;
    unsigned long x;
    booktype *head = (booktype *)malloc(sizeof(booktype));
    booktype *rear = head;
    rear->next = NULL;
    printf("请输入书的序列号(序号为0时结束):");
    scanf("%lu", &x);
    while(x != 0){
        booktype *s = (booktype *)malloc(sizeof(booktype));
        s->index = x;
        while((ch=getchar())!='\n' && ch!=EOF);
        printf("请输入书的名字\n");
        fgets(s->name, MAXNAME, stdin);
        s->flag = 1;
        printf("请输入书的作者\n");
        fgets(s->author, MAXNAME, stdin);
        printf("请输入此书的描述性文字\n");
        fgets(s->description, MAXLEN, stdin);
        s->prior = rear;
        s->next = rear->next;
        rear->next = s;
        rear = s;
        printf("请输入书的序列号:");
        scanf("%lu", &x);
    }
    return head;
}


booktype *addbook(booktype *head, unsigned long x, char *name, char *author, char *description)
{
    booktype *s = (booktype *)malloc(sizeof(booktype));
    s->index = x;
    s->flag = 1;
    strcpy(name, s->name);
    srtcpy(author, s->author);
    srtcpy(description, s->description);
    s->next = head->next;
    head->next->prior = s;
    s->prior = head;
    head->next = s;
    return head;
}


void searchbook(booktype *head, char *bookname, char *bookauthor, char *bookdescrip, int *ablebook, int *stroge){
    booktype *h = head->next;
    while(h){
        if(strcmp(h->name, bookname) == 0){
            stroge++;
            strcpy(bookauthor, h->author);
            strcpy(bookdescrip, h->description);
            if(h->flag == 1)
                ablebook++;
        }
        h = h->next;
    }
}


int loadbook(booktype *head, char *bookname, int *i){
    booktype *h = head->next;
    while(h){
        if(strcmp(h->name, bookname) == 0 && h->flag == 1){
            h->flag = 0;  //借出此书时将flag修改为0,表示借出
            *i = h->index;
            return 0;   //借出成功返回0
        }
        h = h->next;
    }
    return -1;   //没有此书或借出失败
}

int repay(booktype *head, unsigned long i, char *bookname{
    booktype *h = head->next;
    while(h){
        if(strcmp(h->name, bookname) == 0  && h->index == i){
            if(h->flag != 1){
                h->flag = 1;
                return 0;
            }else{
                return -1;
            }
        }
        h = h->next;
    }
    return -1;
}

int deletbook(booktype *head, unsigned long i, char *bookname){
    booktype *h = head->next;
    while(h){
        if(h->index == i && strcmp(h->name, bookname) == 0){
            h->prior->next = h->next;
            h->next->prior = h->prior;
            free(h);
            return 0;
        }
        h = h->next;
    }
    return -1;
}

