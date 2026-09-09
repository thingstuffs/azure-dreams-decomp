#include "common.h"

typedef struct EntityInner {
    u8 pad0[8];
    void *coords;
    void *actor;
} EntityInner;

typedef struct Entity {
    u8 pad0[8];
    EntityInner *inner;
    u8 padC[0x18];
    u16 x;
    u16 y;
    s16 z;
    u16 pad2A;
    s16 state;
    s16 active;
} Entity;

typedef struct Position {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Position;

typedef struct Motion {
    u8 pad0[12];
    u32 value;
} Motion;

extern u16 D_800269F8;
extern u8 D_80045340[];
extern u32 D_800814A0;
extern u8 *D_80027C98[];

extern s32 func_80025F54(s16, s16, s16, s16);
extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern void func_8004491C(void *, void *, void *);

/* Initialize the entity's position and advance its motion state through completion. */
void func_8002432C(Entity *entity, Position *position, Motion *motion)
{
    s16 state;
    void *actor;
    u16 *base_coords;

    D_800269F8++;
    state = entity->state;

    if (state == 0) {
        actor = entity->inner->actor;
        if (entity->active == 0) {
            if (func_8003DE58(*(s32 *)((u8 *)actor + 8), actor,
                              &entity->x, 0) != 0) {
                entity->active = 1;
            } else if (*(u16 *)((u8 *)actor + 0x14) & 0x8000) {
                entity->active = 1;
                entity->z = -0x40;
            }
            if (entity->active == 0) {
                return;
            }
        }

        base_coords = entity->inner->coords;
        position->x = base_coords[1] + entity->x;
        position->y = base_coords[3] + entity->y;
        position->z = base_coords[5] + entity->z;
        func_8004491C((u8 *)entity - 0x20, D_80045340, base_coords);
        goto advance_state;
    }

    if (state == 1) {
        if ((u8)motion->value < 0xC0) {
            motion->value += 0x00202020;
            return;
        }
        if (func_80025F54(position->x, position->y, position->z,
                          *(s16 *)(D_80027C98[0] + 0x2A)) != 0) {
advance_state:
            entity->state++;
            return;
        }
        return;
    }

    if (state == 2) {
        motion->value += 0xFFFBFBFC;
        if ((u8)motion->value == 0) {
            *(u16 *)((u8 *)entity - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
