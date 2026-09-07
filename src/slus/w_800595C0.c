#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 field_2C;
    u8 pad_30[0x4A - 0x30];
    u8 field_4A;
    u8 pad_4B;
    u8 field_4C;
} Entity;

typedef struct {
    s32 field_00;
    u8 pad_04[0x20 - 0x04];
    s32 field_20;
    s32 field_24;
    u8 pad_28[0x2C - 0x28];
    s32 field_2C;
    u8 pad_30[0x50 - 0x30];
} Slot;

extern Slot D_80085FA8[];
extern s32 D_800869B4[3];
extern void *jtbl_8003310C[];

extern s32 func_800589B8(Entity *);
extern void func_80057948(s32, s32, s32);
extern void func_80056E10(s32, s32, s32);
extern void func_80058494(s32, s32, s32);
extern void func_8005845C(u8, u8);
extern void func_8005914C(Entity *, s32, s32, s32);

s32 func_800595C0(Entity *arg0)
{
    register Entity *ent ASM_REG("$17") = arg0;   /* MATCH pin: slus-diff */
    s32 s0;
    s32 s2;
    s32 a2;
    register s32 s3 ASM_REG("$19");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 idx;
    static void *const keepalive[] = {
        &&L_case_46, &&L_case_47, &&L_case_48, &&L_case_49,
        &&L_case_4A, &&L_case_4B, &&L_case_7F, &&L_default
    };
    (void)keepalive;

    s0 = func_800589B8(ent);
    s3 = s0;
    if (!(s0 & 0x80)) {
        s32 v = func_800589B8(ent);
        a2 = v & 0x7F;
        if (a2 != 0) {
            s2 = v;
            func_80056E10(ent->field_4C, s0 & 0x7F, a2);
        } else {
            s2 = v;
            func_80057948(ent->field_4C, s0 & 0x7F, 0);
        }
        ent->field_4A = s3;
        goto ret_bool;
    }

    idx = (s0 & 0x7F) - 0x46;
    if ((u32)idx >= 0x3A) {
        goto L_default;
    }
    goto *jtbl_8003310C[idx];

L_case_46:
    func_80057948(ent->field_4C, ent->field_4A, 0);
    return 0;
L_case_47:
    func_80057948(ent->field_4C, ent->field_4A, 0);
    return 1;
L_case_48: {
    register s32 v ASM_REG("$3") = func_800589B8(ent);   /* MATCH pin: slus-diff */
    u32 count;
    s2 = v;
    count = D_800869B4[0];
    ASM_KEEP(count);   /* MATCH pin: slus-diff */
    if (count != 0) {
        u32 i = 0;
        s32 val = ((v & 0x7F) << 1) + 2;
        ASM_KEEP(v);   /* MATCH pin: slus-diff */
        do {
            D_80085FA8[i].field_24 = val;
            i++;
        } while (i < count);
    }
    goto ret_bool;
}
L_case_49: {
    register s32 v ASM_REG("$2") = func_800589B8(ent);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s2 = v;
    ASM_KEEP(v);   /* MATCH pin: slus-diff */
    func_80058494(ent->field_4C, 0, v & 0x7F);
    goto ret_bool;
}
L_case_4A: {
    register s32 v ASM_REG("$2") = func_800589B8(ent);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s2 = v;
    ASM_KEEP(v);   /* MATCH pin: slus-diff */
    func_8005845C(ent->field_4C, v & 0x7F);
    goto ret_bool;
}
L_case_4B: {
    s32 v = func_800589B8(ent);
    s2 = v;
    ASM_KEEP(v);   /* MATCH pin: slus-diff */
    ent->field_4C = v & 0xF;
    goto ret_bool;
}
L_case_7F:
    s2 = func_800589B8(ent);
    ent->field_2C = 1;
    goto ret_bool;
L_default: {
    register s32 v ASM_REG("$2") = func_800589B8(ent);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s2 = v;
    ASM_KEEP(v);   /* MATCH pin: slus-diff */
    func_8005914C(ent, (ent->field_4C + 0xB0) & 0xFF,
                  s3 & 0x7F, v & 0x7F);
}

ret_bool:
    return 0 < (s2 & 0x80);
}
