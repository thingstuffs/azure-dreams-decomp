#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect/sprite.h"
#include "engine/node.h"

extern u8 D_800D7A78[];

// Creates an object, assigns its data and payload, and increments the object count.
void create_radial_effect_controller(s32 objectPayload) {
    ObjectNodeHeader *newObject;

    newObject = allocate_list_node(2, &scene_object_list_anchor.next);
    if (newObject != 0) {
        g_dungeon_status.activity_counts.parts.pending_action_count += 1;
        newObject->update_callback = D_800D7A78;
        *(s32 *)((u8 *)newObject + 0x2C) = objectPayload;
    }
}
