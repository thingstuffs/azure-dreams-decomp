#include "common.h"

#include "common.h"

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

extern void window_wait_then_play_sound(void *state);
extern void grow_window_extent_to_sixty_four(void *state, void *progress);
extern s32 func_80035DBC(s32 entry_index);
extern void draw_glyph_row(s16 x, s16 y, s32 spacing_index, s32 glyph_codes);
extern void fill_vram_rect(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);
extern void clear_fade_manager(void);
extern s32 has_table_entry(s32 unused, s32 entry_index);
extern u32 *find_sound_table_entry(s32 sound_id);

/* Display the requested sound and select its next state callback. */
void func_80035AF8(Func80035AF8State *state) {
    u8 sound_id;
    s32 display_value;
    u32 *sound_entry;

    sound_id = state->read_ptr[1];
    if (sound_id == 0) {
        return;
    }
    state->sound_id = sound_id;
    fill_vram_rect(state->x, state->y, 0x30, 0x10, 0, 0, 0);
    display_value = (s32)func_80035DBC(state->sound_id);
    draw_glyph_row(state->x, state->y, 1, display_value);
    sound_entry = find_sound_table_entry(state->sound_id);
    if (sound_entry != 0) {
        state->sound_arg = ((u8 *)sound_entry)[2];
        if (has_table_entry(state->sound_id, state->sound_arg) != 0) {
            ((u8 *)sound_entry)[2] = ((u8 *)sound_entry)[3];
            clear_fade_manager();
            state->counter = 1;
            state->callback = window_wait_then_play_sound;
            return;
        }
    }
    state->callback = grow_window_extent_to_sixty_four;
}
