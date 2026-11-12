#include "common.h"
#include "engine/graphics.h"
#include "engine/text.h"
#include "sdk/libgpu.h"

#include "sdk/libgpu_types.h"

/* Struct passed as arg1: only offsets 0x8 and 0xC (two text pointers) are
 * touched by this function; the rest is unknown padding. */
typedef struct S_80052C10_Arg1 {
    u8 pad0[8];
    u8 *text8;
    u8 *textC;
} S_80052C10_Arg1;

/* Clears two 64x16 VRAM text regions and draws the two strings at the given row. */
void clear_and_draw_paired_text_rows(s16 row, S_80052C10_Arg1 *texts) {
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

    draw_double_byte_text(texts->text8, 0x380, row * 0x10);
    draw_double_byte_text(texts->textC, 0x3C0, row * 0x10);
}
