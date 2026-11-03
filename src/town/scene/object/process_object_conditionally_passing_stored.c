#include "script_symbols.h"
#include "common.h"
#include "town.h"
#include "town/scene/object.h"
#include "town/player.h"
#include "town/player/state.h"
#include "town/scene.h"

typedef struct S_806D435C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D435C_0;   /* arg0 in process_object_conditionally_passing_stored */

/* Processes the object, conditionally passing its stored value to initialize_state_two_entries_pointer. */
void process_object_conditionally_passing_stored(S_806D435C_0 *object, s32 context) {
    clear_script_flag_bit(F_sbs34_pad15);
    if ((record_value_table_contains(5) != 0) || (town_table_contains_first_byte_b(5) != 0)) {
        set_script_flag_bit(object->unk_18);
    }
    process_checked_entry(object, context);
}
