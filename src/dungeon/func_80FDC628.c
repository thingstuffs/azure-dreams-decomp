#include "common.h"

typedef struct {
    u8 pad_00[0x84];
    u8 field_84;
    u8 field_85;
    u8 pad_86[0x06];
    s32 field_8c;
    u8 pad_90[0x08];
    u16 field_98;
    s8 field_9a;
    s8 field_9b;
    u8 pad_9c[0x10];
    u8 field_ac;
} Arg0;

typedef struct {
    u8 pad_00[0x03];
    u8 field_03;
    u8 pad_04[0x18];
    s32 field_1c;
    u8 pad_20[0x0a];
    s16 field_2a;
    u8 pad_2c[0x1a];
    u16 field_46;
    u8 pad_48[0x24];
    u8 field_6c;
    u8 field_6d;
    u8 pad_6e[0x03];
    u8 field_71;
    u8 pad_72[0x12];
    u8 field_84;
    u8 field_85;
} Arg3;

typedef struct {
    u8 pad_00[0x24];
    u8 field_24;
    u8 field_25;
    u8 pad_26[0x06];
    u8 *field_2c;
} Arg2;

typedef struct {
    u8 pad_00[0x02];
    u16 flags;
    u8 pad_04[0x08];
} Global83460;

extern Global83460 D_80083460;
extern u16 D_80083462[5];
extern u8 D_80174038[];
extern s16 D_80083228[5];

extern s32 func_80047784(void *, u8, s32);
extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

s32 func_80171E28(Arg0 *arg0, s32 arg1, Arg2 *arg2, Arg3 *arg3) {
    Global83460 *flags_base;
    u8 *table;
    u16 flags;
    s32 temp;
    s32 result;

    arg3->field_71 &= 0x7F;
    flags_base = (Global83460 *)((u8 *)D_80083462 - 2);
    result = 0;
    if (flags_base->flags & 0x2000) {
        return -1;
    }

    temp = func_800A04F0(arg3, arg2->field_24, arg2->field_25, arg3->field_2a);
    if ((func_800A2CB8(arg3, temp) << 16) == 0) {
        return result;
    }

    flags = flags_base->flags;
    if (flags & 0x2000) {
        return -1;
    }
    if ((arg3->field_46 & 0x8000) == 0 && (flags & 8) != 0) {
        return -1;
    }

    if ((u32)((0 - func_800A0134(temp, arg3) + 0x40) & 0xFFFF) >= 0x81U) {
        return result;
    }
    result = 1;
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    arg0->field_9b = 0;
    arg0->field_8c = 0;
    if (arg0->field_98 & 0x8000) {
        arg0->field_9a = 0x17;
        if (arg3->field_1c & 0x1000) {
            arg0->field_98 |= 0x4000;
        } else {
            arg0->field_98 &= 0xBFFF;
        }
        arg0->field_ac = arg3->field_03;
        arg3->field_03 = 0xFF;
        arg3->field_84 = 0x7E;
    } else {
        arg0->field_9a = 0x11;
        arg3->field_84 = 0x7C;
    }
    arg3->field_85 = 8;
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    table = D_80174038;
    arg2->field_2c = table;
    func_80047784(arg2, table[(((s32)D_80083228[0] + arg3->field_2a + 0x100) >> 9) & 7], 0);
    arg3->field_6d--;
    func_8009C93C(arg3, arg2, arg3->field_2a, 1, 0);
    if ((arg0->field_98 & 0x8000) == 0) {
        arg3->field_1c &= 0xFEFFFFFF;
    }
    return result;
}
