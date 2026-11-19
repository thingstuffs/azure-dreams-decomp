#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/monster/beldo_large.h"

#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

extern void update_actor_status_and_mp(void *);
extern void unlink_entity_node(void *);



extern u8 D_8016FC4C[];

/* Update the entity at its position and reset its state fields. */
void reset_encounter_actor_state(void)
{
    ObjectNodeHeader *root = beldo_actor_nodes;
    ActorRecord *entity;
    SpriteFrameState *sprite;

    entity = NODE_BODY(root);

    sprite = root->sprite;

    update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y,
                  (entity->flags1C & 0x2000) ? 0x300 : 0x3000);
    update_actor_status_and_mp(entity);
    unlink_entity_node(entity);
    beldo_actor_nodes->update_callback = D_8016FC4C;
    entity->action_id = 0;
    entity->action_timer = 0;
}
