#include "common.h"

extern u8 D_80701DFC[];
extern void func_807021C8(s32 index);
extern s32 func_80702714(u16 value);

void func_80702260(void) {
    s32 index = 0;
    s32 offset = 0;

    while (func_80702714(*(u16 *)&D_80701DFC[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    func_807021C8(index);
}
