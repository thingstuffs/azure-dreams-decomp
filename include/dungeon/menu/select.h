#ifndef DUNGEON_OVL_1829800_H
#define DUNGEON_OVL_1829800_H
#include "common.h"
#include "dungeon/menu.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"
#include "shared/tile_object.h"
#include "dungeon/system.h"

typedef struct S_81809800_0 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_81809800_0;   /* temp_v1 in func_80025014 */

typedef struct S_81809800_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81809800_1;   /* ((index * 4) + temp_v1) in func_80025014 */

typedef struct S_81809800_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_81809800_2;   /* arg1 in func_80025014 */

typedef struct S_81809800_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81809800_3;   /* temp_a2_base in func_80025014 */

typedef struct S_81809800_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_81809800_4;   /* temp_a2 in func_80025014 */

typedef struct S_81809800_6 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81809800_6;   /* arg2 in func_80025014 */

/* cfail-repair: tf7-phase1-cache-v3 */

/* Move the position toward the selected target and update the blink flag. */

typedef struct S_80025170_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void (*unk_10)(void *, ObjectPosition *, SpriteFrameState *);
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025170_0;   /* temp_v0 in func_80025170 */

/* Allocates an object and initializes its sprite and user data. */

/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct S_8002520C_22 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_22;   /* ((side_index * 4) + arg0) in func_8002520C */

typedef struct S_8002520C_23 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_8002520C_23;   /* ((temp_a0_8 * 2) + counter_page) in func_8002520C */

typedef struct S_8002520C_24 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_24;   /* ((((S_8002520C_0 *)arg0)->unk_26 * 4) + arg0) in func_8002520C */

typedef struct S_8002520C_25 {
    u8 pad_00[0xB6];
    s16 unk_B6;
} S_8002520C_25;   /* ((S_8002520C_24 *)(((((S_8002520C_0 *)arg0)->unk_26 * 4) + arg0)))->unk_0C in func_8002520C */

typedef struct S_8002520C_0_pre {
    u16 unk_00;
} S_8002520C_0_pre;   /* the 0x2 bytes before arg0 in func_8002520C, addressed as arg0[-1] */

typedef struct S_8002520C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    void * unk_14;
    u8 pad_18[0x4];
    s16 unk_1C;
    s16 unk_1E;
    u16 unk_20;
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
} S_8002520C_0;   /* arg0 in func_8002520C */

typedef struct S_8002520C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    u16 unk_16;
} S_8002520C_1;   /* temp_s1 in func_8002520C */

typedef struct S_8002520C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x7];
    u16 unk_16;
    u8 pad_18[0x2];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_8002520C_2;   /* arg2_local in func_8002520C */

typedef struct S_8002520C_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8002520C_4;   /* state_base in func_8002520C */

typedef struct S_8002520C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8002520C_5_pre;   /* the 0x14 bytes before dest in func_8002520C, addressed as dest[-1] */

typedef struct S_8002520C_5 {
    u8 pad_00[0x96];
    s16 unk_96;
} S_8002520C_5;   /* dest in func_8002520C */

typedef struct S_8002520C_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8002520C_6;   /* cell in func_8002520C */

typedef struct S_8002520C_7 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_7;   /* *var_v0_4 in func_8002520C */

typedef struct S_8002520C_8 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_8002520C_8;   /* (void *) slot_a0 in func_8002520C */

typedef struct S_8002520C_9 {
    u8 pad_00[0x3D7C];
    s32 unk_3D7C;
} S_8002520C_9;   /* world_page in func_8002520C */

typedef struct S_8002520C_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_10;   /* world_node in func_8002520C */

typedef struct S_8002520C_11 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8002520C_11;   /* (void *) world_off in func_8002520C */

typedef struct S_8002520C_12 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8002520C_12;   /* world_cell in func_8002520C */

typedef struct S_8002520C_13 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_8002520C_13;   /* counter_ptr in func_8002520C */

typedef struct S_8002520C_14 {
    u8 pad_00[0x45];
    s8 unk_45;
} S_8002520C_14;   /* temp_s1_2 in func_8002520C */

typedef struct S_8002520C_15 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_15;   /* var_v1_4 in func_8002520C */

typedef struct S_8002520C_16 {
    u8 pad_00[0xB6];
    s16 unk_B6;
} S_8002520C_16;   /* temp_v0_4 in func_8002520C */

typedef struct S_8002520C_17 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x1490];
    s32 unk_14A0;
} S_8002520C_17;   /* slot_a2 in func_8002520C */

typedef struct S_8002520C_18 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002520C_18;   /* (void *) slot_v1 in func_8002520C */

typedef struct S_8002520C_19 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8002520C_19;   /* slot_a3 in func_8002520C */

