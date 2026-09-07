#include "common.h"

extern s16 func_8025E01C(void *);

void func_808105EC(void *unused, void *data)
{
    s32 value;

    value = func_8025E01C(data);
    if (value > 0) {
        value = 0;
    }

    *(s32 *)((u8 *)data + 0x14) += 0x1D000;
    if (value < *(s16 *)((u8 *)data + 0xA)) {
        *(s16 *)((u8 *)data + 0xA) = value;
        *(s32 *)((u8 *)data + 0x14) = 0;
    }
}
