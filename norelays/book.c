#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"book.h"

booktype *creatdata(int flag, booktype *head){
    char ch;
    if(flag == 1){
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
    }else{
        unsigned long x;
        printf("请输入书的序列号:\n");
        scanf("%lu", &x);
        booktype *s = (booktype *)malloc(sizeof(booktype));
        s->index = x;
        s->flag = 1;
        while((ch=getchar())!='\n' && ch!=EOF);
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

void searchbook(booktype *head){
    char bookname[MAXNAME];
    printf("请输入你要搜索的书名:");
    fgets(bookname, MAXNAME, stdin);
    booktype *h = head->next;
    char bookauthor[MAXNAME];
    char bookdescrip[MAXLEN];
    int ablebook = 0, stroge = 0;
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
    printf("此书的作者是:");
    puts(bookauthor);
    puts(bookdescrip);
    printf("此书共有%d本,其中%d可以借阅\n", stroge, ablebook);
}


int loadbook(booktype *head){
    char bookname[MAXNAME];
    printf("请输入你要借书的书名:");
    fgets(bookname, MAXNAME, stdin);
    booktype *h = head->next;
    while(h){
        if(strcmp(h->name, bookname) == 0 && h->flag == 1){
            h->flag = 0;  //借出此书时将flag修改为0,表示借出
            printf("SUCCESS!\n");
            printf("你所借的书的序列号为:%lu, 还书时请提供...\n", h->index);
            return 0;   //借出成功返回0
        }
        h = h->next;
    }
    printf("ERROR!\n");
    return -1;   //没有此书或借出失败
}

int repay(booktype *head){
    unsigned long i;
    char bookname[MAXNAME];
    printf("请输入你要还书的书名:");
    fgets(bookname, MAXNAME, stdin);
    printf("请提供你要还书的序列号:");
    scanf("%lu", &i);
    booktype *h = head->next;
    while(h){
        if(strcmp(h->name, bookname) == 0  && h->index == i){
            if(h->flag != 1){
                h->flag = 1;
                printf("SUCCESS!\n");
                return 0;
            }else{
                printf("ERROR!\n\n此书未被借出,还书失败\n");
            }
        }
        h = h->next;
    }
    printf("ERROR!\n");
    return -1;
}

int deletbook(booktype *head){
    char bookname[MAXNAME];
    unsigned long i;
    printf("请输入你要删除的书名:");
    fgets(bookname, MAXNAME, stdin);
    printf("请输入你要删除书的序列号:");
    scanf("%lu", &i);
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

