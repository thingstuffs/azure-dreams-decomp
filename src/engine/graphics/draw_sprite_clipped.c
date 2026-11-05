#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/graphics/sprite_scratch.h"
#include "sdk/libgte.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80045CC4_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    u16 unk_1C;
    u16 unk_1E;
    union {
        struct { s16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_20;   /* overlapping accesses */
} S_80045CC4_0;   /* poly in draw_sprite_clipped */

typedef struct {
    u8 pad00[8];
    u8 *unk08;
    s32 unk0C;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
} S_80045CC4_Arg2;

/* Transform sprite quads, clip them to the screen, and link visible packets into the ordering table. */
void draw_sprite_clipped(void *context, s32 position, S_80045CC4_Arg2 *sprite, s16 depth_bias)
{
    ObjectPosition *position_data = (ObjectPosition *)position;
    void (*callback)(void *, s32, S_80045CC4_Arg2 *, u8 *);
    s32 x;
    s32 packet_addr;
    s32 matrix_yy;
    s32 matrix_xx;
    s32 *packet;
    s32 depth;
    s32 visible_0;
    s32 visible_1;
    s32 any_visible;
    u32 addr_mask;
    s32 visible_3;
    u8 *entry;
    SpriteQuadScratch *scratchpad;
    void **global_slots;
    void *global_base;
    u8 uv_edge;
    s32 visible_2;
    s16 sx;
    s16 sy;
    s16 ex;
    s16 ey;

    global_slots = ((void * *)(&g_game_work));
    global_base = global_slots[0];
    scratchpad = (SpriteQuadScratch *)0x1F800000;
    scratchpad->ordering_table = (s32)((u8 *)global_base + 0xB0);
    {
        s32 translation;
        translation = position_data->x.w.i;
        scratchpad->local_matrix.t[0] = translation;
        translation = position_data->y.w.i;
        scratchpad->local_matrix.t[1] = translation;
        translation = position_data->z.w.i;
        scratchpad->vertices[3].z = 0;
        scratchpad->vertices[2].z = 0;
        scratchpad->vertices[1].z = 0;
        scratchpad->vertices[0].z = 0;
        scratchpad->local_matrix.t[2] = translation;
    }
    packet = *(s32 **)((u8 *)global_base + 0x8D0);
    sprite->unk14 |= 0x8000;
    addr_mask = 0xFFFFFF;
    PushMatrix();

    scratchpad->extent_x = sprite->unk20;
    scratchpad->extent_y = sprite->unk22;
    scratchpad->input_x = sprite->unk1C * 2;
    scratchpad->input_y = sprite->unk1E * 2;
    scratchpad->input_z = 0x2000;
    scratchpad->angle_x = sprite->unk16;
    scratchpad->angle_z = sprite->unk1A;
    scratchpad->angle_y = sprite->unk18;

    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);
    ReadRotMatrix((void *)0x1F80011C);
    CompMatrix((void *)0x1F80011C, (void *)0x1F8000D0, (void *)0x1F800050);
    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    SetTransMatrix((void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);

    entry = sprite->unk08;
    scratchpad->sprite_flags = sprite->unk14;

    for (;;) {
    if (!(entry[0] & 0x20)) {
        u8 u_start;
        u8 width;
        u8 v_start;
        u8 height;

        u_start = entry[8];
        scratchpad->uv_u_start = u_start;
        width = entry[10];
        scratchpad->uv_u_extent = width;
        if ((u_start + width >= 0x100) || sprite->unk1A != 0) {
            scratchpad->uv_u_extent = width - 1;
        }

        v_start = entry[9];
        scratchpad->uv_v_start = v_start;
        height = entry[11];
        scratchpad->uv_v_extent = height;
        if ((v_start + height >= 0x100) || sprite->unk1A != 0) {
            scratchpad->uv_v_extent = height - 1;
        }

        if ((entry[0] ^ scratchpad->sprite_flags) & 1) {
            sx = -((s8 *)entry)[2] - scratchpad->extent_x;
            scratchpad->vertices[2].x = sx;
            scratchpad->vertices[0].x = sx;
            ex = sx - (u16)scratchpad->uv_u_extent;
            scratchpad->vertices[3].x = ex;
            scratchpad->vertices[1].x = ex;
        } else {
            sx = ((s8 *)entry)[2] - scratchpad->extent_x;
            scratchpad->vertices[2].x = sx;
            scratchpad->vertices[0].x = sx;
            ex = sx + (u16)scratchpad->uv_u_extent;
            scratchpad->vertices[3].x = ex;
            scratchpad->vertices[1].x = ex;
        }

        if ((entry[0] ^ scratchpad->sprite_flags) & 2) {
            sy = -((s8 *)entry)[3] - scratchpad->extent_y;
            scratchpad->vertices[1].y = sy;
            scratchpad->vertices[0].y = sy;
            ey = sy - (u16)scratchpad->uv_v_extent;
            scratchpad->vertices[3].y = ey;
            scratchpad->vertices[2].y = ey;
        } else {
            sy = ((s8 *)entry)[3] - scratchpad->extent_y;
            scratchpad->vertices[1].y = sy;
            scratchpad->vertices[0].y = sy;
            ey = sy + (u16)scratchpad->uv_v_extent;
            scratchpad->vertices[3].y = ey;
            scratchpad->vertices[2].y = ey;
        }

        depth = RotAverage4(
            &scratchpad->vertices[0], &scratchpad->vertices[1],
            &scratchpad->vertices[2], &scratchpad->vertices[3],
            packet + 2, packet + 4, packet + 6, packet + 8,
            &scratchpad->depth_cue, &scratchpad->gte_flag);
        depth = depth - depth_bias - 8;
        scratchpad->sort_depth = depth;

        if ((u32)depth < 0x1E0U) {
            visible_0 = 0;
            if ((u32)((((S_80045CC4_0 *)(packet + 1))->unk_04 + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)(packet + 1))->unk_06 + 0x20) & 0xFFFF;
                    visible_0 = clip_y < 0x121U;
                }
            }
            visible_1 = 0;
            if ((u32)((((S_80045CC4_0 *)(packet + 1))->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)(packet + 1))->unk_0E + 0x20) & 0xFFFF;
                    visible_1 = clip_y < 0x121U;
                }
            }
            visible_2 = 0;
            visible_0 |= visible_1;
            if ((u32)((((S_80045CC4_0 *)(packet + 1))->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)(packet + 1))->unk_16 + 0x20) & 0xFFFF;
                    visible_2 = clip_y < 0x121U;
                }
            }
            visible_3 = 0;
            any_visible = visible_0 | visible_2;
            if ((u32)((((S_80045CC4_0 *)(packet + 1))->unk_1C + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)(packet + 1))->unk_1E + 0x20) & 0xFFFF;
                    visible_3 = clip_y < 0x121U;
                }
            }

            if (any_visible | visible_3) {
                ((u8 *)packet)[3] = 9;
                *&sprite->unk14 &= 0x7FFF;

                scratchpad->uv_u_extent += scratchpad->uv_u_start;
                scratchpad->uv_v_extent += scratchpad->uv_v_start;
                scratchpad->uv_v_start <<= 8;
                scratchpad->uv_v_extent <<= 8;

                if (scratchpad->sprite_flags & 0x100) {
                    ((S_80045CC4_0 *)(packet + 1))->unk_0A = sprite->unk12;
                } else {
                    ((S_80045CC4_0 *)(packet + 1))->unk_0A = sprite->unk12 + *(u16 *)(entry + 6);
                }

                ((S_80045CC4_0 *)(packet + 1))->unk_08 = (u16)scratchpad->uv_v_start + (u16)scratchpad->uv_u_start;
                ((S_80045CC4_0 *)(packet + 1))->unk_10.s16 = (u16)scratchpad->uv_v_start + (u16)scratchpad->uv_u_extent;
                {
                    u16 tpage;
                    visible_3 = sprite->unk10;
                    if (visible_3 != 0) {
                        tpage = visible_3 + (*(u16 *)(entry + 4) & 0xFF9F);
                        ((S_80045CC4_0 *)(packet + 1))->unk_12 = tpage;
                        ((S_80045CC4_0 *)(packet + 1))->unk_18.at00.v = (u16)scratchpad->uv_v_extent + (u16)scratchpad->uv_u_start;
                        ((S_80045CC4_0 *)(packet + 1))->unk_20.at00.v = (u16)scratchpad->uv_v_extent + (u16)scratchpad->uv_u_extent;
                        matrix_xx = (u16)scratchpad->matrix.m[0][0];
                    } else {
                        tpage = *(u16 *)(entry + 4);
                        ((S_80045CC4_0 *)(packet + 1))->unk_12 = tpage;
                        ((S_80045CC4_0 *)(packet + 1))->unk_18.at00.v = (u16)scratchpad->uv_v_extent + (u16)scratchpad->uv_u_start;
                        ((S_80045CC4_0 *)(packet + 1))->unk_20.at00.v = (u16)scratchpad->uv_v_extent + (u16)scratchpad->uv_u_extent;
                        matrix_xx = (u16)scratchpad->matrix.m[0][0];
                    }
                }
                {
                    if (((matrix_xx << 16) >> 16) >= 0x1800) {
                        uv_edge = ((S_80045CC4_0 *)(packet + 1))->unk_20.at00u.v;
                        ((S_80045CC4_0 *)(packet + 1))->unk_20.at00u.v = uv_edge + 0xFF;
                        ((S_80045CC4_0 *)(packet + 1))->unk_10.u8 = uv_edge;
                        matrix_yy = (u16)scratchpad->matrix.m[1][1];
                    } else {
                        matrix_yy = (u16)scratchpad->matrix.m[1][1];
                    }
                }
                {
                    if (((matrix_yy << 16) >> 16) >= 0x1800) {
                        uv_edge = ((S_80045CC4_0 *)(packet + 1))->unk_20.at01.v;
                        ((S_80045CC4_0 *)(packet + 1))->unk_20.at01.v = uv_edge + 0xFF;
                        ((S_80045CC4_0 *)(packet + 1))->unk_18.at01.v = uv_edge;
                    }
                }
                if (((s16)((S_80045CC4_0 *)(packet + 1))->unk_04) > ((s16)((S_80045CC4_0 *)(packet + 1))->unk_1C)) {
                    ((S_80045CC4_0 *)(packet + 1))->unk_10.u8--;
                    ((S_80045CC4_0 *)(packet + 1))->unk_20.at00u.v--;
                }
                if (((s16)((S_80045CC4_0 *)(packet + 1))->unk_06) > ((s16)((S_80045CC4_0 *)(packet + 1))->unk_1E)) {
                    ((S_80045CC4_0 *)(packet + 1))->unk_18.at01.v--;
                    ((S_80045CC4_0 *)(packet + 1))->unk_20.at01.v--;
                }

                visible_2 = entry[1];
                ((SpriteFrameState *)sprite)->color.c.code = visible_2;
                visible_3 = scratchpad->sprite_flags;
                if (visible_3 & 8) {
                    if (visible_3 & 4) {
                        x = visible_2 | 2;
                        ((SpriteFrameState *)sprite)->color.c.code = x;
                    } else {
                        x = visible_2 & 0xFD;
                        ((SpriteFrameState *)sprite)->color.c.code = x;
                    }
                }
                visible_0 = 0xFF000000;
                packet[1] = sprite->unk0C;
                packet_addr = (u32)packet & addr_mask;

                {
                    s32 *ot_bucket;

                    *packet = (*packet & (u32)visible_0) |
                        (*(s32 *)(scratchpad->sort_depth * 4 + scratchpad->ordering_table) & addr_mask);
                    ot_bucket = (s32 *)(scratchpad->sort_depth * 4 + scratchpad->ordering_table);
                    packet += 10;
                    *ot_bucket = (*ot_bucket & (u32)visible_0) | packet_addr;
                }
            }
        }
    } else {
        callback = *(void (**)(void *, s32, S_80045CC4_Arg2 *, u8 *))(entry + 8);
        if (callback != NULL) {
            callback(context, position, sprite, entry);
        }
    }

    if ((s8)entry[0] < 0) {
        break;
    }
    entry += 0xC;
    }

    PopMatrix();
    *(s32 **)((u8 *)global_slots[0] + 0x8D0) = packet;
}
