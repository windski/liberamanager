#include "book.h"
#include "utils.h"
#include <getopt.h>

void print_help(char *name)
{
    printf("\nUsage:\n %s <option> <parameters>\n\nParse command options\n\n"
            "Options:\n"
            " -a, Add a book.<Index>\n"
            " -u, Specified username\n"
            " -d, Delete the book\n"
            " -p, Advanced function\n"
            " -h, print this page\n", name);
    exit(0);
}

int main(int argc, char *argv[])
{
    // TODO: Advanced function.
    // TODO: Parse command. sql-like language..
    int opt;
    while((opt = getopt(argc, argv, "u:a:d:ph")) != -1) {
        switch(opt) {
            case 'u':
                if(login_user(optarg) != 0) {
                    exit(-1);
                }
                goto start;
            case 'a':

                break;
            case 'd':

                break;
            case 'p':

                break;
            case 'h':
                print_help(argv[0]);
                break;
            default:
                print_help(argv[0]);
                break;
        }
    }

    char str[MAXLEN];
    book_t *bookdata = NULL;
    FILE *fp = fopen("initcache.dat", "rb");

    if(fp == NULL) {
        printf("Welcome to use it....\n\n使用请先录入图书的数据信息\n");
        bookdata = creatdata(1, bookdata);

        printf("使用方法\n");
        printf("\ta 新增图书\n\td 删除已经废弃不用的图书\n\ts 搜索图书的信息\n\tb 借书\n\tr 还书\n\tp 打印\n\tc 统计\n\tsort 排序\nq 退出\n\n");

        fp = fopen("initcache.dat", "wb");
        set_user(fp);
        fclose(fp);
    } else {
        if(checkout_user(fp) != 0) {
            fclose(fp);
            exit(-1);
        }

        fclose(fp);
start:
        bookdata = read_data();
    }

    while(true) {
        printf("(libmanager) >> ");
        scanf("%s", str);

        FFLUSH();

        if(strcmp(str, "a") == 0) {
            bookdata = creatdata(0, bookdata);
        } else if(strcmp(str, "d") == 0) {
            deletbook(bookdata);
        } else if(strcmp(str, "b") == 0) {
            loadbook(bookdata);
        } else if(strcmp(str, "r") == 0) {
            repay(bookdata);
        } else if(strcmp(str, "s") == 0) {
            searchbook(bookdata);
        } else if(strcmp(str, "p") == 0) {
            print_book(bookdata);
        } else if(strcmp(str, "sort") == 0) {
            sort_book(bookdata);
        } else if(strcmp(str, "q") == 0) {
            write_data(bookdata);
            break;
        } else {
            printf("\ta 新增图书\n\td 删除已经废弃不用的图书\n\ts 搜索图书的信息\n\tb 借书\n\tr 还书\n\tp 打印\n\tc 统计\n\tsort 排序\nq 退出\n\n");
        }
    }
    return 0;
}

