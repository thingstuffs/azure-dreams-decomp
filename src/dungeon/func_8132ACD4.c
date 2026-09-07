#include "common.h"

typedef struct {
    u8 bytes[12];
} Blob12;

extern void **D_80174CD8[];
extern u8 D_80045340[];
void *func_8003FC64(s32);
void func_8004491C(void *, void *);
extern s32 D_801723D0;
extern Blob12 D_80174AC8;

void func_801724D4(void) {
    s32 *temp_s1;
    u8 *temp_v0;
    u8 *temp_a3;
    s32 *temp_a0;
    u8 *temp_v1;

    temp_s1 = (s32 *)D_80174CD8[0][2];
    temp_v0 = (u8 *)func_8003FC64(0x212);
    if (temp_v0 != (void *)0) {
        temp_v1 = temp_v0 + 0x20;
        *(s16 *)(temp_v1 + 0x16) = 0x1E;
        *(s16 *)(temp_v1 + 0x18) = 0x1E;
        *(void **)(temp_v0 + 0x10) = &D_801723D0;
        func_8004491C(temp_v0, D_80045340);
        temp_a3 = *(u8 **)(temp_v0 + 0xC);
        *(s16 *)(temp_a3 + 0x10) = 0x20;
        *(s16 *)(temp_a3 + 6) = 0;
        *(u16 *)(temp_a3 + 0x14) |= 0xC;
        temp_a0 = *(s32 **)(temp_v0 + 8);
        temp_a0[0] = temp_s1[0];
        temp_a0[1] = temp_s1[1];
        temp_a0[2] = temp_s1[2] + 0xFFC80000;
        temp_a3 = *(u8 **)(temp_v0 + 0xC);
        *(s16 *)(temp_a3 + 0x1E) = 0x400;
        *(s16 *)(temp_a3 + 0x1C) = 0x400;
        *(u8 *)(temp_a3 + 0xD) = 0x80;
        *(u8 *)(temp_a3 + 0xC) = 0x80;
        *(u8 *)(temp_a3 + 0xE) = 0;
        *(Blob12 *)(temp_v0 + 0x48) = D_80174AC8;
        *(void **)(temp_a3 + 8) = temp_v0 + 0x48;
    }
}
