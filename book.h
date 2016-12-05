#ifndef BOOK_H
#define BOOK_H

#ifndef MAXNAME
#define MAXNAME 50
#endif

typedef struct booktype{
    unsigned long index;
    struct booktype *next;
    char name[MAXNAME];    //图书的书名
    char author[MAXNAME];    //图书的作者
    int flag = 1;     //图书被借出时,flag = 0
    long num = 1;
}booktype;

booktype *creatdata(void);    //初始化时录入图书数据
booktype *addnewbook(booktype *);    //新增图书
int searchbook(booktype *);    //检索图书
int loadbook(booktype *);    //借出图书
int repay(booktype *);    //还书

#endif
