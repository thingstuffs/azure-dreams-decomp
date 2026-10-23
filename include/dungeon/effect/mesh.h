#ifndef DUNGEON_EFFECT_MESH_H
#define DUNGEON_EFFECT_MESH_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void create_random_radial_vector_effect(s32 radius, s32 initial_value, s16 extent, s32 x, s32 y, s32 z);
void clear_listed_tile_flags(void);
s32 count_flagged_tiles_along_direction_2(s16 scan_direction, s32 start_x, s32 start_y);






void follow_source_then_seek_target(void *effect, ObjectPosition *motion, void *visual);
void update_expanding_fade_effect(void *effect, ObjectPosition *position, SpriteFrameState *sprite);

#endif