typedef struct S_8002520C_20 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002520C_20;   /* (void *) slot_a1 in func_8002520C */

typedef struct S_8002520C_21 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8002520C_21;   /* (s32 *) slot_v0 in func_8002520C */

/* Update the selection menu animation, side positions, and facing directions. */

typedef struct S_80025A14_0 {
    u8 pad_00[0x46];
    s16 unk_46;
    u8 pad_48[0x10];
    void * unk_58;
    u8 pad_5C[0x16];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
} S_80025A14_0;   /* state in func_80025A14 */

typedef struct S_80025A14_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80025A14_1;   /* buffer in func_80025A14 */

typedef struct S_80025A14_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    void * unk_2C;
} S_80025A14_2;   /* obj in func_80025A14 */

typedef struct S_80025A14_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
} S_80025A14_3;   /* template in func_80025A14 */

typedef struct S_80025A14_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80025A14_4_pre;   /* the 0x14 bytes before p in func_80025A14, addressed as p[-1] */

typedef struct S_80025A14_4 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80025A14_4;   /* p in func_80025A14 */

/* Updates the object fade and selects its animation and render flags by direction. */

typedef struct S_80025C94_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x2C];
    void * unk_58;
    M2C_UNK (*unk_5C)(void *, void *, void *, void *);
    u8 pad_60[0xA];
    s16 unk_6A;
    u8 pad_6C[0x6];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
    u8 pad_74[0x14];
    s16 unk_88;
} S_80025C94_0;   /* temp_s0 in func_80025C94 */

typedef struct S_80025C94_1 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x5];
    s8 unk_9D;
} S_80025C94_1;   /* temp_a3 in func_80025C94 */

typedef struct S_80025C94_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80025C94_2;   /* temp_s1 in func_80025C94 */

typedef struct S_80025C94_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80025C94_3;   /* temp_s2 in func_80025C94 */

typedef struct S_80025C94_4 {
    u8 pad_00[0xC8];
    u16 unk_C8;
} S_80025C94_4;   /* temp_s5 in func_80025C94 */

typedef struct S_80025C94_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80025C94_5;   /* temp_s3 in func_80025C94 */

typedef struct S_80025C94_6 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_80025C94_6;   /* (s8 *)temp_table + (((S_80025C94_0 *)temp_s0)->unk_6A * 2) in func_80025C94 */

typedef struct S_80025C94_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80025C94_7_pre;   /* the 0x14 bytes before ((S_80025C94_0 *)temp_s0)->unk_58 in func_80025C94, addressed as ((S_80025C94_0 *)temp_s0)->unk_58[-1] */

typedef struct S_80025C94_7 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_80025C94_7;   /* ((S_80025C94_0 *)temp_s0)->unk_58 in func_80025C94 */

/* Updates an object's fade and position, draws it, and restores its color. */

typedef struct S_800260C8_4 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800260C8_4;   /* ((temp_a0 * 4) + temp_v1) in func_800260C8 */

typedef struct S_800260C8_5 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800260C8_5;   /* ((temp_v0 * 4) + ((S_800260C8_1 *)arg0)->unk_20) in func_800260C8 */

typedef struct S_800260C8_6 {
    u8 pad_00[0xB6];
    s16 unk_B6;
} S_800260C8_6;   /* ((S_800260C8_4 *)(((temp_a0 * 4) + temp_v1)))->unk_0C in func_800260C8 */

typedef struct S_800260C8_7 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800260C8_7;   /* ((S_800260C8_5 *)(((temp_v0 * 4) + ((S_800260C8_1 *)arg0)->unk_20)))->unk_0C in func_800260C8 */

typedef struct ResidentPage {
    u8 pad0[0x2094];
    u16 table[1];
} ResidentPage;

typedef struct S_800260C8_0 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_800260C8_0;   /* temp_a2 in func_800260C8 */

typedef struct S_800260C8_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800260C8_1;   /* arg0 in func_800260C8 */

typedef struct S_800260C8_2 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
} S_800260C8_2;   /* temp_a0_2 in func_800260C8 */

typedef struct S_800260C8_3 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_800260C8_3;   /* temp_a0_3 in func_800260C8 */

/* Update the active index and reset the previous entry's state and offsets. */

typedef void *(*SpawnFunc)(s32, s32, s32, s16);

typedef struct S_80026190_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x14];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x8];
    u16 unk_26;
} S_80026190_0;   /* owner in func_80026190 */

typedef struct S_80026190_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80026190_1;   /* status in func_80026190 */

typedef struct S_80026190_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
} S_80026190_2;   /* early0 in func_80026190 */

