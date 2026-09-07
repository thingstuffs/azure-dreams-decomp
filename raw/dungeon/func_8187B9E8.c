#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

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
    register s32 held_arg0 ASM_REG("$23") = arg0;
    u16 saved[3];
    register s32 i ASM_REG("$20");
    s32 a;
    s32 b;
    s32 x;
    register s32 result ASM_REG("$2");
    register s32 scratch ASM_REG("$8");
    register void *p ASM_REG("$21");
    void *q;
    register void *r0 ASM_REG("$2");
    register void *r1 ASM_REG("$3");
    register u8 *v ASM_REG("$19");

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
        ASM_KEEP(v);
        do {
            i++;
            a = func_80069EF8() & 0xFFF;
            b = func_80069EF8() & 0xFFF;
            scratch = held_arg0 * func_80064584(a);
            x = scratch >> 12;
            scratch = x * func_800644B8(b);
            result = scratch >> 12;
            FIELD(v, s16, 0x16) = result;
            scratch = x * func_80064584(b);
            result = scratch >> 12;
            FIELD(v, s16, 0x44) = result;
            scratch = held_arg0 * func_800644B8(a);
            result = scratch >> 12;
            FIELD(v, s16, 0x72) = result;
            v = (u8 *)v + 2;
        } while (i < 0x17);
        ASM_KEEP(i);
        ASM_KEEP(held_arg0);
        r0 = FIELD(p, void *, 8);
        scratch = saved[0];
        ASM_KEEP(scratch);
        FIELD(r0, u16, 2) = scratch;
        scratch = saved[1];
        ASM_KEEP(scratch);
        FIELD(r0, u16, 6) = scratch;
        scratch = saved[2];
        ASM_KEEP(scratch);
        FIELD(r0, u16, 10) = scratch;
        ASM_KEEP(r0);
        r1 = FIELD(p, void *, 12);
        FIELD(r1, s16, 0x1E) = 0x1000;
        FIELD(r1, s16, 0x1C) = 0x1000;
        ASM_KEEP(r1);
        FIELD(q, s16, 0x14) = 0x17;
        FIELD(p, void *, 0x10) = D_80024D40;
        FIELD(q, s16, 0xA0) = (func_80069EF8() & 0x3F) + 0x3C;
        FIELD(q, s16, 0x10) = arg2;
        FIELD(q, s16, 0x12) = arg2;
        func_8004491C(p, D_800249F4);
        scratch = *(volatile s32 *)&arg1;
        ASM_KEEP(scratch);
        FIELD(q, s32, 0) = scratch;
        ASM_KEEP(p);
    }
}
