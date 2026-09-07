#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 pad_C;
    s32 pad_10;
    s32 velocity_z;
} ObjectState;

typedef struct {
    u8 pad_00[0x50];
    void *callback;
} Owner;

extern s32 D_800D636C[2];
extern u8 D_800C8C3C[];
extern void func_80095388(ObjectState *, s32);

void func_800C8BB4(Owner *owner, ObjectState *state)
{
    s32 *velocity;
    s32 velocity_z;

    velocity = D_800D636C;
    velocity_z = state->velocity_z;
    state->x += velocity[0];
    state->y += velocity[1];
    state->z += velocity_z;
    func_80095388(state, velocity_z);
    if (state->velocity_z >= 0) {
        owner->callback = D_800C8C3C;
    }
}

/* MECHANISM: The three component updates are expressed in record order (x, y, z).
   The named velocity base and velocity_z local expose the page lifetime and call arg. */