typedef struct S_80026190_3 {
    u8 pad_00[0xE];
    s16 unk_0E;
} S_80026190_3;   /* early1 in func_80026190 */

typedef struct S_80026190_4 {
    u8 pad_00[0x10];
    union { void * s; s32 u; } unk_10;   /* accessed as both */
    u8 pad_14[0x64];
    void * unk_78;
} S_80026190_4;   /* (void *)role_s1 in func_80026190 */

typedef struct S_80026190_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
    u8 pad_18[0xE];
    u16 unk_26;
} S_80026190_5;   /* container in func_80026190 */

typedef struct S_80026190_8 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80026190_8;   /* cleanup_page in func_80026190 */

typedef struct S_80026190_9 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_9;   /* child_fail in func_80026190 */

typedef struct S_80026190_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80026190_10_pre;   /* the 0x14 bytes before source in func_80026190, addressed as source[-1] */

typedef struct S_80026190_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x70];
    s16 unk_88;
    u8 pad_8A[0x1E];
    u16 unk_A8;
} S_80026190_10;   /* source in func_80026190 */

typedef struct S_80026190_11 {
    u8 pad_00[0x2090];
    s32 unk_2090;
} S_80026190_11;   /* mode_page in func_80026190 */

typedef struct S_80026190_13 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_13;   /* spawn_fail1 in func_80026190 */

typedef struct S_80026190_15 {
    u8 pad_00[0x14A0];
    union { volatile s32 s; s32 u; } unk_14A0;   /* accessed as both */
} S_80026190_15;   /* flag_page in func_80026190 */

typedef struct S_80026190_16 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_16;   /* spawn_fail3 in func_80026190 */

typedef struct S_80026190_17 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x5];
    s8 unk_25;
    u8 pad_26[0x32];
    void * unk_58;
    s32 unk_5C;
    u8 pad_60[0xA];
    s16 unk_6A;
    u8 pad_6C[0x1B];
    u8 unk_87;
    s16 unk_88;
} S_80026190_17;   /* work in func_80026190 */

typedef struct S_80026190_19 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80026190_19;   /* ((S_80026190_10_pre *)source)[-1].unk_00 in func_80026190 */

/* Initializes child objects and copies source entities, or requests their shutdown. */

/* Initializes an effect, fades its color in and out, and flags completion. */

typedef struct S_800267F0_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void *);
    u8 pad_14[0x32];
    s16 unk_46;
} S_800267F0_0;   /* temp_v0 in func_800267F0 */

/* Initializes an available object with the supplied value and sets up shared state. */

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad1;
    s16 y;
    s16 pad2;
    s16 z;
} ViewPosition;

typedef struct {
    u8 pad0[0xC];
    u8 color[3];
    u8 pad1[7];
    u16 rotation[3];
    u16 width;
    u16 height;
} RenderParams;

typedef struct {
    u8 pad0[3];
    u8 code;
    u8 rgb[3];
    u8 pad1;
    s32 xy0;
    s32 a;
    s32 xy1;
    s32 b;
    s32 xy2;
    u16 u2;
    u16 pad2;
    s32 xy3;
    u16 u3;
    u16 pad3;
} Prim;

typedef struct {
    u8 pad0[0xB0];
    u8 ot[0x820];
    Prim *prim;
} DrawBuffer;

typedef struct {
    DrawBuffer *draw_buffer;
    u8 pad0[0xA4];
    u8 blend[0xC];
    u16 position[3];
    u8 pad1[0xA];
    u16 rotation[3];
} RenderState;

typedef struct {
    u16 i0;
    u16 i1;
    u16 i2;
    u16 i3;
    s32 a;
    s32 b;
    u16 tex;
    u16 u2;
    u16 u3;
    u16 flags;
} Face;

typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 pad;
} Vert;

typedef struct {
    u16 idx;
    u16 bias;
    u16 pad;
} Cell;

typedef struct {
    u8 pad0[4];
    Face **faces;
    Vert *vertices;
    u8 *materials;
} Geometry;

typedef struct {
    u8 pad0[8];
    s32 lo;
    s32 hi;
    u8 pad1[0x10];
    u8 transform[1];
} Object;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
} SpriteData;

typedef struct {
    u8 pad0[8];
    s32 lo;
    SpriteData *data;
    u8 pad1[0x10];
    u8 transform[1];
} Sprite;

typedef struct {
    u8 pad0[8];
    Object *main;
    Object *extra[2];
    Sprite *sprite;
} Objects;

