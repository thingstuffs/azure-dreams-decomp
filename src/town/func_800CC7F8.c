#include "common.h"

typedef struct {
    u8 pad0[0x6C];
    u16 timer;
    u16 value;
    u16 pad70;
    u16 output;
} TownObject;

extern void apply_object_setup_and_update(TownObject *obj, s32 update_context, s32 setup_context);

/* Decrement the timer and lower output until expiry restores the base value. */
void lower_reaction_output_until_expiry(TownObject *obj, s32 update_input_1, s32 update_input_2) {
    u16 timer;

    timer = obj->timer - 1;
    obj->timer = timer;
    if ((timer << 16) <= 0) {
        apply_object_setup_and_update(obj, update_input_1, update_input_2);
        obj->output = obj->value;
        return;
    }
    obj->output -= 0x400;
}
