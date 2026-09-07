#include "common.h"

typedef struct Actor Actor;
typedef struct Motion Motion;
typedef struct Entity Entity;
typedef void (*ActorCallback)(Actor *, Motion *, Entity *, Actor *);

struct Actor {
    u8 pad00[0x1C];
    s32 flags;
    u8 pad20[0x0A];
    s16 angle;
    u8 pad2C[0x41];
    u8 type;
    u8 pad6E[3];
    u8 status71;
    u8 pad72[0x16];
    u16 height88;
    u8 pad8A[2];
    ActorCallback callback;
    s32 position90;
    s16 direction94;
    u8 pad96[2];
    u16 state98;
    u8 dispatch9A;
    u8 pad9B[2];
    u8 counter9D;
    u8 pad9E[6];
    s32 correctionA4;
    u8 padA8[4];
    u16 correctionCountAC;
};

struct Motion {
    s32 x;
    s32 y;
    u8 pad08[2];
    s16 height0A;
    s32 dx;
    s32 dy;
    s32 dz;
};

struct Entity {
    u8 pad00[4];
    s8 kind;
    u8 pad05[7];
    u8 position0C[8];
    u16 flags14;
    u8 pad16[0x0E];
    u8 tileX;
    u8 tileY;
    u8 pad26[6];
    u8 *data;
};

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80171094;
extern u8 D_80176460[8];
extern u8 D_80176490[8];
extern ActorCallback D_801766B8[];

