#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 40
#define LINE 20
#define BUFFER 8
void testFile();
void testFgetsAndFputs();
//可以处理二进制文件
void copyFileGetc(int argc, char *argv[]);
//只能处理文本文件
void copyFileGets(int argc, char *argv[]);
//可以处理二进制文件
void copyFileFread(int argc, char *argv[]);
int main(int argc, char *argv[]){
  copyFileFread(argc, argv);
  return 0;
}
void testFile(){ 
  FILE *fp;
  char buffer[MAX];
  memset(buffer, '\0', MAX);
  if((fp = fopen("words", "a+")) == NULL){
    fprintf(stdout, "打开文件错误\n");
    return;
  }
  puts("输入字符到文件中去,按回车键");
  puts("每行首字母为0时退出循环");
  while (gets(buffer) != NULL && buffer[0] != '\0')
  {
    fprintf(fp, "%s\n", buffer);
  }
  puts("输出文件内容:");
  rewind(fp);
  while (fscanf(fp, "%s", buffer) == 1)
  {
    puts(buffer);
  }
  if(fclose(fp) != 0){
    fprintf(stderr,"关闭文件失败\n");
  }
}
void testFgetsAndFputs(){
  char line[LINE];
  while (fgets(line, LINE, stdin) != NULL && line[0] != '\n')
  {
   fputs(line,stdout);
  }
}


void copyFileGetc(int argc, char *argv[]){
    if(argc < 3) {
      printf("参数错误\n");
      return;
    }
    char *srcFile = argv[1], *destFile = argv[2];
    FILE *srcFp, *destFp;
    if((srcFp = fopen(srcFile, "rb")) == NULL){
      printf("源文件:%s打开错误\n", srcFile);
      return;
    }
     if((destFp = fopen(destFile, "wb")) == NULL){
      printf("目标件:%s打开错误\n", destFile);
      return;
    }
    int temp;
    while((temp = getc(srcFp)) != EOF)
    {
      putc(temp, destFp );
    }
    if(fclose(srcFp) != 0){
        printf("源文件:%s关闭错误\n",srcFile);
        return;
    }
      if(fclose(destFp) != 0){
        printf("目标文件:%s关闭错误\n",destFile);
        return;
    }
}

void copyFileGets(int argc, char *argv[]){
    if(argc < 3) {
      printf("参数错误\n");
      return;
    }
    char *srcFile = argv[1], *destFile = argv[2];
    FILE *srcFp, *destFp;
    if((srcFp = fopen(srcFile, "rb")) == NULL){
      printf("源文件:%s打开错误\n", srcFile);
      return;
    }
     if((destFp = fopen(destFile, "wb")) == NULL){
      printf("目标件:%s打开错误\n", destFile);
      return;
    }
    char temp[BUFFER];
    while(fgets(temp, BUFFER, srcFp) != NULL)
    {
     fputs(temp, destFp);
    }
    if(fclose(srcFp) != 0){
        printf("源文件:%s关闭错误\n",srcFile);
        return;
    }
      if(fclose(destFp) != 0){
        printf("目标文件:%s关闭错误\n",destFile);
        return;
    }
}

void copyFileFread(int argc, char *argv[]){
    if(argc < 3) {
      printf("参数错误\n");
      return;
    }
    char *srcFile = argv[1], *destFile = argv[2];
    FILE *srcFp, *destFp;
    if((srcFp = fopen(srcFile, "rb")) == NULL){
      printf("源文件:%s打开错误\n", srcFile);
      return;
    }
     if((destFp = fopen(destFile, "wb")) == NULL){
      printf("目标件:%s打开错误\n", destFile);
      return;
    }
    char temp[BUFFER];
    while(fread(temp, sizeof(char), BUFFER, srcFp) > 0)
    {
     fwrite(temp, sizeof(char), BUFFER, destFp);
    }
    if(fclose(srcFp) != 0){
        printf("源文件:%s关闭错误\n",srcFile);
        return;
    }
      if(fclose(destFp) != 0){
        printf("目标文件:%s关闭错误\n",destFile);
        return;
    }
}