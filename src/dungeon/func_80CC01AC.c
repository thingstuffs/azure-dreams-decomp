#include "common.h"

extern s32 func_800AB464(void);
extern u8 D_80170F20;
extern u8 D_80173B98;

void func_801739AC(void *arg0)
{
    u8 *value;

    if (func_800AB464() > 0) {
        if (*(u8 *)((u8 *)arg0 + 0xA7) != 0) {
            value = &D_80173B98;
        } else {
            value = &D_80170F20;
        }
        *(u8 **)((u8 *)arg0 + 0x8C) = value;
    }
}
