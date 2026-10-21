#ifndef TOWN_SHOP_MONSTER_STATUS_INITIALIZATION_G00634_H
#define TOWN_SHOP_MONSTER_STATUS_INITIALIZATION_G00634_H
/* Initialize monster status state and entry objects (G00634): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9044, CL:town/func_800B90DC, CL:town/func_800B914C, CL:town/func_800B9168. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D17C8;
/* extern */
s32 invalidate_cached_state_and_queue_read(void *);
/* extern */
extern M2C_UNK D_800B66E8;
extern void func_800B67A4(void *owner, void *instance_data, void *instance1, s32 x, s32 y_arg, s32 z_arg);
extern void clear_linked_entry_state(void *object);

/* Functions defined in this translation unit. */
s32 get_monster_status_type_data(s32 index);
void initialize_monster_status_state(Rec_func_800B683C_arg0 *record, s32 context, s32 type_id);
void initialize_entry_object(void *object, s32 entityId, s32 resourceIndex, s32 positionX, s32 positionY, s32 positionZ);

#endif
