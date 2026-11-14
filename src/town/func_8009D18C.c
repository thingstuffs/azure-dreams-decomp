/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_node.h"
#include "town/player/approach_player_angle_target_g01125.h"
#include "shared/town_handler_entries.h"
#include "town.h"
#include "town/player.h"
#include "town/player/object.h"

typedef struct {
    void *callback0;
    void *callback4;
    u8 pad08[2];
    s16 timer;
    u8 pad0C[4];
    s16 id;
    u8 pad12[0x24];
    s16 x;
    s16 y;
} Entity;

extern void dispatch_selected_entry_if_nonzero(void *entries, void *record,void *handler_param);

extern Entity scene_object_payload_alias;


/* Initializes the scene entity's handlers, masked ID, position, and 16-tick timer. */
void initialize_entity_handlers_and_position(s32 entity_id, s32 x, s32 y) {
    Entity *entity = &scene_object_payload_alias;
    ObjectNodeHeader *node = NODE_HEADER(entity);
    struct SpriteFrameState *sprite = node->sprite;

    clear_object_velocity(node->position);
    dispatch_selected_entry_if_nonzero(approach_action_handler_table, entity, sprite);
    scene_object_payload_alias.callback0 = invoke_object_state_callback;
    entity->callback4 = &D_8009A81C;
    entity->id = entity_id & 0xFFF;
    entity->x = x;
    entity->y = y;
    entity->timer = 0x10;
}
