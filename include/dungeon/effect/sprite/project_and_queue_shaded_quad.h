#ifndef DUNGEON_OVL_7E6E1800_H
#define DUNGEON_OVL_7E6E1800_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_sprite_data.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "records/Rec_func_800247B8_arg0.h"
#include "records/Rec_func_800247B8_arg1.h"
#include "shared/slus_callbacks.h"
#include "shared/entity_height_offsets.h"
typedef struct Row_81922998_S_80024198_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} Row_81922998_S_80024198_0;   /* scratch in func_80024198 */

typedef struct Row_81922998_S_80024198_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Row_81922998_S_80024198_1;   /* arg1 in func_80024198 */

typedef struct Row_81922998_S_80024198_2 {
    u8 pad_00[0xF];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} Row_81922998_S_80024198_2;   /* arg2 in func_80024198 */

typedef struct Row_81922998_S_80024198_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
    u8 pad_B4[0x81C];
    u8 * unk_8D0;
} Row_81922998_S_80024198_3;   /* *(u8 **)D_80083160 in func_80024198 */

typedef struct Row_81922998_S_80024198_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} Row_81922998_S_80024198_4;   /* packet in func_80024198 */

typedef struct Row_81922998_S_80024198_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} Row_81922998_S_80024198_5;   /* context in func_80024198 */

typedef struct Row_81922998_S_80024198_6 {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x10];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u16 unk_32;
    u16 unk_34;
    u16 unk_36;
} Row_81922998_S_80024198_6;   /* arg0 in func_80024198 */

typedef struct Row_81922998_S_80024198_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} Row_81922998_S_80024198_7;   /* *global in func_80024198 */

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} Row_81922998_MATRIX;

/* Projects a shaded quad and adds it to the ordering table when visible. */
typedef struct Row_81922E70_GapNode { u8 pad[8]; void *position; void *appearance; } Row_81922E70_GapNode;

/* Apply the renderer to each node in the linked object chain. */
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 pad;
} Row_81922EC4_DungeonColor;

typedef struct {
    Row_81922EC4_DungeonColor color[8];
    u8 pad_20[0x3A];
    s16 remaining;
    s16 duration;
} Row_81922EC4_DungeonColorWork;

/* Fades four dungeon colors toward black and flags completion when time runs out. */
#ifndef NULL
#define NULL 0
#endif

typedef struct Row_81922FB8_S_800247B8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    union { s16 s; u16 u; } unk_22;   /* accessed as both */
    union { s16 s; u16 u; } unk_24;   /* accessed as both */
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x22];
    s16 unk_5A;
    s16 unk_5C;
} Row_81922FB8_S_800247B8_0;   /* work in func_800247B8 */

typedef struct Row_81922FB8_S_800247B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_81922FB8_S_800247B8_1;   /* obj in func_800247B8 */

/* Creates an effect at the supplied position with randomized color and radial offsets. */
typedef struct Row_819231FC_S_800249FC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} Row_819231FC_S_800249FC_0;   /* arg2 in func_800249FC */

typedef struct Row_819231FC_S_800249FC_1_pre {
    u16 unk_00;
} Row_819231FC_S_800249FC_1_pre;   /* the 0x2 bytes before arg0 in func_800249FC, addressed as arg0[-1] */

typedef struct Row_819231FC_S_800249FC_1 {
    u8 pad_00[0x5A];
    union { s16 s; u16 u; } unk_5A;   /* accessed as both */
} Row_819231FC_S_800249FC_1;   /* arg0 in func_800249FC */

/* Update effect values and flags, then mark the object when its countdown expires. */
typedef struct {
    u8 bytes[12];
} Row_819232EC_U12;

/* cfail-repair: tf7-phase1-cache-v3 */
                /* extern */

typedef struct Row_819232EC_S_80024AEC_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
    u8 pad_5E[0x2A];
    s32 unk_88;
} Row_819232EC_S_80024AEC_0;   /* temp_v1 in func_80024AEC */

typedef struct Row_819232EC_S_80024AEC_1 {
    u8 pad_00[0x88];
    s32 unk_88;
} Row_819232EC_S_80024AEC_1;   /* arg0 in func_80024AEC */

typedef struct Row_819232EC_S_80024AEC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} Row_819232EC_S_80024AEC_3;   /* temp_a3 in func_80024AEC */

/* Create an effect at the supplied position and initialize its rendering state. */
typedef struct {
    s16 value;
    s16 pad_02[4];
} Row_8192340C_DungeonActive;

typedef struct {
    u8 pad_00[0xC];
    s8 unk_C;
    s8 unk_D;
    s8 unk_E;
    u8 pad_0F[5];
    u16 flags_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} Row_8192340C_DungeonEffect;

