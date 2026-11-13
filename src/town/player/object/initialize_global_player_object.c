#include "common.h"
#include "shared/object_node.h"
#include "town/player/object.h"
#include "town/data.h"

extern void dispatch_selected_entry_if_nonzero(void *entries, void *record,void *handler_param);

extern u8 scene_object_payload_alias[];
extern u8 town_position_callback_address[];
extern u8 D_8009ACFC[];
extern u8 town_scene_record_handlers[];

/* Initializes the global object and resets its state pointers and flag. */
void initialize_global_player_object(void)
{
    void *object;
    ObjectNodeHeader *object_header;
    s32 init_value;

    object = scene_object_payload_alias;
    object_header = NODE_HEADER(object);
    init_value = *(s32 *)&object_header->sprite;
    clear_entity_record_fields(*(s32 *)&object_header->position);
    dispatch_selected_entry_if_nonzero(town_scene_record_handlers, object, init_value);
    town_player_target_adjustment = 0;
    *(void **)scene_object_payload_alias = town_position_callback_address;
    *(void **)((u8 *)object + 4) = D_8009ACFC;
}
