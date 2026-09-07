#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void func_80048A44(void *a0, s16 a1, s16 a2, s32 a3);
extern void *func_800A8608(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern void func_800A56E0(s32 a0);
extern void func_8008D928(void);

extern s16 D_80083228;
extern u8 D_800DD0B8[8];
extern s32 D_8008D470;
extern s32 D_8008ACDC;

void func_8008D7D0(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u16 flags;
    s32 idx;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_s0;
    s32 var_a0;

    *(s8 *)(arg0 + 0x9A) = 0x23;
    *(s8 *)(arg0 + 0x9B) = 0;
    *(void **)(arg0 + 0x8C) = NULL;

    flags = *(u16 *)(arg0 + 0xA2);
    *(u16 *)(arg0 + 0xA2) = flags & 0xFF7F;

    *(u8 **)(arg2 + 0x2C) = &D_800DD0B8[0];

    idx = ((D_80083228 + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
    func_80048A44(arg2, D_800DD0B8[idx], 0, 1);

    temp_v0 = func_800A8608(arg0 - 0x20, *(void **)(arg0 + 0xBC), 0, 0, 0);
    *(void **)(arg0 + 0x124) = temp_v0;
    if (temp_v0 != NULL) {
        *(void **)(temp_v0 + 0x10) = &D_8008D470;
        temp_v1 = *(u8 **)(temp_v0 + 8);
        *(s16 *)(temp_v1 + 2) = (s16)((arg2[0x24] << 6) + 0x20);
        *(s16 *)(temp_v1 + 6) = (s16)((arg2[0x25] << 6) + 0x20);
        temp_s0 = temp_v0 + 0x20;
        *(u16 *)(temp_v1 + 0xA) = *(u16 *)(arg3 + 0x88);
        *(s16 *)(temp_s0 + 0xAA) = 1;
        *(s16 *)(temp_s0 + 0xA8) = 0x1E;
        *(u8 **)(temp_s0 + 0x90) = arg2;
        *(s32 *)(temp_s0 + 0x8C) = arg1;
        *(u8 **)(temp_s0 + 0x9C) = temp_v0 + 0xB8;

        var_a0 = 0x505;
        if (*(u8 *)(*(u8 **)(arg0 + 0xBC) + 1) == 0xE) {
            var_a0 = 0x516;
        }
        func_800A56E0(var_a0);

        *(s16 *)(temp_s0 + 0xAE) = (s16)(*(u16 *)(arg3 + 0x46) == 1);
        *(u16 *)(arg0 + 0x46) = 0;
        return;
    }
    *(void **)(arg0 + 0x8C) = &D_8008ACDC;
}
