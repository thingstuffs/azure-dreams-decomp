#ifndef DUNGEON_OVL_7F469800_P01_H
#define DUNGEON_OVL_7F469800_P01_H
#include "common.h"
#include "shared/object_flags.h"

typedef struct T_80170D40_S_80170D40_0_pre {
    u16 unk_00;
} T_80170D40_S_80170D40_0_pre;   /* the 0x2 bytes before arg0 in func_80170D40, addressed as arg0[-1] */

typedef struct T_80170D40_S_80170D40_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    u16 unk_18;
} T_80170D40_S_80170D40_0;   /* arg0 in func_80170D40 */

typedef struct T_80170D40_S_80170D40_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} T_80170D40_S_80170D40_1;   /* arg2 in func_80170D40 */

typedef struct T_80170DC4_S_80170DC4_0_pre {
    u16 unk_00;
} T_80170DC4_S_80170DC4_0_pre;   /* the 0x2 bytes before arg0 in func_80170DC4, addressed as arg0[-1] */

typedef struct T_80170DC4_S_80170DC4_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
} T_80170DC4_S_80170DC4_0;   /* arg0 in func_80170DC4 */

typedef struct T_80170DC4_S_80170DC4_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} T_80170DC4_S_80170DC4_1;   /* arg2 in func_80170DC4 */

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_03[0x15];
    u16 remaining;
    s16 divisor;
} T_80170E2C_FadeState;

typedef struct {
    u8 pad_00[0xC];
    s8 red;
    s8 green;
    s8 blue;
} T_80170E2C_FadeOutput;

#include "records/Rec_D_80082E80.h"

typedef struct T_80170F94_S_80170F94_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} T_80170F94_S_80170F94_0;   /* arg1 in func_80170F94 */

typedef struct T_80170F94_S_80170F94_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u8 pad_10[0x8];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u16 unk_1A;
    u8 pad_1C[0x24];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} T_80170F94_S_80170F94_1;   /* arg0 in func_80170F94 */

#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "records/Rec_func_8017121C_arg1.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
extern void update_actor_behavior();
extern void update_rotating_actor_aura();
#endif

typedef struct T_8017121C_S_8017121C_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x3C];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
} T_8017121C_S_8017121C_0;   /* base in func_8017121C */

typedef struct T_8017121C_S_8017121C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} T_8017121C_S_8017121C_1;   /* effect in func_8017121C */

typedef struct T_8017121C_S_8017121C_3 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} T_8017121C_S_8017121C_3;   /* coords in func_8017121C */

typedef struct T_8017121C_S_8017121C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_8017121C_S_8017121C_5_pre;   /* the 0x14 bytes before arg0 in func_8017121C, addressed as arg0[-1] */

typedef struct T_8017121C_S_8017121C_6 {
    u8 pad_00[0x8];
    void * unk_08;
} T_8017121C_S_8017121C_6;   /* source in func_8017121C */

typedef struct T_8017121C_S_8017121C_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} T_8017121C_S_8017121C_8_pre;   /* the 0x18 bytes before owner in func_8017121C, addressed as owner[-1] */

typedef struct T_8017121C_S_8017121C_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} T_8017121C_S_8017121C_9;   /* tracked in func_8017121C */

typedef struct T_8017121C_S_8017121C_10 {
    u8 pad_00[0x13];
    u8 unk_13;
} T_8017121C_S_8017121C_10;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_8017121C */

typedef struct T_8017121C_Vec3u16 {
    u16 raw_y;
    u16 y;
    u16 z;
} T_8017121C_Vec3u16;

#include "shared/slus_callbacks.h"
#include "shared/game_work.h"

typedef struct { s32 w0, w1, w2, w3; } Blk16;

typedef struct T_801714FC_S_801714FC_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
} T_801714FC_S_801714FC_1;   /* v1 in func_801714FC */

typedef struct T_801714FC_S_801714FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} T_801714FC_S_801714FC_2;   /* s2 in func_801714FC */

typedef struct T_801714FC_S_801714FC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} T_801714FC_S_801714FC_3;   /* s0v in func_801714FC */

typedef struct T_801714FC_S_801714FC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_801714FC_S_801714FC_4;   /* q in func_801714FC */

typedef struct T_801714FC_S_801714FC_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_801714FC_S_801714FC_6_pre;   /* the 0x14 bytes before arg0 in func_801714FC, addressed as arg0[-1] */

typedef struct T_801714FC_S_801714FC_7 {
    u8 pad_00[0x8];
    s32 unk_08;
} T_801714FC_S_801714FC_7;   /* r in func_801714FC */

typedef struct T_801714FC_S_801714FC_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} T_801714FC_S_801714FC_8_pre;   /* the 0x18 bytes before ((S_801714FC_0 *)arg3)->unk_60.p in func_801714FC, addressed as ((S_801714FC_0 *)arg3)->unk_60.p[-1] */

typedef struct T_801714FC_S_801714FC_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} T_801714FC_S_801714FC_8;   /* ((S_801714FC_0 *)arg3)->unk_60.p in func_801714FC */

s32 rand();                                 /* extern */

typedef struct T_80171790_S_80171790_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x3C];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
} T_80171790_S_80171790_0;   /* saved_tail in func_80171790 */

typedef struct T_80171790_S_80171790_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} T_80171790_S_80171790_1;   /* (void *) saved_obj_angle in func_80171790 */

typedef struct T_80171790_S_80171790_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} T_80171790_S_80171790_3;   /* copy_dst in func_80171790 */

typedef struct T_80171790_S_80171790_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80171790_S_80171790_4;   /* saved_arg1 in func_80171790 */

