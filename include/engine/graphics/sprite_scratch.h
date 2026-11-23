#ifndef ENGINE_GRAPHICS_SPRITE_SCRATCH_H
#define ENGINE_GRAPHICS_SPRITE_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"

typedef struct SpriteScratchScreenPoint {
    u16 x;
    u16 y;
} SpriteScratchScreenPoint;

/* Quad renderers share these UV, matrix, vertex, depth and GTE output slots.
 * The three input words at +0x30 hold camera angles before they are reused
 * for scale. The matrix translation is also the temporary sprite offset.
 * The terrain query block (TerrainQueryScratch) starts at +0x140, so a renderer may call
 * sample_terrain_surface_height with these slots live. matrix_50 and matrix_D0 swap roles in
 * transform_mesh_and_append_draw_packets, set_effect_gte_matrix and draw_lit_mesh. */
typedef struct SpriteQuadScratch {
    /* 0x000 */ SVECTOR position; /* RotTransPers input: the sprite's world position; draw_sprite_parts reads vx/vy set by its callers */
    /* 0x008 */ u32 uv_u_start;
    /* 0x00C */ u32 uv_v_start;
    /* 0x010 */ u32 uv_u_extent;
    /* 0x014 */ u32 uv_v_extent;
    /* 0x018 */ void *packet_cursor; /* draw-context packet cursor copied here for the walk */
    /* 0x01C */ u8 pad_1C[4];
    /* 0x020 */ u32 *ordering_table;
    /* 0x024 */ u16 sprite_flags;
    /* 0x026 */ u16 pad_26;
    /* 0x028 */ SVECTOR rotation; /* RotMatrix angles; RotTransPers input position in transform_mesh_and_append_draw_packets; a centre offset in build_transformed_sprite_quads */
    /* 0x030 */ VECTOR input; /* camera angles, then the ScaleMatrix scale */
    /* 0x040 */ VECTOR translation;
    /* 0x050 */ MATRIX matrix_50; /* composed matrix set into the GTE in most renderers; RotMatrix output in three */
    /* 0x070 */ SVECTOR vertices[4]; /* RotTransPers4/RotAverage4 inputs */
    /* 0x090 */ s32 depth_cue;
    /* 0x094 */ s32 gte_flag;
    /* 0x098 */ SVECTOR rotated[4]; /* rotated corners of the rotating quads; projected parts in draw_transformed_sprite_parts; [0] holds RotMatrix angles in the sprite quad builders */
    /* 0x0B8 */ SpriteScratchScreenPoint screen_origin;
    /* 0x0BC */ u8 pad_BC[4];
    /* 0x0C0 */ u32 sort_depth;
    /* 0x0C4 */ s32 second_depth; /* second vertex depth in transform_mesh_and_append_draw_packets; depth base in render_three_by_three_terrain_grid */
    /* 0x0C8 */ s32 third_depth;
    /* 0x0CC */ s32 depth_offset;
    /* 0x0D0 */ MATRIX matrix_D0; /* RotMatrix output in most renderers; composed matrix set into the GTE in three */
    /* 0x0F0 */ SpriteScratchScreenPoint projected_vertices[4];
    /* 0x100 */ SVECTOR angles; /* RotMatrix input; build_transformed_sprite_quads reads centre values here */
    /* 0x108 */ u16 extent_x;
    /* 0x10A */ u16 extent_y;
    /* 0x10C */ u8 pad_10C[8];
    /* 0x114 */ s32 winding; /* NormalClip result of the projected quad */
    /* 0x118 */ void *texture_entries; /* 12-byte texture entry table of the strip projectors */
    /* 0x11C */ MATRIX view_matrix; /* ReadRotMatrix copy composed with the rotation */
    /* 0x13C */ u32 vertex_y_offset; /* set by the callers of project_sprite_commands before the call */
} SpriteQuadScratch;
#define SPRITE_SCRATCH ((SpriteQuadScratch *)0x1F800000)

/* The linked renderer stores the PS1 matrix as five packed rotation words
 * followed by three translation words, then copies those words to its nodes. */
typedef struct SpriteLinkedMatrix {
    s32 rotation_row0_xy;
    s32 rotation_row0_z_row1_x;
    s32 rotation_row1_yz;
    s32 rotation_row2_xy;
    s32 rotation_row2_z_pad;
    s32 translation_x;
    s32 translation_y;
    s32 translation_z;
} SpriteLinkedMatrix;

typedef struct SpriteLinkedScreenPoint {
    u16 x;
    u16 y;
    u32 pad;
} SpriteLinkedScreenPoint;

/* The linked renderer's scratch slots are displaced by four bytes from the
 * other quad renderers: vertices begin at +0x74 and projected XY at +0x9C. The town menu and map
 * quad builders and the ring builder use the same slots. */
typedef struct SpriteLinkedScratch {
    /* 0x000 */ u8 pad_000[4];
    /* 0x004 */ SVECTOR position;
    /* 0x00C */ s32 uv_u_start;
    /* 0x010 */ s32 uv_v_start;
    /* 0x014 */ s32 uv_u_extent;
    /* 0x018 */ s32 uv_v_extent;
    /* 0x01C */ void *packet_cursor;
    /* 0x020 */ u8 pad_020[4];
    /* 0x024 */ u32 *ordering_table;
    /* 0x028 */ u16 context_flags;
    /* 0x02A */ u8 pad_02A[2];
    /* 0x02C */ SVECTOR work_vector; /* RotMatrix angles in animate_spinning_shrinking_object; RotTransSV position in render_shaded_object_primitive */
    /* 0x034 */ VECTOR input; /* ScaleMatrix scale */
    /* 0x044 */ VECTOR translation;
    /* 0x054 */ SpriteLinkedMatrix matrix;
    /* 0x074 */ SVECTOR vertices[4]; /* RotTransPers4 inputs */
    /* 0x094 */ s32 depth_cue;
    /* 0x098 */ s32 gte_flag;
    /* 0x09C */ SpriteLinkedScreenPoint projected_vertices[4];
    /* 0x0BC */ SpriteScratchScreenPoint screen_origin;
    /* 0x0C0 */ u8 pad_0C0[4];
    /* 0x0C4 */ s32 ordering_depth;
    /* 0x0C8 */ MATRIX work_matrix;
    /* 0x0E8 */ SpriteScratchScreenPoint screen[4]; /* RotTransPers4 outputs of the menu and map builders */
    /* 0x0F8 */ SVECTOR work_angles; /* RotMatrix angles for work_matrix in draw_sprites_with_dimmed_copies */
    /* 0x100 */ SVECTOR angles;
    /* 0x108 */ u8 pad_108[0xC];
    /* 0x114 */ u8 pad_114[0x18]; /* slots only the town ring builder uses; its record is TownRingProjection */
} SpriteLinkedScratch;
#define LINKED_SPRITE_SCRATCH ((SpriteLinkedScratch *)0x1F800000)


/* RotTransPersN output arrays: screen points, depths, and one halfword array that receives both the
 * interpolation and flag outputs. */
typedef struct PointListScratch {
    /* 0x000 */ s32 screen_xy[64]; /* packed sxy words RotTransPersN writes; read as words */
    /* 0x100 */ u16 depths[64];
    /* 0x180 */ u16 gte_discard[64]; /* RotTransPersN p and flag arrays, both aimed here and never read */
} PointListScratch;
#define POINT_LIST_SCRATCH ((PointListScratch *)0x1F800000)

#endif
