#include "engine/window/cursor_body.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

#include "common.h"
#include "engine/window.h"
#include "slus/data.h"


typedef struct S_80037394_1 {
    u8 pad_00[0x4C];
    u8 unk_4C;
} S_80037394_1;   /* temp_v0 + temp_v1 in update_cursor_blink_colors */

extern void copy_texture_descriptor_with_page_offsets(s32 *texture_pos, void *src, void *dst);

/* Updates the current entry's output value and applies its blink color. */
void update_cursor_blink_colors(WindowCursorBody *body, ObjectPosition *position, SpriteFrameState *output_arg) {
    void *state_arg = body;
    WindowCursorBody *state = state_arg;
    SpriteFrameState *output = output_arg;
    u8 entry_flags;
    s8 *entry_data;
    s16 entry_offset;

    if (unlink_cursor_when_finished(state_arg) != 0) {
        return;
    }

    copy_texture_descriptor_with_page_offsets(state->script + 3, cursor_texture_template_0, cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(state->script + 3, cursor_texture_template_1, cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(state->script + 3, cursor_texture_template_2, cursor_texture_descriptor_2);
    copy_texture_descriptor_with_page_offsets(state->script + 3, cursor_texture_template_3, cursor_texture_descriptor_3);
    copy_texture_descriptor_with_page_offsets(state->script + 3, cursor_texture_template_4, cursor_texture_descriptor_4);
    copy_texture_descriptor_with_page_offsets(state->script + 3, cursor_texture_template_5, cursor_texture_descriptor_5);

    entry_data = (s8 *)state->script;
    entry_offset = state->cursor_offset;
    entry_flags = ((S_80037394_1 *)(entry_data + entry_offset))->unk_4C;
    if (entry_flags & 0x80) {
        s32 t;
        state->blink_frame = state->blink_frame + 1;
        t = state->blink_frame;
        if (t & 1) {
            output->color.word = 0xC0C0C0;
        } else {
            output->color.word = 0;
        }
    } else {
        output->color.word = 0xC0C0C0;
    }

    output->source =
        cursor_blink_variant_values[(entry_flags & 0x7F) + state->variant_offset];
}
