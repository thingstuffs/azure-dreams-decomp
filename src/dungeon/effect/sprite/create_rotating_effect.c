#include "dungeon/effect/sprite.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"
#include "engine/node.h"

/* Increment the dungeon count and initialize a new object's callback and rotation. */
void create_rotating_effect(void)
{
    u8 *object;

    g_dungeon_status.activity_counts.parts.pending_action_count++;
    object = allocate_list_node(2, &scene_object_list_anchor.next);
    if (object != 0) {
        ((ObjectNodeHeader *)object)->update_callback = update_effect_controller;
        object += 0x20;
        *(u16 *)(object + 4) = ((u16)view_reference_entity.x.w.i);
        *(u16 *)(object + 6) = ((u16)view_reference_entity.y.w.i);
        *(u16 *)(object + 8) = ((u16)view_reference_entity.z.w.i) - 0x30;
    }
}
