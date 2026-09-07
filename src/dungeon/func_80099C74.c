#include "common.h"
#include "m2c_compat.h"

extern u8 D_8008333C[32];
extern s32 D_800E296C[3];

void *func_8003FC64();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_80065420();
M2C_UNK func_80065820();
extern M2C_UNK D_8009F21C;
extern M2C_UNK D_800DD824;

void *func_8009F3D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_a0;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    u8 *s1;
    u8 *s3;
    u8 *s4;

    var_a0 = 2;
    s3 = D_8008333C;
    s4 = s3 - 0x1C4;
    s1 = (u8 *)0x1F800000;
    if (arg4 != 0) {
        var_a0 = 0x202;
    }
    temp_v0 = func_8003FC64(var_a0);
    if (temp_v0 != NULL) {
        temp_s0 = *(void **)((u8 *)temp_v0 + 8);
        *(M2C_UNK **)((u8 *)temp_v0 + 0x10) = &D_8009F21C;
        *(u16 *)(s1 + 0x98) = 0;
        *(u16 *)(s1 + 0x9A) = 0;
        *(u32 *)(s1 + 0x34) = 0x1800;
        *(u32 *)(s1 + 0x30) = 0x1800;
        *(u32 *)(s1 + 0x38) = 0;
        *(u16 *)(s1 + 0x9C) = *(u16 *)(s4 + 0xB0);
        func_80065820((void *)0x1F800098, (void *)0x1F8000D0);
        func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        *(u32 *)(s1 + 0xE4) = 0;
        *(u32 *)(s1 + 0xE8) = 0;
        *(u32 *)(s1 + 0xEC) = 0;
        func_80064CF0((void *)0x1F8000D0);
        func_80064D80((void *)0x1F8000D0);
        *(u16 *)(s1 + 0x74) = 0;
        *(u16 *)(s1 + 0x70) = arg0 - ((s32)(1 << *(s16 *)(s3 + 0x14)) / 2);
        *(u16 *)(s1 + 0x72) = arg1 - ((s32)(1 << *(s16 *)(s3 + 0x16)) / 2);
        func_80065420((void *)0x1F800070, (void *)0x1F8000F0,
                      (void *)0x1F800090, (void *)0x1F800094);
        *(u16 *)((u8 *)temp_s0 + 2) = *(u16 *)(s1 + 0xF0);
        *(u16 *)((u8 *)temp_s0 + 6) = *(u16 *)(s1 + 0xF2);
        temp_v1 = *(void **)((u8 *)temp_v0 + 0xC);
        *(s16 *)((u8 *)temp_v1 + 0x14) = 0xC;
        *(M2C_UNK **)((u8 *)temp_v1 + 8) = &D_800DD824;
        *(s16 *)((u8 *)temp_v1 + 0x1E) = 0x2000;
        *(s16 *)((u8 *)temp_v1 + 0x1C) = 0x2000;
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        *(s16 *)((u8 *)temp_v1_2 + 0x1C) = 8;
        *(s32 *)((u8 *)temp_v0 + 0x20) = arg2;
        *(s32 *)((u8 *)temp_v1_2 + 0x28) = arg3;
        *(s16 *)((u8 *)temp_v1_2 + 0x2E) = (s16)arg4;
        if (arg4 == 0) {
            D_800E296C[0] |= 0x40000;
        }
    }
    return temp_v0;
}
