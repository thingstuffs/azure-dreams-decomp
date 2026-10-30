#include "common.h"
#include "shared/sprite_source.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "engine/runtime.h"
#include "sdk/libc.h"
#include "town/map.h"


typedef struct S_800BBCA0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800BBCA0_2;   /* origin in spawn_burst_particles_around_origin */

typedef struct S_800BBCA0_3 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800BBCA0_3;   /* motion in spawn_burst_particles_around_origin */

extern u8 D_800BC00C[];
extern u8 D_800F1654[];

/* Spawns particles around the origin, emits a burst, then marks the effect finished. */
void spawn_burst_particles_around_origin(BurstParticleSpawnerObject *self, ObjectPosition *origin)
{
    register u16 next_state;
    s32 state;
    u16 timer;
    s32 spawn_count;
    s32 rand_value;
    ObjectNodeHeader *object;
    SpriteFrameState *sprite;
    S_800BBCA0_3 *motion;
    s32 *position;
    s32 *velocity;

    timer = self->timer - 1;
    state = self->state.s;
    self->timer = timer;
    switch (state) {
    case 0:
        spawn_count = 7;
    {
        u8 *object_type;
        u8 *sprite_type;
        object_type = D_800BC00C;
        sprite_type = D_800F1654;
        do {
            object = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (object != 0) {
                object->update_callback = object_type;
                register_node(object, project_sprite_chain);
                sprite = object->sprite;
                motion = (S_800BBCA0_3 *)(((u8 *)object) + 0x20);

                rand_value = rand();
                position = *(s32 * *)&object->position;
                position[0] = origin->x.v + (((rand_value & 0x1FF) - 0x100) << 13);
                rand_value = rand();
                position = *(s32 * *)&object->position;
                position[1] = origin->y.v + (((rand_value & 0x1FF) - 0x100) << 13);
                rand_value = rand();
                position = *(s32 * *)&object->position;
                position[2] = origin->z.v + (((rand_value & 0x1FF) - 0x100) << 13);

                motion->unk_0C = ((S_800BBCA0_2 *)origin)->unk_00.at02.v;
                motion->unk_0E = ((S_800BBCA0_2 *)origin)->unk_04.at02.v;
                motion->unk_10 = ((S_800BBCA0_2 *)origin)->unk_08.at02.v;
                sprite->scale_y = 0x100;
                sprite->scale_x = 0x100;
                sprite->tpage_abr = 0x20;
                sprite->flags |= 0xC;
                motion->unk_48 = 6;
                sprite->unk_00 = sprite_type;
                sprite->source = ((SpriteSourceEntry *)sprite_type)->source;
                sprite->unk_04 = 0;
                sprite->frame_ticks = 0;
                sprite->color.word = 0x101010;
            }
            spawn_count--;
        } while (spawn_count >= 0);
        if (test_resident_bit(0x97) != 0) {
            next_state = self->state.u + 1;
            self->state.u = next_state;
            return;
        }
        return;

    }
    case 1:
    {
        u8 *object_type;
        u8 *sprite_type;
        spawn_count = 0x64;
        object_type = D_800BC00C;
        sprite_type = D_800F1654;
        do {
            object = allocate_list_node(0x312, &scene_object_list_anchor.next);
            motion = (S_800BBCA0_3 *)(((u8 *)object) + 0x20);
            if (object != 0) {
                object->update_callback = object_type;
                register_node(object, project_sprite_chain);
                sprite = object->sprite;

                rand_value = rand();
                position = *(s32 * *)&object->position;
                position[0] = origin->x.v + (((rand_value & 0x1FF) - 0x100) << 10);
                rand_value = rand();
                position = *(s32 * *)&object->position;
                position[1] = origin->y.v + (((rand_value & 0x1FF) - 0x100) << 10);
                rand_value = rand();
                position = *(s32 * *)&object->position;
                position[2] = origin->z.v + (((rand_value & 0x1FF) - 0x100) << 10);
                rand_value = rand();
                velocity = *(s32 * *)&object->position;
                velocity[3] = ((rand_value & 0x1FF) - 0x100) << 14;
                rand_value = rand();
                velocity = *(s32 * *)&object->position;
                velocity[4] = ((rand_value & 0x1FF) - 0x100) << 14;
                rand_value = rand();
                velocity = *(s32 * *)&object->position;
                velocity[5] = ((rand_value & 0x1FF) - 0x100) << 12;

                sprite->scale_y = 0x200;
                sprite->scale_x = 0x200;
                sprite->tpage_abr = 0x20;
                sprite->flags |= 0xC;
                motion->unk_48 = 0xF;
                motion->unk_4C = 1;
                sprite->unk_00 = sprite_type;
                sprite->source = ((SpriteSourceEntry *)sprite_type)->source;
                sprite->unk_04 = 0;
                sprite->frame_ticks = 0;
                sprite->color.word = 0x808080;
            }
            spawn_count--;
        } while (spawn_count >= 0);
        next_state = self->state.u + 1;
        self->timer = 0x10;
        self->state.u = next_state;
        return;

    }
    case 2:
    if ((s16)timer < 0) {
        (*(u16 *)((u8 *)self + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    return;
    default:
        return;
    }
}
