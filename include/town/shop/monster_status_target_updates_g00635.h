#ifndef TOWN_SHOP_MONSTER_STATUS_TARGET_UPDATES_G00635_H
#define TOWN_SHOP_MONSTER_STATUS_TARGET_UPDATES_G00635_H
/* Release handled entries and change the monster status target: shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B93B0, CL:town/func_800B97F4. */

#include "town/shop/object.h"
#include "common.h"
#include "m2c_compat.h"

/* extern */
#include "engine/resource.h"
#include "slus.h"
/* Canonical global flags word shared by several sibling functions across
 * the codebase (code9.c, code10.c, code11.c, code5.c, w_8004FE78.c, ...).
 * Declared as a plain `extern int` so the address is recomputed separately
 * for the load and the store, matching this function's tail. */
extern int D_800814A0;
extern void release_null_terminated_entries(u16 **a0);
void build_monster_status_display(ShopFirstCallbackObject *);
struct Rec_func_800B683C_arg0;
/* extern */
s32 queue_monster_status_reload(struct ShopFirstCallbackObject *);

/* Functions defined in this translation unit. */
void release_monster_status_entries(ItemMenuPart **entries);
void destroy_monster_status_object(ObjectNodeHeader *object);
void change_monster_status_display_target(s32 objectAddress, struct ActorRecord *actor, s16 field08Value);

#endif
