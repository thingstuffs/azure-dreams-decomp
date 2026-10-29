#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "town/player/motion.h"

/* extern */

typedef struct S_8009A58C_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A58C_0;   /* arg0 in clear_player_motion_entry */


void initialize_target_and_handler_table(S_8009A58C_0 *, s32);
/* Clear the indexed table entry and call initialize_target_and_handler_table. */
void clear_player_motion_entry(S_8009A58C_0 *object, s32 value) {
    object_index_slots[object->unk_40].unk_00 = 0;
    initialize_target_and_handler_table(object, value);
}
