#include "common.h"
#include "engine/graphics.h"
#include "engine/window.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "slus/blinking_cursor_data.h"

extern void copy_texture_descriptor_with_page_offsets(u32 *texture_pos, u32 *src, void *dst);

extern void *texture_descriptor_variant_values[];

/* Updates three data tables and selects an output value and flashing intensity. */
void update_blinking_cursor_with_bright_idle(WindowCursorBody *input, ObjectPosition *unused, SpriteFrameState *output) {
    u8 flags;
    s32 *data;

    if (unlink_cursor_when_finished(input) != 0) {
        return;
    }

    copy_texture_descriptor_with_page_offsets(input->script + 3, blinking_cursor_texture_template_0, blinking_cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(input->script + 3, blinking_cursor_texture_template_1, blinking_cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(input->script + 3, blinking_cursor_texture_template_2, blinking_cursor_texture_descriptor_2);

    data = input->script;
    flags = ((u8 *)data + input->cursor_offset)[0x4C];
    if ((flags & 0x80) != 0) {
        s32 frame;

        input->blink_frame++;
        frame = input->blink_frame;
        if ((frame & 1) != 0) {
            output->color.word = 0xC0C0C0;
        } else {
            output->color.word = 0;
        }
    } else {
        output->color.word = 0xC0C0C0;
    }

    output->source = texture_descriptor_variant_values[(flags & 0x7F) + input->variant_offset];
}
