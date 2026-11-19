#include "common.h"
#include "town/shop.h"
#include "town/shop/state.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"

typedef struct S_8009EB20_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009EB20_0;   /* arg1 in start_move_toward_view_reference */

typedef struct S_8009EB20_1 {
    u8 pad_00[0x50];
    void (*unk_50)(TownObjectRecord *, void *, ObjectPosition *, SpriteFrameState *);
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009EB20_1;   /* arg0 in start_move_toward_view_reference */

/*
 * Clears status byte 0x15 and installs move_toward_view_reference with
 * count eight.
 */
void start_move_toward_view_reference(S_8009EB20_1 *state, S_8009EB20_0 *status) {
    status->unk_15 = 0;
    state->unk_50 = &move_toward_view_reference;
    state->unk_6C = 8;
}
