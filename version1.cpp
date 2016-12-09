#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "book.h"
#include "unistd.h"

using namespace std;

void savedata(booktype *);   //将链表中的数据用字符串的形式存起来
booktype *readdata(void);   //从文件中读取数据到链表
void rewritedata(booktype *);  //将整个bookdata.dat重新写一遍

int main(int argc, char *argv[]){
    int i = 1, ch;
    booktype *bookdata;
    FILE *fp;
    fp = fopen("flag.dat", "r");
    if(fp == NULL){
        ofstream openfile("flag.dat", ios::out|ios::binary);
        openfile << "True" << endl;
        openfile.close();   //立个flag
        printf("用法: libmanager [选项] 命令\n\n      -a 用来新增图书.\n      -d <删除已经废弃不用的书 它的序列号>\n      -s <搜索图书的信息的书名>\n      -b <借书的书名>\n      -r <还书的名字>\n\n");
        printf("Welcome to use it....\n\n第一次使用请先录入图书的数据信息\n");
        bookdata = creatdata(1, bookdata);
        /*给文件写入图书的数据*/
        savedata(bookdata);
    }else{
        fclose(fp);
        bookdata = readdata();
        /*读取文件流*/
        while((ch=getopt(argc, argv, "ab:r:d:s:")) != -1){
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
        printf("正在将数据重新写入...请稍后..\n");
        rewritedata(bookdata);
    }
    return 0;
}

void savedata(booktype *head){
    booktype *p = head->next;
    ofstream openfile("bookdata.dat");
    while(p == NULL){
        openfile << p->index << endl;
        openfile << p->name << endl;
        openfile << p->author << endl;
        openfile << p->description << endl;
        p = p->next;
    }
    openfile.close();
}

booktype *readdata(void){
    ifstream readfile("bookdata.dat", ios::in);
    booktype *head = (booktype *)malloc(sizeof(booktype));
    head->next = NULL;
    while(!readfile.eof()){
        booktype *q = (booktype *)malloc(sizeof(booktype));
        readfile >> q->index;
        readfile >> q->name;
        readfile >> q->author;
        readfile >> q->description;
        q->next = head->next;
        head->next = q;
    }
    readfile.close();
    return head;
}

void rewritedata(booktype *head){
    FILE *fp;
    fp = fopen("bookdata.dat", "w");
    fclose(fp);
    ofstream openfile("bookdata.dat");
    while(head->next){
        head = head->next;
        openfile << head->index << endl;
        openfile << head->name << endl;
        openfile << head->author << endl;
        openfile << head->description << endl;
    }
    openfile.close();
}
