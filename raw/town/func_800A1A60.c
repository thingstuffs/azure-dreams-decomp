#include "common.h"

extern u32 D_8009EF88;

typedef struct {
    s32 words[0x15];
} Record84;

extern Record84 D_80100AF8;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_8009F1C0(void *arg0, void *arg1)
{
    u8 state;
    void *callback;

    FIELD(arg1, s8, 0x14) = 4;
    callback = &D_8009EF88;
    FIELD(arg1, s8, 0x15) = 0;
    state = FIELD(arg0, u8, 0x4D);
    FIELD(arg0, void *, 0x50) = callback;
    FIELD(arg0, s16, 0x6C) = 8;

    if (state == 0x13) {
        Record84 *records = (Record84 *)0x80010A80;
        u8 *table = (u8 *)0x80010000;

        
        D_80100AF8 = records
            [table[FIELD(arg0, u8, 0x95) * 4 + 0x983] & 0x3F];
    }
}
