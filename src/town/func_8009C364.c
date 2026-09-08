#include "common.h"

extern void func_8009A18C(void *);

void func_80099AC4(void *arg0)
{
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg0 + 0xA) - 1;
    *(u16 *)((u8 *)arg0 + 0xA) = temp_v0;
    if ((s16)temp_v0 < 0) {
        func_8009A18C(arg0);
    }
}
