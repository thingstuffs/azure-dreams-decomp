#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800374F4(s32);
extern void func_8003DB94(void *, s32, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8009539C(void *);
extern void func_800A360C(void *);

extern u8 D_80045340[];
extern u8 D_800A378C[];
extern s16 D_800D0B18[];
extern s32 D_800D0B20[];
extern s32 D_800D0B50[];

void func_800A3508(void *arg0, void *arg1, void *arg2)
{
    u8 *obj = arg0;
    s32 *vec = arg1;
    register s32 color ASM_REG("$3");
    register s32 r3 ASM_REG("$19");
    s32 scale;
    s32 r1;
    register s32 held ASM_REG("$16");
    s32 value;
    s32 product;
    s32 value2;
    s32 angle;
    s32 fixed;
    s32 *table1;
    s32 *table2;

    table1 = D_800D0B50;
    table2 = D_800D0B20;
    color = 0x808080;
    FIELD(arg2, s32, 0xC) = color;
    fixed = 0x1000;
    FIELD(arg2, s16, 0x1E) = fixed;
    FIELD(arg2, s16, 0x1C) = fixed;
    FIELD(arg2, s32, 8) = table1[FIELD(obj, s16, 0x22)];
    FIELD(arg2, s32, 0) = 0;
    FIELD(arg2, s8, 4) = 0;
    FIELD(arg2, s8, 5) = 0;

    value = table2[FIELD(obj, s16, 0x22)];
    if (value != 0) {
        func_8003DB94(arg2, value, 0);
    }

    func_8004491C(obj - 0x20, D_80045340);

    if (FIELD(obj, s16, 0x22) < 4) {
        value = func_800374F4(0x1000);
        r3 = 0x400;
        r1 = D_800D0B18[FIELD(obj, s16, 0x22)] + (value & 0xFFFF);
        ASM_KEEP(r3);
        ASM_TAILSLOT_PIN(r1);
        func_800A360C(D_800D0B18);
        return;
    }

    r1 = func_800374F4(0x1000) & 0xFFFF;
    r3 = func_800374F4(0x1000) & 0xFFFF;
    angle = func_800374F4(0x1000) & 0xFFFF;
    value2 = angle + 0x1000;
    if (value2 < 0) {
        value2 = angle + 0x101F;
    }
    scale = (s32)value2 >> 5;
    product = func_800644B8(r1) * func_800644B8(r3);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[3] = product >> 12;

    held = func_80064584(r1);
    product = held * func_800644B8(r3);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[4] = product >> 12;

    vec[5] = func_80064584(r3);
    vec[3] *= scale;
    vec[4] *= scale;
    vec[5] *= scale;

    (*(volatile s32 *)((u8 *)obj + 0x2C)) = vec[3] / 23;
    FIELD(obj, s32, 0x30) = vec[4] / 23;
    FIELD(obj, s32, 0x34) = vec[5] / 23;
    FIELD(obj, s32, 0x24) = 0x18;
    FIELD(obj, void *, 0) = D_800A378C;

    func_8009539C(vec);
    func_8009539C(vec);
}
