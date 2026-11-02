#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"

extern ScenePositionEntry D_80018B18;
extern s32 D_80018E38;
extern u8 D_8001C59A[16];

/* Look up the slot's record, falling back to the default table when the query fails. */
void *look_up_slot_record_falling(void *slot, s32 unused, s32 context) {
    if (get_script_flag_mask(F_sbs07_pad25) == 0) {
        return (void *)apply_entry_position(&D_80018B18, &D_80018E38, slot, context);
    }
    return D_8001C59A;
}
