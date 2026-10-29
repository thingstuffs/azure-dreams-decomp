#include "common.h"
#include "shared/object_node.h"
#include "engine/node/allocation.h"
#include "dungeon/item/state.h"

extern s32 D_800C4E00[4];

/* Creates an object with the D_800C4E00 table and initializes its payload fields. */
void *create_timed_region_flag_expiry(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC) {
    ObjectNodeHeader *object;
    void *payload;

    object = allocate_list_node(0, &scene_object_list_anchor.next);
    if (object != 0) {
        object->update_callback = &D_800C4E00[0];
        payload = (s8 *)object + 0x20;
        *(s16 *)((s8 *)payload + 8) = 0x40;
        *(s16 *)((s8 *)payload + 0xA) = payloadValueA;
        *(s16 *)((s8 *)payload + 0xC) = payloadValueC;
    }
    return object;
}
