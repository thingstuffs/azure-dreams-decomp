#ifndef DUNGEON_OVL_1972800_H
#define DUNGEON_OVL_1972800_H
#include "modules/dungeon_native_abi.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
void update_directional_actor_effect(void *, void *);
void update_spiraling_effect_growth_and_fade(void *, void *, void *);
void spawn_spiraling(void *, s16, s16, void *, s32);
void process_effect_modes_and_completion(void *);
void allocate_and_initialize_effect_object(s32, s16, s16, s32);
void draw_textured_ellipse(s32, void *, u16, u16);
void create_timed_model_effect(s32, void *, s32, s32);
s32 rsin(s32);
s32 rcos(s32);
extern u8 D_800DF334[];
extern u8 linked_mesh_processor_address[];
extern u8 D_80024980[];
extern u8 directional_effect_sprite_data[];
extern s16 D_800249A4;
extern u16 D_800249A6[5];
#endif
