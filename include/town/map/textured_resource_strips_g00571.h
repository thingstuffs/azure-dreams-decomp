#ifndef TOWN_MAP_TEXTURED_RESOURCE_STRIPS_G00571_H
#define TOWN_MAP_TEXTURED_RESOURCE_STRIPS_G00571_H
/* Textured resource strips shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A6420, CL:town/func_800A6A78, PD:town/engine:80100D88, PD:town/engine:80100D8A. */

#include "common.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_effect_views.h"
#include "engine/node.h"
#include "shared/gpu_packets.h"

#ifndef NULL
#define NULL 0
#endif


/* town in emit_bidirectional_angular_segments */
typedef struct S_800A3B80_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
} S_800A3B80_1;

/* arg2_temp in emit_bidirectional_angular_segments */
typedef struct S_800A3B80_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A3B80_2;

/* arg2_data in emit_bidirectional_angular_segments */
typedef struct S_800A3B80_3 {
    s16 unk_00;
    u8 pad_02[0x4];
    u8 unk_06;
    u8 pad_07[0x5];
    s16 unk_0C;
} S_800A3B80_3;

/* arg0 in emit_bidirectional_angular_segments */
typedef struct S_800A3B80_4 {
    void * unk_00;
} S_800A3B80_4;

/* global_base in emit_bidirectional_angular_segments */

/* end_town in emit_bidirectional_angular_segments */
typedef struct TownGlobals {
    void *root;
    u8 pad04[0xC4];
    u16 angle;
} TownGlobals;


typedef struct S_800A41D8_0 {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A[0xC];
    u16 unk_16;
} S_800A41D8_0;

/* Scratchpad shared by the angular-segment emitter and strip projector.
 * The emitter supplies four 8-byte vertices at +70..+8F and the texture
 * table at +118. The projector reuses +08..+14 for UV work and +F0..+FF
 * for packed screen coordinates. Keep the existing volatile UV read. */
typedef struct TownStripScratch {
    u8 pad_00[0x8];
    union { s32 n; s32 v; } unk_08;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_0C;   /* accessed as both */
    s32 unk_10;
    union { s32 n; s32 v; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    union { s32 n; void *p; } unk_20;
    u8 pad_24[0x4C];
    s16 data70;
    s16 data72;
    u16 unk_74;
    u8 pad_76[0x2];
    s16 data78;
    s16 data7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s16 data80;
    s16 data82;
    u16 unk_84;
    u8 pad_86[0x2];
    s16 data88;
    s16 data8A;
    u16 unk_8C;
    u8 pad_8E[0x2];
    s32 unk_90;
    u8 pad_94[0x5C];
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_F0;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_F4;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_F8;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    union { s32 n; void *p; } unk_118;
} TownStripScratch;

/* state in project_visible_textured_strips */
typedef struct S_800A41D8_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s32 unk_08;
    s32 uv_0;
    s16 unk_10;
    s16 unk_12;
    s32 uv_1;
    s32 unk_18;
    s16 uv_2;
    u8 pad_1E[2];
    s16 unk_20;
    s16 unk_22;
    s16 uv_3;
    u8 pad_26[6];
    s8 unk_2C;
    u8 pad_2D[0xB];
    s32 unk_38;
    u8 pad_3C[0xC];
    s32 unk_48;
} S_800A41D8_2;

typedef struct S_800A41D8_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0xC];
    s16 unk_18;
    s16 unk_1A;
} S_800A41D8_3;

typedef struct S_800A41D8_4 {
    u8 pad_00[0x5];
    s8 unk_05;
    s8 unk_06;
} S_800A41D8_4;

typedef struct S_800A41D8_5 {
    u8 pad_00[0x7];
    u8 unk_07;
    u8 pad_08[0xC];
    u8 unk_14;
    u8 pad_15[0x8];
    u8 unk_1D;
    u8 pad_1E[0x6];
    u8 unk_24;
    u8 unk_25;
} S_800A41D8_5;

/* prim_buffer bytes in project_visible_textured_strips */
typedef struct S_800A41D8_6 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_800A41D8_6;

/* arg1 in project_visible_textured_strips */
typedef struct S_800A41D8_7 {
    u8 pad_00[0x4];
    s16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800A41D8_7;

typedef struct {
    s16 value;
    u8 pad[10];
} LargeS16;

typedef struct S_800A47A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A47A8_1;

typedef struct S_800A47A8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x8];
    s16 unk_0C;
    u8 pad_0E[0x4];
    s16 unk_12;
    s16 unk_14;
} S_800A47A8_3;

extern s32 rsin(s32);
extern s32 rcos(s32);
/* texture_entry in project_visible_textured_strips */
extern s32 func_80065610();
extern s32 GetTPage();
extern void AddPrim();
extern void SetPolyFT4();
extern void SetDrawMode();

extern s32 D_800A3918[];
extern s32 D_800A3B1C[];
extern s32 D_800D0C40[];

extern u16 D_80100D88;
extern u16 town_display_offset;

/* Functions defined in this translation unit. */
s32 process_linked_state_chain(void *initial_state, s32 carrier1, u8 *carrier2);
s32 emit_bidirectional_angular_segments(S_800A3B80_3 *object, s32 unused, void *context);
void *project_visible_textured_strips(void *origin, void *render_flags, TownStripScratch *draw_state, void *prim_buffer, u16 texture_index);
void create_resource_display_object(s16 resource_index);

#endif
