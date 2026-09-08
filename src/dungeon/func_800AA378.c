#include "common.h"

typedef struct {
    s16 field_0;
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
    u16 offset;
    u16 tick;

    state = obj->state;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    offset = obj->field_6;
    tick = obj->field_0;
    offset += 2;
    goto update_0_1;

state_1:
    offset = obj->field_6;
    tick = obj->field_0;
    offset += 4;

update_0_1:
    tick++;
    obj->field_6 = offset;
    obj->field_0 = tick;
    goto done;

state_2:
    phase = obj->field_8 + 0x40;
    obj->field_8 = phase % 0x1C00;
    goto done;

state_3:
    obj->field_6 += 8;
    phase = (func_800644B8(obj->field_0 << 5) >> 1) + 0xC00;
    obj->field_0++;
    obj->field_8 = phase % 0x1C00;

done:
    return;
}
