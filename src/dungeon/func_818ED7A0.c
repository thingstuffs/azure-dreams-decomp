#include "modules/dungeon_ovl_190d6a4.h"

void spawn_linked_effect_particle(Row_818ED7A0_ParticleNode *owner, s32 age, s32 color, s32 lifetime, s16 dx, s16 dy, s16 dz) {
    Row_818ED7A0_ParticleNode *node = func_8003FD64(0x211, owner);
    NewParticleWork *work;
    if (node != 0) {
        node->update = create_linked_effect_segments;
        node->position->x = owner->position->x + (rand() & 31) + (dx - 16);
        node->position->y = owner->position->y + (rand() & 31) + (dy - 16);
        node->position->z = owner->position->z + (rand() & 31) + (dz - 16);
        work = (NewParticleWork *)((u8 *)node + 0x20);
        work->age = age;
        work->lifetime = lifetime;
        func_8004491C(node, func_80024C54);
        work->color = color;
    }
}
