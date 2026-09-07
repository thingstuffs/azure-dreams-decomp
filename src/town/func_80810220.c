#include "common.h"

typedef struct S_80810220_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    u8 pad_08[0x4C];
    union { s16 s; u16 u; } unk_54;   /* accessed as both */
} S_80810220_0;   /* arg0 in func_80810220 */

typedef struct S_80810220_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    u16 unk_20;
    s16 unk_22;
} S_80810220_1;   /* child in func_80810220 */

typedef struct S_80810220_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_80810220_2;   /* arg2 in func_80810220 */

typedef struct S_80810220_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80810220_3;   /* arg1 in func_80810220 */

typedef struct S_80810220_4 {
    u8 pad_00[0x22];
    s16 unk_22;
} S_80810220_4;   /* ((S_80810220_0 *)arg0)->unk_04 in func_80810220 */


#define NORETURN

extern s32 func_80252550(void *, void *);
extern void func_8052AEB8(void) NORETURN;
extern void func_8052B030() __attribute__((noreturn));
extern u32 D_80012BCC[4];
extern u8 D_805300C4[0x100];
extern u32 D_80530100[];
__asm__(".set D_80530100, 0x80530100");

void func_80810220(S_80810220_0 *arg0, S_80810220_3 *arg1, S_80810220_2 *arg2) {
    S_80810220_1 *child;
    s32 called;
    s16 state;
    u16 flags;

    child = arg0->unk_04;
    called = 0;

    if (child->unk_18 == 0) {
        arg0->unk_00 = 0;
    }

    if (D_80012BCC[0] >= 1000U) {
        if (func_80252550(D_805300C4, arg1) != 0) {
            called = 1;
            func_8052AEB8();
        }
        arg2->unk_08 = D_80530100[arg0->unk_54.s + 3];
    }

    state = arg0->unk_00;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_8052B030();
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_8052B030();
    return;

state_0: {
        s32 value;
        value = arg1->unk_08 - 0x80000;
        arg1->unk_08 = value;
        if (value <= 0) {
            arg1->unk_08 = 0;
            arg2->unk_0C = 0x808080;
            arg0->unk_00 = 1;
            func_8052B030();
        }
        goto done;
    }

state_1: {
        register s32 called_v0 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
        called_v0 = called;
        if (called_v0 != 0 && ((S_80810220_4 *)(arg0->unk_04))->unk_22 == 3) {
            child->unk_20 |= 1;
            arg2->unk_08 = D_80530100[arg0->unk_54.s + 6];
            child->unk_22 = arg0->unk_54.u;
        }
        if (child->unk_22 != 3) {
            if (((S_80810220_4 *)(arg0->unk_04))->unk_22 ==
                arg0->unk_54.s) {
                arg0->unk_00 = 3;
                func_8052B030();
                return;
            }
            arg0->unk_00 = 2;
            func_8052B030();
        }
        goto done;
    }

state_2: {
        s32 value;
        value = arg1->unk_08 + 0x80000;
        arg1->unk_08 = value;
        if (value > 0x3FFFFF) {
            arg1->unk_08 = 0x400000;
            func_8052B030();
        }
        goto done;
    }

state_3:
        flags = child->unk_20;
        if (flags & 1) {
            child->unk_20 = flags | 1;
            arg2->unk_08 = D_80530100[arg0->unk_54.s + 6];
        }
done:
    return;
}
