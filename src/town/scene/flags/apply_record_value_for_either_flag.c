#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"



/* Applies the object's stored value when either condition is active, then forwards the call. */
void apply_record_value_for_either_flag(Rec_func_800165F4_arg0 *object, s32 context) {
    if ((get_script_flag_mask(F_selfy_dungeon_tasuketa) != 0) || (get_script_flag_mask(F_selfy_dungeon_tasukenai) != 0)) {
        set_script_flag_bit(object->unk_18);
    }
    apply_selected_entry_values(object, context);
}
