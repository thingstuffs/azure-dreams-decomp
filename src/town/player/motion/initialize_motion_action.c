#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player.h"
#include "town/player/motion.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                     /* extern */
extern s32 actor_input_dispatch_address;


/* Set up the entity state and motion, then install its handler table. */
void initialize_motion_action(Rec_func_80094268_arg0 *entity, s32 motion, s32 value) {
    entity->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(entity);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(motion);
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, entity, (void *)(value));
    entity->unk_00.as_pm = &actor_input_dispatch_address;
}
