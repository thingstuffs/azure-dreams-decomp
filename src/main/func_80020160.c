#include "common.h"

extern u8 D_80408D40[][2];
extern s32 D_80408D44[];

extern void func_8004DDBC(void *arg0, s32 arg1, s32 *arg2);

void func_80020160(u8 *arg0) {
    s32 index;
    s32 offset;
    u8 (*table)[2];
    s32 *values;
    u8 slot;
    s32 *check;
    s32 *destination;
    s32 value;

    index = 0;
    table = D_80408D40;
    values = D_80408D44;
    offset = 0;
    do {
        slot = table[*(s32 *)(arg0 + 0x24)][index];
        check = *(s32 **)(*(u8 **)(arg0 + 0x60) + slot * 4 + 8);
        if (*check != 0) {
            func_8004DDBC(arg0 + (slot * 0xC + 4),
                          *(s32 *)((u8 *)D_80408D44 + 8 + offset), check);
        }
        slot = table[*(s32 *)(arg0 + 0x24)][index];
        *(*(s32 **)((u8 *)*(s32 **)(offset + *(s32 *)(arg0 + 0x60)) + 4)) =
            values[slot];

        destination = *(s32 **)(
            (u8 *)*(s32 **)(offset + *(s32 *)(arg0 + 0x60) + 8) + 4
        );
        slot = table[*(s32 *)(arg0 + 0x24)][index];
        value = values[slot];
        index += 1;
        *destination = value;
        offset += 4;
    } while (index < 2);
}
