#include "common.h"
#include "shared/object_node.h"
#include "town/map/object_setup.h"
#include "town/scene/list_setup.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "slus.h"
#include "town/map/motion.h"
#include "town/map.h"
#include "town/map/paired_actor_motion_g00645.h"

extern struct SpriteSourceEntry *D_800D211C[4];
extern const u8 *D_800D212C;

/* Initialize the object state, motion, and animation. */
void init_random_wander_object(void *object_data, ObjectPosition *motion, struct SpriteFrameState *anim) {
    TownWanderBody *object = object_data;
    NODE_HEADER(object)->update_callback = update_random_idle_wander;
    object->unk_50 = 0;
    register_node(NODE_HEADER(object), project_sprite_chain);
    object->direction = 2;
    init_scene_node_mode_1(&object->scene, motion, town_map_motion_defaults);
    select_record_entry_and_value(anim, D_800D211C[object->direction], 0);
    object->interaction_script = D_800D212C;
}
