#include "town/person_callbacks_api.h"
#include "common.h"
#include "shared/town_object.h"
#include "town/person/state_updates.h"
#include "engine/script.h"
#include "town/person.h"

extern u8 object_index_slots[9];
extern s32 town_actor_control[5];
extern TownIndexedHandler volatile D_800D5084[];



/* Dispatches the record handler or clears its pending state. */
void dispatch_record_handler(TownObjectRecord *record, struct ObjectPosition *dispatch_arg, struct SpriteFrameState *dispatch_data, int check_arg) {
    s32 slot_offset;
    TownIndexedHandler selected;
    long handler_id;
    u8 *handler_slot;
    TownIndexedHandler handler;
    TownObjectRecord *dispatch_record;
    ObjectPosition *saved_arg;

    if (service_script_controller() == 0) {
        s32 *state;

        dispatch_object_state(record, dispatch_arg, dispatch_data);
        state = town_actor_control;
        if (record == state[4]) {
            state[4] = 0;
            return;
        }
    } else {
        slot_offset = record->slot * 8;
        handler_slot = &object_index_slots[slot_offset];
        handler_id = *handler_slot;
        if ((u32) (handler_id - 2) < 0x14U) {
            selected = D_800D5084[(s8) handler_id];
            dispatch_record = record;
            handler = selected;
            saved_arg = dispatch_arg;
            goto dispatch;
        }
        if ((s8) handler_id >= 0x16) {
            unsigned long table_address;
            saved_arg = dispatch_arg;
            dispatch_record = record;
            handler_id = (s8)handler_id * sizeof(*dispatch_record->indexed_handlers);
            table_address = (unsigned long)dispatch_record->indexed_handlers;
            handler_id += table_address;
            handler = ((TownIndexedHandler *)handler_id)[-0x16];
dispatch:
            handler(dispatch_record, saved_arg, dispatch_data);
            return;
        }
        if ((s8) handler_id < 0) {
            *handler_slot = 0U;
            dispatch_object_state(record, dispatch_arg, dispatch_data);
        }
    }
}
