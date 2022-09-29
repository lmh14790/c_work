#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<ndbm.h>
// #include<gdbm-ndbm.h>
#define FACTOR 1024UL
#define KB FACTOR*1
#define MB FACTOR*KB
#define GB FACTOR*MB
#define TB FACTOR*GB
typedef struct 
{
  char miscChars[16];
  int  anyInter;
  char moreChars[48];
} TestData;
#define TRANS(ANY) ((TestData *) ANY)
const char *file_name = "lock.test";
const char *db_file = "debm1_test";
const int items_used = 3;
void testMaxMemory();
void testAssignErroMemory();
void testSynchronizedFile();
void testLockPartFile();
void testDbm();
int main(int argc, char *argv[]){
 testDbm();
}

void testMaxMemory(){
  char *buffer;
  size_t size = 1;
  while ((buffer = (char *) malloc(size*(TB)*sizeof(char))) != NULL && size <= 10)
  {
   sprintf(buffer, "当前分配内存大小综合为%luTB\n", size);
   printf("%s\n", buffer);
   size++;
  }  
}
void testAssignErroMemory(){
  char *some_memory, *scan_ptr;
  if((some_memory = (char *)malloc(FACTOR)) == NULL){
    printf("分配内存错误\n");
    return;
  }
  scan_ptr = some_memory;
  size_t size = 0;
  while (1)
  {  size++;
     *scan_ptr = 'a';
     scan_ptr++;
     printf("当前使用的内存位置为%lu\n", size);
  }
  
}

void testSynchronizedFile(){
   int file_desc, tries = 10;
   while(tries--){
     file_desc = open(file_name, O_RDWR | O_CREAT | O_EXCL, 0444);
     if(file_desc == -1){
      printf("%d - %s文件已经存在,进程挂起\n", getpid(), file_name);
      sleep(3);
     } else {
       printf("%d - 具有执行权限\n", getpid());
       sleep(2);
       close(file_desc);
       unlink(file_name);
       sleep(1);
     }
   }

}
void testLockPartFile(){
int fileDesc, byteCount, res;
const char *byteToWrite = "A";
struct flock lock1, lock2;
if(!(fileDesc = open(file_name, O_RDWR | O_CREAT, 0666))){
  fprintf(stderr, "读写模式打开文件:%s错误\n", file_name);
  return;
}
for (byteCount = 0; byteCount < 100; byteCount++)
{
 write(fileDesc, byteToWrite, strlen(byteToWrite));
}
lock1.l_type = F_RDLCK;
lock1.l_whence = SEEK_SET;
lock1.l_start = 10;
lock1.l_len = 20;
lock2.l_type = F_WRLCK;
lock2.l_whence = SEEK_SET;
lock2.l_start = 40;
lock2.l_len = 10;
printf("当前进程为:%d,文件%s锁定\n", getpid(), file_name);
if((res = fcntl(fileDesc, F_SETLK, &lock1)) == -1) fprintf(stderr, "区域1锁定失败\n");
if((res = fcntl(fileDesc, F_SETLK, &lock2)) == -1) fprintf(stderr, "区域2锁定失败\n");
sleep(60);
printf("当前进程为:%d,关闭文件%s\n", getpid(), file_name);
close(fileDesc);
}

void testDbm(){
 TestData items[items_used], itemRetrieved;
 char keyToUse[128];
 int i, result;
 datum kye, data;
 DBM *dbmPr;
 dbmPr = dbm_open(db_file, O_RDWR | O_CREAT, 0666);
 if(!dbmPr){
  fprintf(stderr,"打开数据库%s失败\n", db_file);
  return;
 }
 memset(items,'\0', sizeof(items));
 strcpy(items[0].miscChars, "第1个");
 items[0].anyInter = 10;
 strcpy(items[0].moreChars, "测试1");
 strcpy(items[1].miscChars, "第2个");
 items[1].anyInter = 15;
 strcpy(items[1].moreChars, "测试2");
 strcpy(items[2].miscChars, "第3个");
 items[2].anyInter = 5;
 strcpy(items[2].moreChars, "测试3");
 for (size_t i = 0; i < 3; i++)
 {
  sprintf(keyToUse, "%s %s %d", items[i].miscChars, items[i].moreChars,  items[i].anyInter);
  kye.dptr = keyToUse;
  kye.dsize = strlen(keyToUse);
  data.dptr = &items[i];
  data.dsize = sizeof(items[i]);
  fprintf(stdout,"插入数据%s\n", (char *)kye.dptr);
  if((result = dbm_store(dbmPr, kye, data, DBM_REPLACE)) != 0){
  fprintf(stderr,"插入数据%s失败\n", (char *)kye.dptr);
  return;
  }
 }
//  sprintf(keyToUse, "第2个 测试2 15");
//  kye.dptr = keyToUse;
//  kye.dsize = strlen(keyToUse);
//  data = dbm_fetch(dbmPr, kye);
//  if(data.dptr){
//  fprintf(stdout,"查询数据:%s成功\n", (char *)kye.dptr);
//  memcpy(&itemRetrieved, data.dptr, data.dsize);
//  printf("recieve item - %s %d %s\n", itemRetrieved.miscChars, itemRetrieved.anyInter, itemRetrieved.moreChars);
//  printf("fetch item - %s %d %s\n", TRANS(data.dptr)-> miscChars, TRANS(data.dptr)->anyInter, TRANS(data.dptr)->moreChars);
//  } else {
//  fprintf(stderr,"查询数据失败:%s\n", (char *)kye.dptr);
//  }

 printf("浏览所有数据======\n");
 for(kye = dbm_firstkey(dbmPr); kye.dptr; kye = dbm_nextkey(dbmPr)){
  data = dbm_fetch(dbmPr, kye); 
 if(data.dptr){
  printf("检索数据 - %s %d %s\n", TRANS(data.dptr)-> miscChars, TRANS(data.dptr)->anyInter, TRANS(data.dptr)->moreChars);
 } else {
 fprintf(stderr,"检索数据失败%s\n", (char *)kye.dptr);
 }
 dbm_delete(dbmPr, kye);
 }
 dbm_close(dbmPr);
}