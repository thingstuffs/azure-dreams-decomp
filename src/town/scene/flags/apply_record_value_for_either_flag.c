#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 apply_selected_entry_values();             /* extern */
void set_script_flag_bit();                         /* extern */
s32 get_script_flag_mask();                         /* extern */


/* Applies the object's stored value when either condition is active, then forwards the call. */
void apply_record_value_for_either_flag(Rec_func_800165F4_arg0 *object, s32 context) {
    if ((get_script_flag_mask(F_selfy_dungeon_tasuketa) != 0) || (get_script_flag_mask(F_selfy_dungeon_tasukenai) != 0)) {
        set_script_flag_bit(object->unk_18);
    }
    apply_selected_entry_values(object, context);
}
