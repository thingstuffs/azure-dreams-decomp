#include "common.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(s32 record);

extern u8 scene_object_payload_alias[];
extern u8 D_80097D2C[];
extern u8 D_8009ACFC[];
extern u8 town_scene_record_handlers[];
extern s32 town_player_target_adjustment;

/* Initializes the global object and resets its state pointers and flag. */
void initialize_global_player_object(void)
{
    void *object;
    void *object_header;
    s32 init_value;

    object = scene_object_payload_alias;
    object_header = (u8 *)object - 0x20;
    init_value = *(s32 *)((u8 *)object_header + 0xC);
    clear_entity_record_fields(*(s32 *)((u8 *)object_header + 8));
    call_the_handler_selects_nonzero_entry(town_scene_record_handlers, object, init_value);
    town_player_target_adjustment = 0;
    *(void **)scene_object_payload_alias = D_80097D2C;
    *(void **)((u8 *)object + 4) = D_8009ACFC;
}
