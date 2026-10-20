#ifndef DUNGEON_OVL_19A8800_H
#define DUNGEON_OVL_19A8800_H
#include "modules/dungeon_native_abi.h"
struct MainObject;
void update_directional_actor_effect(void *state, void *position);
s32 create_counted_sprite_effect(void *first_item);
void update_effect_and_spawn_fragments(struct MainObject *object);
void mark_referenced_object_and_update_flags(void *entry, void *unused, void *target);
void update_segment(void *effect);
#endif
