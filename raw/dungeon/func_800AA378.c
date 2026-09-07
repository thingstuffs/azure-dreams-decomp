#include "common.h"

typedef struct {
    s16 field_0;
    s16 state;
    s16 field_4;
    u16 field_6;
    u16 field_8;
} Obj;

extern s32 func_800644B8(s32);

void func_800AFAD8(Obj *obj)
{
    s16 state;
    s16 value;
    u16 field_6;
    u16 field_0;

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
    ASM_SCHED_BARRIER();
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    field_6 = obj->field_6;
    field_0 = obj->field_0;
    field_6 += 2;
    goto update_0_1;

state_1:
    field_6 = obj->field_6;
    field_0 = obj->field_0;
    field_6 += 4;

update_0_1:
    field_0++;
    obj->field_6 = field_6;
    obj->field_0 = field_0;
    goto done;

state_2:
    value = obj->field_8 + 0x40;
    obj->field_8 = value % 0x1C00;
    goto done;

state_3:
    obj->field_6 += 8;
    value = (func_800644B8(obj->field_0 << 5) >> 1) + 0xC00;
    obj->field_0++;
    obj->field_8 = value % 0x1C00;

done:
    return;
}

/* MECHANISM: The rowbase-local targets are CFG joins inside func_800AFAD8,
   not external calls. Cases 0/1 share update semantics; cases 2/3 feed one
   signed 16-bit modulo tail, with only s0 and ra live in the 0x18 frame. */
