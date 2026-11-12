#include "common.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libgte.h"
#include "engine/graphics/sprite_scratch.h"

typedef struct OrderingTag { u32 addr : 24; u32 count : 8; } OrderingTag;
/* Build visible textured quads for the matching sprite and link them into the ordering table. */
void *draw_sprite_effect_quads(u8 *sprite_list, ObjectPosition *position, SpriteFrameState *render_state_addr, u8 *placement, u8 *packet_buf)
{
    SpriteQuadScratch *scratch;
    s32 index;

    u8 *sprite;
    u8 *packet;
    u8 *part;
    u8 *quad;
    s32 bottom_y;

    sprite = 0;
    index = 0;
    packet = packet_buf;
    scratch = (SpriteQuadScratch *) 0x1F800000;
    {
        s16 sprite_count;
        sprite_count = *((s16 *) (sprite_list + 0x9E));
        for (; index < sprite_count; index++) {
            u8 *sprite_entry = *((u8 **) (sprite_list + 0xA4));
            if (sprite_entry != 0) {
                sprite = sprite_entry + 0x20;
                if ((*((u16 *) (placement + 6))) == (*((u16 *) (sprite + 6)))) {
                    break;
                }
            }
            sprite_list += 4;
        }
    }
    index = 0;
    if ((*((s16 *) (sprite + 2))) > 0) {
        do {
            s32 part_offset;
            part_offset = (index * 3) << 4;
            part_offset += 8;
            part = sprite + part_offset;
            quad = *((u8 **) (part + 8));
            for (;;) {
                if (!(quad[0] & 0x20)) {
                    scratch->uv_u_start = quad[8];
                    scratch->uv_v_start = quad[9];
                    scratch->uv_u_extent = quad[10];
                    scratch->uv_v_extent = quad[11];
                    {
                        s16 x;
                        u8 quad_flags;
                        quad_flags = quad[0];
                        if ((quad_flags ^ scratch->sprite_flags) & 1) {
                            s32 width;
                            x = -(s8)quad[2] - scratch->extent_x;
                            width = (u16)scratch->uv_u_extent;
                            scratch->vertices[2].vx = x;
                            scratch->vertices[0].vx = x;
                            x -= width;
                            scratch->vertices[3].vx = x;
                            scratch->vertices[1].vx = x;
                        }
                        else {
                            s32 width;
                            width = (u16)scratch->uv_u_extent;
                            x = (s8)quad[2] + scratch->extent_x;
                            scratch->vertices[2].vx = x;
                            scratch->vertices[0].vx = x;
                            x += width;
                            scratch->vertices[3].vx = x;
                            scratch->vertices[1].vx = x;
                        }
                    }
                    {
                        s16 x;
                        if ((placement[0] ^ render_state_addr->flags) & 1) {
                            x = scratch->vertices[2].vx - (s8)placement[2];
                            scratch->vertices[2].vx = x;
                            scratch->vertices[0].vx = x;
                            x = scratch->vertices[3].vx - (s8)placement[2];
                            scratch->vertices[3].vx = x;
                            scratch->vertices[1].vx = x;
                        }
                        else {
                            x = scratch->vertices[2].vx + (s8)placement[2];
                            scratch->vertices[2].vx = x;
                            scratch->vertices[0].vx = x;
                            x = scratch->vertices[3].vx + (s8)placement[2];
                            scratch->vertices[3].vx = x;
                            scratch->vertices[1].vx = x;
                        }
                    }
                    {
                        s16 y;
                        u8 quad_flags;
                        quad_flags = quad[0];
                        if ((quad_flags ^ scratch->sprite_flags) & 2) {
                            s32 width;
                            y = -(s8)quad[3] - scratch->extent_y;
                            width = (u16)scratch->uv_v_extent;
                            scratch->vertices[1].vy = y;
                            scratch->vertices[0].vy = y;
                            y -= width;
                            scratch->vertices[3].vy = y;
                            scratch->vertices[2].vy = y;
                        }
                        else {
                            s32 width;
                            width = (u16)scratch->uv_v_extent;
                            y = (s8)quad[3] - scratch->extent_y;
                            scratch->vertices[1].vy = y;
                            scratch->vertices[0].vy = y;
                            y += width;
                            scratch->vertices[3].vy = y;
                            scratch->vertices[2].vy = y;
                        }
                    }
                    {
                        s16 y;
                        if ((placement[0] ^ render_state_addr->flags) & 2) {
                            y = scratch->vertices[1].vy - (s8)placement[3];
                            scratch->vertices[1].vy = y;
                            scratch->vertices[0].vy = y;
                            y = scratch->vertices[3].vy - (s8)placement[3];
                            scratch->vertices[3].vy = y;
                            scratch->vertices[2].vy = y;
                        }
                        else {
                            y = scratch->vertices[1].vy + (s8)placement[3];
                            scratch->vertices[1].vy = y;
                            scratch->vertices[0].vy = y;
                            y = scratch->vertices[3].vy + (s8)placement[3];
                            scratch->vertices[3].vy = y;
                            scratch->vertices[2].vy = y;
                        }
                    }
                    RotTransPers4(&scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
                        (s32 *)&scratch->projected_vertices[0], (s32 *)&scratch->projected_vertices[1], (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3],
                        &scratch->depth_cue,
                        &scratch->gte_flag);
                    *((u16 *) (packet + 0x8)) = scratch->projected_vertices[0].x + scratch->screen_origin.x;
                    *((u16 *) (packet + 0xA)) = scratch->projected_vertices[0].y + scratch->screen_origin.y;
                    *((u16 *) (packet + 0x10)) = scratch->projected_vertices[1].x + scratch->screen_origin.x;
                    *((u16 *) (packet + 0x12)) = scratch->projected_vertices[1].y + scratch->screen_origin.y;
                    *((u16 *) (packet + 0x18)) = scratch->projected_vertices[2].x + scratch->screen_origin.x;
                    *((u16 *) (packet + 0x1A)) = scratch->projected_vertices[2].y + scratch->screen_origin.y;
                    *((u16 *) (packet + 0x20)) = scratch->projected_vertices[3].x + scratch->screen_origin.x;
                    bottom_y = scratch->projected_vertices[3].y + scratch->screen_origin.y;
                    *((s16 *) (packet + 0x22)) = bottom_y;
                    {
                        s32 pair_visible;
                        s32 clip_test;
                        s32 corner_visible;
                        s32 third_visible;
                        s32 any_visible;
                        pair_visible = 0;
                        if (((u16) ((*((u16 *) (packet + 0x8))) + 0x20)) < 0x181U) {
                            clip_test = (u16) ((*((u16 *) (packet + 0xA))) + 0x20);
                            pair_visible = clip_test < 0x121U;
                        }
                        corner_visible = 0;
                        if (((u16) ((*((u16 *) (packet + 0x10))) + 0x20)) < 0x181U) {
                            corner_visible = ((u16) ((*((u16 *) (packet + 0x12))) + 0x20)) < 0x121U;
                        }
                        third_visible = 0;
                        clip_test = (u16) ((*((u16 *) (packet + 0x18))) + 0x20);
                        pair_visible |= corner_visible;
                        if (clip_test < 0x181U) {
                            clip_test = (u16) ((*((u16 *) (packet + 0x1A))) + 0x20);
                            third_visible = clip_test < 0x121U;
                        }
                        corner_visible = 0;
                        any_visible = pair_visible | third_visible;
                        if (((u16) ((*((u16 *) (packet + 0x20))) + 0x20)) < 0x181U) {
                            corner_visible = ((u16) (bottom_y + 0x20)) < 0x121U;
                        }
                        clip_test = any_visible | corner_visible;
                        if (clip_test != 0) {
                            *((s8 *) (packet + 3)) = 9;
                            scratch->uv_u_extent += scratch->uv_u_start;
                            if (scratch->uv_u_extent & 0x100) {
                                scratch->uv_u_extent -= 1;
                            }
                            scratch->uv_v_extent += scratch->uv_v_start;
                            if (scratch->uv_v_extent & 0x100) {
                                scratch->uv_v_extent -= 1;
                            }
                            scratch->uv_v_extent <<= 8;
                            scratch->uv_v_start <<= 8;
                            *((s32 *) (packet + 0xC)) = (scratch->uv_v_start + scratch->uv_u_start)
                                + ((render_state_addr->clut
                                + (*((u16 *) (quad + 0x6)))) << 16);
                            *((s16 *) (packet + 0x14)) =
                                ((u16)scratch->uv_v_start) + ((u16)scratch->uv_u_extent);
                            {
                                u16 blend_mode;
                                u16 tpage;
                                blend_mode = render_state_addr->tpage_abr;
                                if (blend_mode != 0) {
                                    tpage = blend_mode + ((*((u16 *) (quad + 0x4))) & 0xFF9F);
                                }
                                else {
                                    tpage = *((u16 *) (quad + 0x4));
                                }
                                *((u16 *) (packet + 0x16)) = tpage;
                            }
                            *((s16 *) (packet + 0x1C)) =
                                ((u16)scratch->uv_v_extent) + ((u16)scratch->uv_u_start);
                            {
                                s32 bottom_right_uv;
                                s32 right_x;
                                s32 count_or_x;
                                bottom_right_uv = (u16)scratch->uv_v_extent;
                                bottom_right_uv += (u16)scratch->uv_u_extent;
                                *((s16 *) (packet + 0x24)) = bottom_right_uv;
                                count_or_x = *((s16 *) (packet + 0x8));
                                right_x = *((s16 *) (packet + 0x20));
                                if (right_x < count_or_x) {
                                    *((packet + 0x14)) -= 1;
                                    *((packet + 0x24)) -= 1;
                                }
                            }
                            if ((*((s16 *) (packet + 0xA))) > (*((s16 *) (packet + 0x22)))) {
                                *((packet + 0x1D)) -= 1;
                                *((packet + 0x25)) -= 1;
                            }
                            {
                                u16 part_flags;
                                u8 flags;
                                part_flags = *((u16 *) (part + 0x14));
                                flags = quad[1];
                                *((part + 0xF)) = flags;
                                if (part_flags & 8) {
                                    u8 draw_flags;
                                    if (part_flags & 4) {
                                        draw_flags = flags | 2;
                                    }
                                    else {
                                        draw_flags = flags & 0xFD;
                                    }
                                    *((part + 0xF)) = draw_flags;
                                }
                            }
                            {
                                u8 flags;
                                if ((*((u16 *) (part + 0x14))) & 0x10) {
                                    flags = (*((part + 0xF))) | 1;
                                }
                                else {
                                    flags = (*((part + 0xF))) & 0xFE;
                                }
                                *((part + 0xF)) = flags;
                            }
                            *((s32 *) (packet + 0x4)) = *((s32 *) (part + 0xC));
                            if (!((*((u16 *) (sprite + 4))) & 0x8000)) {
                                ((OrderingTag *)packet)->addr = ((OrderingTag *)((scratch->sort_depth << 2) + (u32)scratch->ordering_table))->addr;
                                ((OrderingTag *)((scratch->sort_depth << 2) + (u32)scratch->ordering_table))->addr = (u32)packet;
                            }
                            packet += 0x28;
                        }
                    }
                }
                if (((s8) quad[0]) < 0) {
                    break;
                }
                quad += 0xC;
            }
            index += 1;
        } while (index < (*((s16 *) (sprite + 2))));

    }
    return packet;
}
