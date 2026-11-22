#include "engine/window/cursor_source.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

#include "engine/window.h"
#include "slus/blinking_cursor_data.h"

/* Updates lookup data and selects the current entry's table value and blinking color. */
void update_blinking_cursor_with_dark_idle(WindowCursorBody *state, ObjectPosition *context, SpriteFrameState *output) {
    u8 entry;

    if (unlink_cursor_when_finished(&state->render) != 0) {
        return;
    }

    copy_texture_descriptor_with_page_offsets(&state->script->texture, &blinking_cursor_texture_template_0, &blinking_cursor_texture_descriptor_0.part);
    copy_texture_descriptor_with_page_offsets(&state->script->texture, &blinking_cursor_texture_template_1, &blinking_cursor_texture_descriptor_1.part);
    copy_texture_descriptor_with_page_offsets(&state->script->texture, &blinking_cursor_texture_template_2, &blinking_cursor_texture_descriptor_2.part);

    {
        u8 *entries = (u8 *)state->script + 0x4C;
        s16 entry_index = state->cursor_offset;

        entry = entries[entry_index];
    }
    if (entry & 0x80) {
        s32 count;

        state->blink_frame++;
        count = state->blink_frame;
        if (count & 1) {
            output->color.word = 0xC0C0C0;
        } else {
            output->color.word = 0;
        }
    } else {
        output->color.word = 0;
    }

    output->source = texture_descriptor_variant_values[((entry & 0x7F) + state->variant_offset)];
}
