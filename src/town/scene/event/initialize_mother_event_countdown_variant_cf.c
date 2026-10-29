/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/object_entries_aliases.h"
#include "town/scene/event.h"
extern s8 D_800826B8;
extern s32 D_800CA0D4;
extern s32 D_800D64DC;



/*
 * Initializes entries from D_800D64DC, clears D_800826B8, and installs D_800CA0D4 with count ten
 * and angle 0x400.
 */
void initialize_mother_event_countdown_variant_4cf44(Rec_func_80094268_arg0 *object, s32 unused, SpriteFrameState *init_data) {
    func_800C2E84((Struct800C5724 *)(object), init_data, &D_800D64DC);
    D_800826B8 = 0;
    object->unk_54 = &D_800CA0D4;
    object->unk_6C.as_s16 = 0xA;
    object->unk_72.as_s16 = 0x400;
}
