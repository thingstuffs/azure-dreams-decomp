#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct OffsetPair {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern s16 D_80083228;
extern s32 D_8008346C;
extern OffsetTable D_80170884;
extern s32 D_80171728;
extern u8 D_80174DEC[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801745BC(void *, s32, s32, s32);
extern void func_80174800(void *, s32, s32, s32);

void func_80174A28(void *arg0, void *arg1, void *arg2, void *arg3)
{
    OffsetTable offsets = D_80170884;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        FIELD(arg0, s16, 0x96) = 0x14;
        FIELD(arg0, u8, 0x9B)++;
        break;

    case 1:
        if ((--FIELD(arg0, s16, 0x96) == 0x12) ||
            (FIELD(arg2, u16, 0x14) & 0x8000)) {
            OffsetPair *offset;
            u16 flags;
            s32 height;
            s32 x;
            s32 x_sum;
            s32 x_raw;
            s32 off_x;
            register s32 y_offset ASM_REG("$2");
            register s32 scratch ASM_REG("$3");
            register void *call_arg0 ASM_REG("$4");

            flags = FIELD(arg2, u16, 0x14);
            call_arg0 = arg3;
            FIELD(arg2, u16, 0x14) = flags | 0x0800;
            height = FIELD(arg1, s16, 0x0A);
            x_raw = FIELD(arg2, u8, 0x24);
            offset = &offsets.entries[(FIELD(arg3, u16, 0x2A) >> 9) & 7];
            off_x = offset->x;
            x_sum = x_raw + off_x;
            y_offset = offset->y;
            ASM_USE(y_offset);
            x = x_sum & 0xFFFF;
            scratch = FIELD(arg2, u8, 0x25) + y_offset;
            func_80174800(call_arg0, x, scratch & 0xFFFF, height);
        }
        if ((FIELD(arg0, s16, 0x96) == 0x0A) ||
            (FIELD(arg2, u16, 0x14) & 0x8000)) {
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
            func_800A56E0(0x605);
        }
        if ((FIELD(arg0, s16, 0x96) == 9) ||
            (FIELD(arg2, u16, 0x14) & 0x8000)) {
            OffsetPair *offset;
            u16 angle;
            s32 height;
            s32 x_raw;
            s32 x;
            s32 x_sum;
            s32 y_offset;
            s32 scratch;

            angle = FIELD(arg3, u16, 0x2A);
            offset = offsets.entries + ((angle >> 9) & 7);
            height = FIELD(arg1, s16, 0x0A);
            x_raw = FIELD(arg2, u8, 0x24);
            scratch = offset->x;
            x_sum = x_raw + scratch;
            y_offset = offset->y;
            scratch = FIELD(arg2, u8, 0x25) + y_offset;
            x = x_sum & 0xFFFF;
            func_801745BC(arg3, x, scratch & 0xFFFF, height);
        }
        if ((FIELD(arg0, s16, 0x96) <= 0) ||
            (FIELD(arg2, u16, 0x14) & 0x8000)) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B)++;
        }
        break;

    case 2:
        if (FIELD(arg2, u16, 0x14) & 0xE000) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_800A2B04(arg1,
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
            if (FIELD(arg2, u8 *, 0x2C) != D_80174DEC) {
                FIELD(arg2, u8 *, 0x2C) = D_80174DEC;
                FIELD(arg2, u16, 0x14) &= 0xF7FF;
                func_80047784(arg2,
                    FIELD(arg2, u8 *, 0x2C)[((D_80083228 +
                        FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
                FIELD(arg0, u8, 0x9B)++;
            }
        }
        break;

    case 3:
        func_800AD594(arg3, 0x400);
        FIELD(arg0, s32 *, 0x8C) = &D_80171728;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        break;
    }
}
