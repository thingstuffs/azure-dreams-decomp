/* Waving textured sprite strips and linked shaded particle rendering. */
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/draw.h"
#include "shared/game_work.h"

/* Projects waving sprite strips, queues visible textured quads, and invokes custom part callbacks. */
void render_textured_effect_parts(Row_818F2800_S_BODY_3 *geometry, void *position, Row_818F2800_S_BODY_1 *state, s32 depth_offset)
{
    u8 *scratch;
    u8 *part;
    u8 *packet;
    s32 angle;
    s32 half;
    s32 strip_x;
    register s32 invalid_coord;
    s32 transform_buf[16];
    u16 depth_bias;
    u16 end_column;
    u16 column;
    s32 texture_u;
    u8 *edge_cache;
    void *graphics;
    s32 column_or_x;
    s32 packed_uv;
    s32 texture_value;
    s32 first_column;
    void **globals;
    Row_818F2800_S_BODY_6 *cache;
    s32 position_z;

    globals = ((void **)(&g_game_work));
    graphics = globals[0];
    scratch = (u8 *)0x1F800000;

    DM_U32(0x20) = (u32)((u8 *)graphics + 0xB0);
    DM_S32(0xE4) = *(s16 *)((u8 *)position + 2);
    DM_S32(0xE8) = *(s16 *)((u8 *)position + 6);
    position_z = *(s16 *)((u8 *)position + 0xA);
    DM_S32(0xEC) = position_z;
    packet = ((GpuContext *)graphics)->packetCursor;
    state->unk_14 = (u16)(state->unk_14 | 0x8000);
    depth_bias = depth_offset;
    PushMatrix();
    DM_U32(0x30) = state->unk_1C * 2;
    DM_U32(0x34) = state->unk_1E * 2;
    DM_U32(0x38) = 0x2000;
    DM_U16(0x100) = state->unk_16;
    DM_U16(0x104) = state->unk_1A;
    DM_U16(0x102) = state->unk_18;
    RotMatrix(0x1F800100, 0x1F8000D0);
    ReadRotMatrix(&transform_buf[0]);
    CompMatrix(&transform_buf[0], 0x1F8000D0, 0x1F800050);
    ScaleMatrix(0x1F800050, 0x1F800030);
    SetTransMatrix(0x1F800050);
    SetRotMatrix(0x1F800050);
    edge_cache = (u8 *)&transform_buf[0];
    {
        s32 init_flags;
        part = state->unk_08;
        init_flags = state->unk_14;
        invalid_coord = 0x7D00;
        DM_U16(0x24) = (u16)init_flags;
    }

    do {
        half = 0;
        if (!(((Row_818F2800_S_BODY_2 *)part)->unk_00 & 0x20)) {
            u8 *first_part;
            s16 start_x;
            s32 state_flags;

            angle = geometry->unk_3A;
            first_column = ((Row_818F2800_S_BODY_2 *)part)->unk_08.at00.v;
            texture_value = first_column + ((Row_818F2800_S_BODY_2 *)part)->unk_08.at02.v;
            first_part = state->unk_08;
            end_column = (u16)texture_value;
            start_x = ((Row_818F2800_S_BODY_4 *)first_part)->unk_02;
            start_x = (s8)start_x;
            column = (u16)first_column;
            strip_x = start_x;
            do {
                ((Row_818F2800_S_BODY_5 *)(edge_cache + half * 2))->unk_38 = (s16)invalid_coord;
                ((Row_818F2800_S_BODY_5 *)(edge_cache + half * 2))->unk_30 = (s16)invalid_coord;
                ((Row_818F2800_S_BODY_5 *)(edge_cache + half * 2))->unk_28 = (s16)invalid_coord;
                ((Row_818F2800_S_BODY_5 *)(edge_cache + half * 2))->unk_20 = (s16)invalid_coord;
            } while (++half < 2);

            do {
                half = 0;
                column_or_x = column;
                texture_u = (s32)(s16)column_or_x;
                do {
                    part = state->unk_08;
                    if (half == 0) {
                        s32 texture_v;
                        DM_U32(0x08) = texture_u;
                        texture_v = (*(u8 *)((u8 *)part + 9));
                        DM_U32(0x10) = 1;
                        DM_U32(0x0C) = texture_v;
                        {
                            s32 half_height;
                            half_height = (u32)((Row_818F2800_S_BODY_2 *)part)->unk_08.at03.v >> 1;
                            DM_U32(0x14) = half_height;
                        }
                    } else {
                        s32 texture_v;
                        DM_U32(0x08) = texture_u;
                        texture_v = ((Row_818F2800_S_BODY_2 *)part)->unk_08.at01.v;
                        state_flags = ((Row_818F2800_S_BODY_2 *)part)->unk_08.at03.v;
                        DM_U32(0x10) = 1;
                        state_flags = (u32)state_flags >> 1;
                        texture_v = texture_v + state_flags;
                        DM_U32(0x0C) = texture_v;
                        {
                            s32 half_height;
                            half_height = (u32)((Row_818F2800_S_BODY_2 *)part)->unk_08.at03.v >> 1;
                            DM_U32(0x14) = half_height;
                        }
                    }
                    {
                        s32 left_z;
                        left_z = (rsin(angle) * geometry->unk_38) >> 0x10;
                        DM_S16(0x84) = (s16)left_z;
                        DM_S16(0x74) = (s16)left_z;
                    }
                    {
                        s32 angle_step;
                        angle_step = geometry->unk_3C;
                        angle += angle_step;
                    }
                    if (angle >= 0x1001) {
                        angle -= 0x1000;
                    }
                    {
                        s32 right_z;
                        right_z = (rsin(angle) * geometry->unk_38) >> 0x10;
                        DM_S16(0x8C) = (s16)right_z;
                        DM_S16(0x7C) = (s16)right_z;
                    }
                    {
                        s32 angle_step;
                        angle_step = geometry->unk_3C;
                        angle -= angle_step;
                    }
                    if (angle < 0) {
                        angle += 0x1000;
                    }
                    {
                        s32 edge_x;
                        if ((((Row_818F2800_S_BODY_2 *)part)->unk_00 ^ DM_U16(0x24)) & 1) {
                            s32 left_x, width;
                            left_x = -strip_x;
                            width = DM_U16(0x10);
                            DM_S16(0x80) = (s16)left_x;
                            DM_S16(0x70) = (s16)left_x;

                            edge_x = left_x - width;
                        } else {
                            s32 width;
                            width = DM_U16(0x10);
                            DM_S16(0x80) = (s16)strip_x;
                            DM_S16(0x70) = (s16)strip_x;
                            edge_x = strip_x + width;
                        }
                        DM_S16(0x88) = (s16)edge_x;
                        DM_S16(0x78) = (s16)edge_x;
                    }
                    {
                        u16 part_flags;
                        s16 edge_y;
                        part_flags = ((Row_818F2800_S_BODY_2 *)part)->unk_00;
                        part_flags = (*(u16 *)(scratch + 0x24)) ^ part_flags;
                        if (part_flags & 2) {
                            if (half == 0) {
                                edge_y = ((Row_818F2800_S_BODY_2 *)part)->unk_03;
                                packed_uv = DM_U16(0x14);
                                edge_y = -(s32)(s8)edge_y;
                                DM_S16(0x7A) = (s16)edge_y;
                                DM_S16(0x72) = (s16)edge_y;
                                edge_y = edge_y - packed_uv;
                                DM_S16(0x8A) = (s16)edge_y;
                                DM_S16(0x82) = (s16)edge_y;
                            } else {
                                s16 offset_y;
                                edge_y = ((Row_818F2800_S_BODY_2 *)part)->unk_03;
                                edge_y = (s8)edge_y;
                                packed_uv = DM_U16(0x14);
                                position_z = -edge_y;
                                texture_value = packed_uv;
                                offset_y = position_z;
                                offset_y = offset_y - packed_uv;
                                DM_S16(0x7A) = (s16)offset_y;
                                DM_S16(0x72) = (s16)offset_y;
                                offset_y = offset_y - texture_value;
                                DM_S16(0x8A) = (s16)offset_y;
                                DM_S16(0x82) = (s16)offset_y;
                            }
                        } else {
                            if (half == 0) {
                                edge_y = ((Row_818F2800_S_BODY_2 *)part)->unk_03;
                                packed_uv = DM_U16(0x14);
                                edge_y = (s8)edge_y;
                                DM_S16(0x7A) = (s16)edge_y;
                                DM_S16(0x72) = (s16)edge_y;
                                edge_y = edge_y + packed_uv;
                                DM_S16(0x8A) = (s16)edge_y;
                                DM_S16(0x82) = (s16)edge_y;
                            } else {
                                edge_y = ((Row_818F2800_S_BODY_2 *)part)->unk_03;
                                packed_uv = DM_U16(0x14);
                                edge_y = (s8)edge_y;
                                texture_value = packed_uv;
                                edge_y = edge_y + packed_uv;
                                DM_S16(0x7A) = (s16)edge_y;
                                DM_S16(0x72) = (s16)edge_y;
                                edge_y = edge_y + texture_value;
                                DM_S16(0x8A) = (s16)edge_y;
                                DM_S16(0x82) = (s16)edge_y;
                            }
                        }
                    }
                    DM_S32(0xC0) = (RotAverage4(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88,
                                                  packet + 8, packet + 0x10, packet + 0x18, packet + 0x20,
                                                  scratch + 0x90, scratch + 0x94)
                                    - (s32)(s16)depth_bias) - 6;
                    cache = (Row_818F2800_S_BODY_6 *)(half * 2 + (long)edge_cache);
                    if (cache->unk_20.s != invalid_coord) {
                        ((Row_818F2800_S_BODY_7 *)packet)->unk_04.u = cache->unk_20.u;
                        ((Row_818F2800_S_BODY_7 *)packet)->unk_06.u = cache->unk_30;
                        ((Row_818F2800_S_BODY_7 *)packet)->unk_14 = cache->unk_28;
                        ((Row_818F2800_S_BODY_7 *)packet)->unk_16 = cache->unk_38;
                    }
                    cache->unk_20.u = ((Row_818F2800_S_BODY_7 *)packet)->unk_0C;
                    cache->unk_28 = ((Row_818F2800_S_BODY_7 *)packet)->unk_1C.u;
                    cache->unk_30 = ((Row_818F2800_S_BODY_7 *)packet)->unk_0E;
                    cache->unk_38 = ((Row_818F2800_S_BODY_7 *)packet)->unk_1E.u;
                    if ((u32)DM_S32(0xC0) < 0x1E0U) {
                        s32 top_visible, three_visible, visible0, visible1, visible2, visible3;
                        visible0 = 0;
                        if ((u32)((((Row_818F2800_S_BODY_7 *)packet)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                            s32 screen_y;
                            screen_y = (((Row_818F2800_S_BODY_7 *)packet)->unk_06.u + 0x20) & 0xFFFF;
                            visible0 = (u32)screen_y < 0x121U;
                        }
                        visible1 = 0;
                        if ((u32)((((Row_818F2800_S_BODY_7 *)packet)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                            s32 screen_y;
                            screen_y = (((Row_818F2800_S_BODY_7 *)packet)->unk_0E + 0x20) & 0xFFFF;
                            visible1 = (u32)screen_y < 0x121U;
                        }
                        visible2 = 0;
                        top_visible = visible0 | visible1;
                        if ((u32)((((Row_818F2800_S_BODY_7 *)packet)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                            s32 screen_y;
                            screen_y = (((Row_818F2800_S_BODY_7 *)packet)->unk_16 + 0x20) & 0xFFFF;
                            visible2 = (u32)screen_y < 0x121U;
                        }
                        visible3 = 0;
                        three_visible = top_visible | visible2;
                        if ((u32)((((Row_818F2800_S_BODY_7 *)packet)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                            s32 screen_y;
                            screen_y = (((Row_818F2800_S_BODY_7 *)packet)->unk_1E.u + 0x20) & 0xFFFF;
                            visible3 = (u32)screen_y < 0x121U;
                        }
                        if ((three_visible | visible3) != 0) {
                            ((Row_818F2800_S_BODY_7 *)packet)->len = 9;
                            state->unk_14 = (u16)(state->unk_14 & 0x7FFF);
                            {
                                s32 right_u, bottom_v;
                                right_u = DM_U32(0x10) + DM_U32(0x08);
                                DM_U32(0x10) = right_u;
                                if (right_u & 0x100) {
                                    DM_U32(0x10) = right_u - 1;
                                }
                                bottom_v = DM_U32(0x14) + DM_U32(0x0C);
                                DM_U32(0x14) = bottom_v;
                                if (bottom_v & 0x100) {
                                    DM_U32(0x14) = bottom_v - 1;
                                }
                            }
                            DM_U32(0x0C) <<= 8;
                            DM_U32(0x14) <<= 8;
                            if (DM_U16(0x24) & 0x100) {
                                s32 clut;
                                clut = state->unk_12;
                                ((Row_818F2800_S_BODY_7 *)packet)->unk_0A = (s16)clut;
                            } else {
                                packed_uv = state->unk_12;
                                packed_uv = packed_uv + ((Row_818F2800_S_BODY_2 *)part)->unk_06;
                                ((Row_818F2800_S_BODY_7 *)packet)->unk_0A = (s16)packed_uv;
                            }
                                                                                    /* --- retail word 404 --- */
                            packed_uv = DM_U16(0x0C);
                            packed_uv = packed_uv + DM_U16(0x08);
                            ((Row_818F2800_S_BODY_7 *)packet)->unk_08 = (s16)packed_uv;
                            packed_uv = DM_U16(0x0C);
                            packed_uv = packed_uv + DM_U16(0x10);
                            ((Row_818F2800_S_BODY_7 *)packet)->unk_10.s16 = (s16)packed_uv;
                            {
                                s32 page_override, texture_page;
                                page_override = state->unk_10;
                                if (page_override != 0) {
                                    s32 masked_page;
                                    masked_page = ((Row_818F2800_S_BODY_2 *)part)->unk_04 & 0xFF9F;
                                    texture_page = page_override + masked_page;
                                } else {
                                    texture_page = ((Row_818F2800_S_BODY_2 *)part)->unk_04;
                                }
                                                                                                /* --- retail word 424 --- */
                                ((Row_818F2800_S_BODY_7 *)packet)->unk_12 = (u16)texture_page;
                            }
                            packed_uv = DM_U16(0x14);
                            packed_uv = packed_uv + DM_U16(0x08);
                            ((Row_818F2800_S_BODY_7 *)packet)->unk_18.at00.v = (s16)packed_uv;
                            packed_uv = DM_U16(0x14);
                            texture_value = DM_U16(0x10);
                            column_or_x = ((Row_818F2800_S_BODY_7 *)packet)->unk_04.s;
                            packed_uv = packed_uv + texture_value;
                            ((Row_818F2800_S_BODY_7 *)packet)->unk_20.at00.v = (s16)packed_uv;
                            if ((s32)((Row_818F2800_S_BODY_7 *)packet)->unk_1C.s < column_or_x) {
                                u8 edge_uv, corner_uv;
                                edge_uv = ((Row_818F2800_S_BODY_7 *)packet)->unk_10.u8;
                                corner_uv = ((Row_818F2800_S_BODY_7 *)packet)->unk_20.at00u.v;
                                edge_uv = (u8)(edge_uv - 1);
                                corner_uv = (u8)(corner_uv - 1);
                                ((Row_818F2800_S_BODY_7 *)packet)->unk_10.u8 = edge_uv;
                                ((Row_818F2800_S_BODY_7 *)packet)->unk_20.at00u.v = corner_uv;
                            }
                            {
                                s32 top_y;
                                top_y = ((Row_818F2800_S_BODY_7 *)packet)->unk_06.s;
                                if ((s32)((Row_818F2800_S_BODY_7 *)packet)->unk_1E.s < top_y) {
                                    u8 edge_uv, corner_uv;
                                    edge_uv = ((Row_818F2800_S_BODY_7 *)packet)->unk_18.at01.v;
                                    corner_uv = ((Row_818F2800_S_BODY_7 *)packet)->unk_20.at01.v;
                                    edge_uv = (u8)(edge_uv - 1);
                                    corner_uv = (u8)(corner_uv - 1);
                                    ((Row_818F2800_S_BODY_7 *)packet)->unk_18.at01.v = edge_uv;
                                    ((Row_818F2800_S_BODY_7 *)packet)->unk_20.at01.v = corner_uv;
                                }
                            }
                            texture_value = ((Row_818F2800_S_BODY_2 *)part)->unk_01;
                            state->unk_0C.at03.v = (u8)texture_value;
                            {
                                s32 render_flags;
                                render_flags = DM_U16(0x24);
                                if (render_flags & 8) {
                                    if (render_flags & 4) {
                                        s32 blend_command;
                                        blend_command = texture_value | 2;
                                        state->unk_0C.at03.v = (u8)blend_command;
                                    } else {
                                        s32 opaque_command;
                                        opaque_command = texture_value & 0xFD;
                                        state->unk_0C.at03.v = (u8)opaque_command;
                                    }
                                }
                            }
                            ((Row_818F2800_S_BODY_7 *)packet)->unk_00 = state->unk_0C.at00.v;
                            {
                                u32 ot_tag = ((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)];
                                u32 packet_tag = *(u32 *)packet & 0xFF000000;
                                *(u32 *)packet = packet_tag | (ot_tag & 0xFFFFFF);
                            }
                            ((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] =
                                (((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] & 0xFF000000)
                            | ((s32)packet & 0xFFFFFF);
                            packet += 0x28;
                        }
                    }
                    half += 1;
                } while (half < 2);
                {
                    s32 angle_step;
                    angle_step = geometry->unk_3C;
                    angle += angle_step;
                }
                if (angle >= 0x1001) {
                    angle -= 0x1000;
                }
                column = (u16)(column + 1);
                strip_x += 1;
            } while ((s32)(s16)column != (s32)end_column);
        } else {
            void (*callback)(void *, void *, void *, void *);

            callback = ((Row_818F2800_S_BODY_2 *)part)->unk_08.at00u.v;
            if (callback != 0) {
                callback(geometry, position, state, part);
            }
        }
        {
            s32 part_flags;
            part_flags = (s8)((Row_818F2800_S_BODY_2 *)part)->unk_00;
            part += 0xC;
            if (part_flags < 0) {
                break;
            }
        }
    } while (1);
    PopMatrix();
    ((GpuContext *)(globals[0]))->packetCursor = packet;
}

/* Draws textured parts for every linked effect node using each node's position, appearance, and depth
   bias. */
s32 draw_linked_gap_effects(void *state, void *position, void *appearance) {
    Row_818F3098_GapNode *node;
    for (;;) {
        render_textured_effect_parts(state, position, appearance, *(s16 *)((u8 *)appearance + 6));
        node = *(Row_818F3098_GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}

/* Projects linked points and queues visible square particles with color scaled by each point's intensity. */
s32 draw_linked_shaded_tiles(void *first_point, void *first_position)
{
    void *point = first_point;
    void *position = first_position;
    GameWork *render_state = &g_game_work;
    u32 addr_mask = 0x00FFFFFF;
    u8 *render_ctx = g_game_work.draw_buffer;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Row_818F30EC_Scratch800248EC *scratch =
        (Row_818F30EC_Scratch800248EC *)0x1F800000;
    Row_818F30EC_Packet800248EC *tile;
    Row_818F30EC_Packet800248EC *draw_mode;
    u8 *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    void *next_node;

    packet_start = ((GpuContext *)render_ctx)->packetCursor;
    scratch->ot = (u32 *)(render_ctx + 0xB0);
    scratch->cursor = packet_start;

    for (;;) {
        tile = *(Row_818F30EC_Packet800248EC **)&scratch->cursor;
        scratch->x = ((Row_818F30EC_S_800248EC_1 *)position)->unk_02;
        scratch->y = ((Row_818F30EC_S_800248EC_1 *)position)->unk_06;
        scratch->z = ((Row_818F30EC_S_800248EC_1 *)position)->unk_0A;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = RotTransPers(scratch, (u8 *)tile + 8,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            ((Row_818F30EC_S_800248EC_2 *)tile)->unk_04.at00.v = ((Row_818F30EC_S_800248EC_3 *)point)->unk_08;

            color_value = (s32)tile->r * ((Row_818F30EC_S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * ((Row_818F30EC_S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * ((Row_818F30EC_S_800248EC_3 *)point)->unk_32;
            tile->b = (color_value / 128);

            ((Row_818F30EC_S_800248EC_2 *)tile)->unk_03 = 2;
            ((Row_818F30EC_S_800248EC_2 *)tile)->unk_04.at03.v = 0x6A;
            ((Row_818F30EC_P_TAG *)&tile->tag)->addr = ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr;
            ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (Row_818F30EC_Packet800248EC *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = GetTPage(0, 1, 0, 0);
            SetDrawMode(draw_mode, 0, 0, (u16)draw_page, 0);

            ((Row_818F30EC_P_TAG *)&draw_mode->tag)->addr = ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr;
            ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr = (u32)((u32)draw_mode);
        }

        next_node = ((Row_818F30EC_S_800248EC_3_pre *)point)[-1].unk_00;
        if (next_node != 0) {
            point = (u8 *)next_node + 0x20;
            position = ((Row_818F30EC_S_800248EC_4 *)next_node)->unk_08;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->draw_buffer;
    ((GpuContext *)final_render_ctx)->packetCursor = scratch->cursor;
    return 0;
}

/* Maps a random low bit to either -1 or 1. */
s32 choose_random_sign(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}
