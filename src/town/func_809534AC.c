#include "common.h"

extern s32 D_800814A0[3];

void func_800204AC(void *arg0) {
    void *temp_v1 = *(void **)((u8 *)arg0 + 0xC);

    if (*(s16 *)arg0 == 0 &&
        (*(u16 *)((u8 *)temp_v1 + 4) & 0x8000) != 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