extern void func_80047738(Entity *, u8, s8);
extern void func_800478B8(Entity *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(Actor *, Motion *, Entity *, Actor *);
extern void func_800AA36C(Actor *, Motion *, Entity *, Actor *);
extern s32 func_800BCB04(s32, s32, s16);

void func_80170AE8(Actor *arg0, Motion *arg1, Entity *arg2)
{
    register Actor *actor ASM_REG("$17") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    Motion *motion = arg1;
    Entity *entity = arg2;
    register Actor *subject ASM_REG("$18") = actor;   /* MATCH pin: load-bearing for the whole function shape */
    register Actor *entryArg0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s16 direction;
    s16 tableIndex;
    s16 oldType;
    s32 velocity;
    register u32 rawVelocity ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 velocityLimit;
    ActorCallback firstCallback;
    ActorCallback dispatchCallback;
    u16 entityFlags;
    s32 actorFlags;
    s16 ground;
    s32 correction;

    if (D_80083462 & 0x2000) {
        firstCallback = actor->callback;
        if (firstCallback == (ActorCallback)&D_80171094) {
            ASM_KEEP(entryArg0);   /* MATCH pin: retail register colouring depends on it */
            firstCallback(entryArg0, motion, entity, entryArg0);
            goto function_end;
        }
        actor->status71 &= 0x7F;
        goto function_end;
    }

    ASM_KEEP(actor);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */

    oldType = (s8)actor->type;
    if (func_800A9E70(actor, motion, entity, actor) != 0) {
        return;
    }

    entityFlags = entity->flags14;
    if (!(entityFlags & 0x8000)) {
        direction = ((D_80083228 + actor->angle + 0x100) >> 9) & 7;
        tableIndex = direction;

        if (actor->direction94 != direction) {
            if (entity->data != 0) {
                func_80047738(entity, entity->data[direction], entity->kind);
            }
            actor->direction94 = direction;
        }

        {
            u16 continuationFlags;

            if (entity->data == D_80176490 && D_8006CCF8[tableIndex] != 0) {
            continuationFlags = entity->flags14 | 1;
                goto store_entity_flags;
            }
            continuationFlags = entity->flags14 & 0xFFFE;

store_entity_flags:
            entity->flags14 = continuationFlags;
        }
        func_800A020C(subject->flags, entity->position0C);
        if (!(subject->flags & 0x20)) {
            if (!(entity->flags14 & 0x40)) {
                func_800478B8(entity);
                goto callback_dispatch;
            }
            goto callback_dispatch;
        } else {
            entity->flags14 |= 0x7000;
            subject->flags &= 0xFFFBFFFF;
            goto callback_dispatch;
        }
    } else {
        if (entityFlags & 0x0800) {
            entity->flags14 = entityFlags & 0x8FFF;
        } else {
            entity->flags14 = entityFlags | 0x7000;
        }
    }

callback_dispatch:
    dispatchCallback = actor->callback;
    if (dispatchCallback != 0) {
        dispatchCallback(actor, motion, entity, subject);
    }
    D_801766B8[actor->dispatch9A](actor, motion, entity, subject);

    if (oldType != (s8)subject->type) {
        func_800AA36C(actor, motion, entity, subject);
    }

    motion->x += motion->dx;
    motion->y += motion->dy;

    if (!(subject->flags & 0x00040000) && !(actor->state98 & 8)) {
        motion->dz += (s8)actor->counter9D * 0x14000;
        actor->counter9D++;
        goto counter_join;
    }
    actor->counter9D = 0;

counter_join:
    actor->position90 += motion->dz;

    if (!(entity->flags14 & 0x8000)) {
        actorFlags = subject->flags;
        actorFlags &= 0xF7FFFFFF;
        subject->flags = actorFlags;
        actorFlags &= 0x00040000;
        if (actorFlags) {
            if (!(entity->flags14 & 0x40) && entity->data == D_80176460) {
                u16 count = actor->correctionCountAC;
                actor->correctionCountAC = count + 1;
                actor->correctionA4 += func_800644B8((s16)count * 0xAA) << 5;
            }
            if (!(actor->state98 & 8)) {
                velocityLimit = -0x18;
                velocity = *(s16 *)((u8 *)actor + 0x92);
                rawVelocity = *(volatile u16 *)((u8 *)actor + 0x92);
                if (velocityLimit < velocity) {
                    velocityLimit = rawVelocity - 8;
                    *(s16 *)((u8 *)actor + 0x92) = velocityLimit;
                    goto final_collision;
                }
                goto adjust_velocity;
            }
            goto final_collision;
        }
        goto ground_reset;
    }

    actorFlags = subject->flags;
    actorFlags &= 0xF7FFFFFF;
    subject->flags = actorFlags;
    actorFlags &= 0x00040000;
    if (!actorFlags) {
ground_reset:
        correction = actor->correctionA4;
        actor->correctionCountAC = 0;
        actor->correctionA4 = 0;
        actor->position90 -= correction;
        if (!(actor->state98 & 8)) {
            ground = (s16)(func_800BCB04(
                *(u16 *)((u8 *)motion + 2),
                *(u16 *)((u8 *)motion + 6),
                (s16)(subject->height88 - 0x20)) - subject->height88);
            if (ground < *(s16 *)((u8 *)actor + 0x92)) {
                *(s16 *)((u8 *)actor + 0x92) = ground;
                actor->counter9D = 0;
                motion->dz = 0;
                subject->flags |= 0x08000000;
                goto final_collision;
            }
        }
        goto final_collision;
    }

    if (!(entity->flags14 & 0x40) && entity->data == D_80176460) {
        u16 count = actor->correctionCountAC;
        actor->correctionCountAC = count + 1;
        actor->correctionA4 += func_800644B8((s16)count * 0xAA) << 5;
    }
    if (!(actor->state98 & 8)) {
        velocityLimit = -0x18;
        velocity = *(s16 *)((u8 *)actor + 0x92);
        rawVelocity = *(volatile u16 *)((u8 *)actor + 0x92);
        if (velocityLimit < velocity) {
            velocityLimit = rawVelocity - 8;
            *(s16 *)((u8 *)actor + 0x92) = velocityLimit;
        } else {
adjust_velocity:
            velocityLimit = velocity < -0x20;
            if (velocityLimit) {
                velocityLimit = rawVelocity + 8;
                *(s16 *)((u8 *)actor + 0x92) = velocityLimit;
            }
        }
    }

final_collision:
    actorFlags = subject->flags;
    if (actorFlags & 0x40000000) {
        subject->flags = actorFlags & 0xBFFFFFFF;
        ground = func_800BCB04((entity->tileX << 6) | 0x20,
                               (entity->tileY << 6) | 0x20,
                               (s16)(subject->height88 - 0x20));
        if (ground < 0x200) {
            *(s16 *)((u8 *)actor + 0x92) += subject->height88 - ground;
            subject->height88 = ground;
        }
    }

    motion->height0A = subject->height88 +
                       *(u16 *)((u8 *)actor + 0x92) -
                       *(u16 *)((u8 *)actor + 0xA6);
    entity->flags14 |= 0x40;

function_end:
    return;
}
