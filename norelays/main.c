#include "book.h"
#include "utils.h"

int main(int argc, const char **argv)
{
    int flags, opt;

/*     while((opt = getopt(argc, argv, "u:p")) != -1) {
 *         switch(opt) {
 *             case 'u':
 *
 *         }
 *     } */

    char str[MAXLEN];
    int i;
    booktype *bookdata = NULL;
    FILE *fp = fopen("initcache.dat", "rb");

    if(fp == NULL) {
        printf("Welcome to use it....\n\n使用请先录入图书的数据信息\n");
        bookdata = creatdata(1, bookdata);

        printf("使用方法\n");
        printf("   a 新增图书\n   d 删除已经废弃不用的图书\n   s 搜索图书的信息\n   b 借书\n   r 还书   q 退出\n\n");

        fp = fopen("initcache.dat", "wb");
        set_user(fp);
        fclose(fp);
    } else {
/*         fread(&i, sizeof(int), 1, fp);
 *         fclose(fp);
 *
 *         if(i == 0) {
 *             printf("数据损坏,请重新建立\n");
 *             bookdata = creatdata(1, bookdata);
 *         } */

        if(checkout_user(fp) != 0) {
            fclose(fp);
            exit(-1);
        }

        fclose(fp);
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
        } else if(strcmp(str, "q") == 0) {
            wirte_data(bookdata);
            break;
        } else {
            printf("   a 新增图书\n   d 删除已经废弃不用的图书\n   s 搜索图书的信息\n   b 借书\n   r 还书   q 退出\n\n");
        }
    }
    return 0;
}

