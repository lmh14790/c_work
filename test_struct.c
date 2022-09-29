#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#define AMOUNT 100000
#define MAXTITL 41
#define MAXAUTL 31
struct book {
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};
struct library{
    struct book books[AMOUNT];
    char name[MAXTITL];
};
union hold
{
   int digit;
   double bigfl;
   char letter;
};
typedef enum color{
red,yellow,blue,green
} color;
typedef enum {
red1,yellow2,blue2,green2
} color2;
typedef color color3;
void testStruct();
//不推荐使用
struct book getBook();
struct book *getBook1();
void testLibrary();
int main()
{
// testStruct();
color a;
enum color c;
color2 b;
color3 d;
testLibrary();  
return 0;
}
void testStruct(){
struct book book;
puts("输入书名");
gets(book.title);
puts("输入作者名称");
gets(book.author);
puts("输入价格");
scanf("%f", &book.value);
printf("名称：%s, 作者：%s, 价格：%f\n", book.title, book.author, book.value);  
}
struct book getBook(){
struct book book;
puts("输入书名");
gets(book.title);
puts("输入作者名称");
gets(book.author);
puts("输入价格");
scanf("%f", &book.value);
return book;
}
struct book *getBook1(){
struct book *book = (struct book *)malloc(sizeof(struct book));
puts("输入书名");
gets(book->title);
puts("输入作者名称");
gets(book->author);
puts("输入价格");
scanf("%f", &book->value);
return book;  
}
void testLibrary(){
    struct library lib;
    puts("输入图书馆名称");
    scanf("%s",lib.name);
    for (size_t i = 0; i < 10; i++)
    {
    lib.books[i] = *getBook1();
    printf("名称：%s, 作者：%s, 价格：%f\n", lib.books[i].title, lib.books[i].author, lib.books[i].value);  
    }
}
