/* Linked particle creation with jittered coordinates, color, and lifetime settings. */
#include "shared/object_node.h"
#include "dungeon/effect/particle/get_a_random_sign_either.h"
#include "shared/object_flags.h"
#include "dungeon/effect/particle.h"


/* Maps a random low bit to either -1 or 1. */
s32 get_a_random_sign_either_n_1_n_1(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}

void create_linked_effect_segments(ParticleWork *work, ParticlePosition *position) {
    *(s16 *)rectangle_effect_updated = 1;
    if (position->z.half.high < (s16)sample_terrain_surface_height(position->x, position->y, (s16)((u16)position->z.half.high + 2))) {
        position->z.word += 0x20000 + (rand() & 0xFFF);
    }
    work->lifetime = (u16)work->lifetime - 8;
    if (work->lifetime <= 0) {
        *(u16 *)((u8 *)work - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a linked particle at a jittered source offset with the supplied age, color, and lifetime. */
void spawn_linked_effect_particle(Row_818ED7A0_ParticleNode *owner, s32 age, s32 color, s32 lifetime, s16 dx, s16 dy, s16 dz) {
    ObjectNodeHeader *node = allocate_list_node(0x211, owner);
    NewParticleWork *work;
    if (node != 0) {
        node->update_callback = create_linked_effect_segments;
        (*(ParticleVector * *)&node->position)->x = owner->position->x + (rand() & 31) + (dx - 16);
        (*(ParticleVector * *)&node->position)->y = owner->position->y + (rand() & 31) + (dy - 16);
        (*(ParticleVector * *)&node->position)->z = owner->position->z + (rand() & 31) + (dz - 16);
        work = (NewParticleWork *)((u8 *)node + 0x20);
        work->age = age;
        work->lifetime = lifetime;
        register_node(node, func_80024C54);
        work->color = color;
    }
}
