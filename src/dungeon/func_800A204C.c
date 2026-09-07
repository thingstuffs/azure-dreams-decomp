#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_8009A21C(s32, s32, s32);
extern void func_800A4300(void *, s32);
extern s16 func_800A71F4(void);

extern s32 D_800814A0;
extern s32 D_80082E80;
extern u16 D_80083460[];
extern s32 D_800E3548[];
typedef struct {
    u8 x;
    u8 y;
    u16 value2;
    u16 value4;
    u16 pad6;
    s32 value8;
} D_800E36C8_Entry;
extern D_800E36C8_Entry D_800E36C8[];
extern s32 D_800E3D7C;

typedef struct {
    u8 pad0[0x98];
    s32 field98;
    u8 pad9C[4];
    s16 fieldA0;
    u8 padA2[8];
    s16 fieldAA;
    s16 fieldAC;
    s16 fieldAE;
} FuncObj;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} FuncVec;

void func_800A77AC(FuncObj *arg0, FuncVec *arg1, FuncVec *arg2) {
    s16 temp_a0;
    u16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v1_4;
    register D_800E36C8_Entry *temp_v0_3 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    temp_v1 = arg1->x;
    arg1->x = temp_v1 +
        (((((arg0->fieldAA << 6) + 0x20) << 0x10) - temp_v1) /
         arg0->fieldA0);
    temp_v1_2 = arg1->y;
    arg1->y = temp_v1_2 +
        (((((arg0->fieldAC << 6) + 0x20) << 0x10) - temp_v1_2) /
         arg0->fieldA0);
    temp_v1_3 = arg1->z;
    temp_a0 = arg0->fieldA0;
    arg1->z = temp_v1_3 +
        (((arg0->fieldAE << 0x10) - temp_v1_3) / temp_a0);

    temp_v0 = (u16)arg0->fieldA0 - 1;
    arg0->fieldA0 = temp_v0;
    if ((s16)temp_v0 <= 0) {
        temp_v0_2 = func_800A71F4();
        if (temp_v0_2 >= 0) {
            D_800E3548[temp_v0_2] = arg0->field98;
            temp_v0_3 = &D_800E36C8[temp_v0_2];
            temp_v0_3->x = arg0->fieldAA;
            temp_v0_3->y = arg0->fieldAC;
            temp_v1_4 = arg0->fieldAE;
            temp_v0_3->value2 = temp_v1_4;
            temp_v0_3->value4 = temp_v1_4;
            temp_v0_3->value8 = arg2->z;
            func_8009A21C(arg0->fieldAA, arg0->fieldAC, 0x800);
            func_800A4300(&D_80082E80, D_800E3D7C);
        }
        D_80083460[5]--;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 = D_800814A0 | 0x8000;
    }
}

/* MECHANISM: Preserve the seed's 0x20 frame, s0 object hold, s1 arg2 hold, and v0 entry pin.
   The allocator call is zero-arity: the preceding signed divisor may remain incidental in a0,
   avoiding the false unsigned reload at word 36 and restoring retail's post-mflo nop. */
