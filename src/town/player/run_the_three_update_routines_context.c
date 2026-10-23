#include "common.h"
#include "m2c_compat.h"

void clear_slot_n_3_copies_slot_n_0(s32);                            /* extern */
void clear_the_global_state_s_fifth_word_copy_source_s_second(s32 *);                         /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                         /* extern */

/*
 * Copies all three source coordinates into town collision state through the component helpers,
 * clearing their paired motion words.
 */
void run_the_three_update_routines_context(s32 context) {
    clear_slot_n_3_copies_slot_n_0(context);
    clear_the_global_state_s_fifth_word_copy_source_s_second((s32 *)(context));
    clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(context));
}
