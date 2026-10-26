#include "shared/entity_height_offsets.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80027368_2 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80027368_2;   /* arg3 in create_offset_sprite_object_with_z */

typedef struct S_80027368_4 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_80027368_4;   /* work in create_offset_sprite_object_with_z */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);

extern s32 D_80027164;
extern s32 D_80028874;

/* Creates a sprite object at the given position with a source-dependent Z offset. */
void *create_offset_sprite_object_with_z(s16 pos_x, s16 pos_y, s16 pos_z, S_80027368_2 *source)
{
    ObjectNodeHeader *object;
    ObjectPosition *part;
    SpriteFrameState *sprite;
    S_80027368_4 *work;

    object = allocate_list_node(0x12, &scene_object_list_anchor.next);
    if (object != 0) {
        object->update_callback = &D_80027164;
        register_node(object, project_sprite_chain);
        part = object->position;
        part->x.w.i = pos_x;
        part->y.w.i = pos_y;
        part->z.w.i =
            pos_z - (entity_height_offsets[source->unk_13] >> 1);
        sprite = object->sprite;
        sprite->source = &D_80028874;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        work = (u8 *)object + 0x20;
        work->unk_04 = source;
        work->unk_66 = 0x10;
    }
    return object;
}
