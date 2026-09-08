#include "common.h"

extern s32 D_800814A0[];

/* Subtracts the limit when available, otherwise marks the record and global flags. */
void func_800DB618(void *record) {
    s32 current = *(s32 *)((s8 *)record + 0x18);
    s32 limit = *(s32 *)((s8 *)record + 0x1C);

    if (current >= limit) {
        *(s32 *)((s8 *)record + 0x18) = current - limit;
        return;
    }
    *(u16 *)((s8 *)record - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
