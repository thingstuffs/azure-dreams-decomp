/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/gpu_packets.h"
#include "shared/position_query.h"
#include "shared/position_views.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "town/map.h"
#include "town/map/position.h"
#include "town/player.h"

   /* coord in draw_entry_overlays */

   /* &D_800D0504 in draw_entry_overlays */

typedef struct S_800970FC_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_3;   /* CUR_PAGE in draw_entry_overlays */

typedef struct S_800970FC_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    u8 pad_0E[0x6];
    s8 unk_14;
    s8 unk_15;
    s16 unk_16;
    u8 pad_18[0x4];
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800970FC_4;   /* temp_s0_2 in draw_entry_overlays */

typedef struct S_800970FC_5 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
} S_800970FC_5;   /* D_800D04D0 in draw_entry_overlays */

typedef struct S_800970FC_6 {
    u16 unk_00;
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    union { u8 u8; u16 u16; } unk_04;   /* accessed as both */
    union { u8 u8; u16 u16; } unk_06;   /* accessed as both */
} S_800970FC_6;   /* xy in draw_entry_overlays */

   /* D_800D04D8 in draw_entry_overlays */

typedef struct S_800970FC_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800970FC_8;   /* rect in draw_entry_overlays */

typedef struct S_800970FC_9 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_9;   /* CUR_CTX in draw_entry_overlays */

typedef struct S_800970FC_10 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_800970FC_10;   /* temp_s0_3 in draw_entry_overlays */

typedef struct S_800970FC_11 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_800970FC_11;   /* temp_s0_4 in draw_entry_overlays */

typedef struct S_800970FC_12 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_800970FC_12;   /* late_entry in draw_entry_overlays */

typedef struct S_800970FC_13 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_13;   /* late_ctx in draw_entry_overlays */

typedef struct S_800970FC_14 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_800970FC_14;   /* temp_s0_8 in draw_entry_overlays */

extern void func_80067EF4(void *, s32, s32);
extern u8 scene_object_payload_alias[];
extern u8 view_reference_entity[];
extern s32 overlay_height_in_range[3];
extern u8 player_overlay_texture_rect[];
extern u8 D_800D04D8[];
extern u8 D_800D04E0[];
extern u8 town_overlay_rotation_offset[];
extern s16 terrain_height_limits[];
extern u8 upper_draw_context[];

#define CUR_CTX (*page_state)
#define CUR_PAGE (g_game_work.draw_buffer)

