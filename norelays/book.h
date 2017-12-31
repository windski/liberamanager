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
#include <signal.h>

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


struct book_t {
    unsigned long index;
    struct book_t *prior;
    struct book_t *next;
    char name[MAXNAME];
    char author[MAXNAME];
    bool flag;
    char description[MAXLEN];
};

typedef struct book_t book_t;

typedef struct {
    unsigned long i;
    char name[MAXNAME];
    char author[MAXNAME];
    int f;
    char des[MAXLEN];
} mem;

extern int core();

extern int deletbook(book_t *);
extern book_t *creatdata(bool, book_t *);
extern void searchbook(book_t *);
extern int loadbook(book_t *);
extern int repay(book_t *);
extern int print_book(book_t *);

#endif
