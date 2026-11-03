#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "engine/object.h"
#include "town/person.h"
#include "town/person/object.h"
#include "town/scene/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */

   /* arg1 in advance_reaction_accumulators */

   /* arg2 in advance_reaction_accumulators */

/* Advance two accumulators and invoke handlers when flag 0x8000 is set. */
void advance_reaction_accumulators(TownObjectRecord *context, ObjectPosition *accumulators, SpriteFlagsView *flagState) {
    accumulators->x.v = (s32) (accumulators->x.v + 0x40000);
    accumulators->y.v = (s32) (accumulators->y.v + 0x15555);
    if (flagState->flags & 0x8000) {
        set_resident_bitmap_bit(F_act_niko);
        unlink_scene_list_node(context);
        clear_object_slot_and_mark_removed(context);
    }
}
