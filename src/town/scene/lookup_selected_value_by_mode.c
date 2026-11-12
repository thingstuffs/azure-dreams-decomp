#include "common.h"
#include "town/scene/choice_data.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern s32 D_8001673C[];
extern s32 D_80016754[];
extern s32 D_800170CC[];

/* Returns the selected table value for mode 1, or delegates the lookup for other modes. */
s32 lookup_selected_value_by_mode(s32 lookupInput, s32 unused, s32 mode) {
    s32 result;

    if (mode != 1) {
        result = apply_entry_position(D_8001673C, D_800170CC, lookupInput, mode);
    } else {
        result = D_80016754[scene_choice_index];
    }
    return result;
}
