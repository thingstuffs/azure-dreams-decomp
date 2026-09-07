#include "common.h"

extern s32 func_800B28A0(void);
extern s32 D_800D0728[];
extern u8 D_80010AC4[];

void func_8003B7C8(void) {
    s32 index = func_800B28A0();
    volatile s32 *table = D_800D0728;
    s32 count = table[index];

    if (count > 0) {
        u8 *ptr = D_80010AC4;
        s32 i = 0;

        do {
            *ptr = 0;
            i++;
            ptr += 0x54;
        } while (i < count);
    }
}
