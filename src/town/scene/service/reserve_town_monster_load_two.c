#include "town/scene.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Reserve the fixed value through the map monster-load service. */
void reserve_town_monster_load_two(struct RuntimeState *unused_transition, void *unused_map_data)
{
    town_scene_root->services->callback_1F4(2);
}
