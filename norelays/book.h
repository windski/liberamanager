#ifndef BOOK_H
#define BOOK_H

#ifndef MAXNAME
#define MAXNAME 64
#endif

#ifndef MAXLEN
#define MAXLEN 513
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define bzero(buff) memset(buff, 0, sizeof(buff))
#if defined (_WIN32)
#define FFLUSH() fflush(stdin)
#elif defined (__linux__)
#define FFLUSH()                                            \
    do {                                                    \
        char ch;                                            \
        while((ch = getchar()) != '\n' && ch != EOF);       \
    } while(0)
#else
#define FFLUSH()
#endif

typedef struct booktype{
    unsigned long index;
    struct booktype *prior;
    struct booktype *next;
    char name[MAXNAME];
    char author[MAXNAME];
    int flag;
    char description[MAXLEN];
}booktype;

typedef struct{
    unsigned long i;
    char name[MAXNAME];
    char author[MAXNAME];
    int f;
    char des[MAXLEN];
}mem;

extern int deletbook(booktype *);
extern booktype *creatdata(int , booktype *);
extern void searchbook(booktype *);
extern int loadbook(booktype *);
extern int repay(booktype *);

#endif
