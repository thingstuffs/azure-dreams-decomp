#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "engine/object.h"
#include "town/person.h"
#include "town/person/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */

typedef struct S_800CA020_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA020_0;   /* arg1 in advance_reaction_accumulators */

   /* arg2 in advance_reaction_accumulators */

/* Advance two accumulators and invoke handlers when flag 0x8000 is set. */
void advance_reaction_accumulators(void *context, S_800CA020_0 *accumulators, SpriteFlagsView *flagState) {
    accumulators->unk_00 = (s32) (accumulators->unk_00 + 0x40000);
    accumulators->unk_04 = (s32) (accumulators->unk_04 + 0x15555);
    if (flagState->flags & 0x8000) {
        set_resident_bitmap_bit(F_act_niko);
        unlink_scene_list_node(context);
        clear_object_slot_and_mark_removed(context);
    }
}
