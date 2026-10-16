#include "common.h"
typedef struct { u16 pad0, x, pad4, y, pad8, z; } ParticleVector;
typedef struct { s32 x, y, z; } ParticleOffsets;
typedef struct ParticleNode { u8 pad0[8]; ParticleVector *position; void *sprite; void *update; } ParticleNode;
typedef struct { u8 pad0[8]; s32 color; u8 padC[8]; u16 age; u8 pad16[0x1C]; u16 lifetime; } NewParticleWork;
extern ParticleNode *func_8003FD64(s32, ParticleNode *);
extern void func_8004491C(void *, void *);
extern void func_80024ED4(void *, void *);
extern void func_80024C54(void);
extern s32 rand(void);
/* Attach a particle with randomized offsets and a finite lifetime to its owner. */
void func_80024FA0(ParticleNode *owner, s32 age, s32 color, s32 lifetime, s16 dx, s16 dy, s16 dz) {
    ParticleNode *node = func_8003FD64(0x211, owner);
    NewParticleWork *work;
    if (node != 0) {
        node->update = func_80024ED4;
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
