#include "common.h"
#include "dungeon/menu.h"
#include "shared/object_node.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/dungeon_floor.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "dungeon/system.h"

typedef struct {
    s32 first;
    u8 pad04[0x2968];
    s32 last;
} E296C;

/* Interpolate target values after a delay, then reduce its counter to zero and update flags. */
void interpolate_delayed_target_values(MapMarkerRevealBody *state, ObjectPosition *unused, SpriteFrameState *sprite) {
    u16 ticks_left;
    u16 target_counter;
    E296C *global_state;
    s32 *status_flags;
    s32 prior_flags;
    s32 state_flags;
    s32 merged_flags;
    s32 cleared_flags;

    if (state->phase == 0) {
        ticks_left = state->ticks_left - 1;
        state->ticks_left = ticks_left;
        if ((s16)ticks_left <= 0) {
            register_node(NODE_HEADER(state), draw_linked_sprites);
            state->ticks_left = 8;
            state->phase++;
            play_sound_if_enabled(0x80F);
        }
    } else if (state->phase == 1) {
        sprite->color.c.r += (state->color.c.r - sprite->color.c.r) / (s16)state->ticks_left;
        sprite->color.c.g += (state->color.c.g - sprite->color.c.g) / (s16)state->ticks_left;
        sprite->color.c.b += (state->color.c.b - sprite->color.c.b) / (s16)state->ticks_left;
        ticks_left = state->ticks_left - 1;
        state->ticks_left = ticks_left;
        if ((s16)ticks_left <= 0) {
            sprite->color.word = state->color.word;
            state->ticks_left = 0x10;
            state->phase++;
            return;
        }
    } else {
        target_counter = sprite->scale_x;
        target_counter -= target_counter / (s16)state->ticks_left;
        sprite->scale_x = target_counter;
        sprite->scale_y = target_counter;
        ticks_left = state->ticks_left - 1;
        state->ticks_left = ticks_left;
        if ((s16)ticks_left <= 0) {
            global_state = ((E296C *)&dungeon_floor_flags);
            prior_flags = global_state->first;
            state_flags = state->floor_flags;
            merged_flags = prior_flags | state_flags;
            global_state->first = merged_flags;
            *(u16 *)((u8 *)state - 2) |= 0x8000;
            status_flags = ((s32 *)(&object_flag_block));
            status_flags[0] |= 0x8000;
            if (state->mode == 0) {
                cleared_flags = merged_flags & 0xFFFBFFFF;
                global_state->first = cleared_flags;
            }
        }
    }

    return;
}
