#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad[0x1A];
    u16 value;
} S_81978140_inner;

typedef struct {
    S_81978140_inner *inner;
    u8 pad04[0x30];
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
    u16 state;
    s16 timer;
} S_81978140;

extern void func_800257B8(void);

/* Advance the entity timers and dispatch its movement and state updates. */
void func_81978140(S_81978140 *entity)
{
    S_81978140_inner *inner;
    u16 timer;
    s32 state;

    inner = entity->inner;
    inner->value++;
    timer = (u16)entity->timer;
    state = (s16)entity->state;
    timer++;
    entity->timer = timer;
    switch (state) {
    case 0:
        func_800257B8();
        func_800257B8();
        (*(u16 *)&D_800814A8->facing) -= 0x200;
        if ((s16)entity->timer < 8) {
            break;
        }
        {
            u16 next_state = entity->state;
            entity->timer = 0;
            next_state++;
            entity->state = next_state;
        }
        break;

    case 1:
        func_800257B8();
        func_800257B8();
        entity->x += entity->dx;
        entity->y += entity->dy;
        entity->z += entity->dz;
        if ((s16)entity->timer < 12) {
            break;
        }
        {
            u16 next_state = entity->state;
            entity->timer = 0;
            next_state++;
            entity->state = next_state;
        }
        break;

    case 2:
        func_800257B8();
        func_800257B8();
        if ((s16)entity->timer < 4) {
            break;
        }
        {
            u16 next_state = entity->state;
            entity->timer = 0;
            next_state++;
            entity->state = next_state;
        }
        break;

    case 3:
        if ((s16)entity->timer < 8) {
            break;
        }
            {
            u16 next_state = entity->state;
            entity->timer = 0;
            next_state++;
            entity->state = next_state;
        }
        break;

    case 4:
        entity[-1].timer |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;
    }
}
