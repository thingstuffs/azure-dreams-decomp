#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

   /* dst in create_offset_actor_object */

typedef struct {
    s32 w[6];
} Block24;

extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);

extern u8 golem_object_callback[9];

/* Creates and initializes an object, copies its data, and applies queried offsets. */
void * create_offset_actor_object(void *unused, void *source_data, Rec_D_80082E80 *source_state)
{
    u16 offsets[3];
    ObjectNodeHeader *object;
    ObjectPosition *object_data;
    SpriteFrameState *primitive;

    object = allocate_flagged_object_node(0x312);
    if (object != 0) {
        object->update_callback = golem_object_callback;
        register_node(object, project_sprite_chain);

        primitive = object->sprite;
        primitive->animation_resource = source_state->unk_28.at00_s32.v;
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

        offsets[2] = 0;
        offsets[1] = 0;
        offsets[0] = 0;
        if (resolve_record_orientation_or_fallback(source_state->unk_08, source_state, offsets, 0) != 0) {
            object_data->x.w.i = (u16)object_data->x.w.i + (offsets[0]);
            object_data->y.w.i = (u16)object_data->y.w.i + (offsets[1]);
            object_data->z.w.i = (u16)object_data->z.w.i + (offsets[2]);
        }
        return object;
    }
    return 0;
}
