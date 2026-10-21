#include "common.h"

#include "common.h"
#include "engine/window.h"

typedef struct {
    u8 unk00[0x44];
    u8 *base;
    u8 unk48[2];
    s16 index;
    u8 unk4c[0x18];
    u16 counter;
    s16 table_index;
} Func37090Input;

typedef struct {
    u8 unk00[8];
    u32 table_value;
    u32 color;
} Func37090Output;

extern void copy_texture_descriptor_with_page_offsets(u8 *, u8 *, u8 *);

extern u32 blinking_cursor_texture_template_0[3];
extern u32 blinking_cursor_texture_template_1[3];
extern u32 blinking_cursor_texture_template_2[3];
extern u32 texture_descriptor_variant_values[32];
extern u8 blinking_cursor_texture_descriptor_0[16];
extern u8 blinking_cursor_texture_descriptor_1[16];
extern u8 blinking_cursor_texture_descriptor_2[16];

/* Updates lookup data and selects the current entry's table value and blinking color. */
void update_blinking_cursor_with_dark_idle(Func37090Input *state, void *context, Func37090Output *output) {
    u8 entry;

    if (unlink_cursor_when_finished(state) != 0) {
        return;
    }

    copy_texture_descriptor_with_page_offsets(state->base + 0xC, (u8 *)blinking_cursor_texture_template_0, blinking_cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(state->base + 0xC, (u8 *)blinking_cursor_texture_template_1, blinking_cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(state->base + 0xC, (u8 *)blinking_cursor_texture_template_2, blinking_cursor_texture_descriptor_2);

    {
        u8 *entries = state->base + 0x4C;
        s16 entry_index = state->index;

        entry = entries[entry_index];
    }
    if (entry & 0x80) {
        s32 count;

        state->counter++;
        count = state->counter;
        if (count & 1) {
            output->color = 0xC0C0C0;
        } else {
            output->color = 0;
        }
    } else {
        output->color = 0;
    }

    output->table_value = texture_descriptor_variant_values[((entry & 0x7F) + state->table_index)];
}
