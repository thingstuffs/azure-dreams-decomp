#include "common.h"
#include "m2c_compat.h"

s32 update_linked_actor_motion(void *, s32, s32, s32);
s32 check_actor_floor_trap(s32, s32);
extern u8 D_80170F20;
extern u8 D_80173B98;

typedef struct S_80172538_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x17];
    u8 unk_A7;
} S_80172538_0;   /* object in select_object_data_by_flag */

/* Selects the object's data pointer by its flag after both update checks succeed. */
void select_object_data_by_flag(void *state, s32 motion, s32 entity, s32 actor) {
    S_80172538_0 *object = state;

    if ((update_linked_actor_motion(state, motion, entity, actor) != 0) &&
        ((check_actor_floor_trap(entity, actor) << 0x10) > 0)) {
        if (object->unk_A7 != 0) {
            object->unk_8C = &D_80173B98;
        } else {
            object->unk_8C = &D_80170F20;
        }
    }
}
