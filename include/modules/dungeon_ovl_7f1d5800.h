#ifndef DUNGEON_OVL_7F1D5800_H
#define DUNGEON_OVL_7F1D5800_H
#include "common.h"
#include "engine/node.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
struct R03_80170A28_S_80170A28_2;
struct ObjectNodeHeader;

   /* work in func_8014C894 */

   /* part_a in func_8014C894 */

   /* actor in func_8014C894 */

extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void set_or_clear_actor_status_slot();
extern void func_8014CA68(void *entity, struct R03_80170A28_S_80170A28_2 *motion, void *part);
extern void func_8014CE94(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);
extern u8 D_80150A7C[];
extern u8 viper_frame_set_6[];

void * func_8014C894(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif
