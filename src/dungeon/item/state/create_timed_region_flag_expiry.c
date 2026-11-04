#include "common.h"
#include "shared/object_node.h"
#include "engine/node/allocation.h"
#include "dungeon/item/state.h"



/* Creates an object with the D_800C4E00 table and initializes its payload fields. */
void *create_timed_region_flag_expiry(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC) {
    ObjectNodeHeader *object;
    RegionFlagExpiryBody *payload;

    object = allocate_list_node(0, &scene_object_list_anchor.next);
    if (object != 0) {
        object->update_callback = tick_region_flag_expiry;
        payload = NODE_BODY(object);
        payload->ticks_remaining = 0x40;
        payload->item_id = payloadValueA;
        payload->room_index = payloadValueC;
    }
    return object;
}
