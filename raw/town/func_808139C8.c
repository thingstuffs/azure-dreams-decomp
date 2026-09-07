#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct FiveWords {
    s32 words[5];
} FiveWords;

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern u8 D_8003C558[12];
extern u8 D_8052F2C8[];
extern u8 D_8028E170[];

void func_808139C8(FiveWords *arg0, s32 arg1)
{
    u8 *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, FiveWords, 0x20) = *arg0;
        FIELD(temp_v0, s32, 0x10) = (s32)D_8052F2C8;
        func_8003BC18(temp_v0, D_8003C558);
        temp_a0 = FIELD(temp_v0, u8 *, 8);
        temp_v1 = FIELD(temp_v0, u8 *, 0xC);
        FIELD(temp_a0, s32, 0) = 0x05380000;
        FIELD(temp_a0, s32, 4) = arg1;
        FIELD(temp_a0, s32, 8) = 0xFFE00000;
        FIELD(temp_v1, s16, 0x1E) = 0x1000;
        FIELD(temp_v1, s16, 0x1C) = 0x1000;
        FIELD(temp_v1, s32, 8) = (s32)D_8028E170;
        FIELD(temp_v1, s8, 4) = 0;
        FIELD(temp_v1, s8, 5) = 0;
        FIELD(temp_v1, s32, 0xC) = 0x808080;
        FIELD(temp_v1, u16, 0x14) = FIELD(temp_v1, u16, 0x14) | 0x80;
    }
}
