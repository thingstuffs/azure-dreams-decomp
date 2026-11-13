#ifndef TOWN_SHOP_STATE_COUNTDOWN_UPDATES_G00558_H
#define TOWN_SHOP_STATE_COUNTDOWN_UPDATES_G00558_H
/* State countdown updates declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A1510. */

#include "common.h"
#include "town/scene/collision.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

/* extern */
typedef struct S_8009ECF0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ECF0_0;

extern s32 find_nearest_unflagged_record_result(s32 record_set, ObjectPosition *target);
extern s32 D_8009ED7C;
extern u8 D_80100B3B;
void apply_bound_adjustments(s32, s32);
/* extern */

/* Functions defined in this translation unit. */
void retarget_entity_to_nearest_entry(void *object, TownObjectRecord *status, ObjectPosition *position, s32 unused_finish_ctx);
void update_entity_until_countdown_ends(S_8009ECF0_0 *state, s32 update_ctx, ObjectPosition *position, s32 finish_ctx);

#endif
