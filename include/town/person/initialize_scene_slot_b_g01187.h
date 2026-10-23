#ifndef TOWN_PERSON_INITIALIZE_SCENE_SLOT_B_G01187_H
#define TOWN_PERSON_INITIALIZE_SCENE_SLOT_B_G01187_H
/* Initialize scene slot b. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01187 - PD:town/engine:800D6824, PD:town/engine:800D682C, PD:town/engine:800D6854, PD:town/engine:800D6858. */

#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 scene_slot_b_data_c[];
extern u8 scene_slot_b_data_d[];
extern u8 scene_slot_b_data_a[];
extern u8 scene_slot_b_data_b[];
extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);

/* Functions defined in this translation unit. */
void initialize_scene_slot_46(void *object, s32 unused, void *context);
void initialize_scene_slot_38(void *object, s32 unused, void *context);
void initialize_scene_slot_30(void *object, s32 unused, void *context);
void initialize_scene_slot_57_context(void *object, s32 unused, void *context);
void initialize_scene_slot_62_context(void *object, s32 unused, void *context);
void initialize_scene_slot_24(void *object, s32 unused, void *context);
void configure_actor_slot_25_and_render_state(void *context, s32 unused, u16 *stateWords);
void initialize_scene_slot_69(void *object, s32 unused, void *context);

#endif
