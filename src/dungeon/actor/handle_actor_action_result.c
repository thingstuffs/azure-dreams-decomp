#include "common.h"
#include "dungeon/system.h"
#include "shared/sprite_frame_state.h"

extern s32 fade_actor_to_removal(s32 value_a, s32 value_b, void *ptr, s32 value_c);

/*
 * Advances removal fading and decrements the bounded counter on completion; otherwise clears the
 * halfword at offset 0x12.
 */
void handle_actor_action_result(s32 value_a, s32 value_b, SpriteFrameState *sprite, s32 value_c) {
    if (fade_actor_to_removal(value_a, value_b, sprite, value_c) != 0) {
        decrement_bounded_counter();
        return;
    }

    sprite->clut = 0;
}