typedef struct T_80171790_S_80171790_5 {
    u8 pad_00[0xAE];
    s16 unk_AE;
} T_80171790_S_80171790_5;   /* saved_arg0 in func_80171790 */

typedef struct {
    u8 data[12];
} T_80171928_Blob12;

typedef struct {
    u8 pad0[0x18];
    s16 value18;
    s16 value1a;
} T_80171928_Header;

typedef struct {
    u8 pad0[8];
    void *field8;
    u8 color_c;
    u8 color_d;
    u8 color_e;
    u8 padf;
    s16 value10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 value1c;
    s16 value1e;
} T_80171928_Child;

typedef struct {
    u8 pad0[8];
    u32 *data;
    T_80171928_Child *child;
    void *field10;
    u8 pad14[0x30];
    T_80171928_Blob12 blob;
} T_80171928_Object;

typedef struct T_80171A38_S_80171A38_0_pre {
    u16 unk_00;
} T_80171A38_S_80171A38_0_pre;   /* the 0x2 bytes before arg0 in func_80171A38, addressed as arg0[-1] */

typedef struct T_80171A38_S_80171A38_0 {
    u8 pad_00[0x20];
    void * unk_20;
} T_80171A38_S_80171A38_0;   /* arg0 in func_80171A38 */

typedef struct T_80171A38_S_80171A38_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} T_80171A38_S_80171A38_1;   /* record in func_80171A38 */

typedef struct T_80171A38_S_80171A38_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x1];
    u16 unk_06;
    u8 pad_08[0x24];
    void * unk_2C;
} T_80171A38_S_80171A38_2;   /* part in func_80171A38 */

typedef struct T_80171A38_S_80171A38_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x14];
    s16 unk_1C;
    s16 unk_1E;
} T_80171A38_S_80171A38_3;   /* arg2 in func_80171A38 */

typedef struct T_80171A38_S_80171A38_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80171A38_S_80171A38_4;   /* arg1 in func_80171A38 */

typedef struct T_80171A38_S_80171A38_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80171A38_S_80171A38_5;   /* source in func_80171A38 */

typedef struct T_80171A38_S_80171A38_6 {
    u8 pad_00[0x8];
    void * unk_08;
} T_80171A38_S_80171A38_6;   /* ((T_80171A38_S_80171A38_1 *)record)->unk_0C in func_80171A38 */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} T_80171A38_Vec3s;

typedef struct T_80171BEC_S_80171BEC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x2C];
    void * unk_40;
} T_80171BEC_S_80171BEC_0;   /* object in func_80171BEC */

typedef struct T_80171BEC_S_80171BEC_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} T_80171BEC_S_80171BEC_1;   /* render in func_80171BEC */

typedef struct T_80171BEC_S_80171BEC_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} T_80171BEC_S_80171BEC_2;   /* position in func_80171BEC */

typedef struct T_80171BEC_S_80171BEC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} T_80171BEC_S_80171BEC_3;   /* arg1 in func_80171BEC */

typedef struct T_80171BEC_S_80171BEC_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_80171BEC_S_80171BEC_4_pre;   /* the 0x14 bytes before arg0 in func_80171BEC, addressed as arg0[-1] */

typedef struct T_80171BEC_S_80171BEC_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} T_80171BEC_S_80171BEC_5;   /* owner in func_80171BEC */

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} T_80171BEC_Offset3;

typedef struct {
    u8 bytes[12];
} T_80171BEC_Packed3;

#include "shared/sprite_frame_state.h"

typedef struct T_80171D64_S_80171D64_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} T_80171D64_S_80171D64_2;   /* position in func_80171D64 */

typedef struct T_80171D64_S_80171D64_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} T_80171D64_S_80171D64_4;   /* the record, addressed through its copy in func_80171D64 */

extern void func_800478B8(void *entity);
extern s32 check_left_tile_and_center_height(u16 x, u16 y, s16 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);
extern s32 resolve_record_orientation_or_fallback(void *, void *, T_8017121C_Vec3u16 *, s32);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void * allocate_list_node();
extern void * func_8003FD64();
extern void select_sprite_entry();
extern void func_80047784();
extern s32 func_800644B8();
extern s32 func_80064584();
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value(void);
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80175EBC[];
extern u8 D_80175EB4[];
extern T_80171928_Blob12 D_80175EDC;
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];
extern T_80171BEC_Packed3 D_80175EE8;
extern s8 D_800E2968;
extern u8 D_801720B4[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];
void update_stepped_rgb_flash(void *fade_state, void *unused, T_80170D40_S_80170D40_1 *primitive);
void update_normalized_gray_fade(void *countdownState, s32 unused, T_80170DC4_S_80170DC4_1 *output);
void update_saved_rgb_fade(T_80170E2C_FadeState *fade, s32 unused, T_80170E2C_FadeOutput *output);
void update_growing_rotating_flash(void *effect, s32 unused, void *visual);
void update_growing_bouncing_effect(void *effect, void *position, void *sprite);
void create_targeted_motion_effect(void *source_handle, Rec_func_8017121C_arg1 *origin, s32 unused, EntityRec *target);
void create_actor_action_effect(void *source_object, void *source_pos, void *sprite_template, EntityRec *actor);
void spawn_random_color_burst_particle(void *source, void *position);
void spawn_growing_rotating_flash(void *unused, s32 *position);
void update_tracked_attachment_sprite(void *object, T_80171A38_S_80171A38_4 *position, T_80171A38_S_80171A38_3 *part_state);
void create_tracked_attachment_sprite(void *attachment, T_80171BEC_S_80171BEC_3 *base_position);
void * create_actor_entity(s16 spawn_flags, s32 sprite_x, s32 sprite_y, s32 initial_height);
extern void update_actor_behavior();
extern void update_rotating_actor_aura();
#endif
