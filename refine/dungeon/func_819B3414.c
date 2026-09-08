#include "common.h"

extern s32 func_800644B8();
extern s32 func_80064710();
extern s32 func_80065420();
extern s32 func_80066460();
extern s32 func_80066640();
extern s32 func_80066708();
extern s32 func_80067F20();
extern void *D_80083160[];

/* Draw fading radial grids of shaded quads for the linked effects. */
s32 func_80024C14(void *effect_data) {
    u16 vertex[3];
    u32 screen_grid[16][16];
    s32 depth_cue;
    s32 projection_flags;
    u8 *effect;
    register u32 link_mask ASM_REG("$22") = 0x00ffffff;   /* MATCH pin: keeps a statement from moving across a call/branch */
    u32 frame_scratch;
    register u8 *next_effect ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    do {
        effect = (u8 *)effect_data;
        ASM_KEEP_MEMDEP(effect, frame_scratch, effect_data);   /* MATCH pin: retail callee-saved set / frame layout depends on it */

        {
            s32 seed_index = 7;
            u32 *seed_color;
            register u32 *seed_colors ASM_REG("$8") = (u32 *)0x1f800000;   /* MATCH pin: retail register colouring depends on it */

            ASM_KEEP_NV(seed_colors);   /* MATCH pin: load-bearing for the whole function shape */
            seed_color = seed_colors + 7;
            do {
                s32 phase;
                s32 shade;
                s32 upper_channels;
                phase = seed_index + *(s16 *)(effect + 0x48);
                shade = func_800644B8((phase * 75) << 4);
                shade = (shade >> 7) + 32;
                upper_channels = (shade << 8) + (shade << 16);
                shade += upper_channels;
                *seed_color = shade;
                seed_color--;
            } while (--seed_index >= 0);
        }

        {
            s32 row;
            for (row = 0; row < 16; row++) {
                s32 row_offset;
                s32 column;
                column = 0;
                row_offset = row << 6;
                do {
                    register s32 dx ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                    register s32 dx_square ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    register s32 dy ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                    register s32 dy_square ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
                    s32 distance;
                    s32 shade;
                    s32 faded_shade;
                    u16 *vertex_arg = vertex;
                    s32 column_offset = column << 6;
                    register u8 *screen_column ASM_REG("$3") =
                        (u8 *)screen_grid + column_offset;
                    register s32 row_word_offset ASM_REG("$5") = row << 2;   /* MATCH pin: load-bearing for the whole function shape */

                    ASM_KEEP_NV(vertex_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    row_word_offset = (u32)screen_column + row_word_offset;

                    vertex[0] = *(u16 *)(effect + 0x0c) + column_offset;
                    vertex[1] = *(u16 *)(effect + 0x0e) + row_offset;
                    vertex[2] = *(u16 *)(effect + 0x10);
                    func_80065420(vertex_arg, (u32 *)row_word_offset,
                        &depth_cue, &projection_flags);

                    vertex[0] -= *(u16 *)(effect + 4);
                    dx = (s16)vertex[0];
                    dx_square = dx * dx;
                    vertex[1] -= *(u16 *)(effect + 6);
                    dy = (s16)vertex[1];
                    dy_square = dy * dy;
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
                        register u8 *color_base ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                        u8 *color_column;
                        color_column = (u8 *)(column << 2);
                        column++;
                        faded_shade >>= 5;
                        color_base = (u8 *)0x1f800000;
                        color_column = (u8 *)((u32)color_column + (u32)color_base);
                        depth_cue = faded_shade;
                        *(volatile u32 *)(row_offset + (u32)color_column) =
                            faded_shade + (faded_shade << 8) + (faded_shade << 16);
                    }
                } while (column < 16);
            }
        }

        {
            s32 age = *(s16 *)(effect + 0x48);
            register s32 first_cell ASM_REG("$21");   /* MATCH pin: retail register colouring depends on it */
            register s32 row ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
            register s32 row_limit ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

            if (age < 7) {
                register s32 start_radius ASM_REG("$2") = 7;   /* MATCH pin: retail register colouring depends on it */
                first_cell = start_radius - age;
            } else {
                first_cell = 0;
            }
            {
                register s32 last_vertex ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                row = first_cell;
                last_vertex = 15;
                row_limit = last_vertex - row;
            }

            if (row < row_limit) {
                volatile s32 saved_row_limit = row_limit;
                register s32 loop_limit ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                register s32 more_rows ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                do {
                    register s32 draw_row ASM_REG("$8") = 1;   /* MATCH pin: retail register colouring depends on it */
                    register s32 column ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
                    ASM_KEEP_NV(draw_row);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    column = first_cell;
                    if (draw_row) {
                        register s32 row_offset = row << 6;
                        s32 row_word_offset = row << 2;
                        s32 column_limit;
                        register u8 *color_column ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                        {
                            s32 last_vertex = 15;
                            column_limit = last_vertex - column;
                        }
                        {
                            register s32 column_byte_offset ASM_REG("$2") = column << 2;   /* MATCH pin: retail register colouring depends on it */
                            register u8 *color_table ASM_REG("$8") =
                                (u8 *)0x1f800000;
                            color_column = (u8 *)(column_byte_offset + (u32)color_table);
                        }

                        do {
                            u8 *quad;
                            u32 first_screen_xy;
                            register void **render_globals ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                            u8 *vertex_colors;

                            {
                                u8 *packet_pool;
                                register void **render_globals ASM_REG("$8") = D_80083160;   /* MATCH pin: retail register colouring depends on it */
                                ASM_KEEP_NV(render_globals);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                                packet_pool = (u8 *)render_globals[0];
                                quad = *(u8 **)(packet_pool + 0x8d0);
                                *(u8 **)(packet_pool + 0x8d0) = quad + 36;
                            }

                            vertex_colors = (u8 *)(row_offset + (u32)color_column);
                            *(u32 *)(quad + 4) = *(u32 *)(vertex_colors + 0);
                            *(u32 *)(quad + 12) = *(u32 *)(vertex_colors + 64);
                            *(u32 *)(quad + 20) = *(u32 *)(vertex_colors + 4);
                            *(u32 *)(quad + 28) = *(u32 *)(vertex_colors + 68);
                            func_80066708(quad);
                            func_80066640(quad, 1);

                            {
                                s32 screen_column_offset = column << 6;
                                register u8 *screen_vertex ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

                                screen_vertex = (u8 *)(screen_column_offset + (u32)screen_grid - 32);
                                ASM_KEEP_NV(screen_vertex);   /* MATCH pin: load-bearing for the whole function shape */
                                screen_vertex += 32;
                                screen_vertex = (u8 *)(row_word_offset + (u32)screen_vertex);
                                render_globals = (void **)0x80080000;
                                ASM_KEEP_NV(render_globals);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                                first_screen_xy = *(u32 *)(screen_vertex + 0);
                                ASM_KEEP(first_screen_xy);   /* MATCH pin: keeps a statement from moving across a call/branch */
                                render_globals = (void **)((u8 *)render_globals + 0x3160);
                                ASM_KEEP_NV(render_globals);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                                *(u32 *)(quad + 8) = first_screen_xy;
                                *(u32 *)(quad + 16) = *(u32 *)(screen_vertex + 4);
                                screen_vertex = (u8 *)screen_grid + 64;
                                screen_vertex += screen_column_offset;
                                screen_vertex = (u8 *)(row_word_offset + (u32)screen_vertex);
                                *(u32 *)(quad + 24) = *(u32 *)(screen_vertex + 0);
                                *(u32 *)(quad + 32) = *(u32 *)(screen_vertex + 4);
                                column++;
                            }

                            {
                                u8 *order_head;
                                u32 packet_length;
                                order_head = (u8 *)render_globals[0];
                                ASM_KEEP_NV(order_head);   /* MATCH pin: load-bearing for the whole function shape */
                                {
                                    register u32 length_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
                                    packet_length = *(u32 *)quad & length_mask;
                                }
                                {
                                    register void **link_globals ASM_REG("$8") =
                                        (void **)0x80080000;
                                    u8 *render_state;
                                    ASM_KEEP_NV(link_globals);   /* MATCH pin: keeps a statement from moving across a call/branch */
                                    order_head = (u8 *)(u32)*(u32 *)(order_head + 0xb0);
                                    ASM_KEEP_NV(order_head);   /* MATCH pin: load-bearing for the whole function shape */
                                    link_globals = (void **)((u8 *)link_globals + 0x3160);
                                    ASM_KEEP_NV(link_globals);   /* MATCH pin: keeps a statement from moving across a call/branch */
                                    *(u32 *)quad = packet_length | ((u32)order_head & link_mask);
                                    render_state = (u8 *)link_globals[0];
                                    {
                                        register u32 length_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
                                        ASM_KEEP_NV(length_mask);
                                        *(u32 *)(render_state + 0xb0) =
                                            (*(u32 *)(render_state + 0xb0) & length_mask) |
                                            ((u32)quad & link_mask);
                                    }
                                }
                            }
                        } while (column < column_limit && (color_column += 4, 1));
                    }
                    loop_limit = saved_row_limit;
                    row++;
                    more_rows = row < loop_limit;
                } while (more_rows);
            }
        }

        {
            u8 *draw_mode;
            s32 texture_page;

            {
                s32 zero_arg = 0;
                s32 blend_mode = 2;
                u8 *packet_pool;
                register void **render_globals ASM_REG("$8") = D_80083160;   /* MATCH pin: retail register colouring depends on it */
                ASM_KEEP_NV(zero_arg);
                ASM_KEEP_NV(blend_mode);
                ASM_KEEP_NV(render_globals);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                packet_pool = (u8 *)render_globals[0];
                draw_mode = *(u8 **)(packet_pool + 0x8d0);

                *(u8 **)(packet_pool + 0x8d0) = draw_mode + 12;
                texture_page = func_80066460(zero_arg, blend_mode, zero_arg, zero_arg);
            }
            {
                register u8 *packet_arg ASM_REG("$4") = draw_mode;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                s32 zero_arg = 0;
                ASM_KEEP_NV(packet_arg);
                ASM_KEEP_NV(zero_arg);
                func_80067F20(packet_arg, zero_arg, zero_arg,
                    texture_page & 0xffff, 0);
            }

            {
                u8 *order_head;
                u32 packet_tag;
                register void **render_globals ASM_REG("$8") = D_80083160;   /* MATCH pin: retail register colouring depends on it */
                ASM_KEEP_NV(render_globals);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                order_head = (u8 *)render_globals[0];
                ASM_KEEP_NV(order_head);   /* MATCH pin: load-bearing for the whole function shape */
                packet_tag = *(u32 *)draw_mode;
                ASM_KEEP_NV(packet_tag);
                {
                    register u32 length_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
                    packet_tag &= length_mask;
                }
                {
                    register void **link_globals ASM_REG("$8") =
                        (void **)0x80080000;
                    u8 *render_state;
                    ASM_KEEP_NV(link_globals);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    order_head = (u8 *)(u32)*(u32 *)(order_head + 0xb0);
                    ASM_KEEP_NV(order_head);   /* MATCH pin: load-bearing for the whole function shape */
                    link_globals = (void **)((u8 *)link_globals + 0x3160);
                    ASM_KEEP_NV(link_globals);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    *(u32 *)draw_mode = packet_tag | ((u32)order_head & link_mask);
                    render_state = (u8 *)link_globals[0];
                    {
                        register u32 length_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
                        *(u32 *)(render_state + 0xb0) =
                            (*(u32 *)(render_state + 0xb0) & length_mask) |
                            ((u32)draw_mode & link_mask);
                    }
                }
            }
        }

        {
            register u8 *effect_cursor ASM_REG("$8") = (u8 *)effect_data;   /* MATCH pin: retail register colouring depends on it */
            next_effect = *(u8 **)(effect_cursor - 8);
        }
    } while (next_effect != 0 && (effect_data = next_effect + 32, 1));

    return 0;
}
