#include "common.h"

typedef struct {
    u16 field_0;
    s16 state;
    s16 field_4;
    u16 field_6;
    u16 field_8;
} Obj;

extern s32 func_800644B8(s32);

/* Advance the object counters and wrapped phase according to its state. */
void func_800AFAD8(Obj *obj)
{
    s16 state;
    s16 phase;
    s32 offset;
    s32 tick;

    state = obj->state;
    switch (state) {
    case 0:
        offset = obj->field_6;
        tick = obj->field_0;
        offset += 2;
        tick++;
        obj->field_6 = offset;
        obj->field_0 = tick;
        return;
    case 1:
        offset = obj->field_6;
        tick = obj->field_0;
        offset += 4;
        tick++;
        obj->field_6 = offset;
        obj->field_0 = tick;
        return;
    case 2:
        phase = obj->field_8 + 0x40;
        obj->field_8 = phase % 0x1C00;
        return;
    case 3:
        obj->field_6 += 8;
        phase = (func_800644B8((s16)obj->field_0 << 5) >> 1) + 0xC00;
        obj->field_0++;
        obj->field_8 = phase % 0x1C00;
        return;
    }
}
