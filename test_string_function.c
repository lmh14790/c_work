#include<stdio.h>
#include<string.h>
#define MSG "you must hava many talents. tell me some. "
#define LIM 5
#define LINELEN 81
void testString();
void diffArrayAndPointer();
void testFgets();
void testPuts();
void fit(char *string, unsigned int sz);
void testFit();
void testCommandParams(int, char *[]);
void getOkChars(const int, char []);
void testOkChars();
//page 308 常用的字符串函数
int main(int argc, char* argv[]){
// testString();
// diffArrayAndPointer();
// testFgets();
// testPuts();
// testFit();
// testCommandParams(argc, argv);
testOkChars();
return 0;
}

void testString(){
    char name[LINELEN];
    char talentes[LINELEN];
    int i;
    const char m1[40] = "Limit yourself to one line's worth. ";
    const char m2[] = "if you can't think of anything, fake it . ";
    const char *m3 = "\nEnough about me - what's your name? ";
    const char *mytal[LIM] = {"Adding numbers swiftly",
    "Multiplying accurately","Stashing data", "Following instructions to the letter","Understanding the c language"};
    printf("Hi! I'm Clyde the computuer." "I hava many talents.\n");
    printf("Let me tell you some of them .\n");
    puts("what were they? Ah, Yes, here's a partail list. ");
    for (int i = 0; i < LIM ; i++) puts(mytal[i]);
    puts(m3);
    gets(name);
    printf("Well, %s, %s \n", name, MSG); 
    printf("%s\n%s\n", m1, m2); 
    gets(talentes);
    puts("Let,s see if I've got that list: ");
    puts(talentes);
    printf("Thanks for the information, %s.\n", name);
    char *test = "我" "是测试的"              "字符串";
    puts(test);
}
//数组声明 和 指针声明的区别与联系 p286 数组初始化是从静态区拷贝了一个字符串给数组 指针初始化只是复制字符串的地址 
void diffArrayAndPointer(){
char heart[] = "I love Tillie!";
//数组可以修改单个的值 指针不可以
heart[4] = 'A';
char *head = "I love Tillie!";
//非法 应为所有的 I love Tillie! 程序内使用这个字符串的地方都是这个地址如果可以修改的话 会影响别的地方的使用 造成未知错误  可以编译 运行时会报错 74869 bus error
// head[4] = 'A';
puts("==========使用数组符号获取=========");
for(int i = 0; i < 6; i++){
putchar(heart[i]);
}
putchar('\n');
for(int i = 0; i < 6; i++){
putchar(head[i]); 
}
putchar('\n');
puts("==========使用指针加法获取=========");
for(int i = 0; i < 6; i++){
putchar(*(heart+i));
}
putchar('\n');
for(int i = 0; i < 6; i++){
putchar(*(head+i)); 
}
putchar('\n');

//只有指针才能使用增量运算
while(*head != '\0') putchar(*(head++));
}
#define MAX 81
void testFgets(){
char name[MAX];
char* ptr;
printf("Hi, what's your name?\n");
ptr = fgets(name, MAX, stdin);
fputs(ptr, stdout);
}
//测试
void testPuts(){
// char side_a[] = "SIDE A"; 
// //dont 不是字符串 没有'\0'结束符;
// char dont[] = {'W','O','W','!'};
// char side_b[] = "SIDE B";
// puts(dont); 
char note[] = "See you at the snack bar. ";
char *pt ;
pt = note;
puts (note);
puts (++pt);
note[7] = '\0';
puts(++pt);
}

void fit(char *string, unsigned int sz){
    if(strlen(string) > sz){
        *(string+sz) = '\0';
    }
}

void testFit(){
    char msg[] = "Hold on to your hats, hackers. ";
    puts(msg);
    fit(msg, 7);
    puts(msg);
    puts("Let's look at some more of the string. ");
    puts(msg+8);
}

void testCommandParams(int argc, char* argv[]){
int count ;
printf("the command line has %d arguments:\n", argc -1);
//参数0 为调用程序本身 此处为 ./test_string_function
for(count = 1; count < argc; count++){
    printf("%d: %s\n", count, argv[count]);
}
putchar('\n');
}

void getOkChars(const int sz, char result []){
  char ch;
  int i = 0; 
  do{
  ch = getchar();
  if(ch == EOF || i == sz) break;
  if(ch == '\n'){
   result[i] = 'H';
  } else if(ch == '\t'){
   result[i] = 'T';
  } else  if(ch == ' '){
  result[i] = 'N';
  } else {
  result[i] = ch; 
  }
  i++;
  }while(1);
  result[i] = '\0';
}
#define TEST 10
void testOkChars(){
 char result[TEST+1];
 puts("请输入字符");
 getOkChars(TEST, result);
 printf("当前的值为%s", result); 
}