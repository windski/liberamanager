#include "utils.h"


#define GET_PASSWD(target)                     \
    do {                                       \
        char ch;                               \
        int i = 0;                             \
        while((ch = getch()) != ENTER) {       \
            if(ch != '\b') {                   \
                (target)[i] = ch;              \
                i++;                           \
            } else {                           \
                i--;                           \
            }                                  \
        }                                      \
        (target)[i] = '\n';                    \
    } while(0)


void write_data(book_t *book)
{
    FILE *fp = fopen("bookdatacache.dat", "w");
    
    if(fp == NULL) {
        printf("[ WARN ]数据存储失败...\n");
        FILE *in = fopen("initcache.dat", "wb");

        if(in == NULL) {
            return ;
        } else {
            fwrite("0", sizeof(char), 1, in);
            fclose(in);
            return ;
        }
    }
    
    book_t *temp;
    temp = book->next;
    mem m;
    
    while(temp) {
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


book_t *read_data(void)
{
    FILE *fp = fopen("bookdatacache.dat", "rb");
    if(fp == NULL) {
        printf("[ ERROR ] 数据已损坏..将重新建立数据\n");
        book_t *t = NULL;
        
        return creatdata(1, t);
    }
    mem m;
    book_t *head = (book_t *)malloc(sizeof(book_t));
    book_t *rear = head;
    
    while(fread(&m, sizeof(mem), 1, fp) == 1) {
        book_t *s = (book_t *)malloc(sizeof(book_t));
        
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

    fclose(fp);
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
    printf("用户名: ");
    fgets(buff, sizeof(buff), stdin);
    rm_enter_ch(buff);
    fwrite(buff, sizeof(buff), 1, fp);
    bzero(buff);

    printf("密码: ");

    GET_PASSWD(buff);

    if(encryption(target, buff) == 1) {
        fprintf(stderr, "\n[ WARN ] WARNNING! The password was NOT Encrypt yet!\n");
    }
    fwrite(target, sizeof(target), 1, fp);

    printf("\n");

    return 0;
}


int checkout_user(FILE *fp)
{
    char buff[MAXLEN], target[MAXLEN];
    bzero(buff);
    bzero(target);

    bool flag_user = false;

    printf("[ INFO ] Login First..\n\n用户名:");

    fgets(target, sizeof(target), stdin);
    rm_enter_ch(target);
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
        printf("Password:");
        bzero(buff);

        GET_PASSWD(buff);

        bzero(target);

        encryption(target, buff);
        fread(buff, sizeof(buff), 1, fp);

        if(strcmp(target, buff) == 0) {
            printf("\n");
            return 0;
        }

        fprintf(stderr, "\n[ ERROR ] The pasword was wrong!\n");
        return 1;
    }

    fprintf(stderr, "\n[ ERROR ] Can't find the user name.\n");
    return 1;
}

#if defined(__linux__)
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
#endif

int login_user(char *username)
{
    FILE *fp = fopen("initcache.dat", "rb");
    if(fp == NULL) {
        fprintf(stderr, "Oops! The user infomations was NOT Found!\n");
        FILE *fp = fopen("initcache.dat", "wb");
        assert(fp != NULL);
        return set_user(fp);
    }

    char buff[MAXLEN], target[MAXLEN];
    bool flag_user = false;
    bzero(buff);
    bzero(target);

    // 跟上面的实现有部分一样...在后期重构的时候再说吧..
    fread(buff, sizeof(buff), 1, fp);
    strncpy(target, username, sizeof(target));
    while(feof(fp) == 0) {
        if(strcmp(target, buff) == 0) {
            flag_user = true;
            break;
        }
        bzero(buff);
        fread(buff, sizeof(buff), 1, fp);
    }

    if(flag_user) {
        bzero(target);
        bzero(buff);

        printf("Password: ");
        GET_PASSWD(buff);
        encryption(target, buff);

        fread(buff, sizeof(buff), 1, fp);
        fclose(fp);
        if(strcmp(buff, target) == 0) {
            printf("\n");
            return 0;
        }

        fprintf(stderr, "[ ERROR ] Password was wrong!\n");
        return -1;
    }

    printf("[ INFO ] Can NOT Find the user name\n");
    fclose(fp);
    return -1;
}

