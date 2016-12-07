#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "unistd.h"

int main(int argc, const char *argv[])
{
    int i = 1, ch;
    booktype *bookdata;
    FILE *fp;
    fp = fopen("bookdata.mem", "r");
    if(fp == NULL){
        printf("Welcome to use it....\n\n第一次使用请先录入图书的数据信息\n");
        fp = fopen("bookdata.mem", "w");
        bookdata = creatdata(1, NULL);
        /*在这儿给文件写入图书的数据*/
    }else{
        fp = fopen("bookdata.mem", "a");
        fseek(fp, 0, SEEK_SET);
        /*读取文件流*/
        //bookdata = restrge(fp);
        while((ch = getopt(argc, argv, "ab:r:d:s:")) != -1){
            switch(ch){
                case 'a':bookdata = creatdata(0, bookdata);
                    break;
                case 'b':loadbook(bookdata, optarg);
                    break;
                case 'r':repay(bookdata, optarg);
                    break;
                case 'd':deletbook(bookdata, optarg, (unsigned long)atol(argv[optind]));
                    break;
                case 's':searchbook(bookdata, optarg);
                    break;
                default:printf("用法: libmanager [选项] 命令\n\n      -a 用来新增图书.\n      -d <删除已经废弃不用的书 它的序列号>\n      -s <搜索图书的信息的书名>\n      -b <借书的书名>\n      -r <还书的名字>\n\n");
            }
        }

    }
    return 0;
}

