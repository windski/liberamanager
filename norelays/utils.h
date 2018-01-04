#ifndef UTILS_H_
#define UTILS_H_

#include "book.h"
#if defined (_WIN32)
#include <conio.h>
#elif defined (__linux__)
#include <termios.h>
#define getch _getch
#endif


#define rm_enter_ch(source)                  \
    do {                                     \
        size_t len = strlen(source);         \
        if((source)[len - 1] == '\n')        \
            (source)[len - 1] = '\0';        \
    } while(0)

extern void write_data(book_t *);
extern book_t *read_data(void);
extern int encryption(char *, const char *);
extern int set_user(FILE *);
extern int checkout_user(FILE *);
extern int login_user(char *);
extern int _getch(void);

#endif
