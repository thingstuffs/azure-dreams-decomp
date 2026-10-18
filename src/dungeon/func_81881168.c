#include "modules/dungeon_ovl_18a0800.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"


typedef struct S_80024968_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024968_0;



   /* arg1 in create_initialized_effect_object */

/* Creates an object, copies three values into its data, and initializes it. */
void *create_initialized_effect_object(s32 resource_id, MovingPosition *source_values, s16 setup_value, s32 object_value) {
    MovingPosition *target_values;
    S_80024968_0 *object;

    object = func_8003FD64(2, (ObjectNodeHeader **)(resource_id - 0x20));
    if (object != NULL) {
        target_values = object->unk_08;
        object->unk_10 = tint_effect_and_advance_motion;
        target_values->unk_02 = (u16) source_values->unk_02;
        target_values->unk_06 = (u16) source_values->unk_06;
        target_values->unk_0A = (u16) source_values->unk_0A;
        object->unk_20 = object_value;
        spawn_ring_effects(target_values, setup_value);
    }
    return object;
}
