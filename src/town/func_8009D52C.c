#include "common.h"

extern void initialize_scene_action_record(void *buffer, s32 header_value08, s32 header_value0C);
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(s32 record);

extern u8 D_800834B8[];
extern u8 D_800D0078[];

// Processes D_800834B8 using the parameters stored in its preceding header.
void initialize_player_object_data(void) {
    void *dataBuffer;
    void *bufferHeader;
    s32 headerValue0C;
    s32 headerValue08;

    dataBuffer = D_800834B8;
    bufferHeader = (s8 *)dataBuffer - 0x20;
    headerValue08 = *(s32 *)((s8 *)bufferHeader + 8);
    headerValue0C = *(s32 *)((s8 *)bufferHeader + 0xC);
    clear_entity_record_fields(headerValue08);
    call_the_handler_selects_nonzero_entry(D_800D0078, dataBuffer, headerValue0C);
    initialize_scene_action_record(dataBuffer, headerValue08, headerValue0C);
}
