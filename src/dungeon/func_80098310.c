#include "common.h"

typedef struct Inner {
    u8 unk0[3];
    u8 type;
    s32 val4;
    s16 val8;
    s16 valA;
} Inner;

typedef struct State {
    u8 pad[0x8D0];
    Inner *next;
} State;

extern State *D_80083160[3];
extern u8 D_801C9E40[16];
extern s32 func_8006658C(s32 arg0, void *arg1);

void func_8009DA70(s32 arg0, s32 arg1, s32 *arg2, s32 arg3)
{
    s32 t1 = arg1 & 0xFFFF;
    s32 t0 = t1 + 0xC0;
    State *outer = D_80083160[0];
    Inner *inner = outer->next;
    s32 a0 = arg0 + 0x300;

    outer->next = inner + 1;
    inner->type = 2;
    inner->val8 = (s16)a0;
    if (outer != (State *)D_801C9E40) {
        t0 = t1 - 0x20;
    }
    inner->valA = (s16)t0;
    inner->val4 = *arg2;
    func_8006658C(arg3, inner);
}
