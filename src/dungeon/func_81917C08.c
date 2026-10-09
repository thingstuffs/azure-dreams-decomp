#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/dir_step.h"

/* Payload of the action object. The entity and motion data are separate objects. */
typedef struct ActionState {
    EntityRec *actor;
    u16 *flags;
    u8 reserved_08;
    u8 event_id;
    s16 phase;
    s16 reserved_0C;
    s16 direction;
    s16 ticks;
    s16 reserved_12;
    s16 pending;
    s16 completed_a;
    s16 completed_b;
} ActionState;

typedef struct EffectMotion {
    Fixed1616 x, y, z;
    s32 next_x, next_y, next_z;
} EffectMotion;

typedef struct EffectVisual {
    u8 reserved_00[0xC];
    u32 color;
} EffectVisual;

typedef struct ActorVisual {
    u8 reserved_00[8];
    void *resource;
    u8 reserved_0C[8];
    u16 flags;
    u8 reserved_16[0xE];
    u8 tile_x, tile_y;
} ActorVisual;

extern u8 D_800DDC40[];
#include "shared/object_flags.h"
typedef struct ActionSlot { s32 value; } ActionSlot;
extern ActionSlot D_8008346C;
extern s32 func_8002416C(ObjectNodeHeader *, EffectMotion *, s32, s16);
extern s32 func_8003DE58(void *, ActorVisual *, s16 *, s32);
extern s16 func_800A44E0(u16, u16, s16, s16);
extern s32 func_800BCB04(u16, u16, s16);
extern void *func_800242EC(ActionState *, EffectMotion *, EntityRec *);
extern s32 func_80064584(s16);
extern s32 func_800644B8(s16);
extern void func_800A56E0(s32);
extern s32 func_80025270(ActionState *, EffectMotion *, s16);
extern void func_8002452C(ActionState *);
extern void func_8009CE1C(EntityRec *, s32, s32, s32, s16, EntityRec *, s32);

/* Advance the seven-stage action and its attached movement/effects.
 * Every finished stage clears the tick counter and steps to the next phase in place
 * (the compiler merges the identical stage tails into one copy). */
