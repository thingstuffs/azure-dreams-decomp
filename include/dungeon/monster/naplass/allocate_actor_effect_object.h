#ifndef DUNGEON_OVL_F7D070_P01_H
#define DUNGEON_OVL_F7D070_P01_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"
#include "dungeon/actor.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
struct ObjectNodeHeader;



   /* obj in func_80170870 */


   /* part_a in func_80170870 */





extern void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern u8 D_80170A3C[];
extern s32 naplass_action_continuation_address;
extern u8 naplass_frame_set_1[];
extern u8 naplass_frame_set[];
void * allocate_actor_effect_object(s16 kind_flags, s16 x, s16 y, s16 part_value);
#endif
