#ifndef TOWN_PLAYER_ITEM_H
#define TOWN_PLAYER_ITEM_H
/* Prototypes of the functions defined in src/town/player/item/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"

struct ObjectPosition;
struct SpriteFrameState;

/* initialize_returned_item_action.c */
void initialize_returned_item_action(TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

/* plt_carry_item_del_ext.c */
void plt_carry_item_del_ext(void);

/* set_hold_item_callback.c */
s32 set_hold_item_callback(void);

/* set_deferred_dispatch_handler.c */
void set_deferred_dispatch_handler(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_context);

/* set_return_item_callback.c */
s32 set_return_item_callback(void);

#endif
