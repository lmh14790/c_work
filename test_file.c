#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 40 
#define CNTL_Z '\032' /* DOS文本文件中的文件结尾标记*/
#define SLEN  81 
#define BUFSIZE 1024
#define ARSIZE 1000
//page 373
void testReadFile(int argc, char * argv[]);
void testAddWord();
void testFseekAndFtell();
void testAppend();
void append(FILE *source, FILE *dest);
void testRandFile();
int main(int argc, char* argv[]){
// testFseekAndFtell();
// testAppend();
testRandFile();
return 0;
}
void testReadFile(int argc, char * argv[]){
    int ch;
    FILE *fp;
    long count  = 0;
    if(argc != 2){
        printf("usage: %s filename\n", argv[0]);
        exit(1);
    }
    if((fp = fopen(argv[1],"r")) == NULL){
        printf("Can't open %s\n", argv[1]);
        exit(1);
    }
    
    while((ch = getc(fp)) != EOF){
        putc(ch, stdout);
        count++;
    }
    fclose(fp);
    printf("file %s has %ld characters\n", argv[1],count);
}
void testAddWord(){
    FILE *fp;
    char words[MAX];
    if((fp = fopen("words","a+")) == NULL){
        fprintf(stdout, "不能打开\"words\"文件\n");
        exit(1);
    }
    puts("输入单词添加到文件：请按回车键");
    puts("首行输入回车键,退出程序");
    while(gets(words) != NULL && words[0] != '\0')
    fprintf(fp, "%s ", words);
    puts("文件内容");
    rewind(fp);
    while(fscanf(fp, "%s", words) == 1)
    puts(words);
    if(fclose(fp) != 0)
    fprintf(stderr, "关闭文件错误\n");
}
//reverse 文件内容
void testFseekAndFtell(){
   char file[SLEN];
   char ch;
   FILE *fp;
   long count, last;
   puts("输入文件名称");
   gets(file);
   //只读和二进制模式
   if((fp = fopen(file,"rb")) == NULL){
       printf("不能打开文件%s\n", file);
       exit(1);
   }
   fseek(fp, 0L, SEEK_END);//定位到文件末尾
   last = ftell(fp);
   for(count = 1L; count <= last; count++){
       fseek(fp, -count, SEEK_END);//回退
       ch = getc(fp);
       //针对dos
       if(ch != CNTL_Z && ch != '\r')
       putchar(ch);
       else if(ch == '\r')
       putchar('\n');
       else
       putchar(ch);
   }
   putchar('\n');
   fclose(fp);
}

void testAppend(){
    FILE *fa, *fs;//fa指向被追加文件 fs指向资源文件
    int files = 0;//追加文件的个数
    char file_app[SLEN];//被追加文件的名称
    char file_src[SLEN];//源文件的名称
    puts("输入目的文件的名称");
    gets(file_app);
    if((fa = fopen(file_app, "ab")) == NULL){
        fprintf(stderr, "不能打开文件%s\n", file_app);
        exit(2);
    }
    if(setvbuf(fa, NULL, _IOFBF, BUFSIZ) != 0){
     fputs("不能创建输出的buffer\n", stderr);
     exit(3);
    }
    puts("输入第一个资源文件的名称(空字符将会退出)");
    while(gets(file_src) && file_src[0] != '\0'){
        if(strcmp(file_src, file_app) == 0){
            fputs("不能给自己添加文件\n",stderr);
        } else if((fs = fopen(file_src,"rb")) == NULL){
            fprintf(stderr, "不能打开文件%s\n", file_src);
        } else {
            if(setvbuf(fs, NULL, _IOFBF, BUFSIZ) != 0){
                fputs("不能创建输入的buffer\n", stderr);
                continue;
            }
            append(fs, fa);
            if(ferror(fs) != 0)
            fprintf(stderr, "Error in reading file %s.\n", file_src);
            if(ferror(fa) != 0)
            fprintf(stderr, "Error in writing file %s.\n", file_app);
            fclose(fs);
            files++;
            printf("文件%s被添加\n", file_src);
            puts("请输入下个文件(空字符将会退出)");
        }
    }

    printf("追加了%d个文件\n", files);
    fclose(fa);
}

void append(FILE *source, FILE *dest){
    size_t bytes;
    static char temp[BUFSIZ];
    while((bytes = fread(temp, sizeof(char), BUFSIZ, source)) > 0)
    fwrite(temp, sizeof(char), bytes, dest);
}

void testRandFile(){
    double numbers[ARSIZE];
    double value;
    const char *file = "number.repository";
    int i;
    long pos ;
    FILE *repository;
    for(i = 0; i< ARSIZE; i++)
    numbers[i] = 100.0 * i + 1.0/(i+1);
    if((repository = fopen(file, "wb")) == NULL){
      fprintf(stderr, "不能写文件%s\n", file);
      exit(1);
    }
    fwrite(numbers, sizeof(double), ARSIZE, repository);
    fclose(repository);
    if((repository = fopen(file, "rb")) == NULL){
    fprintf(stderr, "不能读文件%s\n", file);
    exit(2);
    }
    printf("输入下个index 超出会退出 form 0 to %d\n", ARSIZE-1);
    scanf("%d",&i);
    while (i >= 0 && i< ARSIZE)
    {
    pos = (long) i*sizeof(double);
    fseek(repository, pos, SEEK_SET);
    fread(&value, sizeof(double), 1, repository);
    printf("当前的值为%f\n", value);
    printf("输入下个index 超出会退出\n");
    scanf("%d", &i);
    }
    fclose(repository);
    puts("完成");
}