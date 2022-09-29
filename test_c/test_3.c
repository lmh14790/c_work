#include<stdio.h>
void testDataOverFlow();
int main(){
    testDataOverFlow();
    sound();
    return 0;
}
void testDataOverFlow(){
    //-128 到 127 或 0 到 255 
    //-432%256 = -176  -176 = +80 //当余数不在范围内超出负数范围(为正数) 超出正数范围（为负数） 
    char testChar1 = -432, testChar2 = -130, testChar3 = 80, testChar4 = 1000; 
    printf("testChar1:%c-->testChar2:%c---->testChar3:%c--->testChar4:%c\n",testChar1,testChar2,testChar3,testChar4);
    //2 字节	-32,768 到 32,767
    //x mod y等于 x 减去 y 乘上 x与y的商的下界.
    // 以 -3 mod 2 举例:
    // -3 mod 2
    // = -3 - 2x(-3/2)
   // = -3 - 2x(-1.5)
   // = -3 - 2x(-2)
   // = -3 + 4 = 1
   // -32768 mod 65536
    short short1 = -32768, short2 = 32767, short3 = -32770, short4 = 720897;
    printf("short1:%hd-->short2:%hd---->short3:%hd--->short4:%hd\n",short1,short2,short3, short4);

    unsigned short ushort1 = -32768, ushort2 = 32767, ushort3 = -32770, ushort4 = 720897;
    printf("ushort1:%u-->short2:%u---->short3:%u--->short4:%u\n",ushort1,ushort2,ushort3, ushort4);
}