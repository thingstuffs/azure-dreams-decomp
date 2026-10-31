#include "common.h"
#include "engine/window.h"
#include "shared/entity.h"

typedef struct {
    u8 pad_00[0x44];
    u32 *data;
    u8 enabled;
    s16 data_index;
    u8 pad_4c[0x18];
    u16 frame;
    s16 table_offset;
} FuncInput;

typedef struct {
    u8 pad_00[8];
    u32 value_08;
    u32 value_0c;
} FuncOutput;

extern void copy_texture_descriptor_with_page_offsets(u32 *texture_pos, u32 *src, void *dst);

extern u32 blinking_cursor_texture_template_0[3];
extern u32 blinking_cursor_texture_template_1[3];
extern u32 blinking_cursor_texture_template_2[3];
extern u32 texture_descriptor_variant_values[128];
extern u32 blinking_cursor_texture_descriptor_0[6];
extern u32 blinking_cursor_texture_descriptor_1[6];
extern u32 blinking_cursor_texture_descriptor_2[6];

/* Updates three data tables and selects an output value and flashing intensity. */
void update_blinking_cursor_with_bright_idle(FuncInput *input, ObjectPosition *unused, FuncOutput *output) {
    u8 flags;
    u32 *data;

    if (unlink_cursor_when_finished(input) != 0) {
        return;
    }

    copy_texture_descriptor_with_page_offsets(input->data + 3, blinking_cursor_texture_template_0, blinking_cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(input->data + 3, blinking_cursor_texture_template_1, blinking_cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(input->data + 3, blinking_cursor_texture_template_2, blinking_cursor_texture_descriptor_2);

    data = input->data;
    flags = ((u8 *)data + input->data_index)[0x4C];
    if ((flags & 0x80) != 0) {
        s32 frame;

        input->frame++;
        frame = input->frame;
        if ((frame & 1) != 0) {
            output->value_0c = 0xC0C0C0;
        } else {
            output->value_0c = 0;
        }
    } else {
        output->value_0c = 0xC0C0C0;
    }

    output->value_08 = texture_descriptor_variant_values[(flags & 0x7F) + input->table_offset];
}
