/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/scene_action_setup.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

typedef struct S_80099CE0_2 {
    u8 pad_00[0x14];
    s32 unk_08;
} S_80099CE0_2;   


void init_half_turn_motion_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) ((S_80099CE0_2 *)(((Rec_func_80094268_arg0 *)object)->unk_44))->unk_08, object, handler_context);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &player_slot_state_address;
    object->unk_10.as_s16 = 0x800;
}
