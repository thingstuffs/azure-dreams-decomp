#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_80094268_arg0.h"

extern s32 mother_event_object_entries[];
extern u8 D_800C7CF0[];
extern s8 mother_event_reset_byte;


void initialize_actor_slot_four_countdown(Rec_func_80094268_arg0 *actor, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(actor, output, mother_event_object_entries);
    mother_event_reset_byte = 0;
    actor->unk_54 = D_800C7CF0;
    actor->unk_6C.as_s16 = 16;
}
