#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "engine/graphics.h"

   /* dst in create_offset_actor_object */

typedef struct {
    s32 w[6];
} Block24;



extern u8 golem_object_callback[9];

/* Creates and initializes an object, copies its data, and applies queried offsets. */
void * create_offset_actor_object(void *unused, ObjectPosition *source_data, SpriteFrameState *source_state)
{
    GteOffset offsets;
    ObjectNodeHeader *object;
    ObjectPosition *object_data;
    SpriteFrameState *primitive;

    object = allocate_flagged_object_node(0x312);
    if (object != 0) {
        object->update_callback = golem_object_callback;
        register_node(object, project_sprite_chain);

        primitive = object->sprite;
        primitive->animation_resource = source_state->animation_resource;
        primitive->color.c.b = 0x80;
        primitive->color.c.g = 0x80;
        primitive->color.c.r = 0x80;
        primitive->scale_y = 0x1000;
        primitive->scale_x = 0x1000;
        primitive->depth_bias = 1;
        primitive->flags |= 0xC;
        primitive->tpage_abr |= 0x20;
        select_sprite_entry(primitive, 0x37, 0);

        object_data = object->position;
        *(Block24 *)object_data = *(Block24 *)source_data;

        offsets.distance[2] = 0;
        offsets.distance[1] = 0;
        offsets.distance[0] = 0;
        if (resolve_record_orientation_or_fallback(source_state->source, source_state, &offsets.orientation, 0) != 0) {
            object_data->x.w.i = (u16)object_data->x.w.i + (offsets.distance[0]);
            object_data->y.w.i = (u16)object_data->y.w.i + (offsets.distance[1]);
            object_data->z.w.i = (u16)object_data->z.w.i + (offsets.distance[2]);
        }
        return object;
    }
    return 0;
}
