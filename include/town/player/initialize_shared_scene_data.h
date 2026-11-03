#ifndef TOWN_PLAYER_INITIALIZE_SHARED_SCENE_DATA_H
#define TOWN_PLAYER_INITIALIZE_SHARED_SCENE_DATA_H


struct SpriteFrameState;

/* The shared callback ABI passes position and sprite; this initializer uses only the output slot. */

void initialize_shared_scene_data(int **out_ptr, void *unused_position, struct SpriteFrameState *unused_sprite);

#endif
