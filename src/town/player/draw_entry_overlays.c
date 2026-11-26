#include "engine/graphics/sprite_scratch.h"
#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/gpu_packets.h"
#include "shared/position_query.h"
#include "shared/position_views.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_packets.h"
#include "town/map.h"
#include "town/map/position.h"
#include "town/player.h"
#include "town/player/overlay_height_data.h"
#include "town/data.h"

   /* coord in draw_entry_overlays */

   /* &D_800D0504 in draw_entry_overlays */

/* Texture rectangle used for the page selector and overlay UV limits.
 * Coordinates retain both signed and unsigned halfword reads; extents are
 * read as bytes for UVs and as halfwords for the projected rectangle. */
typedef struct PlayerOverlayTextureRect {
    s16 x;
    s16 y;
    u16 width;
    u16 height;
} PlayerOverlayTextureRect;

   /* D_800D04D8 in draw_entry_overlays */

typedef struct S_800970FC_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800970FC_8;   /* rect in draw_entry_overlays */

   /* late_entry in draw_entry_overlays */

extern u8 scene_object_payload_alias[];
extern PlayerOverlayTextureRect player_overlay_texture_rect;
extern u8 D_800D04D8[];
extern u8 D_800D04E0[];

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
    /* Each quad keeps its final signed Y store ahead of the ordering-table load. */
    POLY_FT4 *textured;
    POLY_F4 *flat;
    TileObject *entry;
    ObjectPosition *coord;
    PlayerOverlayTextureRect *texture_rect;
    TileObject *draw_entry;
    GpuContext *draw_ctx;
    GpuContext **page_state;
    SpriteQuadScratch *scratch_control;
    s16 *scratch_x;
    s16 *scratch_y;
    u16 rect_width;
    u32 rect_height;
    u32 fill_height;

    page_state = &g_game_work.draw_buffer;
    entry = &reference_tile_object;
    alternate_page = CUR_PAGE != upper_draw_context;
    rotation = entry->depth_bias;
    page_index = (u16) alternate_page;
    if (!(entry->sprite_flags & 0x80)) {
        coord = &view_reference_entity;
        overlay_height_in_range = 0;
        coord_x = coord->x.w.i;
        coord_y = coord->y.w.i;
        height_index = check_masked_value_in_current_range(read_map_cell_at_world_position(coord_x, coord_y) & 0xFFFF);
        if (height_index != 0) {
            coord_z = coord->z.w.i;
            height_delta = (s32) (coord_z - terrain_height_limits[height_index]) / 2;
            overlay_height = height_delta + 6;
            if ((u32) ((height_delta + 5) & 0xFFFF) < 0x3FU) {
                overlay_height_in_range = 1;
                scratch_control = SPRITE_SCRATCH;
                scratch_control->vertex_y_offset = 0;
                project_sprite_commands(NULL, coord, D_800D04E0, (s16) (rotation + ((AngleHalfView *)(&town_overlay_rotation_offset))->unk_00));
                scratch_control = (void *)0;
                scratch_control = SPRITE_SCRATCH;
                scratch_control->vertex_y_offset = 0;
                project_sprite_commands(scene_object_payload_alias, coord, entry, (s16) (rotation + ((AngleHalfView *)(&town_overlay_rotation_offset))->unk_00));
                primitive = CUR_PAGE->packetCursor;
                CUR_PAGE->packetCursor = (primitive + 0xC);
                SetDrawArea(primitive, &CUR_PAGE->draw.clip);
                AddPrim(&CUR_PAGE->orderTag[496], primitive);
                textured = CUR_PAGE->packetCursor;
                CUR_PAGE->packetCursor = textured + 1;
                color = 0x808080;
                *(u32 *)&textured->r0 = color;
                SetPolyFT4(textured);
                texture_depth = 2;
                color = texture_depth;
                texture_rect = &player_overlay_texture_rect;
                page_mask = ~0xFF;
                textured->tpage = GetTPage(texture_depth, color,
                    (s16) (((u16)player_overlay_texture_rect.x) & page_mask),
                    (s16) (((u16)texture_rect->y) & page_mask));
                SetSemiTrans(textured, 1);
                textured->u0 = (s8) (player_overlay_texture_rect.x % 0x100);
                textured->v0 = (s8) (texture_rect->y % 0x100);
                textured->u1 = (s8) ((player_overlay_texture_rect.x % 0x100)
                    + ((u8)texture_rect->width));
                textured->v1 = (s8) (texture_rect->y % 0x100);
                textured->u2 = (s8) (player_overlay_texture_rect.x % 0x100);
                textured->v2 = (s8) ((texture_rect->y % 0x100)
                    + ((u8)texture_rect->height));
                textured->u3 = (s8) ((player_overlay_texture_rect.x % 0x100)
                    + ((u8)texture_rect->width));
                texture_y = texture_rect->y;
                if (texture_y < 0) {
                    rounded_texture_y = texture_y + 0xFF;
                    page_offset = alternate_page;
                } else {
                    rounded_texture_y = texture_y;
                    page_offset = page_index;
                }
                uv_sum = texture_y - ((rounded_texture_y >> 8) * 0x100) +
                         ((u8)texture_rect->height);
                textured->v3 = uv_sum;
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
                    textured->x0 = quad_x;
                    textured->y0 = rect_y;
                    rect_width = rect->unk_04;
                    textured->x1 = (s16) (quad_x + rect_width);
                    textured->y1 = rect_y;
                    textured->x2 = quad_x;
                    rect_height = rect->unk_06;
                    textured->y2 = (s16) (rect_y + rect_height);
                    rect_width = 0;
                    rect_width = rect->unk_04;
                    textured->x3 = (s16) (quad_x + rect_width);
                    rect_height = 0;
                    rect_height = rect->unk_06;
                    *(s16 *)((u8 *)textured + 0x22) = (s16) (rect_y + rect_height);
                    AddPrim(&CUR_CTX->orderTag[496], textured);
                    flat = CUR_CTX->packetCursor;
                    CUR_CTX->packetCursor = flat + 1;
                    flat->red = 0x40;
                    flat->green = 0x40;
                    flat->blue = 0xC0;
                    SetPolyF4(flat);
                    SetSemiTrans(flat, 0);
                    flat->x0 = quad_x;
                    fill_height = rect->unk_06;
                    flat->y0 = (s16) ((rect_y + fill_height) - overlay_height);
                    rect_width = rect->unk_04;
                    flat->x1 = (s16) (quad_x + rect_width);
                    fill_height = 0;
                    edge_height = rect->unk_06;
                    flat->x2 = quad_x;
                    flat->y1 = (s16) ((rect_y + edge_height) - overlay_height);
                    edge_height = 0;
                    fill_height = rect->unk_06;
                    flat->y2 = (s16) (rect_y + fill_height);
                    rect_width = 0;
                    rect_width = rect->unk_04;
                    flat->x3 = (s16) (quad_x + rect_width);
                    fill_height = 0;
                    fill_height = rect->unk_06;
                    *(s16 *)((u8 *)flat + 0x16) = (s16) (rect_y + fill_height);
                    AddPrim(&CUR_CTX->orderTag[496], flat);
                    flat = CUR_CTX->packetCursor;
                    CUR_CTX->packetCursor = flat + 1;
                    flat->blue = 0;
                    flat->green = 0;
                    flat->red = 0;
                    SetPolyF4(flat);
                    SetSemiTrans(flat, 0);
                    flat->x0 = quad_x;
                    flat->y0 = rect_y;
                    rect_width = rect->unk_04;
                    flat->x1 = (s16) (quad_x + rect_width);
                    flat->y1 = rect_y;
                    flat->x2 = quad_x;
                    rect_height = rect->unk_06;
                    flat->y2 = (s16) (rect_y + rect_height);
                    rect_width = 0;
                    rect_width = rect->unk_04;
                    flat->x3 = (s16) (quad_x + rect_width);
                    rect_height = 0;
                    rect_height = rect->unk_06;
                    *(s16 *)((u8 *)flat + 0x16) = (s16) (rect_y + rect_height);
                    AddPrim(&CUR_CTX->orderTag[496], flat);
                    primitive = CUR_CTX->packetCursor;
                    CUR_CTX->packetCursor = (primitive + 0xC);
                    SetDrawArea(primitive, rect);
                    AddPrim(&CUR_CTX->orderTag[496], primitive);
                }
                draw_entry = &reference_tile_object;
                quad_x = ((u16)texture_rect->x);
                texture_top = texture_rect->y;
                saved_flags = draw_entry->sprite_flags;
                saved_draw_param = draw_entry->tpage_offset;
                {
                    if (page_offset != 0) {
                        texture_top -= 0xE0;
                    }
                }
                draw_x = quad_x + 0x20;
                draw_y = texture_top + 0x39;
                scratch_x = &SPRITE_SCRATCH->position.vx;
                scratch_y = &SPRITE_SCRATCH->position.vy;
                *scratch_x = draw_x;
                *scratch_y = draw_y;
                draw_entry->tpage_offset = 0x40U;
                draw_entry->sprite_flags = (u16) ((*(u16 *)((u8 *)draw_entry + 0x14)) | 0xC);
                draw_sprite_parts(0, draw_entry, 0x1F0);
                scratch_x = (void *)0;
                scratch_y = (void *)0;
                scratch_x = &SPRITE_SCRATCH->position.vx;
                scratch_y = &SPRITE_SCRATCH->position.vy;
                *scratch_x = draw_x;
                *scratch_y = draw_y;
                draw_entry->tpage_offset = 0x20U;
                draw_entry->sprite_flags = (u16) ((*(u16 *)((u8 *)draw_entry + 0x14)) & 0xFFF3);
                draw_sprite_parts(0, draw_entry, 0x1F0);
                draw_ctx = CUR_CTX;
                draw_entry->sprite_flags = saved_flags;
                draw_entry->tpage_offset = saved_draw_param;
                primitive = draw_ctx->packetCursor;
                draw_ctx->packetCursor = (primitive + 0xC);
                SetPriority(primitive, 0, 0);
                AddPrim(&CUR_CTX->orderTag[496], primitive);
                flat = CUR_CTX->packetCursor;
                CUR_CTX->packetCursor = flat + 1;
                flat->blue = 0xFF;
                flat->green = 0xFF;
                flat->red = 0xFF;
                SetPolyF4(flat);
                SetSemiTrans(flat, 0);
                flat->x0 = quad_x;
                flat->y0 = texture_top;
                flat->x1 = (s16) (quad_x + texture_rect->width);
                flat->y1 = texture_top;
                flat->x2 = quad_x;
                bottom = texture_top + texture_rect->height;
                flat->y2 = bottom;
                flat->x3 = (s16) (quad_x + texture_rect->width);
                bottom = texture_top + texture_rect->height;
                *(s16 *)((u8 *)flat + 0x16) = bottom;
                AddPrim(&CUR_CTX->orderTag[496], flat);
                primitive = CUR_CTX->packetCursor;
                CUR_CTX->packetCursor = (primitive + 0xC);
                SetPriority(primitive, 0, 1);
                AddPrim(&CUR_CTX->orderTag[496], primitive);
                primitive = CUR_CTX->packetCursor;
                CUR_CTX->packetCursor = (primitive + 0xC);
                SetDrawArea(primitive, texture_rect);
                AddPrim(&CUR_CTX->orderTag[496], primitive);
                return 0;
            }
        }
        scratch_control = (void *)0;
        scratch_control = SPRITE_SCRATCH;
        scratch_control->vertex_y_offset = 0;
        project_sprite_commands(scene_object_payload_alias, coord, entry, (s16) (rotation + ((AngleHalfView *)(&town_overlay_rotation_offset))->unk_00));
        return 0;
    }
    return 0;
}
