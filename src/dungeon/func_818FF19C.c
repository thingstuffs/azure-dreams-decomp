#include "common.h"

typedef struct S_818FF19C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    s16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x24];
    void * unk_30;
    void * unk_34;
    void * unk_38;
    void * unk_3C;
} S_818FF19C_0;   /* arg0 in func_818FF19C */

typedef struct S_818FF19C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818FF19C_1;   /* arg1 in func_818FF19C */

typedef struct S_818FF19C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_818FF19C_2;   /* arg2 in func_818FF19C */

typedef struct S_818FF19C_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_818FF19C_3;   /* ((S_818FF19C_0 *)arg0)->unk_34 in func_818FF19C */

typedef struct S_818FF19C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF19C_4;   /* ((S_818FF19C_0 *)arg0)->unk_30 in func_818FF19C */



typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} __attribute__((packed)) Rect8;

extern Rect8 D_80024028;
extern Rect8 D_80024030;
extern s16 D_80025E80;
extern u16 D_80025EE8[];
extern s32 D_800814A0;

extern void func_80024A54() __attribute__((noreturn));
extern void func_80024AEC() __attribute__((noreturn));
extern void func_80024D54() __attribute__((noreturn));
extern s32 func_80067014(s32);
extern void func_800672D8(Rect8 *, u16 *);
extern void func_8006733C(Rect8 *, u16 *);
extern void func_800B8FC8(void *, Rect8 *, s16 *, s32, s32);

/* Updates the tiled texture and draws a moving, fading effect until completion. */
void func_818FF19C(void *effect, void *offset_state, void *render_state) {
    Rect8 *end_rect;
    Rect8 moving_rect;
    Rect8 tile_rect;
    s16 draw_pos[2];
    s32 tile_col;
    s32 tile_row;
    s32 pixel_index;
    s32 rounded_frame;
    s32 y_offset;
    s32 stage;
    s32 offset_applied;
    s16 column_x;
    s16 tile_x;
    s16 tile_y;
    u16 fill_pixel;
    u8 *buffer_base;
    s32 frame;
    s16 next_frame;
    u16 *pixel;

    moving_rect = D_80024028;
    tile_rect = D_80024030;
    offset_applied = ((S_818FF19C_0 *)effect)->unk_0A;
    D_80025E80 = 1;
    if (offset_applied == 0) {
        s32 old_offset;
        s32 offset_step;

        ((S_818FF19C_0 *)effect)->unk_0A = 1;
        old_offset = ((S_818FF19C_1 *)offset_state)->unk_08;
        offset_step = -0x20000;
        ASM_KEEP(old_offset);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(offset_step);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024A54();
    }

    ((S_818FF19C_0 *)effect)->unk_0A = 0;
    ((S_818FF19C_1 *)offset_state)->unk_08 += 0x20000;
    stage = ((S_818FF19C_0 *)effect)->unk_00.s;
    if (stage != 0) {
        if (stage != 1) {
            end_rect = &tile_rect;
            func_80024D54();
        }
        goto draw;
    }

    tile_col = 0;
    buffer_base = (u8 *)0x80020000;
    fill_pixel = 0xFFFF;
    column_x = 0x340;
    do {
        tile_row = 0;
        tile_x = column_x;
        tile_y = 0x154;
        do {
            tile_rect.x = tile_x;
            tile_rect.y = tile_y;
            tile_rect.w = 0x18;
            tile_rect.h = 0x15;
            func_8006733C(&tile_rect, (u16 *)(buffer_base + 0x5EE8));
            do {
            } while (func_80067014(1) != 0);

            pixel = (u16 *)(buffer_base + 0x5EE8);
            pixel_index = 0;
            do {
                if (*pixel == 0) {
                    *pixel = fill_pixel;
                    func_80024AEC(pixel_index);
                }
                *pixel = 0;
                pixel_index++;
                pixel++;
            } while (pixel_index < 0x1F8);

            func_800672D8(&tile_rect, (u16 *)(buffer_base + 0x5EE8));
            tile_row++;
            tile_y += 0x15;
        } while (tile_row < 4);

        tile_col++;
        column_x += 0x18;
    } while (tile_col < 4);

    ((S_818FF19C_0 *)effect)->unk_00.u++;
    ((S_818FF19C_2 *)render_state)->unk_14 &= 0xFF7F;

draw:
    tile_rect.x = 0x340;
    tile_rect.y = 0x100;
    tile_rect.w = 0x60;
    tile_rect.h = 0x54;
    draw_pos[0] = 0x370;
    draw_pos[1] = 0x148;
    func_800B8FC8(((S_818FF19C_0 *)effect)->unk_38, &tile_rect, draw_pos, 0, 1);

    draw_pos[0] = moving_rect.x + (moving_rect.w >> 1) - 6;
    rounded_frame = ((S_818FF19C_0 *)effect)->unk_02;
    if (rounded_frame < 0) {
        rounded_frame += 3;
    }
    y_offset = (rounded_frame >> 2) - 0x4E;
    draw_pos[1] = moving_rect.y - y_offset;
    func_800B8FC8(((S_818FF19C_0 *)effect)->unk_3C, &moving_rect, draw_pos, 1, 1);

    frame = ((S_818FF19C_0 *)effect)->unk_02;
    if (frame < 0x15) {
        ((S_818FF19C_2 *)render_state)->unk_0E = (frame << 7) / 20;
        ((S_818FF19C_2 *)render_state)->unk_0D = (((S_818FF19C_0 *)effect)->unk_02 << 7) / 20;
        ((S_818FF19C_2 *)render_state)->unk_0C = (((S_818FF19C_0 *)effect)->unk_02 << 7) / 20;
    }
    if (((S_818FF19C_0 *)effect)->unk_02 >= 0x51) {
        ((S_818FF19C_2 *)render_state)->unk_0E = ((0x64 - ((S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
        ((S_818FF19C_2 *)render_state)->unk_0D = ((0x64 - ((S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
        ((S_818FF19C_2 *)render_state)->unk_0C = ((0x64 - ((S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
    }

    next_frame = (u16)((S_818FF19C_0 *)effect)->unk_02 + 1;
    ((S_818FF19C_0 *)effect)->unk_02 = next_frame;
    if (next_frame >= 0x65) {
        ((S_818FF19C_0 *)effect)->unk_02 = 0;
        ((S_818FF19C_0 *)effect)->unk_00.u++;
        ((S_818FF19C_3 *)(((S_818FF19C_0 *)effect)->unk_34))->unk_90 = 1;
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if ((u32)(((S_818FF19C_4 *)(((S_818FF19C_0 *)effect)->unk_30))->unk_13 - 0x33) < 4U) {
        ((S_818FF19C_2 *)render_state)->unk_14 |= 0x80;
    }
}
