#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "engine/object.h"
#include "town/person/object.h"
#include "town/person.h"
#include "town/scene/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */

typedef struct ReactionAccumulators {
    s32 unk_00;
    s32 unk_04;
} ReactionAccumulators;   /* arg1 in advance_wedy_reaction */

typedef struct ReactionFlagState {
    u8 pad_00[0x14];
    u16 unk_14;
} ReactionFlagState;   /* arg2 in advance_wedy_reaction */

/* Advance two accumulators and invoke handlers when flag 0x8000 is set. */
void advance_wedy_reaction(TownObjectRecord *context, ObjectPosition *accumulators, SpriteFrameState *flagState) {
    accumulators->x.v = (s32) (accumulators->x.v + 0x40000);
    accumulators->y.v = (s32) (accumulators->y.v - 0x15555);
    if (flagState->flags & 0x8000) {
        set_resident_bitmap_bit(F_act_wedy);
        unlink_scene_list_node(context);
        clear_object_slot_and_mark_removed(context);
    }
}
