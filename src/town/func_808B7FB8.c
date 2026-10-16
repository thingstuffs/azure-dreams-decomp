/* Relinked copy of town/func_80878260 (func_80878260.c); retail differs only at relocation sites. */
#include "common.h"

extern u8 D_00003F88[];
extern void func_80003720(s32 index);
extern s32 func_80003C70(u16 value);

/* Select the first table entry whose value check returns zero. */
void func_800037B8(void) {
    s32 index = 0;
    s32 offset = 0;

    while (func_80003C70(*(u16 *)&D_00003F88[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    func_80003720(index);
}
