#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "dungeon/monster/golem.h"
#include "sdk/libc.h"

#ifndef NULL
#define NULL 0
#endif

typedef RandomizedOffsetVector Copy24;

extern void *allocate_list_node(s32, s32);
extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);

extern u8 D_80175018;

   /* copy in create_randomized_offset_object */

/* Creates an object with randomized initial state and source-derived offsets. */
void *create_randomized_offset_object(ActorRecord *allocation_param, Copy24 *initial_data, SpriteFrameState *sprite)
{
    GteOffset delta;
    s32 random_value;
    ObjectNodeHeader *object;
    RandomizedOffsetObjectBody *work;
    SpriteFrameState *node;
    SpriteFrameState *source;
    Copy24 *copy;

    object = allocate_list_node(0x312, (s32)&((ObjectNodeHeader *)allocation_param - 1)->next);
    if (object != NULL) {
        object->update_callback = &D_80175018;
        register_node(object, project_sprite_chain);
        work = NODE_BODY(object);

        random_value = rand();
        work->unk_06.s = (s16)(random_value % 0x1000);

        random_value = rand();
        work->unk_08.s = (s16)(random_value % 0x1000);

        work->unk_40 = allocation_param;
        work->unk_44 = initial_data;
        work->unk_48 = sprite;
        work->unk_4C = allocation_param;

        node = object->sprite;
        node->animation_resource = sprite->animation_resource;
        node->color.c.b = 0x80;
        node->color.c.g = 0x80;
        node->color.c.r = 0x80;
        node->scale_y = 0x1000;
        node->scale_x = 0x1000;
        node->flags |= 0xC;
        node->tpage_abr |= 0x20;
        select_sprite_entry(node, 0x3F, 0);

        copy = *(Copy24 * *)&object->position;
        *copy = *initial_data;

        delta.distance[2] = 0;
        delta.distance[1] = 0;
        delta.distance[0] = 0;
        source = work->unk_48;
        if (resolve_record_orientation_or_fallback(source->source, source, &delta.orientation, 3) != 0) {
            ((MovingPosition *)copy)->x += delta.distance[0];
            ((MovingPosition *)copy)->y += delta.distance[1];
            ((MovingPosition *)copy)->z += delta.distance[2];
            work->unk_0A = delta.distance[0];
            work->unk_0C = delta.distance[1];
            work->unk_0E.u = delta.distance[2];
        } else {
            work->unk_0A = 0;
            work->unk_0C = 0;
            work->unk_0E.s = -0x40;
        }
        return object;
    }
    return NULL;
}
