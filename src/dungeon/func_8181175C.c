#include "common.h"

/* Initialize descriptor fields and set its high flag bit. */
void func_8002675C(void *descriptor)
{
    volatile s32 saved_settings;
    s32 settings;

    saved_settings = 0x8040F0;
    *(s8 *)((u8 *)descriptor + 1) = 0x28;
    settings = saved_settings;
    *(s8 *)((u8 *)descriptor + 3) = 0x18;
    *(s8 *)((u8 *)descriptor + 0xA) = 7;
    *(s8 *)((u8 *)descriptor + 2) = 0;
    *(s8 *)((u8 *)descriptor + 0xB) = 2;
    *(s32 *)((u8 *)descriptor + 4) = settings;
    *(u8 *)descriptor |= 0x80;
}
