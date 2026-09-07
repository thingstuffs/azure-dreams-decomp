#include "common.h"

typedef struct S_818C8924_0_pre {
    u16 unk_00;
} S_818C8924_0_pre;   /* the 0x2 bytes before arg0 in func_818C8924, addressed as arg0[-1] */



typedef struct {
    u8 pad0[2];
    u16 life;
    u16 timer;
    u8 pad6[0x58 - 6];
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
} EffectState;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} EffectObject;

extern void func_800478B8(void *);
extern s16 D_80024D04;
extern s32 D_800814A0[3];

void func_818C8924(EffectState *arg0, s32 *arg1, EffectObject *arg2)
{
    u16 timer;
    u16 life;

    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    arg1[0] += arg0->x;
    arg1[1] += arg0->y;
    arg1[2] += arg0->z;

    D_80024D04 = 1;
    timer = arg0->timer + 1;
    arg0->timer = timer;
    if (!(timer & 1)) {
        func_800478B8(arg2);
    }

    arg2->field1C += 200;
    arg2->field1E += 200;

    life = arg0->life - 1;
    arg0->life = life;
    if ((life << 16) <= 0) {
        ((S_818C8924_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (arg2->flags & 0x8000) {
        ((S_818C8924_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
