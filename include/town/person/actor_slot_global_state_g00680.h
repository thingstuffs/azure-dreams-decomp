#ifndef TOWN_PERSON_ACTOR_SLOT_GLOBAL_STATE_G00680_H
#define TOWN_PERSON_ACTOR_SLOT_GLOBAL_STATE_G00680_H
/* G00680: shared declarations for actor slot global state. */
/* Original-file evidence (G00680): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6674, PD:town/engine:800D667C, PD:town/engine:800D66A4, PD:town/engine:800D66A8. */

/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern s32 loaded_town_resource_attributes[];
extern u8 D_800D6674[];
extern u8 D_800D667C[];
extern u8 D_800D66A4[];
extern u8 D_800D66A8[];

/* Functions defined in this translation unit. */
void configure_actor_slot_75_and_copy_global(void *actor, s32 unused, void *state);
void configure_actor_slot_76_and_copy_global(void *actor, s32 unused, void *state);
void configure_actor_slot_77_and_copy_global(void *actor, s32 unused, void *state);
void configure_actor_slot_78_and_copy_global(void *actor, s32 unused, void *state);

#endif
