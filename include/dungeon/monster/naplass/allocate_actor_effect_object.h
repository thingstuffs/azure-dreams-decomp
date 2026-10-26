#ifndef DUNGEON_OVL_F7D070_P01_H
#define DUNGEON_OVL_F7D070_P01_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"
#include "dungeon/actor.h"
struct ObjectNodeHeader;



   /* obj in func_80170870 */

typedef struct T_80170870_S_80170870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} T_80170870_S_80170870_1;   /* work in func_80170870 */

   /* part_a in func_80170870 */

typedef struct T_80170870_S_80170870_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} T_80170870_S_80170870_3;   /* part_b in func_80170870 */

typedef struct T_80170870_S_80170870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} T_80170870_S_80170870_4;   /* actor in func_80170870 */



extern void * allocate_list_node();
extern void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern u8 D_80170A3C[];
extern s32 naplass_action_continuation_address;
extern u8 naplass_frame_set_1[];
extern u8 naplass_frame_set[];
void * allocate_actor_effect_object(s16 kind_flags, s16 x, s16 y, s16 part_value);
#endif
