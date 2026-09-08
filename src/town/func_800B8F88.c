#include "common.h"

extern void func_800B65D8(s32 arg0, s16 arg1);
extern void func_800B6508(void *arg0);
extern s32 D_800B6578[];

void func_800B66E8(void *arg0) {
    s16 temp_a1;

    temp_a1 = *(s16 *)((u8 *)arg0 + 0xE);
    if (temp_a1 < 5) {
        func_800B65D8(*(s32 *)((u8 *)arg0 + 0x98), temp_a1);
        *(u16 *)((u8 *)arg0 + 0xE) = *(u16 *)((u8 *)arg0 + 0xE) + 1;
        return;
    }
    func_800B6508(arg0);
    *(void **)arg0 = &D_800B6578[0];
}
