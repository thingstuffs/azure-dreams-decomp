#include "common.h"

typedef struct S_8125414C_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8125414C_0;   /* entity in func_8125414C */

typedef struct S_8125414C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8125414C_1;   /* state in func_8125414C */



extern u8 *D_80174710;
extern u8 D_80082E80[];

extern void func_8009A3D0(s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_8009A21C(s32, s32, s32);

void func_8125414C(s32 arg0)
{
    s16 delta[2] = { 1, -1 };
    u8 *object;
    u8 *state;
    u8 *entity;
    void *motion;
    u8 *step;
    u8 *origin;

    object = D_80174710;
    state = object + 0x20;
    entity = *(u8 **)(object + 0xC);
    motion = *(void **)(object + 8);

    ((S_8125414C_0 *)entity)->unk_14 &= 0xFF7F;

    func_8009A3D0(entity[0x24], entity[0x25],
                  (((S_8125414C_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    origin = D_80082E80;
    step = (u8 *)&delta[arg0 * 2];
    entity[0x24] = origin[0x24] + step[0];
    entity[0x25] = origin[0x25] + step[2];

    func_800A2B04(motion, entity[0x24], entity[0x25]);

    func_8009A21C(entity[0x24], entity[0x25],
                  (((S_8125414C_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);
}
