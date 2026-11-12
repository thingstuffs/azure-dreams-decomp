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
 * for scale. The matrix translation is also the temporary sprite offset. */
typedef struct SpriteQuadScratch {
    SVECTOR position; /* RotTransPers input: the sprite's world position */
    u32 uv_u_start;
    u32 uv_v_start;
    u32 uv_u_extent;
    u32 uv_v_extent;
    u8 pad_18[8];
    u32 *ordering_table; /* ordering-table slot the sprite packets are linked into */
    u16 sprite_flags;
    u16 pad_26;
    SVECTOR rotation;
    VECTOR input; /* camera angles, then the ScaleMatrix scale */
    VECTOR translation;
    MATRIX matrix;
    SVECTOR vertices[4]; /* RotTransPers4/RotAverage4 inputs */
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
    SVECTOR angles; /* RotMatrix input */
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
    VECTOR input; /* object scale (ScaleMatrix) */
    VECTOR translation; /* TransMatrix translation */
    SpriteLinkedMatrix matrix;
    SVECTOR vertices[4]; /* RotTransPers4 inputs */
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
    VECTOR input; /* camera angles, then the ScaleMatrix scale (sprite scale) */
    u8 pad_40[0x30];
    SVECTOR point; /* RotTransSV input: the flipped attachment X in vx, 0 in vy, the flipped Y in vz */
    u8 pad_78[0x1C];
    s32 transform_flag;
    u8 pad_98[0x38];
    MATRIX local_matrix;
    u8 pad_F0[0x10];
    SVECTOR angles; /* RotMatrix input */
    u16 extent_x;
    u16 extent_y;
} SpriteAttachmentScratch;

#endif
