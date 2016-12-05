#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"book.h"

booktype *creatdata(int flag, booktype *head){
    if(flag == 1){
        unsigned long x = 1;
        booktype *head = (booktype *)malloc(sizeof(booktype));
        booktype *rear = head;
        while(x != 0){
            scanf("请输入书的序列号:%lu", &x); 
            putchar('\n');
            booktype *s = (booktype *)malloc(sizeof(booktype));
            s->index = x;
            s->flag = 1;
            printf("请输入书的名字\n");
            fgets(s->name, MAXNAME, stdin);
            printf("请输入书的作者\n");
            fgets(s->author, MAXNAME, stdin);
            printf("请输入此书的描述性文字\n");
            fgets(s->description, MAXLEN, stdin);
            s->prior = rear;
            s->next = rear->next;
            rear = s;
        }
        rear->next = NULL;
        return head;
    }else{
        unsigned long x;
        scanf("请输入书的序列号:%lu", &x); 
        putchar('\n');
        booktype *s = (booktype *)malloc(sizeof(booktype));
        s->index = x;
        s->flag = 1;
        printf("请输入书的名字\n");
        fgets(s->name, MAXNAME, stdin);
        printf("请输入书的作者\n");
        fgets(s->author, MAXNAME, stdin);
        printf("请输入此书的描述性文字\n");
        fgets(s->description, MAXLEN, stdin);
        s->next = head->next;
        head->next->prior = s;
        s->prior = head;
        head->next = s;
        return head;
    }
}

void searchbook(booktype *head, char *bookname){
    booktype *h = head->next;
    char bookauthor[MAXNAME];
    char bookdescrip[MAXLEN];
    int ablebook = 0, stroge = 0;
    while(h->next == NULL){
        if(strcmp(h->name, bookname) == 0){
            stroge++;
            strcpy(bookauthor, h->author);
            strcpy(bookdescrip, h->description);
            if(h->flag == 1)
                ablebook++;
        }
        h = h->next;
    }
    printf("此书的作者是:");
    puts(bookauthor);
    puts(bookdescrip);
    printf("此书共有%d本,其中%d可以借阅\n", stroge, ablebook);
}


int loadbook(booktype *head, char *bookname){
    booktype *h = head->next;
    while(h->next){
        if(strcmp(h->name, bookname) == 0 && h->flag == 1){
            h->flag = 0;  //借出此书时将flag修改为0,表示借出
            return 0;   //借出成功返回0
        }
        h = h->next;
    }
    return -1;   //没有此书或借出失败
}

int repay(booktype *head, char *bookname){
    booktype *h = head->next;
    while(h->next){
        if(strcmp(h->name, bookname) == 0  && h->flag != 1){
            h->flag = 1;
            return 0;
        }
        h = h->next;
    }
    return -1;
}

int deletbook(booktype *head, char *bookname, unsigned long i){
    booktype *h = head->next;
    while(h->next){
        if(h->index == i && strcmp(h->name, bookname) == 0){
            h->prior->next = h->next;
            h->next->prior = h->prior;
            free(h);
            return 0;
        }
        h = h->next;
    }
    return 1;
}
