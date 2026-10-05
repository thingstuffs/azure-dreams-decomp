#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x8C];
    void *field8C;
    s32 position90;
    u8 pad94[2];
    s16 countdown96;
    u16 flags98;
    u8 pad9A;
    u8 state9B;
    u8 pad9C[2];
    s16 timer9E;
    s32 velocityA0;
} State;

typedef struct {
    u8 pad00[2];
    s16 x2;
    u8 pad04[2];
    s16 y6;
    u8 pad08[4];
    s32 dxC;
    s32 dy10;
    s32 dz14;
} Motion;

typedef struct {
    u8 pad00[0x14];
    u16 flags14;
    u8 pad16[0xE];
    u8 x24;
    u8 y25;
    u8 pad26[6];
    u8 *table2C;
} Actor;

typedef struct {
    u8 pad00[0x1C];
    u32 flags1C;
    u8 pad20[0xA];
    s16 direction2A;
    u8 pad2C[0x1A];
    u16 field46;
} Entity;

extern u8 D_80171E20[];
extern u8 D_801753D4[];
extern u8 D_801753DC[];

extern void func_80047784(Actor *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void func_800A2B04(Motion *, u8, u8);
extern void func_800A4ACC(Entity *);
extern void func_800A9A04(Entity *);
extern void func_800AD594(Entity *, s32);
extern s32 func_800AD9B4(Actor *, Entity *);

/* Updates timed movement toward the actor's tile and finishes the action when its countdown expires. */
void func_80173210(State *action, Motion *motion, Actor *actor, Entity *entity)
{
    s32 direction_work[2];
    s32 facing_index;
    u8 phase;
    u32 entity_flags;

    phase = action->state9B;
    switch (phase) {
    case 0:
        if ((actor->flags14 & 0x6000) == 0) {
            break;
        }
        *(u32 * )((u8 *)actor + 0x2C) = (u32)D_801753D4;
        facing_index = (gameWork.view.viewAngle + entity->direction2A + 0x100) >> 9;
        func_80047784(actor, D_801753D4[facing_index & 7], 0);
        action->flags98 |= 8;
        entity->flags1C &= 0xF7FFFFFF;
        action->timer9E = 5;
        action->velocityA0 = 0;
        action->state9B++;
                /* fallthrough */
    case 1:
        action->position90 -= action->velocityA0;
        if (action->timer9E != 0) {
            s32 target_x;
            s32 x_origin;
            s32 x_velocity;
            s32 y_origin;

            target_x = actor->x24 << 6;
            x_origin = motion->x2 - 0x20;
            x_velocity = ((target_x - x_origin) << 16) /
                         action->timer9E;
            y_origin = motion->y6 - 0x20;
            motion->dxC = x_velocity;
            motion->dy10 = (((actor->y25 << 6) - y_origin) << 16) /
                         action->timer9E;
            action->velocityA0 = -func_800644B8(action->timer9E * 0x199) << 9;
        }
        action->position90 += action->velocityA0;
        action->timer9E--;
        if (action->timer9E < 0) {
            action->flags98 &= 0xFFF7;
            action->position90 = 0;
            entity->flags1C |= 0x08000000;
            action->state9B++;
        }
                /* fallthrough */
    case 2:
        if ((entity->flags1C & 0x08000000) == 0) {
            break;
        }
        action->flags98 &= 0xFFF7;
        motion->dz14 = 0;
        motion->dy10 = 0;
        motion->dxC = 0;
        func_800A2B04(motion, actor->x24, actor->y25);
        *(u32 * )((u8 *)actor + 0x2C) = (u32)D_801753DC;
        facing_index = (gameWork.view.viewAngle + entity->direction2A + 0x100) >> 9;
        func_80047784(actor, D_801753DC[facing_index & 7], 0);
        action->state9B = 3;
        break;
    default:
        break;
    }

end_state:
    action->countdown96--;
    if (action->countdown96 > 0) {
        return;
    }

    motion->dz14 = 0;
    motion->dy10 = 0;
    motion->dxC = 0;
    func_800A2B04(motion, actor->x24, actor->y25);
    func_800AD594(entity, 4);
    func_800A4ACC(entity);

    {

        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08 -= 1;
        }
    }

    entity_flags = entity->flags1C;
    if ((entity_flags & 0x2000) != 0) {
        if ((entity->field46 & 0x8000) != 0) {
            entity->field46 &= 0x7FFF;
        }
    } else if ((entity_flags & 0x410) == 0) {
        if ((entity_flags & 0x20000) != 0) {
            entity->direction2A = func_800A0818(
                actor->x24, actor->y25, D_80082E80.tileX,
                D_80082E80.tileY, direction_work);
        }
    }

    if ((func_800AD9B4(actor, entity) << 16) > 0) {
        action->field8C = D_80171E20;
        func_800A9A04(entity);
    }
}

/* MECHANISM: The four live arguments plus direction_work[2] produce retail's 0x38 frame
   and s0/s2/s3/s1 roles. A guarded a1 table register preserves coloring; removing
   both ASM_KEEP barriers lets each D_80083228 lui cross the table store exactly. */
