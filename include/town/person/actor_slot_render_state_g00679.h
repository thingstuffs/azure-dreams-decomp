#ifndef TOWN_PERSON_ACTOR_SLOT_RENDER_STATE_G00679_H
#define TOWN_PERSON_ACTOR_SLOT_RENDER_STATE_G00679_H
/* G00679: shared declarations for actor slot render state. */
/* Original-file evidence (G00679): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6430, PD:town/engine:800D6438, PD:town/engine:800D6460, PD:town/engine:800D6464. */

#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6430[];
extern u8 D_800D6438[];
extern u8 D_800D6460[];
extern u8 D_800D6464[];
extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);

/* Functions defined in this translation unit. */
void initialize_scene_slot_36(void *object, s32 unused, void *context);
void configure_actor_slot_26_and_render_state(void *context, s32 unused, u16 *stateWords);

#endif
