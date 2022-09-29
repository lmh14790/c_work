#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
const char *menu[] = {
"a - 添加一个新记录",
"d - 删除一个记录",
"q - 退出",
NULL
};
void testChoice();
int  getChoice(const char *greet, const char *choice[], FILE *in, FILE *out);
void testScanf();
int main(int argc, char *argv[]){
   testScanf();
}
void testChoice(){
int choice = 0;
FILE *in, *out;
if(!isatty(fileno(stdout))){
    fprintf(stderr,"不是一个terminal\n");
}
in = fopen("/dev/tty", "r");
out = fopen("/dev/tty", "w");
if(!in || !out){
fprintf(stderr,"打开/dev/tty失败\n");
return;  
}
do{
choice = getChoice("请输入一个选择:", menu, in, out);
fprintf(out, "选中结果为--->%c\n", choice);
} while(choice != 'q');
if(fclose(in) != 0){
 fprintf(stderr,"关闭输入流错误\n");
} else {
  in = NULL;
}
if(fclose(out) != 0){
 fprintf(stderr,"关闭输入流错误\n");
} else {
 out = NULL;
}
}
int  getChoice(const char *greet, const char *choice[], FILE *in, FILE *out){  
  fprintf(out,"调用开始---->\n");   
  int chosen = 0;
  int selected;
  const char **option;
  do {
   fprintf(out,"%s\n", greet);
   option = choice;
   while (*option)
   {
     fprintf(out,"%s\n", *option); 
     option++;
   }
   selected = getc(in);
   fflush(in);
   option = choice;
   while (*option)
   {  
     //*option[0] (*option)[0] option[0][0]
     if(selected == **option){
        chosen = 1;
        break;
     }
     option++;
   }
   if(!chosen){
    fprintf(out,"选择菜单错误,重新选择\n");
   }
  } while (!chosen);
 return selected;
}
void testScanf(){
  printf("输入数字格式为:\n%%d,%%d%%d %%d\n");
  int a, b,c,d;
  char f;
  scanf("%d,%d%d %d",&a,&b,&c,&d);
  scanf("%c", &f);
  printf("f的值为:%c换行符\n",f);
  printf("%d,%d,%d,%d\n",a,b,c,d);
}