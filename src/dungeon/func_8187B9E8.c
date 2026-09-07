#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8187B9E8_0 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x2C];
    s16 unk_44;
    u8 pad_46[0x2C];
    s16 unk_72;
} S_8187B9E8_0;   /* v in func_8187B9E8 */

typedef struct S_8187B9E8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8187B9E8_1;   /* p in func_8187B9E8 */

typedef struct S_8187B9E8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8187B9E8_2;   /* r0 in func_8187B9E8 */

typedef struct S_8187B9E8_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8187B9E8_3;   /* r1 in func_8187B9E8 */

typedef struct S_8187B9E8_4 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x8A];
    s16 unk_A0;
} S_8187B9E8_4;   /* q in func_8187B9E8 */



typedef union {
    u16 value;
    s32 word;
} U16Arg;

extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();
extern u8 D_800249F4[];
extern u8 D_80024D40[];

void func_8187B9E8(s32 arg0, s32 arg1, s16 arg2, u16 arg3, U16Arg arg4, U16Arg arg5) {
    register s32 held_arg0 ASM_REG("$23") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 saved[3];
    s32 i;
    s32 a;
    s32 b;
    s32 x;
    register s32 result ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 scratch ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    void *p;
    S_8187B9E8_4 *q;
    S_8187B9E8_2 *r0;
    S_8187B9E8_3 *r1;
    register u8 *v ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */

    scratch = arg4.value;
    saved[1] = scratch;
    scratch = arg5.value;
    saved[2] = scratch;
    saved[0] = arg3;
    p = func_8003FC64(0x212);
    if (p != NULL) {
        i = 0;
        q = (u8 *)p + 0x20;
        v = q;
        do {
            i++;
            a = func_80069EF8() & 0xFFF;
            b = func_80069EF8() & 0xFFF;
            scratch = held_arg0 * func_80064584(a);
            x = scratch >> 12;
            scratch = x * func_800644B8(b);
            result = scratch >> 12;
            ((S_8187B9E8_0 *)v)->unk_16 = result;
            scratch = x * func_80064584(b);
            result = scratch >> 12;
            ((S_8187B9E8_0 *)v)->unk_44 = result;
            scratch = held_arg0 * func_800644B8(a);
            result = scratch >> 12;
            ((S_8187B9E8_0 *)v)->unk_72 = result;
            v = (u8 *)v + 2;
        } while (i < 0x17);
        r0 = ((S_8187B9E8_1 *)p)->unk_08;
        scratch = saved[0];
        r0->unk_02 = scratch;
        scratch = saved[1];
        r0->unk_06 = scratch;
        scratch = saved[2];
        r0->unk_0A = scratch;
        ASM_KEEP(r0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        r1 = ((S_8187B9E8_1 *)p)->unk_0C;
        r1->unk_1E = 0x1000;
        r1->unk_1C = 0x1000;
        q->unk_14 = 0x17;
        ((S_8187B9E8_1 *)p)->unk_10 = D_80024D40;
        q->unk_A0 = (func_80069EF8() & 0x3F) + 0x3C;
        q->unk_10 = arg2;
        q->unk_12 = arg2;
        func_8004491C(p, D_800249F4);
        scratch = *(volatile s32 *)&arg1;
        ASM_KEEP(scratch);   /* MATCH pin: retail register colouring depends on it */
        q->unk_00 = scratch;
    }
}
