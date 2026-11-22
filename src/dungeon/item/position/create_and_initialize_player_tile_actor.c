#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;



extern void init_monster_from_stats();
extern void *create_player_tile_actor_at_coordinates();



/* Looks up an entry, clears its linked state, and processes it if found. */
s32 create_and_initialize_player_tile_actor(void) {
    s32 found;
    ActorRecord *entry;

    entry = create_player_tile_actor_at_coordinates(
        reference_tile_object.tile_position.parts.tile_x,
        reference_tile_object.tile_position.parts.tile_y,
        dungeon_actor_ring_anchor->ground_height);
    if (entry != 0) {
        NODE_HEADER(entry)->sprite->color.word = 0;
        init_monster_from_stats(entry, entry->species);
        found = 1;
    } else {
        found = 0;
    }
    return found;
}
