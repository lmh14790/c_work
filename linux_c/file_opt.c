#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<time.h>
#include<dirent.h>
#include<sys/mman.h>
#include<fcntl.h>
#define STDIN 0
#define STDOUT 1
#define STDERROR 2
#define BUFFER 128
#define SPACE -30
#define MAX_LENGTH 100
#define  SIZE(m,n) (sizeof(m)*n)
static const char *actionMap[8] = {
  "", "x","w","wx","r","rx","rw","rwx"
};
typedef struct 
{
  int index;
  char array[24];
} RECORD;
void testWriteCall();
void testReadCall();
void copyFile(int argc, char *argv[]);
void testFile(int argc, char *argv[]);
void testChmod(int argc, char *argv[]);
void testChown(int argc, char *argv[]);
void testAddRemoveDir(int argc, char *argv[]);
void testChangeDir(int argc, char *argv[]);
void sanfDir(int argc, char *argv[]);
void modeStr(__uint32_t flage, char *dest);
void testMmap(int argc, char *argv[]);
int main(int argc, char *argv[]){
  testAddRemoveDir(argc, argv);
  return 0;
}
void testWriteCall(){
const char *stdOut = "这是一个输出测试\n", *errOut = "标准输出发生未知错误\n";
const size_t stdCount = strlen(stdOut), errCount  =  strlen(errOut);
if(write(STDOUT, stdOut, stdCount) != stdCount){
    write(STDERROR, errOut, errCount);
}
}

void testReadCall(){
    char buffer[BUFFER];
    int  readCount;
    readCount = read(STDIN, buffer, BUFFER);
    if(readCount == -1){
        write(STDERROR, "读取标准输入失败\n", strlen("读取标准输入失败\n"));
    }
    if(write(STDOUT, buffer, readCount) != readCount){
        write(STDERROR, "输出标准输出失败\n", strlen("输出标准输出失败\n")); 
    }
}

void copyFile(int argc, char *argv[]){
    if(argc < 3){
    write(STDERROR, "参数非法\n", strlen("参数非法\n"));
    return;
    }
    char *src =  argv[1], *dest = argv[2];
    int srcFile, destFile;
    if((srcFile = open(src, O_RDONLY, S_IRUSR)) <= 0){
      int size = strlen("文件:") + strlen(argv[1]) + strlen("打开失败\n")+1;
      char temp[size];
      memset(temp, '\0', size);
      strcat(temp, "文件:");
      strcat(temp, argv[1]);
      strcat(temp, "打开失败\n");
      write(STDERROR, temp, strlen(temp));
      return;  
    }
    if((destFile = open(dest, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR)) <= 0){
      int size = strlen("文件:") + strlen(argv[2]) + strlen("打开失败\n")+1;
      char temp[size];
      memset(temp, '\0', size);
      strcat(temp, "文件:");
      strcat(temp, argv[2]);
      strcat(temp, "打开失败\n");
      write(STDERROR, temp, strlen(temp));
      return;   
    }
    char buffer[BUFFER];
    size_t size;
    while ((size = read(srcFile, buffer, BUFFER)) > 0)
    {
        write(destFile, buffer, size);
    }
    if(close(srcFile) != 0){
      int size = strlen("文件:") + strlen(argv[1]) + strlen("关闭失败\n")+1;
      char temp[size];
      memset(temp, '\0', size);
      strcat(temp, "文件:");
      strcat(temp, argv[1]);
      strcat(temp, "关闭失败\n");
      write(STDERROR, temp, strlen(temp));
    }
    if(close(destFile) != 0){
      int size = strlen("文件:") + strlen(argv[2]) + strlen("关闭失败\n")+1;
      char temp[size];
      memset(temp, '\0', size);
      strcat(temp, "文件:");
      strcat(temp, argv[2]);
      strcat(temp, "关闭失败\n");
      write(STDERROR, temp, strlen(temp)); 
    }
}

void testFile(int argc, char *argv[]){
   if(argc < 2){
    printf("参数非法\n");
    return;
    }
 struct stat dest;
 stat(argv[1], &dest);
 switch(dest.st_mode & S_IFMT){
    case S_IFBLK:
    printf("%s是特殊的设备块\n",argv[1]);
    break;
    case S_IFDIR:
    printf("%s是路径\n",argv[1]);
    break;
    case S_IFCHR:
    printf("%s是特殊的字符设备\n",argv[1]);
    break;
    case S_IFIFO:
    printf("%s是管道\n",argv[1]);
    break;
    case S_IFREG:
    printf("%s是文件\n",argv[1]);
    break;
    case S_IFLNK:
    printf("%s是链接\n",argv[1]);
    break;
    case S_IFSOCK:
    printf("%s是socket\n",argv[1]);
    break;
    default:
    printf("%s是文件标识\n",argv[1]);

 }
 struct tm *tm_now;
 tm_now = localtime(&dest.st_atimespec.tv_sec); 
 char datetime[BUFFER];
 strftime(datetime, BUFFER, "%Y-%m-%d %H:%M:%S", tm_now);
 printf("now datetime : %s\n", datetime);
}

