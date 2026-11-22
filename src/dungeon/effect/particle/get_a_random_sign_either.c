#include "engine/node/registration.h"
/* Linked particle creation with jittered coordinates, color, and lifetime settings. */
#include "shared/object_node.h"
#include "dungeon/effect/particle/get_a_random_sign_either.h"
#include "shared/object_flags.h"
#include "dungeon/effect/particle.h"
#include "dungeon/effect/mesh_callbacks_api.h"


/* Maps a random low bit to either -1 or 1. */
s32 random_sign(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}

void lift_particle_above_terrain_and_age(ParticleWork *work, ObjectPosition *position) {
    rectangle_effect_updated = 1;
    if (position->z.w.i < (s16)sample_terrain_surface_height((u16)position->x.w.i, (u16)position->y.w.i, (s16)((u16)position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }
    work->lifetime = (u16)work->lifetime - 8;
    if (work->lifetime <= 0) {
        *(u16 *)((u8 *)work - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a linked particle at a jittered source offset with the supplied age, color, and lifetime. */
void spawn_linked_effect_particle(ObjectNodeHeader *owner, s32 age, s32 color, s32 lifetime, s16 dx, s16 dy, s16 dz) {
    ObjectNodeHeader *node = allocate_list_node(0x211, owner);
    NewParticleWork *work;
    if (node != 0) {
        node->update_callback = lift_particle_above_terrain_and_age;
        /* BYTES: The X source integer half is read by lhu. */
        (*(ParticleVector * *)&node->position)->x = owner->position->x.unsigned_parts.integer + (rand() & 31) + (dx - 16);
        /* BYTES: The Y source integer half is read by lhu. */
        (*(ParticleVector * *)&node->position)->y = owner->position->y.unsigned_parts.integer + (rand() & 31) + (dy - 16);
        /* BYTES: The Z source integer half is read by lhu. */
        (*(ParticleVector * *)&node->position)->z = owner->position->z.unsigned_parts.integer + (rand() & 31) + (dz - 16);
        work = NODE_BODY(node);
        work->age = age;
        work->lifetime = lifetime;
        register_node(node, draw_linked_brightness_points);
        work->color = color;
    }
}
