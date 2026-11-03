#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "engine/object.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "shared/scratchpad.h"
#include "shared/vector.h"
#include "slus/data.h"


extern u8 effect_view_matrix[32];
extern u8 sprite_projection_matrix[32];

/* Renders linked textured sprites with dimmed offset copies near the screen center. */
s32 runtime_render_linked_textured_sprites(u8 *node_data, ObjectPosition *position, u8 *render_state)
{
    ScratchPad *scratch;
    GteMatrix *fixed_matrix;
    s32 base_x;
    s32 center_x;
    s32 center_y;
    u16 base_y;
    s32 copies;
    s32 copy_index;
    s32 sin_x;
    s32 sin_y;
    s32 scaled_depth;
    s32 depth_value;
    s32 product_x;
    s32 product_y;
    s16 *amplitude;
    u8 * amplitude_addr;
    u8 *record;
    u8 *prim;
    s32 scale;
    s32 abs_offset;
    s16 sx;
    s16 sy;
    s16 ex;
    s16 ey;
    s32 screen_coord;
    s32 visible_0;
    s32 visible_1;
    s32 visible_01;
    s32 visible_2;
    s32 visible_012;
    s32 visible_3;
    s32 u_end;
    s32 v_end;
    s32 v_end_bits;
    s32 v_start_bits;
    u16 texture_page;
    u16 texture_bias;
    s32 packed_uv;
    u8 draw_code;
    ObjectNodeHeader *next_node;
    u8 *copy_matrix_a;
    u8 *copy_matrix_b;
    GpuContext **render_pools;
    GpuContext *render_pool;
    u8 *next_prim;
    scratch = (ScratchPad *) 0x1F800000;
    render_pool = g_game_work.draw_buffer;
    next_prim = render_pool->packetCursor;
    scratch->sw[0x24 / 4] = (s32) (((u8 *) render_pool) + 0xB0);
    scratch->sw[0xE4 / 4] = 0;
    scratch->sw[0x1C / 4] = (s32) next_prim;
    render_pools = ((GpuContext * *)(&g_game_work));
    fixed_matrix = (GteMatrix *) 0x1F8000C8;
    do {
        copy_matrix_a = sprite_fixed_transform_matrix;
        copy_matrix_b = effect_view_matrix;
        scratch->h[0x04 / 2] = position->x.unsigned_parts.integer;
        scratch->h[0x06 / 2] = position->y.unsigned_parts.integer;
        scratch->h[0x08 / 2] = position->z.unsigned_parts.integer;
        scratch->sw[0xC4 / 4] = RotTransPers(scratch->b + 0x04, &scratch->sw[0xBC / 4], &scratch->sw[0x94 / 4], &scratch->sw[0x98 / 4]);
        *((u16 *) (render_state + 0x14)) |= 0x8000;
        sprite_scaled_depth_word[0] = (scaled_depth = (scratch->sw[0xC4 / 4]) << 2);
        *((s32 *) (copy_matrix_b + 0x1C)) = scaled_depth;
        *((s32 *) (copy_matrix_a + 0x1C)) = scaled_depth;
        depth_value = (scratch->sw[0xC4 / 4]) - (*((s16 *) (render_state + 0x06)));
        scratch->sw[0xC4 / 4] = depth_value;
        if (((u32) depth_value) < 0x1E0) {
            copies = 1;
            do {
                PushMatrix();
                center_x = (scratch->h[0xBC / 2]) - 0xA0;
                center_y = (scratch->h[0xBE / 2]) - 0x78;
                *((u16 *) (scratch->b + 0xBC)) = center_x;
            } while (0);
            base_x = center_x;
            abs_offset = abs((s16)base_x);
            scratch->h[0xBE / 2] = center_y;
            base_y = center_y;
            if (abs_offset < 0x330) {
                abs_offset = (s16) center_y;
                if (abs_offset < 0) {
                    abs_offset = -abs_offset;
                }
                if (abs_offset < 0x330) {
                    copies = 5;
                }
            }
            copy_index = 0;
            if (copies != 0) {
            do {
                if (copy_index != 0) {
                    scratch->sw[0xC4 / 4] = 10;
                    sin_x = rsin(ratan2((s16) base_x, 0x200));
                    amplitude_addr = (u8 *)sprite_depth_amplitude_table;
                    amplitude = (s16 *) (amplitude_addr + (copy_index << 1));
                    product_x = (*amplitude) * sin_x;
                    scratch->h[0xBC / 2] = base_x - (product_x / 4096);
                    sin_y = rsin(ratan2((s16) base_y, 0x200));
                    product_y = (*amplitude) * sin_y;
                    scratch->h[0xBE / 2] = base_y - (product_y / 4096);
                }

                scratch->h[0xF8 / 2] = *((u16 *) (render_state + 0x16));
                scratch->h[0xFA / 2] = *((u16 *) (render_state + 0x18));
                scratch->h[0xFC / 2] = *((u16 *) (render_state + 0x1A));
                scale = *((u16 *) (render_state + 0x20));
                scratch->sw[0xDC / 4] = scale;
                scratch->h[0x100 / 2] = scale;
                scale = *((u16 *) (render_state + 0x22));
                scratch->sw[0xE0 / 4] = scale;
                scratch->h[0x102 / 2] = scale;
                RotMatrix(scratch->b + 0xF8, fixed_matrix);
                if (copy_index != 0) {
                    if (sprite_transform_copy_flags[copy_index] != 0) {
                        CompMatrix(sprite_fixed_transform_matrix, fixed_matrix, scratch->b + 0x54);
                    }
                    else {
                        CompMatrix(effect_view_matrix, fixed_matrix, scratch->b + 0x54);
                    }
                }
                else {
                    CompMatrix(sprite_projection_matrix, fixed_matrix, scratch->b + 0x54);
                }
                SetTransMatrix(scratch->b + 0x54);
                SetRotMatrix(scratch->b + 0x54);
                record = *((u8 **) (render_state + 0x08));
                scratch->h[0x28 / 2] = *((u16 *) (render_state + 0x14));
                for (;;) {
                if (!(record[0] & 0x20)) {
                    prim = (u8 *) (scratch->sw[0x1C / 4]);
                    scratch->sw[0x1C / 4] = (s32) (prim + 0x28);
                    scratch->sw[0x0C / 4] = record[8];
                    scratch->sw[0x10 / 4] = record[9];
                    scratch->sw[0x14 / 4] = record[10];
                    scratch->sw[0x18 / 4] = record[11];
                    if ((record[0] ^ scratch->h[0x28 / 2]) & 1) {
                        sx = (-((s8 *) record)[2]) - scratch->h[0x100 / 2];
                        scratch->h[0x84 / 2] = sx;
                        scratch->h[0x74 / 2] = sx;
                        ex = sx - scratch->h[0x14 / 2];
                        scratch->h[0x8C / 2] = ex;
                        scratch->h[0x7C / 2] = ex;
                    }
                    else {
                        sx = ((s8 *) record)[2] - scratch->h[0x100 / 2];
                        scratch->h[0x84 / 2] = sx;
                        scratch->h[0x74 / 2] = sx;
                        ex = sx + scratch->h[0x14 / 2];
                        scratch->h[0x8C / 2] = ex;
                        scratch->h[0x7C / 2] = ex;
                    }
                    if ((record[0] ^ scratch->h[0x28 / 2]) & 2) {
                        sy = (-((s8 *) record)[3]) - scratch->h[0x102 / 2];
                        scratch->h[0x7E / 2] = sy;
                        scratch->h[0x76 / 2] = sy;
                        ey = sy - scratch->h[0x18 / 2];
                        scratch->h[0x8E / 2] = ey;
                        scratch->h[0x86 / 2] = ey;
                    }
                    else {
                        sy = ((s8 *) record)[3] - scratch->h[0x102 / 2];
                        scratch->h[0x7E / 2] = sy;
                        scratch->h[0x76 / 2] = sy;
                        ey = sy + scratch->h[0x18 / 2];
                        scratch->h[0x8E / 2] = ey;
                        scratch->h[0x86 / 2] = ey;
                    }
                    scratch->h[0x90 / 2] = 0;
                    scratch->h[0x88 / 2] = 0;
                    scratch->h[0x80 / 2] = 0;
                    scratch->h[0x78 / 2] = 0;
                    RotTransPers4(scratch->b + 0x74, scratch->b + 0x7C, scratch->b + 0x84, scratch->b + 0x8C, &scratch->sw[0xE8 / 4],
                        &scratch->sw[0xEC / 4], &scratch->sw[0xF0 / 4], &scratch->sw[0xF4 / 4], &scratch->sw[0x94 / 4], &scratch->sw[0x98 / 4]);
                    screen_coord = scratch->h[0xE8 / 2];
                    screen_coord += scratch->h[0xBC / 2];
                    *((s16 *) (prim + 0x08)) = screen_coord;
                    screen_coord = scratch->h[0xEA / 2];
                    screen_coord += scratch->h[0xBE / 2];
                    *((s16 *) (prim + 0x0A)) = screen_coord;
                    screen_coord = scratch->h[0xEC / 2];
                    screen_coord += scratch->h[0xBC / 2];
                    *((s16 *) (prim + 0x10)) = screen_coord;
                    screen_coord = scratch->h[0xEE / 2];
                    screen_coord += scratch->h[0xBE / 2];
                    *((s16 *) (prim + 0x12)) = screen_coord;
                    screen_coord = scratch->h[0xF0 / 2];
                    screen_coord += scratch->h[0xBC / 2];
                    *((s16 *) (prim + 0x18)) = screen_coord;
                    screen_coord = scratch->h[0xF2 / 2];
                    screen_coord += scratch->h[0xBE / 2];
                    *((s16 *) (prim + 0x1A)) = screen_coord;
                    *((s16 *) (prim + 0x20)) = (scratch->h[0xF4 / 2]) + (scratch->h[0xBC / 2]);
                    *((s16 *) (prim + 0x22)) = (scratch->h[0xF6 / 2]) + (scratch->h[0xBE / 2]);
                    visible_0 = 0;
                    if (((u16) ((*((s16 *) (prim + 0x08))) + 0x20)) < 0x181) {
                        visible_0 = ((u16) ((*((s16 *) (prim + 0x0A))) + 0x20)) < 0x121;
                    }
                    visible_1 = 0;
                    if (((u16) ((*((s16 *) (prim + 0x10))) + 0x20)) < 0x181) {
                        visible_1 = ((u16) ((*((s16 *) (prim + 0x12))) + 0x20)) < 0x121;
                    }
                    visible_01 = visible_0 | visible_1;
                    visible_2 = 0;
                    if (((u16) ((*((s16 *) (prim + 0x18))) + 0x20)) < 0x181) {
                        visible_2 = ((u16) ((*((s16 *) (prim + 0x1A))) + 0x20)) < 0x121;
                    }
                    visible_012 = visible_01 | visible_2;
                    visible_3 = 0;
                    if (((u16) ((*((s16 *) (prim + 0x20))) + 0x20)) < 0x181) {
                        visible_3 = ((u16) ((*((s16 *) (prim + 0x22))) + 0x20)) < 0x121;
                    }
                    if (visible_012 | visible_3) {
                        prim[3] = 9;
                        *((u16 *) (render_state + 0x14)) &= 0x7FFF;
                        u_end = (scratch->sw[0x14 / 4]) + (scratch->sw[0x0C / 4]);
                        scratch->sw[0x14 / 4] = u_end;
                        if (u_end & 0x100) {
                            scratch->sw[0x14 / 4] = u_end - 1;
                        }
                        v_end = (scratch->sw[0x18 / 4]) + (scratch->sw[0x10 / 4]);
                        scratch->sw[0x18 / 4] = v_end;
                        if (v_end & 0x100) {
                            scratch->sw[0x18 / 4] = v_end - 1;
                        }
                        v_end_bits = (scratch->sw[0x18 / 4]) << 8;
                        v_start_bits = (scratch->sw[0x10 / 4]) << 8;
                        scratch->sw[0x18 / 4] = v_end_bits;
                        scratch->sw[0x10 / 4] = v_start_bits;
                        *((u32 *) (prim + 0x0C)) = (v_start_bits + (scratch->sw[0x0C / 4]))
                        + (((*((u16 *) (render_state + 0x12))) + (*((u16 *) (record + 6)))) << 16);
                        if (copy_index != 0) {
                            packed_uv = scratch->h[0x10 / 2];
                            packed_uv += scratch->h[0x14 / 2];
                            *((u16 *) (prim + 0x14)) = packed_uv;
                            texture_bias = *((u16 *) (render_state + 0x10));
                            if (texture_bias != 0) {
                                texture_page = (texture_bias + ((*((u16 *) (record + 4))) & 0xFF9F)) | 0x20;
                            }
                            else {
                                texture_page = (*((u16 *) (record + 4))) | 0x20;
                            }
                        }
                        else {
                            packed_uv = scratch->h[0x10 / 2];
                            packed_uv += scratch->h[0x14 / 2];
                            *((u16 *) (prim + 0x14)) = packed_uv;
                            texture_bias = *((u16 *) (render_state + 0x10));
                            if (texture_bias != 0) {
                                texture_page = texture_bias + ((*((u16 *) (record + 4))) & 0xFF9F);
                            }
                            else {
                                texture_page = *((u16 *) (record + 4));
                            }
                        }
                        *((u16 *) (prim + 0x16)) = texture_page;
                        packed_uv = scratch->h[0x18 / 2];
                        packed_uv += scratch->h[0x0C / 2];
                        *((u16 *) (prim + 0x1C)) = packed_uv;
                        *((u16 *) (prim + 0x24)) = (scratch->h[0x18 / 2]) + (scratch->h[0x14 / 2]);
                        if ((*((s16 *) (prim + 0x08))) > (*((s16 *) (prim + 0x20)))) {
                            prim[0x14]--;
                            prim[0x24]--;
                        }
                        if ((*((s16 *) (prim + 0x0A))) > (*((s16 *) (prim + 0x22)))) {
                            prim[0x1D]--;
                            prim[0x25]--;
                        }
                        draw_code = record[1];
                        render_state[0x0F] = draw_code;
                        if (copy_index != 0) {
                            render_state[0x0F] = draw_code | 2;
                        }
                        else if ((scratch->h[0x28 / 2]) & 8) {
                            if ((scratch->h[0x28 / 2]) & 4) {
                                render_state[0x0F] = draw_code | 2;
                            }
                            else {
                                render_state[0x0F] = draw_code & 0xFD;
                            }
                        }
                        if ((scratch->h[0x28 / 2]) & 0x10) {
                            render_state[0x0F] &= 0xFE;
                        }
                        else {
                            render_state[0x0F] |= 1;
                        }
                        *((u32 *) (prim + 4)) = *((u32 *) (render_state + 0x0C));
                        if (copy_index != 0) {
                            prim[4] >>= 2;
                            prim[5] >>= 2;
                            prim[6] >>= 2;
                        }
                        AddPrim((void *) ((scratch->sw[0x24 / 4]) + ((scratch->sw[0xC4 / 4]) << 2)), prim);
                    }
                }

                if (((s8) record[0]) < 0) {
                    break;
                }
                record += 0x0C;
                }
                copy_index++;
            } while (copy_index < copies);
            }
            PopMatrix();
        }
        next_node = ((ObjectNodeHeader *)node_data - 1)->chain_next;
        if (next_node != 0) {
            node_data = NODE_BODY(next_node);
            position = next_node->position;
            render_state = (u8 *)next_node->sprite;
        }
    }
    while (next_node != 0);
    render_pools[0]->packetCursor = (u8 *) (scratch->sw[0x1C / 4]);
    return 0;
}
