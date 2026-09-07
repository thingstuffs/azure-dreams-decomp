#include "common.h"

extern void func_800478B8(void *arg0);

extern struct {
    s32 value;
    s32 pad[2];
} D_800814A0;

void func_800D78C0(void *arg0) {
    register s32 i ASM_REG("$16");
    register s32 offset ASM_REG("$17");

    if (*(*(u16 **)((u8 *)arg0 + 0x98)) & 0x8000) {
        *((u16 *)arg0 - 1) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

    i = 0;
    if (*(s16 *)((u8 *)arg0 + 2) > 0) {
        offset = 8;
        do {
            func_800478B8((u8 *)arg0 + offset);
            offset += 0x30;
            i++;
        } while (i < *(s16 *)((u8 *)arg0 + 2));
    }
}
