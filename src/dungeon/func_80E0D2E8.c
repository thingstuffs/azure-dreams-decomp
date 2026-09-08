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

/* Updates actor direction, callbacks, motion, and ground height. */
void func_80170AE8(Actor *input_actor, Motion *input_motion, Entity *input_entity)
{
    register Actor *actor ASM_REG("$17") = input_actor;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Motion *motion = input_motion;
    Entity *entity = input_entity;
    register Actor *subject ASM_REG("$18") = actor;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Actor *entry_actor = input_actor;
    s16 direction;
    s16 direction_index;
    s16 old_type;
    s32 height_offset;
    register u32 raw_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 height_adjust;
    ActorCallback special_callback;
    ActorCallback dispatch_callback;
    u16 entity_flags;
    s32 actor_flags;
    s16 ground;
    s32 correction;

    if (D_80083462 & 0x2000) {
        special_callback = actor->callback;
        if (special_callback == (ActorCallback)&D_80171094) {
            ASM_KEEP(entry_actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            special_callback(entry_actor, motion, entity, entry_actor);
            goto function_end;
        }
        actor->status71 &= 0x7F;
        goto function_end;
    }

    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    old_type = (s8)actor->type;
    if (func_800A9E70(actor, motion, entity, actor) != 0) {
        return;
    }

    entity_flags = entity->flags14;
    if (!(entity_flags & 0x8000)) {
        direction = ((D_80083228 + actor->angle + 0x100) >> 9) & 7;
        direction_index = direction;

        if (actor->direction94 != direction) {
            if (entity->data != 0) {
                func_80047738(entity, entity->data[direction], entity->kind);
            }
            actor->direction94 = direction;
        }

        {
            u16 updated_flags;

            if (entity->data == D_80176490 && D_8006CCF8[direction_index] != 0) {
                updated_flags = entity->flags14 | 1;
                goto store_entity_flags;
            }
            updated_flags = entity->flags14 & 0xFFFE;

store_entity_flags:
            entity->flags14 = updated_flags;
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
        if (entity_flags & 0x0800) {
            entity->flags14 = entity_flags & 0x8FFF;
        } else {
            entity->flags14 = entity_flags | 0x7000;
        }
    }

callback_dispatch:
    dispatch_callback = actor->callback;
    if (dispatch_callback != 0) {
        dispatch_callback(actor, motion, entity, subject);
    }
    D_801766B8[actor->dispatch9A](actor, motion, entity, subject);

    if (old_type != (s8)subject->type) {
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
        actor_flags = subject->flags;
        actor_flags &= 0xF7FFFFFF;
        subject->flags = actor_flags;
        actor_flags &= 0x00040000;
        if (actor_flags) {
            if (!(entity->flags14 & 0x40) && entity->data == D_80176460) {
                u16 correction_count = actor->correctionCountAC;
                actor->correctionCountAC = correction_count + 1;
                actor->correctionA4 += func_800644B8((s16)correction_count * 0xAA) << 5;
            }
            if (!(actor->state98 & 8)) {
                height_adjust = -0x18;
                height_offset = *(s16 *)((u8 *)actor + 0x92);
                raw_height = *(volatile u16 *)((u8 *)actor + 0x92);
                if (height_adjust < height_offset) {
                    height_adjust = raw_height - 8;
                    *(s16 *)((u8 *)actor + 0x92) = height_adjust;
                    goto final_collision;
                }
                goto adjust_height;
            }
            goto final_collision;
        }
        goto ground_reset;
    }

    actor_flags = subject->flags;
    actor_flags &= 0xF7FFFFFF;
    subject->flags = actor_flags;
    actor_flags &= 0x00040000;
    if (!actor_flags) {
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
        u16 correction_count = actor->correctionCountAC;
        actor->correctionCountAC = correction_count + 1;
        actor->correctionA4 += func_800644B8((s16)correction_count * 0xAA) << 5;
    }
    if (!(actor->state98 & 8)) {
        height_adjust = -0x18;
        height_offset = *(s16 *)((u8 *)actor + 0x92);
        raw_height = *(volatile u16 *)((u8 *)actor + 0x92);
        if (height_adjust < height_offset) {
            height_adjust = raw_height - 8;
            *(s16 *)((u8 *)actor + 0x92) = height_adjust;
        } else {
adjust_height:
            height_adjust = height_offset < -0x20;
            if (height_adjust) {
                height_adjust = raw_height + 8;
                *(s16 *)((u8 *)actor + 0x92) = height_adjust;
            }
        }
    }

final_collision:
    actor_flags = subject->flags;
    if (actor_flags & 0x40000000) {
        subject->flags = actor_flags & 0xBFFFFFFF;
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
