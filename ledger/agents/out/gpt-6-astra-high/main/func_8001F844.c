#include "common.h"

extern short D_80408EC8[];
extern short D_8040077C[];
extern void func_8003830C(int a, void *b);
extern void func_8007BF50(void *a, void *b);
extern int D_80010208;

/* Initialize the destination from templates, apply index data, and set the mode flag. */
void func_80406844(short *dest, int index, int mode)
{
    unsigned char index_data[16];
    short *dest_start;

    dest_start = dest;
    memcpy(dest_start, D_80408EC8, 0x200);
    memcpy(dest_start + 2, D_8040077C, 39);
    func_8003830C(index + 1, index_data);
    func_8007BF50(dest_start + 2, index_data);
    D_80010208 = (mode == 2);
}
