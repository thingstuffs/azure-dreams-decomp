#ifndef ENGINE_GRAPHICS_SPRITE_SCRATCH_H
#define ENGINE_GRAPHICS_SPRITE_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"

typedef struct SpriteScratchVertex {
    u16 x;
    u16 y;
    u16 z;
    u16 flag;
} SpriteScratchVertex;

typedef struct SpriteScratchScreenPoint {
    u16 x;
    u16 y;
} SpriteScratchScreenPoint;

/* Quad renderers share these UV, matrix, vertex, depth and GTE output slots.
 * The three input words at +0x30 hold camera angles before they are reused
 * for scale. The matrix translation is also the temporary sprite offset. */
typedef struct SpriteQuadScratch {
    u16 position_x;
    u16 position_y;
    u16 position_z;
    u16 pad_06;
    u32 uv_u_start;
    u32 uv_v_start;
    u32 uv_u_extent;
    u32 uv_v_extent;
    u8 pad_18[8];
    u32 *ordering_table; /* ordering-table slot the sprite packets are linked into */
    u16 sprite_flags;
    u16 pad_26;
    s16 rotation_x;
    s16 rotation_y;
    s16 rotation_z;
    s16 pad_2E;
    s32 input_x;
    s32 input_y;
    s32 input_z;
    u8 pad_3C[4];
    s32 translation_x;
    s32 translation_y;
    s32 translation_z;
    u8 pad_4C[4];
    MATRIX matrix;
    SpriteScratchVertex vertices[4];
    s32 depth_cue;
    s32 gte_flag;
    u8 pad_98[0x20];
    SpriteScratchScreenPoint screen_origin;
    u8 pad_BC[4];
    u32 sort_depth;
    u8 pad_C4[8];
    s32 depth_offset;
    MATRIX local_matrix;
    SpriteScratchScreenPoint projected_vertices[4];
    u16 angle_x;
    u16 angle_y;
    u16 angle_z;
    u16 pad_106;
    u16 extent_x;
    u16 extent_y;
    u8 pad_10C[0x30];
    u32 vertex_y_offset;
} SpriteQuadScratch;

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
 * other quad renderers: vertices begin at +0x74 and projected XY at +0x9C. */
typedef struct SpriteLinkedScratch {
    u8 pad_00[0xC];
    s32 uv_u_start;
    s32 uv_v_start;
    s32 uv_u_extent;
    s32 uv_v_extent;
    s32 primitive_cursor;
    u8 pad_20[4];
    s32 ordering_table;
    u16 context_flags;
    u8 pad_2A[0xA];
    s32 input_x;
    s32 input_y;
    s32 input_z;
    u8 pad_40[4];
    s32 translation_x;
    s32 translation_y;
    s32 translation_z;
    u8 pad_50[4];
    SpriteLinkedMatrix matrix;
    SpriteScratchVertex vertices[4];
    s32 depth_cue;
    s32 gte_flag;
    SpriteLinkedScreenPoint projected_vertices[4];
    u8 pad_BC[8];
    s32 ordering_depth;
    MATRIX work_matrix;
} SpriteLinkedScratch;

/* Attachment transform scratchpad slots, based on the calls to RotMatrix,
 * ScaleMatrix and RotTransSV in runtime_transform_sprite_attachment_point. */
typedef struct SpriteAttachmentScratch {
    u16 transformed_x;
    u16 transformed_y;
    u8 pad_04[0x20];
    u16 sprite_flags;
    u8 pad_26[0xA];
    s32 input_x; /* camera angles, then sprite scale; low halves feed ScaleMatrix */
    s32 input_y;
    s32 input_z;
    u8 pad_3C[0x34];
    s16 point_x;
    s16 point_z;
    s16 point_y;
    u8 pad_76[0x1E];
    s32 transform_flag;
    u8 pad_98[0x38];
    MATRIX local_matrix;
    u8 pad_F0[0x10];
    u16 angle_x;
    u16 angle_y;
    u16 angle_z;
    u16 pad_106;
    u16 extent_x;
    u16 extent_y;
} SpriteAttachmentScratch;

#endif