typedef struct {
    u8 pad0[0x20];
    s32 ot;
    u8 pad1[0xC];
    s32 view_w;
    s32 view_h;
    s32 view_mid;
    u8 pad2[4];
    s32 eye[3];
    u8 pad3[4];
    u8 matrix[0x20];
    s32 xy0;
    s16 h0;
    s16 pad4;
    s32 xy1;
    s16 h1;
    s16 pad5;
    s32 xy2;
    s16 h2;
    s16 pad6;
    s32 xy3;
    s16 h3;
    s16 pad7;
    s32 out0;
    s32 out1;
    u8 pad8[0x28];
    s32 depth;
    s32 depth_base;
    u8 pad9[0x28];
    u8 buf[0x24];
    s32 facing;
    u8 pad10[0x24];
    s32 clear;
} Scratch;

/* Render a 3x3 grid of terrain faces and its associated objects. */

/* Sets the scratchpad offset to the negated global coordinates before forwarding the call. */

/* Queues four shaded quadrants and a draw-mode packet for each linked rectangle. */


void *allocate_sprite_data_object(s32 user_data);
void update_selection_menu_animation(void *menu_in, void *motion_in, void *appearance_in);
void update_directional_object_fade(void *state_arg, void *buffer_arg, void *obj_arg);
void draw_and_restore_fading_object(void *object_arg, void *position_arg, void *sprite_arg);
void switch_active_object_index(void *object, s16 new_index);
void initialize_children_or_shutdown(void *owner);
/* Work shared by the fade controller and its four-quadrant draw callback. */
typedef struct MenuFadeRect {
    union { s16 s; u16 u; } x;
    union { s16 s; u16 u; } y;
    union { s16 s; u16 u; } extent_x;
    union { s16 s; u16 u; } extent_y;
    SpriteColor color;
    union { s16 s; u16 u; } frames_left;
    union { s16 s; u16 u; } state;
} MenuFadeRect;

void initialize_fading_effect(MenuFadeRect *effect, ObjectPosition *control);
void *initialize_available_object(s16 initialValue);
s32 render_three_by_three_terrain_grid(Objects *objects, ViewPosition *view_position, RenderParams *render_params);
void set_negated_coordinate_scratch(s32 call_value, s32 call_option, s16 call_mode, s32 call_extra);
s32 queue_four_shaded_quadrants(MenuFadeRect *rect_arg, ObjectPosition *owner_arg);

extern void advance_sprite_animation_and_textures(void *, s16, void *, void *);
void select_record_entry_and_value(void *state, void *entries, short index);  /* extern */
#include "shared/sprite_source.h"
extern SpriteSourceEntry menu_effect_sprite_entries[];
s32 rsin(s32);                        /* extern */
s32 resolve_player_input_facing();               /* extern */
void append_packed_action_record();      /* extern */
u32 get_rounded_facing_and_rounding_flag(); /* extern */
extern u8 last_frame_ticks[16];
#include "engine/texture.h"
struct Entry;
struct ObjectNodeHeader;
extern void step_actor_animation(void *,s32);
extern void func_80048AC8(void *, s32);
extern s16 selection_menu_closing;
extern u8 player_camera_reset_frames[];
extern u16 direction_x_offsets[];
extern u16 direction_y_offsets[];
extern void drain_cd_command_queue(void);
extern void func_80042640(void *, s16);
extern void copy_entity_record(void *, void *);
extern void func_80042710(void *, void *);
extern s32 get_entity_class(void *);
extern s32 func_800429E4(void *);
extern void set_code_for_entity_mode(void *);
extern void func_8004397C(void *);
extern void unlink_node(void *);
extern void func_80044A50(void *);
extern void enqueue_script_message_command(void);
extern void *load_monster_resource_data(s32 resource_id, u8 *resource_entry, s32 wait_for_read);
extern u8 *find_or_retain_sprite_resource_slot(s32, s32);
struct EntityLinkNode;
extern void unlink_entity_node(struct EntityLinkNode *node);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void retire_tracked_effect_by_id(void *);
void set_message_mode(int value);                     /* extern */
void runtime_call_selected_mode_handler(void);                            /* extern */
void submit_script_with_registered_context(void *context);                   /* extern */
extern M2C_UNK D_80027160;
extern Cell menu_mesh_cells[];
extern s16 D_8002713A[];
extern s8 scene_geometry[];
void PushMatrix(void);
void * TransMatrix(void *, void *);
void * RotMatrix(void *, void *);
void * ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
extern s32 RotTransPers();
extern s32 func_800656C0();
extern void func_80065034();
extern void project_sprite_commands();
extern void func_800453E0(void *context, void *position, struct Entry *entry, s16 depth_bias);
extern void draw_sprite_clipped();
extern void func_80045CC4();
void PopMatrix(void);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetPolyG4(void *);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s16 selection_blink_timer[5];
extern u16 selection_blink_target[5];
extern s16 selection_animation_counters[5];
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
void AddPrim(void *, void *);
#endif
