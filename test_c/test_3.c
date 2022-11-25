#include<stdio.h>
void testDataOverFlow();
int main(){
    testDataOverFlow();
    return 0;
}
void testDataOverFlow(){
    //-128 到 127 或 0 到 255 
    //-432%256 = -176  -176 = +80 //当余数不在范围内超出负数范围(为正数) 超出正数范围（为负数） 
    char testChar1 = -432, testChar2 = -130, testChar3 = 80, testChar4 = 896; 
    printf("testChar1:%c-->testChar2:%c---->testChar3:%c--->testChar4:%c\n",testChar1,testChar2,testChar3,testChar4);
    printf("testChar1:%u-->testChar2:%u---->testChar3:%u--->testChar4:%u\n",testChar1,testChar2,testChar3,testChar4);
    //2 字节	-32,768 到 32,767
    //取模和取余的区别  x和y正负号一样时结果一样
    //x和y不一样时rem 函数结果的符号和 x 的一样，而 mod 和 y 一样。
    //这是由于这两个函数的生成机制不同，取余 函数采用 fix函数，而 取模 函数采用了 floor 函数（fix 函数向 0 方向舍入，floor 函数向无穷小方向舍入)
    //取余运算时（-10/3）= -3.3333 fix(-3.3333) = -3 结果为 （-10%3）= -1  -10-(-3*3) = -1
    //取模运算时（-10/3）= -3.3333 floor(-3.3333) = -4 结果为 （-10%3）= 2 -10-(-3*4) = 2
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