#ifndef TOWN_PLAYER_CALL_THE_HANDLER_SELECTS_NONZERO_ENTRY_G01123_H
#define TOWN_PLAYER_CALL_THE_HANDLER_SELECTS_NONZERO_ENTRY_G01123_H
/* call the handler selects nonzero entry g01123. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_80097264, CL:town/func_80097300. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "records/Rec_D_80082D58.h"

extern u8 animation_tick_scale;

/* Functions defined in this translation unit. */
void dispatch_selected_entry_if_nonzero(s32 *entries, TownObjectRecord *record, void *ptr2);
void set_sprite_frame_by_view_angle(u8 *sourceBytes, s32 selection, u8 *destination);
void store_entry_and_set_frame(s32 value, Rec_D_80082D58 *record, void *destination);
void forward_selected_entry_value(s32 *values, TownObjectRecord *selector, void *ptr2);

#endif
