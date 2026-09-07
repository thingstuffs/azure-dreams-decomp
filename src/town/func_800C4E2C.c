#include "common.h"

extern void *D_800C25C0;
extern s32 D_800D4FA0[];

void func_800C258C(void *arg0) {
    *(void **)((u8 *)arg0 - 0x10) = &D_800C25C0;
    *(s32 *)((u8 *)arg0 + 0x60) = *((u8 *)arg0 + 0x96);
    *(s32 *)((u8 *)arg0 + 0x50) = D_800D4FA0[*((u8 *)arg0 + 0x94)];
}
