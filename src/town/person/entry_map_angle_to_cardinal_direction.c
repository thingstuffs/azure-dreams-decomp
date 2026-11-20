#include "engine/message/data.h"
#include "engine/message.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/town_object.h"
#include "town/player/record.h"
#include "shared/object_index_slots.h"
#include "town/person/person_object_lifecycle_g00659.h"

extern s32 map_angle_to_cardinal_direction(s32, void *); /* This call also passes the selected body in a1. */

/* anyone_now_ang_get: store the selected object's current angle in the script result. */
void anyone_now_ang_get(s32 object_slot) {
    ScriptController *controller = &runtime_script_state;
    ObjectNodeHeader *entry;
    u8 *data;
    u16 angle;

    if (object_slot != 0) {
        entry = object_index_slots[object_slot].object;
        if (entry != 0) {
            data = NODE_BODY(entry);
            if (object_slot == 1 && entry->update_callback != update_object_position_or_cleanup &&
                entry->update_callback != update_object_motion_and_flags) {
                angle = ((TownPlayerRecord *)data)->unk_10;
            } else {
                angle = ((TownObjectRecord *)data)->heading;
            }
            controller->variables[0] = map_angle_to_cardinal_direction((s16)angle, data);
        }
    }
}
