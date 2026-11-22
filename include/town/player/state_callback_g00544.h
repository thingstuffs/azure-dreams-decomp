#ifndef TOWN_PLAYER_STATE_CALLBACK_G00544_H
#define TOWN_PLAYER_STATE_CALLBACK_G00544_H
/* Dispatch state callbacks by mode. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A688. */

#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

struct ObjectPosition;
struct SpriteFrameState;
typedef void (*TownPlayerStateCallback)(void *, struct ObjectPosition *, struct SpriteFrameState *);

extern TownPlayerStateCallback D_800D0508[];
/* Raw callback addresses. The item action and interaction handlers have distinct body types. */
extern s32 *town_player_action_callback[3];

/* Functions defined in this translation unit. */
void dispatch_state_callback_by_mode(void *object, struct ObjectPosition *position, struct SpriteFrameState *sprite, s32 unused);
void forward_state_callback_dispatch(void *object, struct ObjectPosition *position, struct SpriteFrameState *sprite, s32 mode);

#endif
