#include "common.h"

extern s32 func_800ABDBC(void);
extern u8 D_80170F20;
extern u8 D_80173B98;

void func_80173000(void *arg0)
{
    u8 *value;

    if (func_800ABDBC() != 0) {
        if (*(u8 *)((u8 *)arg0 + 0xA7) != 0) {
            value = &D_80173B98;
        } else {
            value = &D_80170F20;
        }
        *(u8 **)((u8 *)arg0 + 0x8C) = value;
    }
}
