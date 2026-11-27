#include "engine/message.h"
#include "shared/object_index_slots.h"
#include "town/player/record.h"
#include "shared/town_object.h"
#include "shared/object_node.h"

#include "engine/script.h"
#include "slus/data.h"

extern u8 message_motion_type_a[];

/* Opcode 0x0F: Set actor motion/expression (u8 actor, u8 motion; no motion byte for actor 0); waits while the actor is busy. */
void script_set_actor_motion(MessageWindow *window)
{
    u8 *cursor = window->cursor;
    u8 *value_ptr;
    u8 index_byte = *cursor;
    s32 entry_index;
    ObjectIndexSlot *entries;
    ObjectIndexSlot *entry;
    ScriptController *controller;
    void *object;
    ObjectNodeHeader *object_header;
    void *object_type;

    cursor++;
    window->cursor = cursor;
    entry_index = index_byte & 0xFF;
    entries = object_index_slots;
    entry = entries + entry_index;
    controller = window->controller;
    if (entry->active == 0) {
        if (entry_index == 0) {
            return;
        }

        do {
            object = ms_mot_accpt_ow(entry_index);
        } while (0);
        if (object != 0) {
            object_header = NODE_HEADER(object);
            value_ptr = window->cursor;
            entry->motion_id = *value_ptr;
            value_ptr++;
            window->cursor = value_ptr;
            entry->active = 1;
            entry->motion_param = controller->variables[0];

            if (entry_index == 1 &&
                (object_type = object_header->update_callback) != message_motion_type_a &&
                object_type != message_motion_type_b) {
                TownPlayerRecord *player = object;
                player->target_x = controller->variables[1];
                player->target_y = controller->variables[2];
                return;
            }

            {
                TownObjectRecord *person = object;
                person->target_x = controller->variables[1];
                person->target_y = controller->variables[2];
            }
        } else {
            window->message_handler = wait_message_motion_accept;
            window->entry_index = index_byte;
            window->motion_timer = 0x10;
            window->cursor -= 2;
        }
    } else {
        do {
            window->cursor = cursor - 2;
            window->entry_index = index_byte;
            window->message_handler = wait_message_entry_ready;
        } while (0);
    }
}
