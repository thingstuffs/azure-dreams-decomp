#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

#ifndef NULL
#define NULL 0
#endif





/* Finds the first entry matching both keys, the value range, and the type filter. */
void *find_species_actor_on_tile(ActorRecord *body, u16 key_a, u16 key_b, s16 range_center) {
    void *head = body;

    body = NODE_BODY(body->next_actor_header);
    while (body != head) {
        SpriteFrameState *node_data = NODE_HEADER(body)->sprite;
        void *entry = NODE_HEADER(body);
        s16 node_value;

        if ((node_data->tile_x == key_a) &&
            (node_data->tile_y == key_b) &&
            (node_value = body->ground_height, node_value <= range_center + 0x20) &&
            (node_value >= range_center - 0x20) &&
            ((u32)(body->species - 0x33) < 4)) {
            return entry;
        }
        body = NODE_BODY(body->next_actor_header);
    }
    return NULL;
}
