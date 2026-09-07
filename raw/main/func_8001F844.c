#include "common.h"

extern short D_80408EC8[];
extern short D_8040077C[];
extern void func_8003830C(int a, void *b);
extern void func_8007BF50(void *a, void *b);
extern int D_80010208;

void func_80406844(short *dest, int index, int mode)
{
    unsigned char work[16];
    short *dst;

    dst = dest;
    memcpy(dst, D_80408EC8, 0x200);
    memcpy(dst + 2, D_8040077C, 39);
    func_8003830C(index + 1, work);
    func_8007BF50(dst + 2, work);
    D_80010208 = (mode == 2);
}
