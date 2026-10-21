#ifndef DUNGEON_OVL_7E6B7800_H
#define DUNGEON_OVL_7E6B7800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
struct Row_8194C81C_Delta {
    s32 x;
    s32 y;
    s32 z;
};

/* Computes orientation angles from the displacement between two points. */
typedef struct Row_8194C8F0_S_800240F0_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    union { s16 n; u16 n2; } unk_0C;   /* accessed as both */
    u8 pad_0E[0x2];
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
    u16 unk_12;
} Row_8194C8F0_S_800240F0_0;   /* arg0 in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} Row_8194C8F0_S_800240F0_1;   /* source in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8194C8F0_S_800240F0_2;   /* arg1 in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_8194C8F0_S_800240F0_3;   /* position in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} Row_8194C8F0_S_800240F0_4;   /* arg2 in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} Row_8194C8F0_S_800240F0_6;   /* ((Row_8194C8F0_S_800240F0_0 *)arg0)->unk_00 in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_7 {
    u16 unk_00;
} Row_8194C8F0_S_800240F0_7;   /* ((Row_8194C8F0_S_800240F0_0 *)arg0)->unk_08 in func_800240F0 */

typedef struct Row_8194C8F0_S_800240F0_8 {
    u8 pad_00[0x8];
    void * unk_08;
} Row_8194C8F0_S_800240F0_8;   /* ((Row_8194C8F0_S_800240F0_0 *)arg0)->unk_04 in func_800240F0 */

/* Updates an effect that follows its source, arcs to a target, then grows and brightens. */
/* Allocate an effect and initialize its state and sprite. */
typedef struct Row_8194CD5C_S_8002455C_0_pre {
    u16 unk_00;
} Row_8194CD5C_S_8002455C_0_pre;   /* the 0x2 bytes before arg0 in func_8002455C, addressed as arg0[-1] */

typedef struct Row_8194CD5C_S_8002455C_0 {
    void * unk_00;
    u8 pad_04[0x28];
    s16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
} Row_8194CD5C_S_8002455C_0;   /* arg0 in func_8002455C */

typedef struct Row_8194CD5C_S_8002455C_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} Row_8194CD5C_S_8002455C_1;   /* temp_v1 in func_8002455C */

typedef struct Row_8194CD5C_S_8002455C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8194CD5C_S_8002455C_2;   /* arg1 in func_8002455C */

                      /* extern */
                             /* extern */
                             /* extern */
                            /* extern */
                            /* extern */
        /* extern */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Row_8194CD5C_InputVector;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Row_8194CD5C_OutputVector;

/* Updates a rotating effect, fades and shrinks its sprite, and flags completion. */
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Row_8194CF00_WordQuad;

typedef struct Row_8194CF00_S_80024700_0 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x4];
    union { u16 u; s16 s; } unk_2C;   /* accessed as both */
    union { u16 u; s16 s; } unk_2E;   /* accessed as both */
    u8 unk_30;
} Row_8194CF00_S_80024700_0;   /* data in func_80024700 */

typedef struct Row_8194CF00_S_80024700_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    union { u16 u16; s32 s32; } unk_10;   /* accessed as both */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_14;   /* overlapping accesses */
    s16 unk_18;
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} Row_8194CF00_S_80024700_1;   /* primitive in func_80024700 */

/* Creates a textured object from the source and applies a transformed positional offset. */
typedef struct Row_8194D118_S_80024918_0 {
    void * unk_00;
    u8 pad_04[0x30];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x28];
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
} Row_8194D118_S_80024918_0;   /* arg0 in func_80024918 */

typedef struct Row_8194D118_S_80024918_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} Row_8194D118_S_80024918_1;   /* temp_v1 in func_80024918 */

/* Advance object motion and animation, setting completion flags after nine ticks. */
typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 word;
} Row_8194D1E4_Packed4;

typedef struct {
    s32 words[4];
} Row_8194D1E4_FourWords __attribute__((aligned(4)));

typedef struct {
    Row_8194D1E4_Packed4 part[2];
} Row_8194D1E4_Packed8;

