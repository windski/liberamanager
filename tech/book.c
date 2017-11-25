#include <stdio.h>
#include <string.h>
#include "book.h"


void initData(stabk_t *stabk)
{
    memset(stabk->data, 0, sizeof(stabk->data));
    stabk->length = 0;
}

/* *
 * 下面的这个函数用于初始化的时候创建数据..
 * 使用到了fgets这个标准库函数(在string.h)这个头文件中, 它的函数原型为:
 * char *fgets(char *s, int size, FILE *stream);
 * 它的作用与scanf相似, 但是为了软件的安全我选择fgets...2333
 */
int createData(stabk_t *stabk)
{
    char ch;
    unsigned long x;
    int len;

    printf("请输入序列号(输入`0`结束)\n");
    scanf("%lu", &x);

    len = stabk->length;       // 记录下长度

    while(x != 0) {
        stabk->data[len].index = x;
        while((ch = getchar()) != '\n' && ch != EOF);
        printf("请输入书的名字\n");
        fgets(stabk->data[len].name, MAXNAME, stdin);           // 从标准输入(比如,键盘)读取MAXNAME个字符到stabk->data[len].name指向的地方
        printf("请输入书的作者\n");
        fgets(stabk->data[len].author, MAXNAME, stdin);
        printf("请输入书的描述文字\n");
        fgets(stabk->data[len].description, MAXLEN, stdin);
        stabk->data[len].flag = 1;                     // 设置没有借出的标志

        len++;            // 开始记录下一个数据

        printf("请输入下一本书的序列号\n");
        scanf("%lu", &x);
    }

    stabk->length = len;

    return 0;
}


int addData(stabk_t *stabk)
{
    if(stabk->length >= MAXARRAY - 1) {
        printf("没有足够的空间了....\n");
        return -1;
    }

    char ch;
    unsigned long x;
    int len;
    printf("请输入序列号\n");
    scanf("%lu", &x);
    while((ch = getchar()) != '\n' && ch != EOF);

    len = stabk->length;
    len++;
    stabk->data[len].index = x;
    stabk->data[len].flag = 1;

    printf("请输入书的名字\n");
    fgets(stabk->data[len].name, MAXNAME, stdin);
    printf("请输入书的作者\n");
    fgets(stabk->data[len].author, MAXNAME, stdin);
    printf("请输入书的描述文字\n");
    fgets(stabk->data[len].description, MAXLEN, stdin);

    stabk->length = len;

    return 0;
}


void mvElem(booktype *data, int current, int size)
{
    for( ; current < size; current++) {
        data[current] = data[current + 1];
    }
}


int delData(stabk_t *stabk)
{
    unsigned long x;
    char n_buff[MAXNAME];

    int len, i;

    printf("你要删除哪本书?\n");
    fgets(n_buff, MAXNAME, stdin);

    printf("此书的序列号\n");
    scanf("%lu", &x);

    i = 0;
    len = stabk->length;
    while(i <= len) {
        if(strcmp(n_buff, stabk->data[i].name) == 0 && x == stabk->data[i].index) {
            mvElem(stabk->data, i, len);
            stabk->length--;
            return 0;
        }
        i++;
    }

    return -1;
}


int loadbook(stabk_t *stabk)
{
    char n_buff[MAXNAME];

    int len, i;
    printf("你要借哪本书?");
    fgets(n_buff, MAXNAME, stdin);

    i = 0;
    len = stabk->length;
    while(i <= len) {
        if(strcmp(n_buff, stabk->data[i].name) == 0 && stabk->data[i].flag == 1) {
            stabk->data[i].flag = 0;
            printf("SUCCESS!\n");
            printf("你所借书的序列号为%lu,还书时请提供\n", stabk->data[i].index);
            return 0;
        }
        i++;
    }

    return -1;
}


int repay(stabk_t *stabk)
{
    char n_buff[MAXNAME];
    unsigned long x;

    int len, i;

    printf("你要还的书名是:");
    fgets(n_buff, MAXNAME, stdin);
    printf("此书的序列号为:");
    scanf("%lu", &x);

    i = 0;
    len = stabk->length;
    while(i <= len) {
        if(strcmp(n_buff, stabk->data[i].name) == 0 && x == stabk->data[i].index) {
            stabk->data[i].flag = 1;
            printf("SUCCESS!\n");
            return 0;
        }
        i++;
    }

    return -1;
}


void searchbook(stabk_t *stabk)
{
    char n_buff[MAXNAME], a_buff[MAXNAME], d_buff[MAXLEN];
    int len, i;
    int storage_bk, enable_bk;

    storage_bk = 0;
    enable_bk = 0;
    memset(a_buff, 0, sizeof(a_buff));
    memset(d_buff, 0, sizeof(d_buff));

    printf("你要搜索的书名:");
    fgets(n_buff, MAXNAME, stdin);

    i = 0;
    len = stabk->length;
    while(i <= len) {
        if(strcmp(n_buff, stabk->data[i].name) == 0) {
            storage_bk++;
            strcpy(a_buff, stabk->data[i].author);
            strcpy(d_buff, stabk->data[i].description);
            if(stabk->data[i].flag == 1) {
                enable_bk++;
            }
        }
        i++;
    }

    printf("此书的作者是:");
    puts(a_buff);
    puts(d_buff);
    printf("此时共有%d本,其中有%d可供借阅\n", storage_bk, enable_bk);
}
