#ifndef DUNGEON_OVL_E1B054_H
#define DUNGEON_OVL_E1B054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"
struct RegistrationNode;
struct S_80170A98_2;



typedef struct S_80158854_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80158854_0;   /* work in func_80158854 */

   /* obj in func_80158854 */

   /* part_a in func_80158854 */

typedef struct S_80158854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158854_3;   /* part_b in func_80158854 */

typedef struct S_80158854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158854_4;   /* actor in func_80158854 */


extern void func_80158A58(void *entity, struct S_80170A98_2 *motion, SpriteFrameState *monster);
extern void func_80158E5C(void *actor_in, void *context_in, void *sprite_in, void *status_in);
extern u8 volcano_slot_c_frame_set[];
extern u8 D_8015C538[];

extern void *allocate_list_node();
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct RegistrationNode *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void initialize_actor_sprite_and_animation();

void * func_80158854(s16 value, s16 part_b_value_a, s16 part_b_value_b, s16 part_a_value);
#endif
