#include "common.h"
#include "shared/town_lookup_data.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

s32 func_800179A0(void);
extern s32 D_80018AD0;
extern M2C_UNK D_80019C79;

/* Resolve a selection and return the fallback entry when its check succeeds. */
s32 *lookup_entry_with_fallback_level_30(s32 selection_id, s32 unused, s32 context) {
    s32 *result;

    if (get_town_state_count() >= 0x1E) {
        func_800179A0();
    }
    result = apply_entry_position(&D_8001896C, &D_80018AD0, selection_id, context);
    if (resolve_entry_flag(&D_8001896C, selection_id, context) != 0) {
        result = &D_80019C79;
    }
    return result;
}
