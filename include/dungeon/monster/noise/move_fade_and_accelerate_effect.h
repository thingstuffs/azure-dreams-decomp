#ifndef DUNGEON_OVL_7F43F800_P02_H
#define DUNGEON_OVL_7F43F800_P02_H
#include "common.h"
#include "sdk/libc.h"
#include "dungeon/actor.h"
#ifndef NULL
#define NULL 0
extern void update_actor_behavior_and_direction();
extern void create_timed_offset_motion_effect();
#endif
#include "shared/object_flags.h"

typedef struct T_80170F0C_S_func_80D1170C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[1];
    union {
        s32 unk_04;
        struct {
            s8 unk_04;
            s8 unk_05;
            s8 unk_06;
            u8 pad_07[1];
        } bytes;
    } unk_04;
    s32 unk_08;
    u8 pad_0C[0x26];
    union {
        s16 unk_32;
        u16 unk_32_u;
    } unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[8];
    s32 unk_54;
} T_80170F0C_S_func_80D1170C_1;

#include "shared/entity.h"

typedef struct T_80171020_S_80171020_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80171020_S_80171020_7;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80171020 */


typedef struct T_80171020_S_80171020_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} T_80171020_S_80171020_0;   /* temp_v0 in func_80171020 */

typedef struct T_80171020_S_80171020_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x8];
    s32 unk_54;
} T_80171020_S_80171020_1;   /* temp_s0 in func_80171020 */

typedef struct T_80171020_S_80171020_2 {
    s32 unk_00;
} T_80171020_S_80171020_2;   /* temp_a2 in func_80171020 */

typedef struct T_80171020_S_80171020_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} T_80171020_S_80171020_3;   /* temp_a2_2 in func_80171020 */

#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/vector.h"
#include "shared/object_links.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"
struct RegistrationNode;

   /* obj in func_80171190 */

   /* part_a in func_80171190 */

typedef struct T_80171190_S_80171190_2 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} T_80171190_S_80171190_2;   /* part_b in func_80171190 */

typedef struct T_80171190_Work {
    u8 pad0[0x13];
    s8 byte13;
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x6C];
    void *ptr8c;
    u8 pad90[0xA];
    u8 byte9a;
    u8 pad9b;
    s8 byte9c;
} T_80171190_Work;

extern void * allocate_list_node();
extern void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct RegistrationNode *entry, void *registration_id);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern u8 D_80171358[];
extern u8 noise_direction_frames[];
extern u8 noise_frame_set[];
void move_fade_and_accelerate_effect(T_80170F0C_S_func_80D1170C_1 *effect, IntVector3 *position);
void spawn_random_velocity_offset_effect(EntityRec *parent, s16 effect_id, s32 effect_param, s32 unused, s16 x_offset,
    s16 y_offset, s16 z_offset);
void * create_actor_with_direction_behavior(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
extern void update_actor_behavior_and_direction();
extern void create_timed_offset_motion_effect();
#endif
