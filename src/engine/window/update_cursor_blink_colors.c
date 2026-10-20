#include "common.h"

#include "common.h"

typedef struct S_80037394_0 {
    u8 pad_00[0x44];
    s32 * unk_44;
    u8 pad_48[0x2];
    s16 unk_4A;
    u8 pad_4C[0x18];
    u16 unk_64;
    s16 unk_66;
} S_80037394_0;   /* arg0 in update_cursor_blink_colors */

typedef struct S_80037394_1 {
    u8 pad_00[0x4C];
    u8 unk_4C;
} S_80037394_1;   /* temp_v0 + temp_v1 in update_cursor_blink_colors */

typedef struct S_80037394_2 {
    u8 pad_00[0x8];
    u32 unk_08;
    s32 unk_0C;
} S_80037394_2;   /* arg2 in update_cursor_blink_colors */


extern s32 unlink_cursor_when_finished(void *state);
extern void copy_texture_descriptor_with_page_offsets(s32 *texture_pos, void *src, void *dst);

extern u8 cursor_texture_template_0[];
extern u8 cursor_texture_template_1[];
extern u8 cursor_texture_template_2[];
extern u8 cursor_texture_template_3[];
extern u8 cursor_texture_template_4[];
extern u8 cursor_texture_template_5[];
extern u32 cursor_blink_variant_values[];
extern u8 cursor_texture_descriptor_4[];
extern u8 cursor_texture_descriptor_5[];
extern u8 cursor_texture_descriptor_0[];
extern u8 cursor_texture_descriptor_1[];
extern u8 cursor_texture_descriptor_2[];
extern u8 cursor_texture_descriptor_3[];

/* Updates the current entry's output value and applies its blink color. */
void update_cursor_blink_colors(void *state, s32 mode, void *output) {
    u8 entry_flags;
    s8 *entry_data;
    s16 entry_offset;

    if (unlink_cursor_when_finished(state) != 0) {
        return;
    }

    copy_texture_descriptor_with_page_offsets(((S_80037394_0 *)state)->unk_44 + 3, cursor_texture_template_0, cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(((S_80037394_0 *)state)->unk_44 + 3, cursor_texture_template_1, cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(((S_80037394_0 *)state)->unk_44 + 3, cursor_texture_template_2, cursor_texture_descriptor_2);
    copy_texture_descriptor_with_page_offsets(((S_80037394_0 *)state)->unk_44 + 3, cursor_texture_template_3, cursor_texture_descriptor_3);
    copy_texture_descriptor_with_page_offsets(((S_80037394_0 *)state)->unk_44 + 3, cursor_texture_template_4, cursor_texture_descriptor_4);
    copy_texture_descriptor_with_page_offsets(((S_80037394_0 *)state)->unk_44 + 3, cursor_texture_template_5, cursor_texture_descriptor_5);

    entry_data = (s8 *)((S_80037394_0 *)state)->unk_44;
    entry_offset = ((S_80037394_0 *)state)->unk_4A;
    entry_flags = ((S_80037394_1 *)(entry_data + entry_offset))->unk_4C;
    if (entry_flags & 0x80) {
        s32 t;
        ((S_80037394_0 *)state)->unk_64 = ((S_80037394_0 *)state)->unk_64 + 1;
        t = ((S_80037394_0 *)state)->unk_64;
        if (t & 1) {
            ((S_80037394_2 *)output)->unk_0C = 0xC0C0C0;
        } else {
            ((S_80037394_2 *)output)->unk_0C = 0;
        }
    } else {
        ((S_80037394_2 *)output)->unk_0C = 0xC0C0C0;
    }

    ((S_80037394_2 *)output)->unk_08 =
        cursor_blink_variant_values[(entry_flags & 0x7F) + ((S_80037394_0 *)state)->unk_66];
}
