#include "common.h"
#include "shared/object_node.h"
#include "engine/script.h"
#include "town/player/object.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record,void *handler_param);
extern void init_motion_action_callback(void *block, s32 header_param_08, s32 header_param_0c);

extern u8 D_8006CADE[];
extern u8 scene_object_payload_alias[];
extern u8 town_scene_record_handlers[];

/* Set the block's 12-bit value and apply its header parameters. */
void set_player_block_value(s32 value)
{
    void *block;
    ObjectNodeHeader *header;
    s32 header_param_0c;
    s32 header_param_08;

    block = scene_object_payload_alias;
    header = (s8 *)block - 0x20;
    header_param_08 = *(s32 *)&header->position;
    header_param_0c = *(s32 *)&header->sprite;
    clear_entity_record_fields(header_param_08);
    *(s16 *)((s8 *)block + 0x10) = value & 0xFFF;
    call_the_handler_selects_nonzero_entry(town_scene_record_handlers, block, header_param_0c);
    init_motion_action_callback(block, header_param_08, header_param_0c);
    call_script(D_8006CADE);
}
