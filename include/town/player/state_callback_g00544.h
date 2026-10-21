#ifndef TOWN_PLAYER_STATE_CALLBACK_G00544_H
#define TOWN_PLAYER_STATE_CALLBACK_G00544_H
/* Dispatch state callbacks by mode (G00544). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A688. */

#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

typedef void (*Callback)(s32, void *, void *);

extern s32 service_script_controller(void);
extern s32 *D_800D0508[];
extern s32 *town_player_action_callback[3];

/* Functions defined in this translation unit. */
void dispatch_state_callback_by_mode(s32 value, void *ptr, void *ptr2, s32 unused);
void forward_value_context_data_mode(s32 value, void *context, void *data, s32 mode);

#endif
