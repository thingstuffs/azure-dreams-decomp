#include "common.h"
#include "engine/scene/scene_load.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/graphics.h"
#include "engine/scene.h"

extern int D_800814A0; /* global 32-bit "used"/flags word */

/* Propagates the second entity's 0x2000 flag and marks the record and global flags after scene_load_variant_texture_set. */
void propagate_scene_flag(SceneLoadBody *record)
{
    ObjectNodeHeader *entity;

    if (record->task->flags & 0x2000) {
        scene_load_variant_texture_set();
        entity = record->parent;
        entity->flags |= 0x2000;
        *(u16 *)((u8 *)record - 2) |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
