#ifndef DUNGEON_EFFECT_SHADE_H
#define DUNGEON_EFFECT_SHADE_H
#include "shared/dungeon_effect_source.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct Obj;
void apply_random_value_gain(struct Obj *target, int amount_param, void *record);
void apply_conditional_target_effect(void *target, int packed_value, void *record);
struct Owner;
void create_owner_color_sprite(struct Owner *owner, unsigned int color);


void advance_damped_effect_motion(void *effect, ObjectPosition *motion, void *color);

/* Callback entry points. */
int build_sorted_effect_quads(void *quad_entry);
void advance_damped_effect_and_expire(unsigned char *effect, int *motion);

#endif
