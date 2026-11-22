#include "common.h"
#include "engine/graphics.h"
#include "engine/text.h"
#include "sdk/libgpu.h"

#include "sdk/libgpu_types.h"

#include "engine/effect/cd_sequence.h"

/* Clears two 64x16 VRAM text regions and draws the two strings at the given row. */
void clear_and_draw_paired_text_rows(s16 row, CdCueSequenceFrame *frame) {
    RECT left_rect;
    RECT right_rect;

    left_rect.x = 0x380;
    left_rect.y = row * 0x10;
    left_rect.w = 0x40;
    left_rect.h = 0x10;
    ClearImage(&left_rect, 0, 0, 0);

    right_rect.x = 0x3C0;
    right_rect.y = row * 0x10;
    right_rect.w = 0x40;
    right_rect.h = 0x10;
    ClearImage(&right_rect, 0, 0, 0);

    draw_double_byte_text(frame->left_text, 0x380, row * 0x10);
    draw_double_byte_text(frame->right_text, 0x3C0, row * 0x10);
}
