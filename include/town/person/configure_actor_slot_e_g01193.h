#ifndef TOWN_PERSON_CONFIGURE_ACTOR_SLOT_E_G01193_H
#define TOWN_PERSON_CONFIGURE_ACTOR_SLOT_E_G01193_H
/* Configure actor slot e. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01193 - PD:town/engine:800D7238, PD:town/engine:800D7240, PD:town/engine:800D7268, PD:town/engine:800D726C. */

/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D7238[];
extern u8 D_800D7240[];
extern u8 D_800D7268[];
extern u8 D_800D726C[];

/* Functions defined in this translation unit. */
void configure_actor_slot_34(void *actor);
void configure_actor_slot_14(void *actor);
void configure_actor_slot_20(void *actor);
void configure_actor_slot_58(void *actor);
void configure_actor_slot_43(void *actor);
void configure_actor_slot_80(void *actor);

#endif
