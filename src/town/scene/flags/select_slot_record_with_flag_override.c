#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
#include "town/scene.h"
#include "town/player.h"

extern ScenePositionEntry D_80017A20;
extern u8 D_80017B5C[9];
extern u8 D_80018CC0[9];
extern u8 D_80018D9F[9];
extern u8 D_80018E42[9];


/* Look up the slot's record, substituting fixed records when it is claimed or the 7-flag is set. */
void *select_slot_record_with_flag_override(TownObjectSet *slot, s32 unused, s32 context)
{
    void *result;

    result = apply_entry_position(&D_80017A20, D_80017B5C, slot, context);
    if (query_referenced_flag_for_table_entry(&D_80017A20, slot, context) != 0) {
        if (get_script_flag_mask(F_sbs36_pad19) != 0) {
            result = D_80018D9F;
        } else {
            result = D_80018CC0;
        }
    } else {
        clear_script_flag_bit(F_sbs36_pad19);
    }
    if (record_value_table_contains(7) != 0) {
        result = D_80018E42;
    }
    return result;
}
