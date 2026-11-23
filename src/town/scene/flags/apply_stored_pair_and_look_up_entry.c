#include "town/scene/event.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern ScenePositionEntry D_80018E80;

/* Apply the stored global pair, then process the requested entry with the supplied value. */
void apply_stored_pair_and_look_up_entry(TownObjectSet *context, s32 unused, s32 lookup_key) {
    forward_stored_pair();
    lookup_entry_value_and_set_flag(&D_80018E80, context, lookup_key);
}
