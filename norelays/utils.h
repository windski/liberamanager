#ifndef UTILS_H_
#define UTILS_H_

#include "book.h"
#if defined (_WIN32)
#include <coino.h>
#elif defined (__linux__)
#include <termios.h>
#define getch _getch
#endif

extern void wirte_data(booktype *);
extern booktype *read_data(void);
extern int encryption(char *, const char *);
extern int set_user(FILE *);
extern int checkout_user(FILE *);

extern int _getch(void);

#endif
