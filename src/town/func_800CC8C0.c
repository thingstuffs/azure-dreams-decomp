#include "common.h"
#include "m2c_compat.h"
#include "shared/types3b_types.h"

void set_resident_bitmap_bit();                     /* extern */
void unlink_scene_list_node();                      /* extern */
void clear_object_slot_and_mark_removed();                      /* extern */

typedef struct S_800CA020_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA020_0;   /* arg1 in advance_reaction_accumulators */

   /* arg2 in advance_reaction_accumulators */

/* Advance two accumulators and invoke handlers when flag 0x8000 is set. */
void advance_reaction_accumulators(void *context, S_800CA020_0 *accumulators, SpriteFlagsView *flagState) {
    accumulators->unk_00 = (s32) (accumulators->unk_00 + 0x40000);
    accumulators->unk_04 = (s32) (accumulators->unk_04 + 0x15555);
    if (flagState->unk_14 & 0x8000) {
        set_resident_bitmap_bit(0x49);
        unlink_scene_list_node(context);
        clear_object_slot_and_mark_removed(context);
    }
}
