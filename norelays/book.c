#include "book.h"
#include "utils.h"

#define __TMP_MAX_DES 64
#define __TMP_MAX_LEN 24

#define PRINT_TABLE_LINE(len)                     \
    do {                                          \
        int lens[5] = {7, 26, 26, 66, 6};         \
        int len_i = 0;                            \
        for(int i = 0; i < (len); i++) {          \
            printf("+");                          \
            int j = 0;                            \
            for( ; j < lens[len_i]; j++) {        \
                printf("-");                      \
            }                                     \
            len_i++;                              \
            i = j;                                \
            if(len_i == 5) {                      \
                printf("+");                      \
                break;                            \
            }                                     \
        }                                         \
        printf("\n");                             \
    } while(0)


int core()
{

    return 0;
}


book_t *creatdata(bool flag, book_t *head)
{
    if(flag == true) {
        unsigned long x;
        book_t *head = (book_t *)malloc(sizeof(book_t));
        book_t *rear = head;
        rear->next = NULL;

        printf("Input book's index(Press `0` to exit): ");
        scanf("%lu", &x);

        while(x != 0){
            book_t *s = (book_t *)malloc(sizeof(book_t));
            s->index = x;

            FFLUSH();

            printf("Input book's name: ");
            fgets(s->name, MAXNAME, stdin);
            rm_enter_ch(s->name);

            s->flag = true;

            printf("Author: ");
            fgets(s->author, MAXNAME, stdin);
            rm_enter_ch(s->author);
            printf("Description: ");
            fgets(s->description, MAXLEN, stdin);
            rm_enter_ch(s->description);

            s->prior = rear;
            s->next = rear->next;
            rear->next = s;
            rear = s;

            printf("Index: ");
            scanf("%lu", &x);
        }

        return head;
    } else {
        unsigned long x;
        printf("Just Input the book's index: ");
        scanf("%lu", &x);

        book_t *s = (book_t *)malloc(sizeof(book_t));

        s->index = x;
        s->flag = true;

        FFLUSH();

        printf("Input the book's name: ");
        fgets(s->name, MAXNAME, stdin);
        rm_enter_ch(s->name);
        printf("Author: ");
        fgets(s->author, MAXNAME, stdin);
        rm_enter_ch(s->author);
        printf("Description: ");
        fgets(s->description, MAXLEN, stdin);
        rm_enter_ch(s->description);

        s->next = head->next;
        head->next->prior = s;
        s->prior = head;
        head->next = s;

        return head;
    }
}

void searchbook(book_t *head)
{
    char bookname[MAXNAME];
    bzero(bookname);
    printf("Whitch book you wanna search: ");
    fgets(bookname, MAXNAME, stdin);

    book_t *h = head->next;

    char bookauthor[MAXNAME];
    char bookdescrip[MAXLEN];
    bzero(bookauthor);
    bzero(bookdescrip);

    int ablebook = 0, stroge = 0;

    while(h) {
        if(strcmp(h->name, bookname) == 0) {
            stroge++;
            strcpy(bookauthor, h->author);
            strcpy(bookdescrip, h->description);

            if(h->flag == 1)
                ablebook++;
        }

        h = h->next;
    }

    printf("Author: ");
    puts(bookauthor);
    printf("Description: ");
    puts(bookdescrip);
    printf("此书共有%d本,其中%d可以借阅\n", stroge, ablebook);
}


int loadbook(book_t *head)
{
    char bookname[MAXNAME];
    bzero(bookname);

    printf("请输入你要借书的书名:");
    fgets(bookname, MAXNAME, stdin);
    rm_enter_ch(bookname);

    book_t *h = head->next;

    while(h) {
        if(strcmp(h->name, bookname) == 0 && h->flag == true) {
            h->flag = false;
            printf("SUCCESS!\n");
            printf("你所借的书的序列号为:%lu, 还书时请提供...\n", h->index);
            return 0;
        }
        h = h->next;
    }
    printf("ERROR!\n");
    return -1;
}

int repay(book_t *head)
{
    unsigned long i;
    char bookname[MAXNAME];
    bzero(bookname);

    printf("请输入你要还书的书名:");
    fgets(bookname, MAXNAME, stdin);
    rm_enter_ch(bookname);
    printf("请提供你要还书的序列号:");
    scanf("%lu", &i);

    book_t *h = head->next;
    while(h) {
        if(strcmp(h->name, bookname) == 0  && h->index == i) {
            if(h->flag != true) {
                h->flag = true;
                printf("SUCCESS!\n");
                return 0;
            } else {
                printf("ERROR!\n\n此书未被借出,还书失败\n");
            }
        }
        h = h->next;
    }
    printf("ERROR!\n");
    return -1;
}

int deletbook(book_t *head)
{
    char bookname[MAXNAME];
    bzero(bookname);
    unsigned long i;

    printf("请输入你要删除的书名:");
    fgets(bookname, MAXNAME, stdin);
    rm_enter_ch(bookname);
    printf("请输入你要删除书的序列号:");
    scanf("%lu", &i);

    book_t *h = head->next;

    while(h) {
        if(h->index == i && strcmp(h->name, bookname) == 0) {
            h->prior->next = h->next;
            h->next->prior = h->prior;

            free(h);

            return 0;
        }
        h = h->next;
    }
    return -1;
}


int print_book(book_t *head)
{
    book_t *tmp = head->next;

    char buff[4096];
    bzero(buff);
    printf("[ INFO ] T 代表未被借出, F 代表已借出\n");

    sprintf(buff, "| %-s | %-24s | %-24s | %-64s | flag |", "Index", "Name", "Author", "Description");
    int len = strlen(buff);

    PRINT_TABLE_LINE(len);
    puts(buff);
    PRINT_TABLE_LINE(len);

    while(tmp) {
        bzero(buff);
        char buf_des[__TMP_MAX_DES], buf_nam[__TMP_MAX_LEN], buf_aut[__TMP_MAX_LEN];
        
        bzero(buf_nam);
        bzero(buf_aut);
        bzero(buf_des);
        
        strncpy(buf_des, tmp->description, sizeof(buf_des));
        strncpy(buf_aut, tmp->author, sizeof(buf_aut));
        strncpy(buf_nam, tmp->name, sizeof(buf_nam));
        buf_des[__TMP_MAX_DES - 1] = '\0';
        buf_aut[__TMP_MAX_LEN - 1] = '\0';
        buf_nam[__TMP_MAX_LEN - 1] = '\0';

        for(int i = 2; i < 4; i++) {
            buf_des[__TMP_MAX_DES - i] = '.';
            buf_aut[__TMP_MAX_LEN - i] = '.';
            buf_nam[__TMP_MAX_LEN - i] = '.';
        }

        if(tmp->flag) {
            sprintf(buff, "| %-5lu | %-24s | %-24s | %-64s | %-4s |",
                    tmp->index, buf_nam, buf_aut, buf_des, "T");
        } else {
            sprintf(buff, "| %-5lu | %-24s | %-24s | %-64s | %-4s |",
                    tmp->index, buf_nam, buf_aut, buf_des, "F");
        }
        puts(buff);
        PRINT_TABLE_LINE(len);
        tmp = tmp->next;
    }

    return 0;
}

#undef __TMP_MAX_DES
#undef __TMP_MAX_LEN


