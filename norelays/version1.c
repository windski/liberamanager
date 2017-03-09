#include<stdio.h>
#include<stdlib.h>
#include"book.h"
#include<string.h>

void wirte_data(booktype *);
booktype *read_data(void);

int main(void){
    char ch, str[10];
    int i;
    booktype *bookdata = NULL;
    FILE *fp = fopen("initcache.dat", "rb");
    if(fp == NULL)
    {
        printf("Welcome to use it....\n\n使用请先录入图书的数据信息\n");
        bookdata = creatdata(1, bookdata);
        printf("使用方法\n");
        printf("   a 新增图书\n   d 删除已经废弃不用的图书\n   s 搜索图书的信息\n   b 借书\n   r 还书   q 退出\n\n");
        fp = fopen("initcache.dat", "wb");
        fwrite("1", sizeof(char), 1, fp);
        fclose(fp);
    }
    else
    {
        fread(&i, sizeof(int), 1, fp);
        fclose(fp);
        if(i == 0)
        {
            printf("数据损坏,请重新建立\n");
            bookdata = creatdata(1, bookdata);
        }
        bookdata = read_data();
    }
    while(1){
        printf("(libmanager)");
        scanf("%s", str);
        while((ch=getchar())!='\n' && ch!=EOF);
        if(strcmp(str, "a") == 0){
            bookdata = creatdata(0, bookdata);
        }else if(strcmp(str, "d") == 0){
            deletbook(bookdata);
        }else if(strcmp(str, "b") == 0){
            loadbook(bookdata);
        }else if(strcmp(str, "r") == 0){
            repay(bookdata);
        }else if(strcmp(str, "s") == 0){
            searchbook(bookdata);
        }else if(strcmp(str, "q") == 0){
            wirte_data(bookdata);
            break;
        }else{
             printf("   a 新增图书\n   d 删除已经废弃不用的图书\n   s 搜索图书的信息\n   b 借书\n   r 还书   q 退出\n\n");
        }
    }
    return 0;
}


void wirte_data(booktype *book)
{
    FILE *fp = fopen("bookdatacache.dat", "w");
    if(fp == NULL)
    {
        printf("数据存储失败...\n");
        FILE *in = fopen("initcache.dat", "wb");
        if(in == NULL)
        {
            return ;
        }
        else
        {
            fwrite("0", sizeof(char), 1, in);
            fclose(in);
            return ;
        }
    }
    booktype *temp;
    temp = book->next;
    mem m;
    while(temp)
    {
        m.i = temp->index;
        strcpy(m.name, temp->name);
        strcpy(m.author, temp->author);
        m.f = temp->flag;
        strcpy(m.des, temp->description);
        fwrite(&m, sizeof(mem), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}


booktype *read_data(void)
{
    FILE *fp = fopen("bookdatacache.dat", "rb");
    if(fp == NULL)
    {
        printf("数据已损坏..将重新建立数据\n");
        booktype *t;
        return creatdata(1, t);
    }
    mem m;
    booktype *head = (booktype *)malloc(sizeof(booktype));
    booktype *rear = head;
    while(fread(&m, sizeof(mem), 1, fp) == 1)
    {
        booktype *s = (booktype *)malloc(sizeof(booktype));
        s->index = m.i;
        s->flag =m.f;
        strcpy(s->name, m.name);
        strcpy(s->author, m.author);
        strcpy(s->description, m.des);
        s->prior = rear;
        s->next = rear->next;
        rear->next = s;
        rear = s;
    }
    return head;
}
