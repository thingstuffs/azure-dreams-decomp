#include "common.h"

#include "common.h"

typedef struct S_800847D0 {
    u32 flags1;
    u32 flags2;
    u32 field8;
    u32 fieldC;
    u32 field10;
    u32 field14;
    u32 field18;
    u8 pad1C[2];
    s16 field1E;
    s16 field20;
    s16 field22;
    u8 pad24[2];
    s16 field26;
    u8 field28;
    u8 pad29[7];
    s8 field30;
    s8 field31;
    s8 field32;
    s8 field33;
} S_800847D0;

typedef struct S_800848F8 {
    void (*field0)(void);
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s16 field10;
    s16 field12;
    s16 field14;
    s16 field16;
    s16 field18;
} S_800848F8;

extern S_800847D0 D_800847D0;
extern S_800848F8 D_800848F8;
extern void func_800553D4(s32 a0);
extern void func_800550E8(void);
extern void func_80054F9C(s32 a0, S_800848F8 *a1);

void func_8005500C(s32 a0)
{
    s32 a1 = a0;

    a0 &= 0xF000;
    if (a0 == 0x2000) {
        goto set_e1;
    }
    if (a0 >= 0x2001) {
        goto upper;
    }
    if (a0 == 0) {
        goto special;
    }
    if (a0 == 0x1000) {
        goto do_71;
        do { } while (0);
    }
    return;

upper:
    if (a0 == 0x8000) {
        if (1) {
            goto special;
        }
    }
    if (a0 > 0x8000) {
        goto high;
    }
    if (a0 == 0x4000) {
        goto do_f1;
    }
    return;

high:
    if (a0 != 0x9000) {
        return;
    }

special:
    {
        S_800847D0 *p = &D_800847D0;
        s32 v = a1 & 0xFF;

        do { } while (0);
        a0 = a1 & 0xF000;
        p->field26 = (s16)v;
        if (a0 != 0) {
            p->field26 = (s16)(v | a0);
        }
        if (D_800847D0.flags1 & 0x100) {
            func_80054F9C(0xB1, &D_800848F8);
            return;
            a0 = a1;
        }
    }

    func_800550E8();
    return;

set_e1:
    a0 = 0xE1;
    goto call;

do_71:
    a0 = 0x71;
    goto call;

do_f1:
    a0 = 0xF1;

call:
    func_800553D4(a0);
}
