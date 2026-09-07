#include "common.h"

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 f10;
    u8 f11;
} S_80084478;

extern S_80084478 D_80084478[16];

/* Initializes the D_80084478 array of 16 fixed-size (12-byte) records with
 * constant template values; each entry's offset-9 byte is set to index*16. */
void func_80052A20(void)
{
    s32 i;
    S_80084478 *p;

    p = D_80084478;
    i = 0;
    do {
        p->f0 = 0xC0;
        p->f1 = 0x2C;
        p->f2 = 0;
        p->f3 = 0;
        p->f4 = 0xE;
        p->f6 = 0x7080;
        p->f8 = 0;
        p->f9 = i << 4;
        p->f10 = 0xFC;
        p->f11 = 0x10;
        i++;
        p++;
    } while (i < 16);
}
