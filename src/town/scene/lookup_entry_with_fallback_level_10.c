#include "common.h"
#include "shared/town_lookup_data.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

s32 func_800179A0(void);
extern s32 D_80018AD0;
extern M2C_UNK D_80019B97;

/* Retrieves a result and substitutes the fallback when the follow-up check succeeds. */
s32 *lookup_entry_with_fallback_level_10(s32 key, s32 unused, s32 context) {
    s32 *result;

    if (get_linked_record_field_2_d_60() >= 0xA) {
        func_800179A0();
    }
    result = apply_entry_position(&D_8001895C, &D_80018AD0, key, context);
    if (resolve_entry_flag(&D_8001895C, key, context) != 0) {
        result = &D_80019B97;
    }
    return result;
}
