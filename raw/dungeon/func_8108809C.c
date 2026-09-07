#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u32 words[6];
} Copy24;

extern void *func_8003FD64(s32, s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern u8 D_80045340;
extern u8 D_80175018;

void *func_8017589C(s32 arg0, Copy24 *arg1, void *arg2)
{
    u16 delta[3];
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    void *object;
    void *work;
    void *node;
    void *source;
    Copy24 *copy;

    object = func_8003FD64(0x312, arg0 - 0x20);
    if (object != NULL) {
        FIELD(object, void *, 0x10) = &D_80175018;
        func_8004491C(object, &D_80045340);
        work = (u8 *)object + 0x20;

    var_v0 = rand();
    temp_v1 = var_v0;
    ASM_KEEP(var_v0);
    var_v0 >>= 0xC;
    if (temp_v1 < 0) {
        var_v0 = (s32)(temp_v1 + 0xFFF) >> 0xC;
    }
    FIELD(work, s16, 6) = (s16)(temp_v1 - (var_v0 << 0xC));

    var_v0_2 = rand();
    temp_v1 = var_v0_2;
    if (temp_v1 < 0) {
        var_v0_2 = temp_v1 + 0xFFF;
    }
    FIELD(work, s16, 8) = (s16)(temp_v1 - ((var_v0_2 >> 0xC) << 0xC));

    FIELD(work, s32, 0x40) = arg0;
    FIELD(work, void *, 0x44) = arg1;
    FIELD(work, void *, 0x48) = arg2;
    FIELD(work, s32, 0x4C) = arg0;

    node = FIELD(object, void *, 0xC);
    FIELD(node, s32, 0x28) = FIELD(arg2, s32, 0x28);
    FIELD(node, u8, 0xE) = 0x80;
    FIELD(node, u8, 0xD) = 0x80;
    FIELD(node, u8, 0xC) = 0x80;
    FIELD(node, s16, 0x1E) = 0x1000;
    FIELD(node, s16, 0x1C) = 0x1000;
    FIELD(node, u16, 0x14) |= 0xC;
    FIELD(node, u16, 0x10) |= 0x20;
    func_80047784(node, 0x3F, 0);

    copy = FIELD(object, Copy24 *, 8);
    *copy = *arg1;

    delta[2] = 0;
    delta[1] = 0;
    delta[0] = 0;
    source = FIELD(work, void *, 0x48);
    if (func_8003DE58(FIELD(source, s32, 8), source, delta, 3) != 0) {
        FIELD(copy, u16, 2) += delta[0];
        FIELD(copy, u16, 6) += delta[1];
        FIELD(copy, u16, 0xA) += delta[2];
        FIELD(work, u16, 0xA) = delta[0];
        FIELD(work, u16, 0xC) = delta[1];
        FIELD(work, u16, 0xE) = delta[2];
    } else {
        FIELD(work, u16, 0xA) = 0;
        FIELD(work, u16, 0xC) = 0;
        FIELD(work, s16, 0xE) = -0x40;
    }
        return object;
    }
    return NULL;
}

/* MECHANISM: True-space positive CFG preserves the null-result block and return jump.
   Copy24 assignment groups the six-word copy; delta[3] exposes the contiguous callee output.
   ASM_KEEP on the first RNG result prevents CSE from replacing retail's v0 shift with v1. */
