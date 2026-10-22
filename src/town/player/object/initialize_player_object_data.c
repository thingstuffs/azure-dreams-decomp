#include "common.h"
#include "shared/object_node.h"

extern void initialize_scene_action_record(void *buffer, s32 header_value08, s32 header_value0C);
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(s32 record);

extern u8 scene_object_payload_alias[];
extern u8 town_scene_record_handlers[];

// Processes D_800834B8 using the parameters stored in its preceding header.
/* Clears the player's entity fields, selects its scene handlers, and initializes its action record. */
void initialize_player_object_data(void) {
    void *dataBuffer;
    ObjectNodeHeader *bufferHeader;
    s32 headerValue0C;
    s32 headerValue08;

    dataBuffer = scene_object_payload_alias;
    bufferHeader = (s8 *)dataBuffer - 0x20;
    headerValue08 = *(s32 *)&bufferHeader->position;
    headerValue0C = *(s32 *)&bufferHeader->sprite;
    clear_entity_record_fields(headerValue08);
    call_the_handler_selects_nonzero_entry(town_scene_record_handlers, dataBuffer, headerValue0C);
    initialize_scene_action_record(dataBuffer, headerValue08, headerValue0C);
}
