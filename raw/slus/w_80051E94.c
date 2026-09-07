#include "common.h"

/* Element of the D_80071A68 lookup table indexed by an object's "kind" field. */
typedef struct S_80071A68 {
    /* 0x00 */ s32 field_0x00;
} S_80071A68;

extern S_80071A68 D_80071A68[];

extern void func_80051CC4(void);
extern void func_80044BB0(void);

/* Struct pointed to by S_80051E94.ptr (offset 0xC). */
typedef struct S_80051E94_Ptr {
    /* 0x00 */ u8 unk00[0x8];
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ s32 field_0x0C;
    /* 0x10 */ u8 pad10[0xC];
    /* 0x1C */ s16 field_0x1C;
    /* 0x1E */ s16 field_0x1E;
} S_80051E94_Ptr;

/* Sub-object embedded at offset 0x20 of S_80051E94 ("Entity"-style object). */
typedef struct S_80051E94_Sub {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ u8 pad_0x08[2];
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
} S_80051E94_Sub;

/* Struct pointed to by S_80051E94.vecPtr (offset 0x8); populated by
 * func_8004491C as a side effect and then filled in here with three
 * 16.16-fixed-point constants (integer part only, low half zero). */
typedef struct S_80051E94_Vec {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ s32 field_0x04;
    /* 0x08 */ s32 field_0x08;
} S_80051E94_Vec;

/* Common "Entity"/"Obj" object layout used across code.c: update_func at 0x10. */
typedef struct S_80051E94 {
    /* 0x00 */ u8 unk00[0x8];
    /* 0x08 */ S_80051E94_Vec *vecPtr;
    /* 0x0C */ S_80051E94_Ptr *ptr;
    /* 0x10 */ void (*update_func)(void);
    /* 0x14 */ u8 unk14[0xC];
    /* 0x20 */ S_80051E94_Sub sub;
} S_80051E94;

extern void func_8004491C(S_80051E94 *a0, void (*a1)(void));

/* summary: initialize an object's update-func, embedded sub-object, D_80071A68
 * lookup-derived ptr fields, then finish init via func_8004491C and fill vecPtr. */
void func_80051E94(S_80051E94 *a0, s32 a1)
{
    register S_80051E94_Sub *sub ASM_REG("$2");
    S_80051E94_Ptr *ptr;
    S_80051E94_Vec *vec;
    s32 val;

    a0->update_func = func_80051CC4;
    sub = &a0->sub;
    sub->field_0x00 = a1;
    sub->field_0x04 = 0;
    sub->field_0x06 = 0;
    sub->field_0x0A = 0;
    sub->field_0x0C = 0;

    ptr = a0->ptr;
    ptr->field_0x0C = 0;
    val = D_80071A68[sub->field_0x0A].field_0x00;
    ptr->field_0x1E = 0x1000;
    ptr->field_0x1C = 0x1000;
    ptr->field_0x08 = val;

    func_8004491C(a0, func_80044BB0);

    vec = a0->vecPtr;
    vec->field_0x00 = 0x380000;
    vec->field_0x04 = 0x280000;
    vec->field_0x08 = 0x900000;
}
