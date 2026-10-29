#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"

#ifndef NULL
#define NULL 0
#endif

   /* the 0x2 bytes before self in spawn_short_lived_objects_around_origin, addressed as self[-1] */

typedef struct {
    s32 word[6];
} Copy24;

typedef struct {
    u8 pad00[4];
    void *word;
} Resource;

typedef struct {
    Resource *resource;
    s8 x;
    s8 y;
    u8 pad06[2];
    s32 resource_word;
    s32 color;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    s16 scale_y;
    s16 scale_x;
} Primitive;

typedef struct {
    u8 pad00[8];
    Copy24 *position;
    Primitive *primitive;
    u8 *callback;
} Object;

typedef struct {
    u8 pad00[0x48];
    s16 lifetime;
} Motion;

typedef struct {
    u8 pad00[0x48];
    u16 timer;
    s16 count;
} Self;


#include "engine/node.h"
#include "sdk/libc.h"

extern u8 D_800BBA98[];
extern Resource D_800F162C[];

/* Spawn short-lived objects around the origin and set expiry flags when the timer ends. */
void spawn_short_lived_objects_around_origin(Self *self, Copy24 *origin) {
    s32 remaining = self->count;

    if (remaining >= 0) {
        u8 *callback = D_800BBA98;
        Resource *resource;

        do {
            ObjectNodeHeader *object = allocate_list_node(0x312, &scene_object_list_anchor.next);

            if (object != NULL) {
                SpriteFrameState *primitive;

                object->update_callback = callback;
                register_node(object, project_sprite_chain);
                primitive = object->sprite;
                **(Copy24 * *)&object->position = *origin;

                (*(Copy24 * *)&object->position)->word[0] +=
                    ((rand() % 255) - 0x80) * 0x40000;
                (*(Copy24 * *)&object->position)->word[1] +=
                    ((rand() % 255) - 0x80) * 0x40000;

                primitive->scale_y = 0x1000;
                primitive->scale_x = 0x1000;
                object = (void *)((u8 *)object + 0x20);
                if (origin->word[3] < 0) {
                    primitive->flags |= 1;
                }
                resource = D_800F162C;
                primitive->unk_00 = resource;
                primitive->source = resource->word;
                primitive->unk_04 = 0;
                primitive->frame_ticks = 0;
                primitive->color.word = 0x808080;
                ((Motion *)object)->lifetime = 10;
            }
            remaining--;
        } while (remaining >= 0);
    }

    {
        u16 timer = self->timer - 1;

        self->timer = timer;
        if ((s16)timer <= 0) {
            ((ObjectRetirementFlags *)self)[-1].flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
