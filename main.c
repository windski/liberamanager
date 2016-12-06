#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main(int argc, const char **argv)
{
    int i = 1;
    booktype *bookdata;
    FILE *fp;
    fp = fopen("bookdata.mem", "r");
    if(fp == NULL){
        printf("Welcome to use it....\n\n");
        /*code here*/
    }
    for(; i<=argc; i++){
        if(strcmp("-a", argv[i] == 0)){
            bookdata = creatdata(0, bookdata);
        }else if(strcmp("-d", argv[i] == 0)){
            deletbook(bookdata, argv[i+1], argv[i+2]);
        }else if(strcmp("-s", argv[i]) == 0){
            searchbook(bookdata, argv[i+1]);
        }else if(strcmp("-r", argv[i]) == 0){
            repay(bookdata, argv[i+1]);
        }else if(strcmp("-b", argv[i]) == 0){
            loadbook(bookdata, argv[i+1]);
        }else{
            printf("用法: libmanager [选项] 命令\n\n      -a <新增图书的名字>\n      -d <删除已经废弃不用的书 它的序列号>\n      -s <搜索图书的信息的书名>\n      -b <借书的书名>\n      -r <还书的名字>\n\n");
        }
    /*code here*/
    }
    return 0;
}

