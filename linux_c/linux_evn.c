#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<sys/types.h>
#include<sys/utsname.h>
#include<pwd.h>
#include<syslog.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<math.h>
void testGetOpt(int, char *[]);
void testGetEnv(int, char *[]);
void testEnv();
void testTime();
void testTemFile();
void testUerInfo();
void testComputerInfo();
void testSyslog();
void testPriority();
void work();
int main(int argc, char *argv[]){
testPriority();
}

void testGetOpt(int argc , char *argv[]){
    int opt;
    char preChar = '\0';
    while((opt = getopt(argc, argv, ":if:lrt:")) != -1){   
       switch(opt){
        case 'i':
        case 'l':
        case 'r':
        printf("参数操作符:%c\n", opt);
        break;
        case 'f':
        printf("文件操作符:%c\t参数为:%s\n", opt, optarg);
        break;
        case 't':
        printf("文件操作符:%c\t参数为:%s\n", opt, optarg);
        break;
        case ':':
        printf("操作符:%c需要一个参数\n", preChar);
        break;
        default:
        printf("未知的操作符:%c\n", opt);
       }
    } 
}
void testGetEnv(int argc, char *argv[]){
    if(argc !=2 && argc !=3){
        printf("参数非法\n");
        return;
    }
    char *arg = argv[1], *value = getenv(arg);
    if(value){
        printf("环境变量%s的值为:%s\n", arg, value);
    } else {
        printf("环境变量%s没有值\n", arg); 
    }
    if(argc == 3){
        char data[1024*1024];
        sprintf(data, "%s=%s",arg, argv[2]);
        putenv(data);
        value = getenv(arg);
        if(value){
        printf("环境变量%s的值为:%s\n", arg, value);
        } else {
        printf("环境变量%s没有值\n", arg); 
        }
    }
}

void testEnv(){
    int i = 0;
    extern char **environ ;
    char **temp = environ;
    while (*temp)
    {
        printf("address->%p\n", temp);
        printf("%s\n", *temp);
        temp++;
    }
}

void testTime(){
time_t t;
time(&t);
struct tm *tm_ptr;
char gBuffer[128], lBuffer[128];
tm_ptr = gmtime(&t);
printf("格林尼治时间处理\n");
printf("%d:%d:%d %d-%d-%d\n",tm_ptr->tm_hour + 8, tm_ptr->tm_min, tm_ptr->tm_sec, tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday);
tm_ptr->tm_hour+=8;
printf("asctime: %s", asctime(tm_ptr));
printf("ctime: %s", ctime(&t));
strftime(gBuffer,256,"%A %d %B, %I:%S %p",tm_ptr);
printf("strftime: %s\n", gBuffer);
tm_ptr = localtime(&t);
printf("本地时间处理\n");
printf("%d:%d:%d %d-%d-%d\n",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday);
printf("asctime: %s", asctime(tm_ptr));
strftime(gBuffer,256,"%A %d %B, %I:%S %p",tm_ptr);
printf("strftime: %s\n", gBuffer);
}

void testTemFile(){
     char buffer[1024];
     char *fileName;
     FILE *temfp;
     fileName = tmpnam(buffer);
     printf("临时文件的名称为%s\n", fileName);
     temfp = tmpfile();
     if(temfp){
        printf("临时文件的名称为打开成功\n"); 
     }
     fclose(temfp);
}

void testUerInfo(){
    uid_t uid = getuid();
    gid_t gid = getgid();
    struct passwd *pw;
    printf("当前的登录用户为%s\n", getlogin());
    printf("用户id为:%d,组id为:%d\n", uid, gid);
    pw = getpwuid(uid);
    printf("用户名=%s, 密码=%s,uid=%d, gid=%d, home=%s, shell=%s\n", pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid, pw->pw_name, pw->pw_shell);
    pw = getpwnam("root");
    printf("用户名=%s, 密码=%s,uid=%d, gid=%d, home=%s, shell=%s\n", pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid, pw->pw_name, pw->pw_shell);
}

void testComputerInfo(){
char hostName[256];
struct utsname sysInfo;
if(gethostname(hostName, 255) != 0 || uname(&sysInfo) < 0){
    printf("获取系统信息错误\n");
    return;
}
printf("ip=%s\n", hostName);
printf("系统=%s,硬件=%s,ip=%s,版本号=%s,发行级别=%s\n", sysInfo.sysname, sysInfo.machine, sysInfo.nodename, sysInfo.release, sysInfo.version);
}

void testSyslog(){
    FILE *f;  
    if((f = fopen("测试","r")) == NULL){
    time_t t;
    time(&t);
    struct tm *tm_ptr;
    char gBuffer[128];
    tm_ptr = localtime(&t);
    strftime(gBuffer,256,"%A %d %B, %I:%S %p", tm_ptr);
    syslog(LOG_USER|LOG_ERR, "%s打开文件:%s失败\n", gBuffer, "测试");
    }
}
void testPriority(){
    struct rusage r_usage;
    struct rlimit r_limit;
    int priority;
    work();
    getrusage(RUSAGE_SELF, &r_usage);
    printf("cpu usage: user = %ld,%06d, system = %ld,%06d\n", r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,
    r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);
    priority = getpriority(PRIO_PROCESS, getpid());
    printf("当前的优先级为:%d\n", priority);
    getrlimit(RLIMIT_FSIZE, &r_limit);
    printf("当前的文件限制数为: soft = %llu, hard = %llu\n", r_limit.rlim_cur, r_limit.rlim_max);
    r_limit.rlim_cur = 2048;
    r_limit.rlim_max = 4096;
    printf("设置一个2k大小的文件限制\n");
    setrlimit(RLIMIT_FSIZE, &r_limit);
    work();
}

void work(){
    FILE *f;
    int i;
    double x = 4.5;
    f = tmpfile();
    for(i=0; i<10000 ; i++){
    fprintf(f,"这是一个测试输出\n");
    if(ferror(f)){
     fprintf(stderr,"往临时文件写发生错误\n");
     return;    
    }   
    }
    for ( i = 0; i <1000000; i++)
    {
        x = log(x*x + 3.21);
    }
    
}
