#include<string>

typedef struct node
{
    unsigned long index;
    string name;
    string author;
    string desciption;
    struct node *prior;
    struct node *next
}book;

book *create_list(void);
