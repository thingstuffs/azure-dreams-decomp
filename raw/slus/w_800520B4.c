#include "common.h"

#include "common.h"

typedef struct S_800520B4_Sub {
    void *field_0x00;
    s16 field_0x04;
    s16 field_0x06;
    u8 pad_0x08[2];
    s16 field_0x0A;
    s16 field_0x0C;
} S_800520B4_Sub;

typedef struct S_800520B4_Ptr {
    u8 pad_0x00[8];
    void *field_0x08;
    s32 field_0x0C;
    u8 pad_0x10[0xC];
    s16 field_0x1C;
    s16 field_0x1E;
} S_800520B4_Ptr;

typedef struct S_800520B4_Vec {
    s32 field_0x00;
    s32 field_0x04;
    s32 field_0x08;
} S_800520B4_Vec;

typedef struct S_800520B4 {
    u8 pad_0x00[8];
    S_800520B4_Vec *vec;
    S_800520B4_Ptr *ptr;
    void (*update_func)(void);
    u8 pad_0x14[0xC];
    S_800520B4_Sub sub;
} S_800520B4;

extern u8 D_80071FF0[0x10];
extern void func_80051F58(void);
extern void func_80044BB0(void);
extern void func_8004491C(S_800520B4 *a0, void (*a1)(void));

void func_800520B4(S_800520B4 *a0, void *a1)
{
    register s16 *sub ASM_REG("$2");
    S_800520B4_Ptr *ptr;
    S_800520B4_Vec *vec;

    a0->update_func = func_80051F58;
    sub = (s16 *)((u8 *)a0 + 0x20);
    a0->sub.field_0x00 = a1;
    sub[2] = 0;
    sub[3] = 0;
    sub[5] = 0;
    sub[6] = 0;

    ptr = a0->ptr;
    ptr->field_0x08 = D_80071FF0;
    ptr->field_0x0C = 0;
    ptr->field_0x1E = 0x1000;
    ptr->field_0x1C = 0x1000;

    func_8004491C(a0, func_80044BB0);

    vec = a0->vec;
    vec->field_0x00 = 0x980000;
    vec->field_0x04 = 0x800000;
    vec->field_0x08 = 0xA00000;
}
