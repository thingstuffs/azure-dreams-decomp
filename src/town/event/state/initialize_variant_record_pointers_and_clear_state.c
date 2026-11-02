#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_effect_views.h"
#include "town.h"
#include "town/event/state.h"
#include "town/player/object.h"

typedef struct S_800A9858_0 {
    s32 * unk_00;
    u8 pad_04[0x5C];
    s32 * unk_60;
} S_800A9858_0;   /* arg0 in initialize_variant_record_pointers_and_clear_state; pointer addresses record offset 0x10 */

   /* arg1 in initialize_variant_record_pointers_and_clear_state */

/* Initialize the record's pointers and clear the associated state field. */
void initialize_variant_record_pointers_and_clear_state(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *state = placement;

    ((S_800A9858_0 *)((u8 *)record_data - 0x10))->unk_00 = &retire_object_on_check_or_callback;
    record_data->unk_50.as_pm = &set_resident_flag_when_item_present;
    state->z.v = 0;
}
