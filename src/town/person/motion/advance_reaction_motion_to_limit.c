#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "town/person.h"

void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);                      /* extern */
s16 query_lowered_transform_position(void *position);                          /* extern */
void initialize_reaction_object_four(PersonSetupState *, void *, void *);


/* Advance motion and handle reaching the position limit. */
void advance_reaction_motion_to_limit(Rec_func_800C9B44_arg0 *state, EntityRec *motion, s32 context) {
    u16 remaining_count;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        remaining_count = state->unk_90 - 1;
        state->unk_90 = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            motion->flags14 = 0;
            choose_reaction_action_and_heading(state, motion, context);
            return;
        }
        initialize_reaction_object_four(state, motion, context);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(motion);
}
