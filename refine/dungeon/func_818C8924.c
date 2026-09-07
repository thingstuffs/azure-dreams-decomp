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

/* Advance effect motion and lifetime, updating its object and marking completion. */
void func_818C8924(EffectState *effect, s32 *position, EffectObject *object)
{
    u16 timer;
    u16 life;

    effect->x += effect->vx;
    effect->y += effect->vy;
    effect->z += effect->vz;
    position[0] += effect->x;
    position[1] += effect->y;
    position[2] += effect->z;

    D_80024D04 = 1;
    timer = effect->timer + 1;
    effect->timer = timer;
    if (!(timer & 1)) {
        func_800478B8(object);
    }

    object->field1C += 200;
    object->field1E += 200;

    life = effect->life - 1;
    effect->life = life;
    if ((life << 16) <= 0) {
        ((S_818C8924_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (object->flags & 0x8000) {
        ((S_818C8924_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