/* Draws the entry and its height-dependent textured and solid overlays. */
s32 draw_entry_overlays(void) {
    s32 page_offset;
    s32 texture_y;
    s32 uv_sum;
    s32 rounded_texture_y;
    s16 draw_y;
    s16 draw_x;
    s32 rect_y;
    s32 texture_top;
    s32 bottom;
    s32 alternate_page;
    s16 page_index;
    s32 overlay_height;
    s32 height_index;
    s32 height_delta;
    s32 coord_z;
    s32 coord_x;
    s32 coord_y;
    s32 color;
    s32 page_mask;
    s32 texture_depth;
    u16 saved_draw_param;
    u32 saved_flags;
    u16 rotation;
    u16 quad_x;
    void *primitive;
    TileObject *entry;
    ObjectPosition *coord;
    S_800970FC_6 *texture_rect;
    TileObject *draw_entry;
    S_800970FC_13 *draw_ctx;
    void **page_state;
    u32 *scratch_control;
    u16 *scratch_x;
    u16 *scratch_y;
    u16 rect_width;
    u32 rect_height;
    u32 fill_height;

    page_state = &g_game_work.draw_buffer;
    entry = &reference_tile_object;
    alternate_page = CUR_PAGE != (void *)upper_draw_context;
    rotation = entry->depth_bias;
    page_index = (u16) alternate_page;
    if (!(entry->sprite_flags & 0x80)) {
        coord = view_reference_entity;
#define view_reference_entity (*(u8 *)coord)
        overlay_height_in_range[0] = 0;
        coord_x = coord->x.w.i;
        coord_y = coord->y.w.i;
        height_index = check_masked_value_in_current_range(read_map_cell_at_world_position(coord_x, coord_y) & 0xFFFF);
        if (height_index != 0) {
            coord_z = coord->z.w.i;
            height_delta = (s32) (coord_z - terrain_height_limits[height_index]) / 2;
            overlay_height = height_delta + 6;
            if ((u32) ((height_delta + 5) & 0xFFFF) < 0x3FU) {
                overlay_height_in_range[0] = 1;
                scratch_control = (u32 *)0x1F80013C;
                *scratch_control = 0;
                project_sprite_commands(NULL, coord, D_800D04E0, (s16) (rotation + ((AngleHalfView *)(&town_overlay_rotation_offset))->unk_00));
                scratch_control = (void *)0;
                scratch_control = (u32 *)0x1F80013C;
                *scratch_control = 0;
                project_sprite_commands(scene_object_payload_alias, coord, entry, (s16) (rotation + ((AngleHalfView *)(&town_overlay_rotation_offset))->unk_00));
                primitive = ((S_800970FC_3 *)CUR_PAGE)->unk_8D0;
                ((S_800970FC_3 *)CUR_PAGE)->unk_8D0 = (void *) (primitive + 0xC);
                SetDrawArea(primitive, CUR_PAGE);
                AddPrim(CUR_PAGE + 0x830, primitive);
                primitive = ((S_800970FC_3 *)CUR_PAGE)->unk_8D0;
                ((S_800970FC_3 *)CUR_PAGE)->unk_8D0 = (void *) (primitive + 0x28);
                color = 0x808080;
                ((S_800970FC_4 *)primitive)->unk_04 = color;
                SetPolyFT4(primitive);
                texture_depth = 2;
                color = texture_depth;
                texture_rect = (S_800970FC_6 *)player_overlay_texture_rect;
                page_mask = ~0xFF;
                ((S_800970FC_4 *)primitive)->unk_16 = GetTPage(texture_depth, color,
                    (s16) (((S_800970FC_5 *)player_overlay_texture_rect)->unk_00.u & page_mask),
                    (s16) (texture_rect->unk_02.u & page_mask));
                SetSemiTrans(primitive, 1);
                ((S_800970FC_4 *)primitive)->unk_0C = (s8) (((S_800970FC_5 *)player_overlay_texture_rect)->unk_00.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_0D = (s8) (texture_rect->unk_02.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_14 = (s8) ((((S_800970FC_5 *)player_overlay_texture_rect)->unk_00.s % 0x100)
                    + texture_rect->unk_04.u8);
                ((S_800970FC_4 *)primitive)->unk_15 = (s8) (texture_rect->unk_02.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_1C = (s8) (((S_800970FC_5 *)player_overlay_texture_rect)->unk_00.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_1D = (s8) ((texture_rect->unk_02.s % 0x100)
                    + texture_rect->unk_06.u8);
                ((S_800970FC_4 *)primitive)->unk_24 = (s8) ((((S_800970FC_5 *)player_overlay_texture_rect)->unk_00.s % 0x100)
                    + texture_rect->unk_04.u8);
                texture_y = texture_rect->unk_02.s;
                if (texture_y < 0) {
                    rounded_texture_y = texture_y + 0xFF;
                    page_offset = alternate_page;
                } else {
                    rounded_texture_y = texture_y;
                    page_offset = page_index;
                }
                uv_sum = texture_y - ((rounded_texture_y >> 8) * 0x100) +
                         texture_rect->unk_06.u8;
                ((S_800970FC_4 *)primitive)->unk_25 = uv_sum;
                {
                    S_800970FC_8 *rect;
                    u32 edge_height;
                    rect = (S_800970FC_8 *)D_800D04D8;
                    quad_x = ((DisplayXHalfView *)D_800D04D8)->unk_00;
                    rect_y = rect->unk_02;
                    page_offset = page_index;
                    if (page_offset != 0) {
                        rect_y -= 0xE0;
                    }
                    (*(u16 *)((u8 *)primitive + 8)) = quad_x;
                    (*(s16 *)((u8 *)primitive + 0xA)) = rect_y;
                    rect_width = rect->unk_04;
                    (*(s16 *)((u8 *)primitive + 0x10)) = (s16) (quad_x + rect_width);
                    (*(s16 *)((u8 *)primitive + 0x12)) = rect_y;
                    (*(u16 *)((u8 *)primitive + 0x18)) = quad_x;
                    rect_height = rect->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x1A)) = (s16) (rect_y + rect_height);
                    rect_width = 0;
                    rect_width = rect->unk_04;
                    (*(s16 *)((u8 *)primitive + 0x20)) = (s16) (quad_x + rect_width);
                    rect_height = 0;
                    rect_height = rect->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x22)) = (s16) (rect_y + rect_height);
                    AddPrim(CUR_CTX + 0x830, primitive);
                    primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                    ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0x18);
                    ((S_800970FC_10 *)primitive)->unk_04 = 0x40;
                    ((S_800970FC_10 *)primitive)->unk_05 = 0x40;
                    ((S_800970FC_10 *)primitive)->unk_06 = 0xC0;
                    SetPolyF4(primitive);
                    SetSemiTrans(primitive, 0);
                    (*(u16 *)((u8 *)primitive + 8)) = quad_x;
                    fill_height = rect->unk_06;
                    (*(s16 *)((u8 *)primitive + 0xA)) = (s16) ((rect_y + fill_height) - overlay_height);
                    rect_width = rect->unk_04;
                    (*(s16 *)((u8 *)primitive + 0xC)) = (s16) (quad_x + rect_width);
                    fill_height = 0;
                    edge_height = rect->unk_06;
                    (*(u16 *)((u8 *)primitive + 0x10)) = quad_x;
                    (*(s16 *)((u8 *)primitive + 0xE)) = (s16) ((rect_y + edge_height) - overlay_height);
                    edge_height = 0;
                    fill_height = rect->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x12)) = (s16) (rect_y + fill_height);
                    rect_width = 0;
                    rect_width = rect->unk_04;
                    (*(s16 *)((u8 *)primitive + 0x14)) = (s16) (quad_x + rect_width);
                    fill_height = 0;
                    fill_height = rect->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x16)) = (s16) (rect_y + fill_height);
                    AddPrim(CUR_CTX + 0x830, primitive);
                    primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                    ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0x18);
                    ((S_800970FC_11 *)primitive)->unk_06 = 0;
                    ((S_800970FC_11 *)primitive)->unk_05 = 0;
                    ((S_800970FC_11 *)primitive)->unk_04 = 0;
                    SetPolyF4(primitive);
                    SetSemiTrans(primitive, 0);
                    ((S_800970FC_11 *)primitive)->unk_08 = quad_x;
                    ((S_800970FC_11 *)primitive)->unk_0A = rect_y;
                    rect_width = rect->unk_04;
                    ((S_800970FC_11 *)primitive)->unk_0C = (s16) (quad_x + rect_width);
                    ((S_800970FC_11 *)primitive)->unk_0E = rect_y;
                    ((S_800970FC_11 *)primitive)->unk_10 = quad_x;
                    rect_height = rect->unk_06;
                    ((S_800970FC_11 *)primitive)->unk_12 = (s16) (rect_y + rect_height);
                    rect_width = 0;
                    rect_width = rect->unk_04;
                    ((S_800970FC_11 *)primitive)->unk_14 = (s16) (quad_x + rect_width);
                    rect_height = 0;
                    rect_height = rect->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x16)) = (s16) (rect_y + rect_height);
                    AddPrim(CUR_CTX + 0x830, primitive);
                    primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                    ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0xC);
                    SetDrawArea(primitive, rect);
                    AddPrim(CUR_CTX + 0x830, primitive);
                }
                draw_entry = &reference_tile_object;
                quad_x = texture_rect->unk_00;
                texture_top = texture_rect->unk_02.s;
                saved_flags = draw_entry->sprite_flags;
                saved_draw_param = draw_entry->tpage_offset;
                {
                    if (page_offset != 0) {
                        texture_top -= 0xE0;
                    }
                }
                draw_x = quad_x + 0x20;
                draw_y = texture_top + 0x39;
                scratch_x = (u16 *)0x1F800000;
                scratch_y = (u16 *)0x1F800002;
                *scratch_x = (u16) draw_x;
                *scratch_y = (u16) draw_y;
                draw_entry->tpage_offset = 0x40U;
                draw_entry->sprite_flags = (u16) ((*(u16 *)((u8 *)draw_entry + 0x14)) | 0xC);
                draw_sprite_parts(0, draw_entry, 0x1F0);
                scratch_x = (void *)0;
                scratch_y = (void *)0;
                scratch_x = (u16 *)0x1F800000;
                scratch_y = (u16 *)0x1F800002;
                *scratch_x = (u16) draw_x;
                *scratch_y = (u16) draw_y;
                draw_entry->tpage_offset = 0x20U;
                draw_entry->sprite_flags = (u16) ((*(u16 *)((u8 *)draw_entry + 0x14)) & 0xFFF3);
                draw_sprite_parts(0, draw_entry, 0x1F0);
                draw_ctx = CUR_CTX;
                draw_entry->sprite_flags = saved_flags;
                draw_entry->tpage_offset = saved_draw_param;
                primitive = draw_ctx->unk_8D0;
                draw_ctx->unk_8D0 = (void *) (primitive + 0xC);
                func_80067EF4(primitive, 0, 0);
                AddPrim(CUR_CTX + 0x830, primitive);
                primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0x18);
                ((S_800970FC_14 *)primitive)->unk_06 = 0xFF;
                ((S_800970FC_14 *)primitive)->unk_05 = 0xFF;
                ((S_800970FC_14 *)primitive)->unk_04 = 0xFF;
                SetPolyF4(primitive);
                SetSemiTrans(primitive, 0);
                (*(u16 *)((u8 *)primitive + 8)) = quad_x;
                (*(s16 *)((u8 *)primitive + 0xA)) = texture_top;
                (*(s16 *)((u8 *)primitive + 0xC)) = (s16) (quad_x + texture_rect->unk_04.u16);
                (*(s16 *)((u8 *)primitive + 0xE)) = texture_top;
                (*(u16 *)((u8 *)primitive + 0x10)) = quad_x;
                bottom = texture_top + texture_rect->unk_06.u16;
                (*(s16 *)((u8 *)primitive + 0x12)) = bottom;
                (*(s16 *)((u8 *)primitive + 0x14)) = (s16) (quad_x + texture_rect->unk_04.u16);
                bottom = texture_top + texture_rect->unk_06.u16;
                (*(s16 *)((u8 *)primitive + 0x16)) = bottom;
                AddPrim(CUR_CTX + 0x830, primitive);
                primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0xC);
                func_80067EF4(primitive, 0, 1);
                AddPrim(CUR_CTX + 0x830, primitive);
                primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0xC);
                SetDrawArea(primitive, texture_rect);
                AddPrim(CUR_CTX + 0x830, primitive);
                return 0;
            }
        }
        scratch_control = (void *)0;
        scratch_control = (u32 *)0x1F80013C;
        *scratch_control = 0;
        project_sprite_commands(scene_object_payload_alias, coord, entry, (s16) (rotation + ((AngleHalfView *)(&town_overlay_rotation_offset))->unk_00));
        return 0;
    }
    return 0;
}
