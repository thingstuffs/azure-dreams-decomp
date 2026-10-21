#include "common.h"

extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void update_actor_status_and_mp(void *);
extern void unlink_entity_node(void *);

typedef struct Entity {
    u8 pad_00[0x1C];
    s32 flags;
    u8 pad_20[0x76];
    s16 field_96;
    u8 pad_98[2];
    u8 field_9A;
} Entity;

typedef struct Root {
    u8 pad_00[0xC];
    u8 *position;
    u8 *field_10;
    u8 pad_14[0xC];
    Entity entity;
} Root;

extern Root *beldo_actor_nodes;
extern u8 D_8016FC4C[];

/* Update the entity at its position and reset its state fields. */
void reset_encounter_actor_state(void)
{
    Root *root = beldo_actor_nodes;
    Entity *entity;
    u8 *position;

    entity = &root->entity;

    position = root->position;

    update_map_cell_flags_with_item_limit(position[0x24], position[0x25],
                  (entity->flags & 0x2000) ? 0x300 : 0x3000);
    update_actor_status_and_mp(entity);
    unlink_entity_node(entity);
    beldo_actor_nodes->field_10 = D_8016FC4C;
    entity->field_9A = 0;
    entity->field_96 = 0;
}
