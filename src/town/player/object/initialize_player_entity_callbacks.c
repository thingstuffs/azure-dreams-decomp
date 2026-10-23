#include "common.h"
#include "shared/town_handler_entries.h"

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

extern void clear_entity_record_fields(s32 record);
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);

extern Entity scene_object_payload_alias;
extern s32 town_position_callback_address[3];
extern s32 D_8009A724;


/* Initialize the entity's callbacks, ID, position, and timer. */
void initialize_player_entity_callbacks(s32 entity_id, s32 x, s32 y) {
    Entity *entity = &scene_object_payload_alias;
    s32 *context = (s32 *)((u8 *)entity - 0x20);
    s32 context_value = context[3];

    clear_entity_record_fields(context[2]);
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, entity, context_value);
    scene_object_payload_alias.callback0 = town_position_callback_address;
    entity->callback4 = &D_8009A724;
    entity->id = entity_id & 0xFFF;
    entity->x = x;
    entity->y = y;
    entity->timer = 8;
}
