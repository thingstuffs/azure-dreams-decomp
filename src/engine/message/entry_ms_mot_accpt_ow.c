#include "common.h"
#include "shared/object_index_slots.h"
#include "town/player/record.h"
#include "shared/town_object.h"

#include "engine/message.h"
#include "shared/object_node.h"

extern u8 message_motion_type_a[];
extern u8 message_motion_type_b[];

/* Activates an unused entry and stores its pair of values according to the block type. */
s32 accept_message_motion_request(s32 entry_value, s32 first_value, s32 second_value, s32 packed_index) {
    ObjectIndexSlot *entries = object_index_slots;
    u8 entry_index = packed_index;
    ObjectIndexSlot *entry = entries + entry_index;
    void *block;
    ObjectNodeHeader *header;
    void *type;

    if (entry->active == 0) {
        if (entry_index != 0) {
            block = ms_mot_accpt_ow(entry_index);
            if (block != 0) {
                header = NODE_HEADER(block);
                entry->motion_id = packed_index >> 8;
                entry->active = 1;
                entry->motion_param = entry_value;

                if (entry_index == 1 &&
                    (type = header->update_callback) != message_motion_type_a &&
                    type != message_motion_type_b) {
                    TownPlayerRecord *player = block;
                    player->target_x = first_value;
                    player->target_y = second_value;
                } else {
                    TownObjectRecord *person = block;
                    person->target_x = first_value;
                    person->target_y = second_value;
                }
            }
        }
        return 1;
    }
    return 0;
}
