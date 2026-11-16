#ifndef DUNGEON_OVL_7F51D800_H
#define DUNGEON_OVL_7F51D800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"
struct ObjectNodeHeader;

extern s32 clown_object_callback;
extern s32 D_8014D014;
extern s32 D_8015020C;
extern s32 D_8015025C;

extern s32 generate_random_value(void);

   /* var_s0 in func_8014C878 */


/* Allocates an object and initializes its state, placement, and callbacks. */

void *allocate_object_state_and_callbacks(s16 init_flags, s16 grid_x, s16 grid_y, s16 type_id);
#endif
