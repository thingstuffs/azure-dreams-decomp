#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/sprite/linked_object_chain.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "engine/scene.h"

#ifndef NULL
#define NULL 0
#endif

   /* header in create_linked_object_chain */

   /* node in create_linked_object_chain */



extern void func_80025B5C();

extern u8 D_80028268[];
extern int D_800814A0;

/* Create 18 linked objects at the given position and angle, marking them for cleanup on failure. */
void *create_linked_object_chain(s16 x, s16 y, s16 z, s16 angle)
{
    ObjectNodeHeader *objects[18];
    s32 i;
    ObjectPosition *position;
    SpriteFrameState *node;
    LinkedObjectChainBody *object_state;
    ObjectNodeHeader *obj;

    if (has_enough_available_runtime_nodes(18) == 0) {
        return NULL;
    }
    for (i = 0; i < 18; i++) {
        objects[i] = allocate_list_node(18, (i != 0) ? objects[0] : (void *)&scene_object_list_anchor);
        if (objects[i] != NULL) {
            objects[i]->update_callback = update_linked_object_chain;
            position = objects[i]->position;
            position->x.w.i = x;
            position->y.w.i = y;
            position->z.w.i = z;
            node = objects[i]->sprite;
            node->angle_x = 0x400;
            node->angle_z = angle + 0x400;
            node->offset_x = 0x1000;
            node->scale_y = 0x1000;
            node->scale_x = 0x1000;
            node->source = &D_80028268[i * 16];
            node->tpage_abr = 0x20;
            node->flags |= 0xC;
            object_state = NODE_BODY(objects[i]);
            if (i != 0) {
                object_state->head = objects[0];
            }
            object_state->unk_30 = 0x10;
            object_state->unk_34 = angle;
            object_state->unk_36 = 7;
        } else {
            for (i--; i >= 0; i--) {
                obj = objects[i];
                D_800814A0 |= OBJECT_REMOVE_PENDING;
                obj->flags |= 0x8000;
            }
            return NULL;
        }
    }
    func_80025B5C(objects[0], angle);
    return objects[0];
}
