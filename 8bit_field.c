#include <stdio.h>
#define WORD unsigned int 
#define BYTE unsigned char

WORD field_addition(WORD A, WORD B);

int main()
{
    /* 
    printf("Hello world!\n");
    return 0; 
    */

    WORD test1 = 0x01; 
    WORD test2 = 0x03;
    WORD test3 = field_addition(test1, test2);
    // printf("%02x\n", test3);
    
    unsigned char a = 0xff;
    printf("%02x\n", a);
    a <<= 1;
    printf("%02x\n", a);


    return 0;
}

WORD field_addition(WORD A, WORD B)
{
    return A^B;
}

BYTE x_time(BYTE b, BYTE n)
{
    int i;
    BYTE temp = 0, mask = 0x01;

    for(int i = 0; i < 8; i++) {
        if(n & mask)
            temp ^= b;
        
        if(b & 0x80)
            b = (b<<1)^0x1B;
        else
            b<<=1;
        mask <<=1;
        
    }

    return temp;
}
