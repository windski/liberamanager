#include<stdio.h>
#include<stdlib.h>
#include"book.h"
#include<string.h>

// 声明两个函数
void wirte_data(stabk_t stabk);                  // write_data 这个函数将我们存储的数据写到一个文件里, 使得程序再打开时, 能够不重新录入数据
stabk_t read_data(void);                    // read_data 这个函数将我们已经存储好的数据(文件里的数据), 读到程序里.使得能够搜索的时候更快点儿..

int main(void){                               // 程序入口
    char ch, str[10];
    int i;
    stabk_t stabk;
    initData(&stabk);
    FILE *fp = fopen("initcache.dat", "rb");
    if(fp == NULL)
    {
        printf("Welcome to use it....\n\n使用请先录入图书的数据信息\n");
        createData(&stabk);
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
            createData(&stabk);
        }
        stabk = read_data();
    }
    while(1)
    {
        printf("(libmanager)");
        scanf("%s", str);
        while((ch=getchar())!='\n' && ch!=EOF);
        if(strcmp(str, "a") == 0)
        {
            addData(&stabk);
        }
        else if(strcmp(str, "d") == 0)
        {
            delData(&stabk);
        }
        else if(strcmp(str, "b") == 0)
        {
            loadbook(&stabk);
        }
        else if(strcmp(str, "r") == 0)
        {
            repay(&stabk);
        }
        else if(strcmp(str, "s") == 0)
        {
            searchbook(&stabk);
        }
        else if(strcmp(str, "q") == 0)
        {
            wirte_data(stabk);
            break;
        }
        else
        {
             printf("   a 新增图书\n   d 删除已经废弃不用的图书\n   s 搜索图书的信息\n   b 借书\n   r 还书   q 退出\n\n");
        }
    }
    return 0;
}


void wirte_data(stabk_t book)
{
    FILE *fp;
    int len, i;

    fp = fopen("bookdatacache.dat", "w");
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

    i = 0;
    len = book.length;
    mem m;
    while(i < len)
    {
        m.i = book.data[i].index;
        strcpy(m.name, book.data[i].name);
        strcpy(m.author, book.data[i].author);
        m.f = book.data[i].flag;
        strcpy(m.des, book.data[i].description);
        fwrite(&m, sizeof(mem), 1, fp);
        i++;
    }
    fclose(fp);
}


stabk_t read_data(void)
{
    FILE *fp;
    int len;

    fp = fopen("bookdatacache.dat", "rb");
    if(fp == NULL)
    {
        printf("数据已损坏..将重新建立数据\n");
        stabk_t stabk;
        createData(&stabk);
        return stabk;
    }

    stabk_t stabk;
    initData(&stabk);
    len = stabk.length;
    mem m;
    while(fread(&m, sizeof(mem), 1, fp) == 1)
    {
        stabk.data[len].index = m.i;
        stabk.data[len].flag =m.f;
        strcpy(stabk.data[len].name, m.name);
        strcpy(stabk.data[len].author, m.author);
        strcpy(stabk.data[len].description, m.des);
        len++;
    }
    fclose(fp);
    stabk.length = len;

    return stabk;
}
