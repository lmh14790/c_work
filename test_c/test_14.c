#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXTITLE 128
#define MAXAUTHOR 128
#define MAXBOOKS 10
typedef struct{
char title[MAXTITLE];
char author[MAXAUTHOR];
float price;
} BOOK;
void  putAndShowBook(int argc, char *argv[]);
static void  showBookList(int size, BOOK *bookshelf);
int main(int argc, char *argv[]){
putAndShowBook(argc, argv);
}
void putAndShowBook(int argc, char *argv[]){ 
 BOOK bookshelf[MAXBOOKS];
 int historyCount = 0;
 int index, filecount;
 FILE *library;
 int bookSize = sizeof(BOOK);
 if((library = fopen("library.dat", "a+b")) == NULL){
  printf("打开文件:%s失败\n", "library.dat");
  return;
 }
 rewind(library);
 historyCount = fread(bookshelf, bookSize, MAXBOOKS, library);
 showBookList(historyCount, bookshelf);
  filecount = historyCount;
  if(historyCount == MAXBOOKS){
    printf("已经达到最大的存储数量\n");
    return;
  }
 puts("添加新书了");
 while (1)
 {
   char end;
   puts("输入新书的名称");
   scanf("%s", bookshelf[filecount].title);
   puts("输入新书的作者");
   scanf("%s", bookshelf[filecount].author);
   puts("输入新书的价格");
   scanf("%f", &bookshelf[filecount].price);
   puts("是否继续 Y OR N");
   fflush(stdin);
   scanf("%c", &end);
   filecount++;
   if(end == 'N' || filecount == MAXBOOKS){
    puts("退出");
    break;
   }
 }
 if(filecount > 0){
  showBookList(filecount, bookshelf);
 } else {
  puts("没有输入书籍,图书馆为空");
 }

 fwrite(&bookshelf[historyCount], bookSize, filecount- historyCount, library);
 
 if(fclose(library) != 0){
   printf("关闭文件:%s失败\n", "library.dat");
 }
}

void  showBookList(int size, BOOK *bookshelf){
  puts("当前的图书列表\n");
  for (size_t i = 0; i < size; i++)
  {
    printf("当前书的名称:%s,\t作者%s,\t价格:%f\n", bookshelf[i].title, bookshelf[i].author, bookshelf[i].price);
  }
}