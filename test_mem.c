static unsigned long int next = 1;//随机数种子
int rand0(){
    next = next * 1103514245 + 123456;
    return (unsigned int)(next/65536)%32768;
}