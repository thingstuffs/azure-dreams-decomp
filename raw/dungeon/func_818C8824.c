#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

typedef struct {
    u8 pad0[2];
    u16 life;
    u8 pad4[0x58 - 4];
    s32 x;
    s32 y;
    s32 z;
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

/* Private body-only reconstruction, linked at retail 0x818C8824. */
void func_818C8824(EffectState *arg0, s32 *arg1, EffectObject *arg2)
{
    u16 life;

    arg1[0] += arg0->x;
    arg1[1] += arg0->y;
    D_80024D04 = 1;
    arg1[2] += arg0->z;
    func_800478B8(arg2);
    arg2->field1C += 0x80;
    arg2->field1E += 0x80;
    life = arg0->life - 1;
    arg0->life = life;
    if ((life << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (arg2->flags & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
