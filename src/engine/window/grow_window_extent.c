#include "common.h"

#include "common.h"
#include "engine/audio.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/object.h"
#include "engine/resource.h"
#include "engine/window.h"
#include "engine/window/message.h"

typedef struct Func80035AF8State {
    u8 pad00[0x14];
    s16 x;
    s16 y;
    u8 pad18[0x4C];
    u16 counter;
    u8 pad66[2];
    void (*callback)(void *, void *);
    u8 pad6C[8];
    u8 *read_ptr;
    u8 sound_id;
    s8 sound_arg;
} Func80035AF8State;

/* Display the requested sound and select its next state callback. */
void display_sound_selection_and_prepare_playback(Func80035AF8State *state) {
    u8 sound_id;
    s32 display_value;
    u32 *sound_entry;

    sound_id = state->read_ptr[1];
    if (sound_id == 0) {
        return;
    }
    state->sound_id = sound_id;
    fill_vram_rect(state->x, state->y, 0x30, 0x10, 0, 0, 0);
    display_value = (s32)select_resident_resource_table_value(state->sound_id);
    draw_glyph_row(state->x, state->y, 1, display_value);
    sound_entry = find_sound_table_entry(state->sound_id);
    if (sound_entry != 0) {
        state->sound_arg = ((u8 *)sound_entry)[2];
        if (has_table_entry(state->sound_id, state->sound_arg) != 0) {
            ((u8 *)sound_entry)[2] = ((u8 *)sound_entry)[3];
            clear_fade_manager();
            state->counter = 1;
            state->callback = activate_delayed_window_resource;
            return;
        }
    }
    state->callback = grow_window_extent_to_sixty_four;
}
