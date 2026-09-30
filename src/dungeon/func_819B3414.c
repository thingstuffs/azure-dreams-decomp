#include "common.h"
#include "shared/game_work.h"

typedef struct Quad {
    u32 tag;
    u32 color0;
    u32 xy0;
    u32 color1;
    u32 xy1;
    u32 color2;
    u32 xy2;
    u32 color3;
    u32 xy3;
} Quad;

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

extern s32 func_800644B8();
extern s32 func_80064710();
extern s32 func_80065420();
extern s32 func_80066460();
extern s32 func_80066640();
extern s32 func_80066708();
extern s32 func_80067F20();

/* Draw fading radial grids of shaded quads for the linked effects. */
s32 func_80024C14(void *effect_data) {
    u16 vertex[3];
    u32 screen_grid[16][16];
    s32 depth_cue;
    s32 projection_flags;
    u8 *effect;
    u8 *next_effect;
    GameWork *gw = &gameWork;
    u8 *scratch = (u8 *)0x1f800000;
    s32 grid_last = 15;

    do {
        effect = (u8 *)effect_data;

        {
            s32 seed_index = 7;
            u32 *seed_color;
            seed_color = (u32 *)scratch + 7;
            seed_loop: {
                s32 phase;
                s32 shade;
                s32 upper_channels;
                phase = seed_index + *(s16 *)(effect + 0x48);
                shade = func_800644B8(phase * 1200);
                shade = (shade >> 7) + 32;
                upper_channels = (shade << 8) + (shade << 16);
                shade += upper_channels;
                *seed_color = shade;
                seed_color--;
            } if (--seed_index >= 0) goto seed_loop;
        }

        {
            s32 row;
            for (row = 0; row < 16; row++) {
                s32 row_offset;
                s32 column;
                column = 0;
                row_offset = row << 6;
                do {
                    s32 dx_square;
                    s32 dy_square;
                    s32 distance;
                    s32 shade;
                    s32 faded_shade;
                    s32 column_offset = column << 6;

                    vertex[0] = *(u16 *)(effect + 0x0c) + column_offset;
                    vertex[1] = *(u16 *)(effect + 0x0e) + row_offset;
                    vertex[2] = *(u16 *)(effect + 0x10);
                    func_80065420(vertex, &screen_grid[column][row],
                        &depth_cue, &projection_flags);

                    vertex[0] -= *(u16 *)(effect + 4);
                    dx_square = (s16)vertex[0] * (s16)vertex[0];
                    vertex[1] -= *(u16 *)(effect + 6);
                    dy_square = (s16)vertex[1] * (s16)vertex[1];
                    distance = func_80064710(dx_square + dy_square);
                    shade = func_800644B8(
                        100 * (distance >> 2) -
                        (*(s16 *)(effect + 0x48) << 8));
                    shade = (shade >> 7) + 32;
                    faded_shade = shade * (32 - *(s16 *)(effect + 0x48));
                    depth_cue = shade;
                    if (faded_shade < 0) {
                        faded_shade += 31;
                    }
                    {
                        u8 *color_column;
                        color_column = (u8 *)(column << 2);
                        column++;
                        faded_shade >>= 5;
                        color_column = (u8 *)((u32)color_column + (u32)scratch);
                        depth_cue = faded_shade;
                        *(u32 *)(row_offset + (u32)color_column) =
                            faded_shade + (faded_shade << 8) + (faded_shade << 16);
                    }
                } while (column < 16);
            }
        }

        {
            s32 age = *(s16 *)(effect + 0x48);
            s32 first_cell;
            s32 row;
            s32 row_limit;

            if (age < 7) {
                first_cell = 7 - age;
            } else {
                first_cell = 0;
            }
            row = first_cell;
            row_limit = grid_last - row;

            if (row < row_limit) {
                s32 saved_row_limit = row_limit;
                s32 draw_row = 1;
                do {
                    s32 column;
                    column = first_cell;
                    if (draw_row) {
                        s32 row_offset = row << 6;
                        s32 column_limit;
                        u8 *color_column;

                        do {
                            Quad *quad;
                            u8 *vertex_colors;
                            color_column = (u8 *)((column << 2) + (u32)scratch);

                            {
                                u8 *packet_pool;
                                packet_pool = (u8 *)gw->unk_000;
                                quad = *(Quad **)(packet_pool + 0x8d0);
                                *(Quad **)(packet_pool + 0x8d0) = quad + 1;
                            }

                            vertex_colors = (u8 *)(row_offset + (u32)color_column);
                            quad->color0 = *(u32 *)(vertex_colors + 0);
                            quad->color1 = *(u32 *)(vertex_colors + 64);
                            quad->color2 = *(u32 *)(vertex_colors + 4);
                            quad->color3 = *(u32 *)(vertex_colors + 68);
                            func_80066708(quad);
                            func_80066640(quad, 1);

                            quad->xy0 = screen_grid[column][row];
                            quad->xy1 = screen_grid[column][row + 1];
                            quad->xy2 = screen_grid[column + 1][row];
                            quad->xy3 = screen_grid[column + 1][row + 1];
                            column++;
                            {
                                s32 last_vertex = 15;
                                column_limit = last_vertex - first_cell;
                            }

                            ((P_TAG *)quad)->addr = ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr;
                            ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr = (u32)quad;
                        } while (column < column_limit);
                    }
                    row++;
                } while (row < saved_row_limit);
            }
        }

        {
            u8 *draw_mode;
            s32 texture_page;

            {
                u8 *packet_pool;
                packet_pool = (u8 *)gw->unk_000;
                draw_mode = *(u8 **)(packet_pool + 0x8d0);
                *(u8 **)(packet_pool + 0x8d0) = draw_mode + 12;
            }
            texture_page = func_80066460(0, 2, 0, 0);
            func_80067F20(draw_mode, 0, 0, texture_page & 0xffff, 0);

            ((P_TAG *)draw_mode)->addr = ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr;
            ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr = (u32)draw_mode;
        }

        next_effect = *(u8 **)((u8 *)effect_data - 8);
        if (next_effect == 0) break;
        next_effect += 32;
        effect_data = next_effect;
    } while (1);

    return 0;
}
