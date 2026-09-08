#include "common.h"

typedef struct Inner_800B45A0 {
    u8 pad0[8];
    s16 field8;
} Inner_800B45A0;

typedef struct Obj_800B45A0 {
    u8 pad0[4];
    s32 field4;
    void *field8;
    void *fieldC;
    u8 pad10[0x3C - 0x10];
    Inner_800B45A0 *field3C;
    u8 pad40[0x54 - 0x40];
    void **field54;
} Obj_800B45A0;

extern void func_8004E994(void *arg0, void *arg1);
extern void func_8004B1A4(void *arg0);
extern s32 D_800814A0[3];

/* Advance the inner value and mark completion when it exceeds the object's threshold. */
void func_800B1D00(Obj_800B45A0 *obj)
{
    Inner_800B45A0 *inner;
    u16 old_value;
    s32 next_value;
    s32 delta_step;

    inner = obj->field3C;
    old_value = inner->field8;
    next_value = old_value + 4;
    delta_step = (s16)old_value;
    delta_step += 4;
    delta_step -= obj->field4;
    delta_step >>= 2;
    next_value += delta_step;
    inner->field8 = next_value;

    if (obj->field4 + 0x80 < obj->field3C->field8) {
        func_8004E994(*obj->field54, inner);
        func_8004B1A4(obj->field8);
        func_8004B1A4(obj->fieldC);
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
