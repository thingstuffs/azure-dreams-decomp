#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player.h"
#include "town/player/state.h"

extern s16 D_80017A6C;
extern s16 D_80017A74;


/* Refresh the four menu labels plus the two fixed rows from the scene's state query. */
void invoke_callback_and_set_shared_pointer(void) {
    s16 *label_cursor;
    s16 *state_cursor;
    s32 state;
    s32 slot;

    state = town_scene_root->services->callback_330(0);
    slot = 0;
    label_cursor = &D_80017A6C;
    state_cursor = &D_80017A74;
    do {
        if (state == *state_cursor) {
            set_script_flag_bit(*label_cursor++);
        } else {
            clear_script_flag_bit(*label_cursor++);
        }
        state_cursor += 1;
        slot += 1;
    } while (slot < 4);
    if (town_scene_root->services->callback_334(0) != 5) {
        set_script_flag_bit(F_sbs48_pad06);
    } else {
        clear_script_flag_bit(F_sbs48_pad06);
    }
    if ((get_linked_record_field_2_d_60() < 5) || ((get_linked_record_field_2_d_60() >= 5) && (get_script_flag_mask(Ftt_fkoya_isaku_scene01_ok) != 0))) {
        set_script_flag_bit(F_sbs48_pad07);
    } else {
        clear_script_flag_bit(F_sbs48_pad07);
    }
}