void testChmod(int argc, char *argv[]){
    if(argc < 2){
    printf("参数非法\n");
    return;
    }
   if(chmod(argv[1], 0722) != 0){
      printf("%s修改mode权限失败\n",argv[1]);
   } 
}

void testChown(int argc, char *argv[]){
    if(argc < 2){
    printf("参数非法\n");
    return;
    }
    if(chown(argv[1], 501, 20) != 0){
      printf("%s修改mode数组失败\n",argv[1]);
   } 
}

void testAddRemoveDir(int argc, char *argv[]){
    if(argc < 3){
    fprintf(stderr, "参数非法\n");
    return;
    }
    if(argv[1][1] == 'm'){
       if(mkdir(argv[2], 0733) != 0){
        printf("%s目录创建失败\n",argv[2]);
       }
    } else {
     if(rmdir(argv[2]) != 0){
        printf("%s目录删除失败\n",argv[2]);
       }
    }
}

void testChangeDir(int argc, char *argv[]){
   if(argc < 2){
    fprintf(stderr, "参数非法\n");
    return;
    }
    if(chdir(argv[1]) != 0){
    fprintf(stderr, "cd到目录:%s失败\n", argv[1]);
    return;
    }
    char buffer[BUFFER];
    memset(buffer, '\0', BUFFER);
   if(getcwd(buffer, BUFFER) == NULL){
    fprintf(stderr, "获取目录:%s失败\n", argv[1]);
    return;
   }
   printf("当前的目录为:%s\n", buffer);
}

void sanfDir(int argc, char *argv[]){
    if(argc < 2){
    fprintf(stderr, "参数非法\n");
    return;
    }
    DIR *current;
    if((current = opendir(argv[1])) == NULL){
        fprintf(stderr, "打开目录%s失败\n", argv[1]);
        return;
    }
    struct dirent *dirent;
    printf("%*s\t%s\t%s\n",SPACE,"文件名","文件类型","文件权限");
    while ((dirent = readdir(current)) != NULL)
    { 
    char mod[BUFFER];
    memset(mod,'\0',BUFFER); 
    struct stat dest;
    switch(dirent->d_type){
    case DT_BLK:
    printf("%*s\tDe\n",SPACE,dirent->d_name);
    break;
    case DT_DIR:
    stat(dirent->d_name, &dest);
    modeStr(dest.st_mode, mod);
    printf("%*s\tD\t%s\n",SPACE,dirent->d_name, mod);
    break;
    case DT_CHR:
    printf("%*s\tC\n",SPACE,dirent->d_name);
    break;
    case DT_FIFO:
    printf("%*s\tP\n",SPACE,dirent->d_name);
    break;
    case DT_REG:
    stat(dirent->d_name, &dest);
    modeStr(dest.st_mode, mod);
    printf("%*s\tF\t%s\n",SPACE,dirent->d_name, mod);
    break;
    case DT_LNK:
    printf("%*s\tL\n",SPACE,dirent->d_name);
    break;
    case DT_SOCK:
    printf("%*s\tS\n",SPACE,dirent->d_name);
    break;
    default:
    printf("%*s\tN\n",SPACE,dirent->d_name);

 }     
}
    closedir(current);
    free(dirent);
    dirent = NULL;
}

void modeStr(__uint32_t flage, char *dest){
   int u = (flage & S_IRWXU) >> 6;
   int g = (flage & S_IRWXG) >> 3;
   int o = (flage & S_IRWXO);
   sprintf(dest, "%03s-%03s-%03s",actionMap[u],actionMap[g],actionMap[o]);
}
void testMmap(int argc, char *argv[]){
 if(argc < 1){
  printf("参数异常\n");
  return;
 } 
 RECORD record, *mapped;
 int i, f;
 FILE *fp;
 if((fp = fopen(argv[1],"wb+")) == NULL){
  printf("文件打开失败%s\n", argv[1]);
 }
 for (size_t i = 0; i < MAX_LENGTH; i++)
 {
    record.index = i;
    sprintf(record.array,"RECORD-%d", i);
    fwrite(&record, SIZE(RECORD,1), 1, fp);
 }
 fclose(fp);
 fp = fopen(argv[1],"rb+");
 fseek(fp, SIZE(RECORD,43), SEEK_SET);
 fread(&record, SIZE(RECORD,1), 1, fp);
 record.index = 143;
 sprintf(record.array,"RECORD-%d", 143);
 fseek(fp, SIZE(RECORD,43), SEEK_SET);
 fwrite(&record, SIZE(RECORD,1), 1, fp);
 fclose(fp);
 f = open(argv[1], O_RDWR);
 mapped = (RECORD *)mmap(0, SIZE(RECORD,MAX_LENGTH), PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);
 mapped[43].index = 243;
 sprintf(mapped[43].array,"RECORD-%d", mapped[43].index);
 msync(mapped, SIZE(RECORD,MAX_LENGTH), MS_ASYNC);
 munmap(mapped, SIZE(RECORD,MAX_LENGTH));
 close(f);
}