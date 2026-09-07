#include "common.h"

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80164BC4[];
extern u8 D_80164DA4[];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_80165018(void *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4,
                   s32 arg5) {
    register s32 held_arg4 ASM_REG("$19") = arg4;
    register s32 held_arg5 ASM_REG("$20") = arg5;
    void *obj;
    void *state;
    void *tail;
    void *pos;
    register s32 random ASM_REG("$2");
    register s32 value ASM_REG("$3");

    obj = func_8003FD64(0x211, arg0);
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = D_80164DA4;
        random = rand() & 7;
        value = FIELD(FIELD(arg0, void *, 8), u16, 2) + arg3;
        value -= 3;
        value += random;
        FIELD(FIELD(obj, void *, 8), s16, 2) = (s16)value;
        random = rand() & 7;
        value = FIELD(FIELD(arg0, void *, 8), u16, 6) + held_arg4;
        value -= 3;
        value += random;
        FIELD(FIELD(obj, void *, 8), s16, 6) = (s16)value;
        random = rand() & 7;
        value = FIELD(FIELD(arg0, void *, 8), u16, 0xA) + held_arg5;
        value -= 3;
        value += random;
        FIELD(FIELD(obj, void *, 8), s16, 0xA) = (s16)value;
        FIELD(FIELD(obj, void *, 0xC), s16, 6) = 0;
        state = FIELD(obj, void *, 0xC);
        tail = (u8 *)obj + 0x20;
        FIELD(state, u16, 0x14) = FIELD(state, u16, 0x14) | 0xC;
        FIELD(FIELD(obj, void *, 0xC), s16, 0x10) = 0x20;
        pos = FIELD(obj, void *, 8);
        FIELD(pos, s32, 0x14) = 0;
        FIELD(pos, s32, 0x10) = 0;
        FIELD(pos, s32, 0xC) = 0;
        FIELD(tail, s16, 0x32) = arg2;
        FIELD(tail, s16, 0x34) = arg2;
        func_8004491C(obj, D_80164BC4);
        FIELD(obj, s32, 0x20) = arg1;
        FIELD(tail, s32, 8) = arg1;
    }
}

/* MECHANISM: s3/s4 stack-argument holds reproduce the 0x30 frame and seven-register save set.
   Pinned v0 RNG plus pinned v1 compound accumulation preserves all three coordinate sequences.
   One cached obj+8 pointer collapses the three zero stores to retail's single-load form. */
