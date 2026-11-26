#ifndef TOWN_SHOP_MONSTER_STATUS_INITIALIZATION_G00634_H
#define TOWN_SHOP_MONSTER_STATUS_INITIALIZATION_G00634_H
struct ShopFirstCallbackObject;
/* Initialize monster status state and entry objects: shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9044, CL:town/func_800B90DC, CL:town/func_800B914C, CL:town/func_800B9168. */

#include "town/shop/object.h"
#include "shared/sprite_part_command.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

extern SpritePartCommand *D_800D17C8[4];
/* extern */
s32 queue_monster_status_reload(ShopFirstCallbackObject *);
/* extern */

extern void initialize_positioned_display_templates(void *owner, void *instance_data, void *instance1, s32 x, s32 y_arg, s32 z_arg);
extern void reset_monster_status_links(struct ShopFirstCallbackObject *object);

/* Functions defined in this translation unit. */
SpritePartCommand *get_monster_status_type_data(s32 index);
void initialize_monster_status_state(ShopFirstCallbackObject *record, struct ActorRecord *actor, s32 type_id);
void initialize_monster_status_object(ShopFirstCallbackObject *object, struct ActorRecord *actor, s32 resourceIndex, s32 positionX, s32 positionY, s32 positionZ);

#endif