typedef struct Row_8194D1E4_S_800249E4_0 {
    u8 pad_00[0x74];
    s16 unk_74;
    s16 unk_76;
} Row_8194D1E4_S_800249E4_0;   /* temp_a0 in func_800249E4 */

/* Allocate an object and initialize its endpoints, one-eighth movement steps, and parameters. */
typedef struct Row_8194D354_S_80024B54_0_pre {
    u16 unk_00;
} Row_8194D354_S_80024B54_0_pre;   /* the 0x2 bytes before arg0 in func_80024B54, addressed as arg0[-1] */

typedef struct Row_8194D354_S_80024B54_0 {
    s32 unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    s16 unk_1A;
} Row_8194D354_S_80024B54_0;   /* arg0 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} Row_8194D354_S_80024B54_1_pre;   /* the 0x14 bytes before temp_v1_2 in func_80024B54, addressed as temp_v1_2[-1] */

typedef struct Row_8194D354_S_80024B54_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    s16 unk_88;
    u8 pad_8A[0x1C];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
    u8 pad_F8[0x13B0];
    void * unk_14A8;
} Row_8194D354_S_80024B54_1;   /* temp_v1_2 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} Row_8194D354_S_80024B54_5;   /* temp_a0 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_6_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
} Row_8194D354_S_80024B54_6_pre;   /* the 0x18 bytes before temp_v0_3 in func_80024B54, addressed as temp_v0_3[-1] */

typedef struct Row_8194D354_S_80024B54_7 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
} Row_8194D354_S_80024B54_7;   /* var_s1 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Row_8194D354_S_80024B54_8;   /* held_arg1 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_9 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} Row_8194D354_S_80024B54_9;   /* temp_a2 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_10 {
    u8 pad_00[0x2E94];
    u16 unk_2E94;
} Row_8194D354_S_80024B54_10;   /* var_v0 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} Row_8194D354_S_80024B54_11;   /* var_v1 in func_80024B54 */

typedef struct Row_8194D354_S_80024B54_13_pre {
    void * unk_00;
    u8 pad_04[0x10];
} Row_8194D354_S_80024B54_13_pre;   /* the 0x14 bytes before ((Row_8194D354_S_80024B54_0 *)arg0)->unk_14 in func_80024B54, addressed as ((Row_8194D354_S_80024B54_0 *)arg0)->unk_14[-1] */







/* Updates a three-way effect, selects its target, and animates the target color. */
s32 func_80065F90(s32, s32);
s32 func_80064710(s32);
void register_node(void *, void *);
void func_8004491C(void *, void *);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
s32 func_800644B8(s32);
void *allocate_list_node();
void *func_8003FD64();
M2C_UNK advance_sprite_animation_and_textures();
s32 func_80064584();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064B30();
M2C_UNK select_record_entry_and_value();

s32 read_sound_mode_blocking_status();
M2C_UNK func_80065820();
s32 func_80069EF8();
void apply_attack_power_and_element_effects();
void *scan_monster_along_heading();
s32 check_left_tile_and_center_height();
s32 play_sound_if_enabled();
s16 get_surface_height_at_record();

extern M2C_UNK D_800240F0;
extern M2C_UNK D_8002455C[];
extern u8 D_800DE938[];
extern M2C_UNK D_80024918;
extern M2C_UNK D_800DE5DC;

void update_directional_actor_effect(s16 start_x, s16 start_y, s16 start_z, s16 end_x, s16 end_y,
                   s16 end_z, s16 *angles);
void update_homing_arc_and_brighten_effect(void *effect, void *motion, void *sprite);
void allocate_effect_and_initialize_sprite(s32 effect_data, s32 effect_param, s32 render_param);
void update_rotating_effect_and_fade(void *effect, void *position, void *sprite);
void create_textured_offset_object(void *source_object);
void advance_object_motion_and_animation(void *object);
void allocate_effect_with_endpoints(s32 object_value, void *start_pos, void *end_pos, s16 setting, Row_8194D1E4_FourWords params_a,
    Row_8194D1E4_FourWords params_b, Row_8194D1E4_Packed8 packed_params);
void update_three_way_target_effect(void *effect_arg, void *position);
extern u8 actor_direction_sprites[];
#endif
