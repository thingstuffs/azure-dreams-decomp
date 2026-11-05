#include "town/player/position_handlers.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"

typedef struct S_80098544_0 {
    u8 pad_00[0x4];
    void (*unk_04)(s32,  ObjectPosition *, SpriteFrameState *);
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2A];
    s16 unk_36;
    s16 unk_38;
} S_80098544_0;   /* arg0 in advance_coordinates_toward_target */

   /* out in advance_coordinates_toward_target */

#include "town/player/object/entity_record_fields.h"
#include "town/player.h"
#include "town/player/object.h"

/* Advance the fixed-point coordinates toward their targets and finish when the countdown expires. */
void advance_coordinates_toward_target(S_80098544_0 *state, ObjectPosition *position) {
    s32 remaining;
    s32 current_coord;
    s32 current_coord_2;
    u16 steps_left;
    s32 target_y;

    steps_left = state->unk_0A - 1;
    state->unk_0A = steps_left;
    if ((s16) steps_left > 0) {
        current_coord_2 = position->x.v;
        position->x.v = (s32) (current_coord_2 + ((s32) ((state->unk_36 << 0x10)
            - current_coord_2) / (s16) steps_left));
        target_y = state->unk_38;
        current_coord = position->y.v;
        remaining = ((s16)state->unk_0A);
        position->y.v = (s32) (current_coord + ((s32) ((target_y << 0x10) - current_coord) / remaining));
        return;
    }
    position->x.v = (s32) (state->unk_36 << 0x10);
    position->y.v = (s32) (state->unk_38 << 0x10);
    clear_entity_record_fields((position));
    state->unk_04 = &update_falling_actor_and_handle_ground;
}
