#include "town/person_callbacks_api.h"
#include "script_symbols.h"
#include "common.h"
#include "engine/object.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"

extern u8 D_800CC524;

// Decrements the countdown and resets the state and color when it expires.
void finish_selfi_magic_fade(TownObjectRecord *state, struct ObjectPosition *unused_position, SpriteFrameState *sprite) {
    if ((s16)(--state->timer) <= 0) {
        set_resident_bitmap_bit(F_selfy_magic_trg);
        state->handler = &D_800CC524;
        state->timer = 0xA;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
    }
}
