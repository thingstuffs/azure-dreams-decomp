#include "modules/dungeon_ovl_191eef8.h"

void func_8002499C(void *effect, void *offset_state, void *render_state) {
    Row_818FF19C_Rect8 moving_rect;
    Row_818FF19C_Rect8 tile_rect;
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
    offset_applied = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_0A;
    (*(s16 *)D_80025E80) = 1;
    if (offset_applied == 0) {
        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_0A = 1;
        ((Row_818FF19C_S_818FF19C_1 *)offset_state)->unk_08 += -0x20000;
    } else {
        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_0A = 0;
        ((Row_818FF19C_S_818FF19C_1 *)offset_state)->unk_08 += 0x20000;
    }
    stage = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_00.s;
    switch (stage) {
    case 0:
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
                    } else {
                        *pixel = 0;
                    }
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

        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_00.u++;
        ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_14 &= 0xFF7F;

    case 1:
        tile_rect.x = 0x340;
        tile_rect.y = 0x100;
        tile_rect.w = 0x60;
        tile_rect.h = 0x54;
        draw_pos[0] = 0x370;
        draw_pos[1] = 0x148;
        func_800B8FC8(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_38, &tile_rect, draw_pos, 0, 1);

        draw_pos[0] = moving_rect.x + (moving_rect.w >> 1) - 6;
        rounded_frame = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02;
        y_offset = (rounded_frame / 4) - 0x4E;
        draw_pos[1] = moving_rect.y - y_offset;
        func_800B8FC8(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_3C, &moving_rect, draw_pos, 1, 1);

        frame = ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02;
        if (frame < 0x15) {
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0E = (frame << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0D = (((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0C = (((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 << 7) / 20;
        }
        if (((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 >= 0x51) {
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0E = ((0x64 - ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0D = ((0x64 - ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
            ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_0C = ((0x64 - ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02) << 7) / 20;
        }

        next_frame = (u16)((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 + 1;
        ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 = next_frame;
        if (next_frame >= 0x65) {
            ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_02 = 0;
            ((Row_818FF19C_S_818FF19C_0 *)effect)->unk_00.u++;
            ((Row_818FF19C_S_818FF19C_3 *)(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_34))->unk_90 = 1;
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }

    if ((u32)(((Row_818FF19C_S_818FF19C_4 *)(((Row_818FF19C_S_818FF19C_0 *)effect)->unk_30))->unk_13 - 0x33) < 4U) {
        ((Row_818FF19C_S_818FF19C_2 *)render_state)->unk_14 |= 0x80;
    }
}
