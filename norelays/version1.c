#include<stdio.h>
#include<stdlib.h>
#include"book.h"
#include<string.h>

int main(void){
    char str[MAXNAME] = "t";
    FILE *fp;
    booktype *bookdata;
    fp = fopen("flag.dat", "r");
    if(fp == NULL){
        fp = fopen("flag.dat", "w");
        fgets("ture", sizeof("ture"), 1, fp);
        fclose(fp);
        printf("Welcome to use it....\n\n第一次使用请先录入图书的数据信息\n");
        bookdata = creatdata(1, bookdata);
        printf("重启使用...\n");
    }else{
        while(1){
            printf("   a 新增图书\n   d 删除已经废弃不用的图书\n   s 搜索图书的信息\n   b 借书\n   r 还书   q 退出\n\n");
            printf("(libmanager)");
            scanf("%s", &str);
            if(strcmp(str, "a") == 0){
                bookdata = creatdata(0, bookdata);
            }else if(strcmp(str, "d") == 0){
                bookdata = deletbook(bookdata);
            }else if(strcmp(str, "b") == 0){
                bookdata = loadbook(bookdata);
            }else if(strcmp(str, "r") == 0){
                bookdata = repay(bookdata);
            }else if(strcmp(str, "s") == 0){
                searchbook(bookdata);
            }else if(strcmp(str, "q") == 0){
                break;
            }
        }
    }
    return 0;
}