/* Advance the effect, fade it as its timer runs down, and flag it for removal when finished. */
typedef struct Row_81923534_S_80024D34_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
} Row_81923534_S_80024D34_0;   /* sub in func_80024D34 */

/* Creates and initializes an effect at a random offset from the given position. */
/* extern */
      /* extern */
      /* extern */
         /* extern */
                      /* extern */
           /* extern */
                     /* extern */
      /* extern */

typedef struct Row_8192365C_S_80024E5C_0_pre {
    u16 unk_00;
} Row_8192365C_S_80024E5C_0_pre;   /* the 0x2 bytes before arg0 in func_80024E5C, addressed as arg0[-1] */

typedef struct Row_8192365C_S_80024E5C_0 {
    u8 pad_00[0x56];
    u16 unk_56;
    union { u16 u; s16 s; } unk_58;   /* accessed as both */
    union { u16 u; s16 s; } unk_5A;   /* accessed as both */
    u16 unk_5C;
    u8 pad_5E[0x2];
    s16 unk_60;
    s16 unk_62;
    u8 pad_64[0xE];
    u16 unk_72;
    u8 pad_74[0x14];
    void * unk_88;
    void * unk_8C;
    u8 pad_90[0x8];
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} Row_8192365C_S_80024E5C_0;   /* arg0 in func_80024E5C */

typedef struct Row_8192365C_S_80024E5C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    union { s8 s; u8 u; } unk_0C;   /* accessed as both */
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} Row_8192365C_S_80024E5C_1;   /* arg2 in func_80024E5C */

typedef struct Row_8192365C_S_80024E5C_2 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8192365C_S_80024E5C_2;   /* arg1 in func_80024E5C */

typedef struct Row_8192365C_S_80024E5C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} Row_8192365C_S_80024E5C_3;   /* temp_a1 in func_80024E5C */

typedef struct Row_8192365C_S_80024E5C_4_pre {
    void * unk_00;
    u8 pad_04[0x14];
} Row_8192365C_S_80024E5C_4_pre;   /* the 0x18 bytes before ((Row_8192365C_S_80024E5C_0 *)arg0)->unk_88 in func_80024E5C, addressed as ((Row_8192365C_S_80024E5C_0 *)arg0)->unk_88[-1] */

typedef struct Row_8192365C_S_80024E5C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} Row_8192365C_S_80024E5C_4;   /* ((Row_8192365C_S_80024E5C_0 *)arg0)->unk_88 in func_80024E5C */

typedef struct Row_8192365C_S_80024E5C_5 {
    u8 pad_00[0x86];
    s16 unk_86;
} Row_8192365C_S_80024E5C_5;   /* ((Row_8192365C_S_80024E5C_0 *)arg0)->unk_8C in func_80024E5C */

/* Update the effect's color cycle, movement, bursts, and destruction. */
void CompMatrix(void *, void *, void *);
void PushMatrix(void);
void PopMatrix(void);
void ReadRotMatrix(void *);
void ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
void RotMatrix(void *, void *);
u16 GetTPage(s32, s32, s32, s32);
void SetDrawMode(void *, s32, s32, u16, s32);
s32 project_and_queue_visible_shaded_quad(s32);
s32 register_node();
s32 func_8004491C();
s32 rsin(s32);
s32 rcos(s32);
s32 rand();
s32 advance_sprite_animation_and_textures(void *effect_data);
void select_record_entry_and_value();
int abs(int);
void select_sprite_entry();
void func_80047784();
s32 check_adjacent_tile_height_clearance();
s32 play_sound_if_enabled();
void create_attached_effect();

extern s32 D_80024670[];
extern s32 D_800246C4[];

extern M2C_UNK D_800249FC;
extern M2C_UNK D_80025B48;

extern u8 D_80024C0C[16];
extern u8 D_80025B38[9];
void project_and_queue_shaded_quad(void *quad, void *position, void *render_state, s16 depth_bias);
s32 draw_linked_shaded_quads(void *state, void *position, void *appearance);
void fade_four_colors_to_black(Row_81922EC4_DungeonColorWork *work);
void create_randomized_radial_effect(Rec_func_800247B8_arg0 *source, Rec_func_800247B8_arg1 *origin, void *unused_sprite);
void update_effect_values_and_expire(void *object, s32 unused, Row_819231FC_S_800249FC_0 *effect);
void create_positioned_render_effect(Row_819232EC_S_80024AEC_1 *source, Rec_func_800247B8_arg1 *position, void *unused_sprite);
void advance_radial_effect_state(void *entity_data, s32 unused, SpriteFrameState *effect_data);
void create_random_offset_effect(void *unused, Rec_func_800247B8_arg1 *origin, void *unused_sprite);
void update_effect_cycle_and_bursts(void *effect, void *motion, SpriteFrameState *sprite);
extern u8 shaded_effect_update_flag[];
#endif