void func_80025408(ActionState *action, EffectMotion *motion, EffectVisual *visual)
{
    EntityRec *actor;
    EntityRec *target;
    ObjectNodeHeader *node;
    EffectMotion *target_motion;
    EffectMotion *actor_motion;
    ActorVisual *actor_visual;
    ActorVisual *scan_visual;
    EffectMotion destination;
    s16 offset[3];
    s16 dest_tile_y;
    u16 tile_x, tile_y;
    s32 steps;
    s32 height;
    s16 dest_tile_x;

    action->ticks++;
    actor = action->actor;
    switch (action->phase) {
    case 0:
        action->ticks = 0;
        action->completed_a = 0;
        action->completed_b = 0;
        action->phase++;
        action->direction = ((u16)actor->facing >> 9) & 7;
        visual->color = 0x808080;
        func_8002416C((ObjectNodeHeader *)actor - 1, motion, 8, 0x300);
        /* The initial movement work is shared with phase 1. */
    case 1:
        node = (ObjectNodeHeader *)actor - 1;
        actor_visual = node->unk_0C;
        if (!func_8003DE58(actor_visual->resource, actor_visual, offset, 0)) {
            if (!( ((ActorVisual *)node->unk_0C)->flags & 0x8000))
                break;
        }
        actor_motion = node->unk_08;
        motion->x.w.i = actor_motion->x.w.i;
        motion->y.w.i = actor_motion->y.w.i;
        motion->z.w.i = actor_motion->z.w.i;
        if (!(((ActorVisual *)node->unk_0C)->flags & 0x8000)) {
            motion->x.w.i += offset[0];
            motion->y.w.i += offset[1];
            motion->z.w.i += offset[2];
        } else {
            motion->z.w.i -= 0x40;
        }
        if (!(*action->flags & 0x80))
            break;
        steps = 0;
        target = actor->target;
        if (target) {
            target_motion = ((ObjectNodeHeader *)target - 1)->unk_08;
            motion->next_x = target_motion->x.v;
            motion->next_y = target_motion->y.v;
            motion->next_z = target_motion->z.v - (D_800DDC40[((u8 *)actor->target)[0x13]] << 15);
        } else {
            scan_visual = node->unk_0C;
            tile_x = scan_visual->tile_x;
            tile_y = scan_visual->tile_y;
            dest_tile_x = tile_x;
            dest_tile_y = tile_y;
            do {
                if (func_800A44E0((s16)tile_x * 0x40, (s16)tile_y * 0x40,
                                 actor->unk_88, action->direction << 9))
                    break;
                height = func_800BCB04(((s16)tile_x + dirStepX[action->direction]) * 0x40 + 0x20,
                                     ((s16)tile_y + dirStepY[action->direction]) * 0x40 + 0x20,
                                     actor->unk_88 - 0x20);
                if ((s16)height > 0x200 || (s16)(height - actor->unk_88) < -0x3F)
                    break;
                steps++;
                tile_x += (u16)dirStepX[action->direction];
                tile_y += (u16)dirStepY[action->direction];
                dest_tile_y = tile_y;
                dest_tile_x = tile_x;
            } while (steps < 8);
            target_motion = &destination;
            target_motion->x.w.i = (dest_tile_x * 64) + ((dirStepX[action->direction] + 1) * 32);
            target_motion->y.w.i = (dest_tile_y * 64) + ((dirStepY[action->direction] + 1) * 32);
            target_motion->z.w.i = motion->z.w.i;
            motion->next_x = target_motion->x.v;
            motion->next_y = target_motion->y.v;
            motion->next_z = motion->z.v - 0x200000;
        }
        func_800242EC(action, motion, actor);
        action->ticks = 0;
        action->phase++;
        break;
    case 2:
        motion->x.v += ((func_80064584(actor->facing) >> 4) * (8 - action->ticks)) << 8;
        motion->y.v += ((func_800644B8(actor->facing) >> 4) * (8 - action->ticks)) << 8;
        motion->z.v -= 0x20000;
        if (action->ticks == 5) {
            func_800A56E0(0x300);
            for (steps = 0; steps < 8; steps++)
                func_80025270(action, motion, (s16)steps);
        }
        if (action->ticks >= 9) {
            action->ticks = 0;
            action->phase++;
            break;
        }
        action->pending = 0;
        return;
    case 3:
        if (action->ticks < 0xD)
            motion->z.v -= 0x20000;
        if (action->ticks < 0x3C)
            break;
        func_8002452C(action);
        target = actor->target;
        if (target) {
            target_motion = ((ObjectNodeHeader *)target - 1)->unk_08;
            motion->next_x = (target_motion->x.v - motion->x.v) / 32;
            motion->next_y = (target_motion->y.v - motion->y.v) / 32;
            motion->next_z = (target_motion->z.v -
                (D_800DDC40[((u8 *)actor->target)[0x13]] << 15) - motion->z.v) / 32;
        } else {
            motion->next_x = (motion->next_x - motion->x.v) / 32;
            motion->next_y = (motion->next_y - motion->y.v) / 32;
            motion->next_z = (motion->next_z - motion->z.v) / 32;
        }
        action->ticks = 0;
        action->phase++;
        break;
    case 4:
        motion->x.v += motion->next_x;
        motion->y.v += motion->next_y;
        motion->z.v += motion->next_z;
        if (action->ticks >= 0x20) {
            action->ticks = 0;
            action->phase++;
            break;
        }
        action->pending = 0;
        return;
    case 5:
        if (action->completed_a < 8 || action->completed_b < 8)
            break;
        if (actor->target)
            func_8009CE1C(actor->target, 0x18, action->event_id, 2,
                         action->direction << 9, actor, 1);
        action->ticks = 0;
        action->phase++;
        break;
    case 6:
        if (!action->pending) {
            D_8008346C.value = 0;
            ((ObjectNodeHeader *)action)[-1].flags |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }
    action->pending = 0;
}
