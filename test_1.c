#include <stdio.h>
#include <string.h>
#include <limits.h>
//page 68 70 71占位符
#define DENSITY 62.4 
#define PAGES -931
#define UPAGES 931
#define BLURB "Authentic imitation! "
#define EPAGES 336
#define WORDS 65534
#define WORDS2 65618
void showPrinf(void);
void showFloat(void);
void showFlag(void);
void showStr(void);
//转型错误
void showErrorNum(void);
//转型失败 page 75
void showErrorFloat(void);

void scanfTest(void);
//测试“%*d”
void printfTestUniqeChar(void);
//测试“%*d”
void scanfTestUniqeChar(void);
int main(){
  showErrorNum();
   return 0;
}
void showPrinf(){
printf("d*%d*\n", PAGES);
printf("d*%d*\n", UPAGES);
printf("2d*%2d*\n", PAGES);
printf("2d*%2d*\n", UPAGES);
printf("10d*%10d*\n", PAGES);
printf("10d*%10d*\n", UPAGES);
printf("-10*%-10d*\n", PAGES);
printf("-10*%-10d*\n", UPAGES);
printf("+10*%+10d*\n", PAGES);
printf("+10*%+10d*\n", UPAGES);
printf(" 10*% 10d*\n", PAGES);
printf(" 10*% 10d*\n", UPAGES);
//使用0填充
printf("010*%010d*\n", PAGES);
printf("010*%010d*\n", UPAGES);
}
void showFloat(){
const double RENT = 3852.86;    
printf("f*%f*\n", RENT);
printf("e*%e*\n", RENT);
printf("1.2f*%1.2f*\n", RENT);
printf("3.1f*%3.1f*\n", RENT);
printf("10.3f*%10.3f*\n", RENT);
printf("10.3e*%10.3e*\n", RENT);
printf("+4.2f*%+4.2f*\n", RENT);
printf("010.2f*%010.2f*\n", RENT);
}

void showFlag(void){
    printf("%x %X %#x %#X\n",31,31,31,31);
    printf("**%d**% d**% d**\n",42,42,-42);
    printf("**%5d**%5.2d**%05d**%-05.3d**\n",6,6,6,6);
}

void showStr(void){
printf("/%2s/\n", BLURB);
printf("/%30s/\n", BLURB);
printf("/%24.5s/\n", BLURB);
printf("/%-24.5s/\n", BLURB);
}

void showErrorNum(void){
short num = EPAGES;
short mnum = -EPAGES;
printf("num as short and unsigned short: %hd %hu\n", num, num);
printf("-num as short and unsigned short: %hd %hu\n", mnum, mnum);
printf("num as int and char: %d %c\n", num, num);
//当前数字和最大数值（SHRT_MIN -32768  SHRT_MAX +32767  65536）取余  余数在0-32767为整数 32768-65535 为负数 65535为-1 即65535-65536 = -1
printf("words as int short and char: %d  %hd %c \n", WORDS, WORDS, WORDS);
printf("words2 as int short and char: %d %hd %c \n", WORDS2, WORDS2, WORDS2);
}
//page 75
void showErrorFloat(void){
    float n1  = 3.0;
    double n2 = 3.0;
    long n3 = 2000000000;
    long n4 = 1234567890;
    printf("%.1e %.1e %.1e %.1e\n", n1, n2, n3, n4);
    printf("%ld %ld \n", n3, n4);
    printf("%ld %ld %ld %ld\n", n1, n2, n3, n4);
}

void scanfTest(void){
    int age;
    float assets;
    char pet[30];
    printf("输入 年龄 资产 宠物\n");
    scanf("%d %f", &age, &assets);
    scanf("%s", pet);
    printf("%d %.2f %s\n", age, assets, pet);
}

void printfTestUniqeChar(void){
    //*为宽度占位符
  unsigned width, precision;
  int number = 256;
  double weight = 242.6;
  char names[50];
  char sNames[50];
  printf("输入字符位数\n");
  scanf("%d", &width);
  printf("数字为:%*d: \n", width, number);
  printf("输入字符位数和小数位数\n");
  scanf("%d %d", &width, &precision);
  printf("重量为=%*.*f\n", width, precision, weight);
  printf("输入名字\n");
  scanf("%s", names);
  printf("名字为:\"%s\"\n",names);
  printf("输入姓氏\n");
  scanf("%s", sNames);
  printf("姓氏为:\"%s\"\n",sNames);
}

void scanfTestUniqeChar(void){
    //*跳过输入的头两位字符
   int n;
   printf("输入三个数字\n");
   int b = scanf("%*d %*d %d", &n);
   printf("最后一个数字为:%d\n", n);
   printf("scanf:%d\n", b);
}
