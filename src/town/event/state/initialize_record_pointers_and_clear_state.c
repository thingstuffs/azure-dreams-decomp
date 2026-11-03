#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"
#include "town/event/state.h"
#include "town/player/object.h"

typedef struct S_800A97D8_0 {
    void (*unk_00)();
    u8 pad_04[0x5C];
    void (*unk_60)();
} S_800A97D8_0;   /* arg0 in initialize_record_pointers_and_clear_state; pointer addresses record offset 0x10 */

   /* arg1 in initialize_record_pointers_and_clear_state */



extern void trigger_action_and_finish_record(u16 *record);

/* Initialize the record pointers and clear the associated state field. */
void initialize_record_pointers_and_clear_state(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *state = placement;

    ((S_800A97D8_0 *)((u8 *)record_data - 0x10))->unk_00 = retire_object_on_check_or_callback;
    ((S_800A97D8_0 *)((u8 *)record_data - 0x10))->unk_60 = &trigger_action_and_finish_record;
    state->z.v = 0;
}
