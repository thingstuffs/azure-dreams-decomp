#ifndef TOWN_PERSON_ACTOR_SLOT_RENDER_STATE_G00667_H
#define TOWN_PERSON_ACTOR_SLOT_RENDER_STATE_G00667_H
/* Actor slot render state (G00667). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D5DD4, PD:town/engine:800D5DDC, PD:town/engine:800D5E04, PD:town/engine:800D5E08. */

#include "common.h"
#include "town/person.h"

extern u8 D_800D5DD4[];
extern u8 D_800D5DDC[];
extern u8 D_800D5E04[];
extern u8 D_800D5E08[];
extern void func_800C3050(void *, s32, s32, s32, s32, s32);

/* Functions defined in this translation unit. */
void initialize_scene_slot_53(void *object, s32 unused, void *context);
void initialize_scene_slot_55(void *object, s32 unused, void *context);
void initialize_scene_slot_49(void *object, s32 unused, void *context);
void configure_actor_slot_28_and_render_state(void *context, s32 unused, u16 *stateWords);

#endif
