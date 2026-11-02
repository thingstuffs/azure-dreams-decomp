#include "common.h"
#include "shared/town_lookup_data.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

s32 func_800179A0(void);
extern s32 D_80018AD0;
extern M2C_UNK D_80019BD1;

/* Look up an entry and return the fallback when its check succeeds. */
s32 *lookup_entry_with_fallback_level_20(s32 entry_id, s32 unused, s32 context) {
    s32 *entry;

    if (get_linked_record_field_2_d_60() >= 0x14) {
        func_800179A0();
    }
    entry = apply_entry_position(&D_80018964, &D_80018AD0, entry_id, context);
    if (resolve_entry_flag(&D_80018964, entry_id, context) != 0) {
        entry = &D_80019BD1;
    }
    return entry;
}
