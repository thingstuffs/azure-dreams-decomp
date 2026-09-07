#include "common.h"

#ifndef NULL
#define NULL 0
#endif


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


typedef struct S_8017589C_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017589C_0;   /* object in func_8017589C */

typedef struct S_8017589C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    union { u16 u; s16 s; } unk_0E;   /* accessed as both */
    u8 pad_10[0x30];
    s32 unk_40;
    void * unk_44;
    void * unk_48;
    s32 unk_4C;
} S_8017589C_1;   /* work in func_8017589C */

typedef struct S_8017589C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_8017589C_2;   /* node in func_8017589C */

typedef struct S_8017589C_3 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_8017589C_3;   /* arg2 in func_8017589C */

typedef struct S_8017589C_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8017589C_4;   /* source in func_8017589C */

typedef struct S_8017589C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017589C_5;   /* copy in func_8017589C */

void *func_8017589C(s32 arg0, Copy24 *arg1, S_8017589C_3 *arg2)
{
    u16 delta[3];
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    void *object;
    S_8017589C_1 *work;
    S_8017589C_2 *node;
    S_8017589C_4 *source;
    Copy24 *copy;

    object = func_8003FD64(0x312, arg0 - 0x20);
    if (object != NULL) {
        ((S_8017589C_0 *)object)->unk_10 = &D_80175018;
        func_8004491C(object, &D_80045340);
        work = (u8 *)object + 0x20;

    var_v0 = rand();
    temp_v1 = var_v0;
    ASM_KEEP(var_v0);   /* MATCH pin: retail register colouring depends on it */
    var_v0 >>= 0xC;
    if (temp_v1 < 0) {
        var_v0 = (s32)(temp_v1 + 0xFFF) >> 0xC;
    }
    work->unk_06 = (s16)(temp_v1 - (var_v0 << 0xC));

    var_v0_2 = rand();
    temp_v1 = var_v0_2;
    if (temp_v1 < 0) {
        var_v0_2 = temp_v1 + 0xFFF;
    }
    work->unk_08 = (s16)(temp_v1 - ((var_v0_2 >> 0xC) << 0xC));

    work->unk_40 = arg0;
    work->unk_44 = arg1;
    work->unk_48 = arg2;
    work->unk_4C = arg0;

    node = ((S_8017589C_0 *)object)->unk_0C;
    node->unk_28 = arg2->unk_28;
    node->unk_0E = 0x80;
    node->unk_0D = 0x80;
    node->unk_0C = 0x80;
    node->unk_1E = 0x1000;
    node->unk_1C = 0x1000;
    node->unk_14 |= 0xC;
    node->unk_10 |= 0x20;
    func_80047784(node, 0x3F, 0);

    copy = ((S_8017589C_0 *)object)->unk_08;
    *copy = *arg1;

    delta[2] = 0;
    delta[1] = 0;
    delta[0] = 0;
    source = work->unk_48;
    if (func_8003DE58(source->unk_08, source, delta, 3) != 0) {
        ((S_8017589C_5 *)copy)->unk_02 += delta[0];
        ((S_8017589C_5 *)copy)->unk_06 += delta[1];
        ((S_8017589C_5 *)copy)->unk_0A += delta[2];
        work->unk_0A = delta[0];
        work->unk_0C = delta[1];
        work->unk_0E.u = delta[2];
    } else {
        work->unk_0A = 0;
        work->unk_0C = 0;
        work->unk_0E.s = -0x40;
    }
        return object;
    }
    return NULL;
}

/* MECHANISM: True-space positive CFG preserves the null-result block and return jump.
   Copy24 assignment groups the six-word copy; delta[3] exposes the contiguous callee output.
   ASM_KEEP on the first RNG result prevents CSE from replacing retail's v0 shift with v1. */
