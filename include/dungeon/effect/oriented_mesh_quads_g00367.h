#ifndef DUNGEON_EFFECT_ORIENTED_MESH_QUADS_G00367_H
#define DUNGEON_EFFECT_ORIENTED_MESH_QUADS_G00367_H
/* Oriented mesh quads shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800C9858. */

#include "common.h"
#include "slus/data.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "shared/sprite_frame_state.h"

typedef struct Node {
    s32 pad[2];
    s32 value1;
    SpriteFrameState *value2;
} Node;

typedef struct S_800CEFB8_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CEFB8_0;

/* arg2_hold in draw_mesh_quads_with_orientation_mode */
typedef struct S_800CEFB8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800CEFB8_2;

/* arg1 in draw_mesh_quads_with_orientation_mode */
typedef struct S_800CEFB8_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800CEFB8_3;

/* (s32 *)end_depth in draw_mesh_quads_with_orientation_mode */
typedef struct S_SCRATCH {
    u16 endpoint_x;
    u16 endpoint_y;
    u16 endpoint_z;
    u8 pad_006[0x2];
    union {
        s32 s32;
        u16 u16;
    } texture_u;
    s32 texture_v;
    union {
        s32 s32;
        u16 u16;
    } texture_width;
    union {
        s32 s32;
        u16 u16;
    } texture_height;
    u8 pad_018[0x8];
    s32 ordering_table;
    u16 sprite_flags;
    u8 pad_026[0xA];
    s32 scale_x;
    s32 scale_y;
    s32 scale_z;
    u8 pad_03C[0x34];
    u16 unk_070;
    u16 unk_072;
    u16 unk_074;
    u8 pad_076[0x2];
    u16 unk_078;
    u16 unk_07A;
    u16 unk_07C;
    u8 pad_07E[0x2];
    u16 unk_080;
    u16 unk_082;
    u16 unk_084;
    u8 pad_086[0x2];
    u16 unk_088;
    u16 unk_08A;
    u16 unk_08C;
    u8 pad_08E[0x2A];
    u16 start_screen_x;
    u16 start_screen_y;
    u8 pad_0BC[0x4];
    s32 sort_depth;
    u8 pad_0C4[0x20];
    s32 translate_x;
    s32 translate_y;
    s32 translate_z;
    u16 end_screen_x;
    u16 end_screen_y;
    u8 pad_0F4[0xC];
    u16 rotation_x;
    u16 rotation_y;
    u16 rotation_z;
    u8 pad_106[0x2];
    u16 sprite_offset_x;
    u16 sprite_offset_y;
    u8 pad_10C[0x2];
    u16 segment_angle;
} S_SCRATCH;

typedef struct S_800CEFB8_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800CEFB8_6;

/* part in draw_mesh_quads_with_orientation_mode */
typedef struct S_800CEFB8_8 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    u16 unk_0A;
    s16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union { s16 s16; u8 u8; } unk_14;   /* accessed as both */
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_1C;   /* overlapping accesses */
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    u16 unk_22;
    union {
        struct { s16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_800CEFB8_8;

s32 CompMatrix(void *, void *, void *);
s32 PushMatrix(void);
s32 PopMatrix(void);
s32 ScaleMatrix(void *, void *);
s32 SetRotMatrix(void *);
s32 SetTransMatrix(void *);
s32 RotTransPers(void *, s32 *, s32 *, s32 *);
s32 RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s32 RotMatrix(void *, void *);
u16 ratan2();

/* Functions defined in this translation unit. */
s32 draw_linked_oriented_mesh_quads(void *initial_state, s32 value, SpriteFrameState *data);
void draw_mesh_quads_with_orientation_mode(void *unused, void *endpoints, SpriteFrameState *sprite, s16 depth_bias, s16 orient_mode);

#endif
