#ifndef BOOK_H
#define BOOK_H

#define MAXNAME 50

#define MAXARRAY 1024

#define MAXLEN 200


struct booktype {
    unsigned long index;       // 索引用
    char name[MAXNAME];    //图书的书名
    char author[MAXNAME];    //图书的作者
    int flag;     //图书被借出时,flag = 0
    char description[MAXLEN];  //此书的描述
};

typedef struct booktype booktype;

typedef struct {
    unsigned long i;
    char name[MAXNAME];
    char author[MAXNAME];
    int f;
    char des[MAXLEN];
}mem;

struct storage_book {
    booktype data[MAXARRAY];
    int length;
};


typedef struct storage_book stabk_t;

void initData(stabk_t *);
int delData(stabk_t *);   //去除已经废弃不用的书
int createData(stabk_t *);
int addData(stabk_t *);
void searchbook(stabk_t *);    //检索图书
int loadbook(stabk_t *);    //借出图书
int repay(stabk_t *);    //还书

#endif
