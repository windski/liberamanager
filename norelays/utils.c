#include "utils.h"

void wirte_data(booktype *book)
{
    FILE *fp = fopen("bookdatacache.dat", "w");
    if(fp == NULL)
    {
        printf("数据存储失败...\n");
        FILE *in = fopen("initcache.dat", "wb");
        if(in == NULL)
        {
            return ;
        }
        else
        {
            fwrite("0", sizeof(char), 1, in);
            fclose(in);
            return ;
        }
    }
    booktype *temp;
    temp = book->next;
    mem m;
    while(temp)
    {
        m.i = temp->index;
        strcpy(m.name, temp->name);
        strcpy(m.author, temp->author);
        m.f = temp->flag;
        strcpy(m.des, temp->description);
        fwrite(&m, sizeof(mem), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}


booktype *read_data(void)
{
    FILE *fp = fopen("bookdatacache.dat", "rb");
    if(fp == NULL)
    {
        printf("数据已损坏..将重新建立数据\n");
        booktype *t;
        return creatdata(1, t);
    }
    mem m;
    booktype *head = (booktype *)malloc(sizeof(booktype));
    booktype *rear = head;
    while(fread(&m, sizeof(mem), 1, fp) == 1)
    {
        booktype *s = (booktype *)malloc(sizeof(booktype));
        s->index = m.i;
        s->flag =m.f;
        strcpy(s->name, m.name);
        strcpy(s->author, m.author);
        strcpy(s->description, m.des);
        s->prior = rear;
        s->next = rear->next;
        rear->next = s;
        rear = s;
    }
    return head;
}


int encryption(char target[], const char *source)
{
#if defined (_WIN32)
    strcpy(target, source);
    return 1;
#elif defined (__linux__)
    char buff[MAXLEN];
    bzero(buff);

    sprintf(buff, "echo -n \"%s\" | sha512sum > demo", source);
    system(buff);
    FILE *fp = fopen("demo", "r");

    bzero(buff);
    fread(buff, sizeof(buff), 1, fp);
    fclose(fp);
    system("rm -f demo");

    strcpy(target, buff);
    return 0;
#endif
}


int set_user(FILE *fp)
{
    char buff[MAXLEN], target[MAXLEN];
    bzero(buff);
    bzero(target);

    FFLUSH();
    printf("用户名:");
    fgets(buff, sizeof(buff), stdin);
    fwrite(buff, sizeof(buff), 1, fp);
    bzero(buff);

    printf("密码:");
    fgets(buff, sizeof(buff), stdin);
    if(encryption(target, buff) == 1) {
        fprintf(stderr, "WARNNING! The password was NOT Encrypt yet!\n");
    }
    fwrite(target, sizeof(target), 1, fp);

    return 0;
}


int checkout_user(FILE *fp)
{
    char buff[MAXLEN], target[MAXLEN];
    bzero(buff);
    bzero(target);

    bool flag_user = false;

    printf("Login First..\n\n用户名:");

    FFLUSH();
    fgets(target, sizeof(target), stdin);
    fread(buff, sizeof(buff), 1, fp);
    
    while(feof(fp) == 0) {
        if(strcmp(target, buff) == 0) {
            flag_user = true;
            break;
        }
        bzero(buff);
        fread(buff, sizeof(buff), 1, fp);
    }

    if(flag_user) {
        char ch;
        int i = 0;
        printf("Password:");
        bzero(buff);
        while((ch = getch()) != '\n') {
            buff[i] = ch;
            i++;
        }
        buff[i - 1] = '\0';
        bzero(target);

        encryption(target, buff);
        fread(buff, sizeof(buff), 1, fp);

        if(strcmp(target, buff) == 0) {
            return 0;
        }
    }

    fprintf(stderr, "Can't find the user name.\n");

    return 1;
}


int _getch(void)
{
    struct termios tm, tm_old;
    int c;

    if(tcgetattr(STDIN_FILENO, &tm_old) < 0) {
        perror("tcgetattr");
        return -1;
    }
    
    tm = tm_old;
    tm.c_lflag &= ~(ECHO | ICANON);
    if(tcsetattr(STDIN_FILENO, TCSANOW, &tm) < 0) {
        perror("tcsetattr");
        return -1;
    }

    c = getc(stdin);

    if(tcsetattr(STDIN_FILENO, TCSANOW, &tm_old) < 0) {
        perror("tcsetattr old");
        return -1;
    }

    return c;
}

