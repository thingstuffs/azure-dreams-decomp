#include "common.h"
#include "shared/object_node.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(s32 record);

extern u8 scene_object_payload_alias[];
extern u8 D_8008FFC0[];
extern u8 D_80093D48[];
extern u8 town_scene_record_handlers[];
extern void *town_player_action_callback;

/* Processes the object's header values and updates the global pointers. */
void create_familiar_deployment_effect_with_owner_state(void) {
    void *object;
    ObjectNodeHeader *object_header;
    s32 header_value;

    object = scene_object_payload_alias;
    object_header = (u8 *)object - 0x20;
    header_value = *(s32 *)&object_header->sprite;
    clear_entity_record_fields(*(s32 *)&object_header->position);
    call_the_handler_selects_nonzero_entry(town_scene_record_handlers, object, header_value);
    *(void **)scene_object_payload_alias = D_8008FFC0;
    town_player_action_callback = D_80093D48;
}
