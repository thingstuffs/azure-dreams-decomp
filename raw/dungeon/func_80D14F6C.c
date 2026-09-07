#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
s32 func_8009B25C();
s32 func_800A2B5C();
M2C_UNK func_800A4ACC();
M2C_UNK func_800C7930();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174EC8;

void func_8017476C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 temp_v1;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8)(M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
            M2C_FIELD(arg0, s16 *, 0x96) = 0xF;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg2, u8 **, 0x2C) = &D_80174EC8;
            func_80047784(
                arg2,
                *(&D_80174EC8 + (((s32)(D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)),
                0);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, u8 *, 0x6D) = (u8)(M2C_FIELD(arg3, u8 *, 0x6D) - 1);
            temp_v1 = ((u16)M2C_FIELD(arg3, s16 *, 0x2A) >> 9) & 7;
            M2C_FIELD(arg3, s32 *, 0x60) = func_8009B25C(
                arg3,
                (M2C_FIELD(arg2, u8 *, 0x24) + D_8006CCD8[temp_v1]) & 0xFFFF,
                (M2C_FIELD(arg2, u8 *, 0x25) + D_8006CCE8[temp_v1]) & 0xFFFF,
                M2C_FIELD(arg3, s16 *, 0x88));
        }
    }
}
