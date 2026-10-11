#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

/* The action record shares its timer bytes between signed tests and unsigned updates. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    void *nextBehavior;
    s32 scratch;
    u8 pad_94[2];
    union { u16 raw; s16 signedValue; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    s16 idleElapsed;
    s16 idleDelay;
    u8 pad_A2[0xA];
    union { u16 raw; s16 signedValue; } startHeight;
} ActorActionView;

/* Sprite state passed to the frame selector; the tile pair is also compared as one halfword. */
typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 framePhase;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[4];
    union { struct { u8 x, y; } bytes; u16 packed; } tile;
    union { u8 raw; s8 signedValue; } room;
    u8 pad_27[5];
    u8 *frameTable;
} ActorSpriteView;

typedef struct ActorFacingView {
    u8 pad_00[0x1C];
    s32 flags;
    u8 pad_20[0xA];
    union { u16 raw; s16 signedValue; } facing;
    u8 pad_2C[0x1A];
    u16 actionFlags;
    u8 pad_48[0x25];
    u8 remainingActions;
    u8 pad_6E[0x1A];
    s16 groundHeight;
} ActorFacingView;

typedef struct ActorMotionView {
    Fixed1616 x, y, z;
    s32 velocityX;
    s32 velocityY;
    s32 velocityZ;
} ActorMotionView;

extern s16 D_80081468[];
extern void func_801590F4(void *, void *, void *, void *);
extern u8 D_8015CEF8[];
extern u8 D_8015CF00[];
extern u8 D_8015CF58[];
extern u16 D_8015CFC4[];
extern u16 D_8015CFD4[];

extern void func_80047784();
extern void func_8009A21C(s16 x, s16 y, u16 flags);
extern void func_8009A3D0(s32, s32, s32);
extern void func_800A2B04();
extern s32 func_800A4ACC(void *);
extern s16 func_800A4E2C(u8 *, u8 *);
extern s32 func_800A56E0(s32);
extern void func_800AA53C(u8 *context);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);

/* Updates movement, destination selection, and recovery animation for the entity. */
void func_8015C428(ActorActionView *action, ActorMotionView *motion, ActorSpriteView *sprite, ActorFacingView *entity)
{
    s32 y_step;
    s32 x_step;
    s16 *x_step_ptr;
    s32 direction_offset;
    u32 direction_or_test;
    s16 height;
    s32 attempts_left;
    TileObject *player_tile;
    s16 *floor_limits;
    u32 state_id;
    x_step_ptr = (s16 *)((u8 *)dirStepX);
    direction_or_test = entity->facing.raw;
    direction_offset = direction_or_test >> 8;
    direction_offset &= 0xE;
    state_id = action->phase;
    x_step_ptr = (s16 *)((u8 *)x_step_ptr + direction_offset);
    direction_offset += (u32)((u8 *)dirStepY);
    direction_or_test = state_id < 6;
    x_step = *x_step_ptr;
    y_step = *(s16 *)direction_offset;
    if (!direction_or_test) {
        return;
    }
    switch (state_id) {
    case 0:
        func_8009A3D0(sprite->tile.bytes.x, sprite->tile.bytes.y,
            (entity->flags & 0x2000) ? 0x300 : 0x3000);
        (sprite->frameTable) = D_8015CEF8;
        func_80047784(sprite,
            D_8015CEF8[((gameWork.view.viewAngle + entity->facing.signedValue + 0x100) >> 9) & 7], 0);
        motion->velocityX = (x_step << 19) + (x_step << 18);
        motion->velocityY = (y_step << 19) + (y_step << 18);
        action->timer.raw = 4;
        func_800A56E0(0x80E);
        action->phase++;
        /* fallthrough */
    case 1:
        if (!(sprite->flags & 0x8000)) {
            action->timer.raw--;
            if (action->timer.signedValue > 0) {
                return;
            }
        }
        motion->velocityY = 0;
        motion->velocityX = 0;
        (sprite->frameTable) = D_8015CF58;
        func_80047784(sprite,
            D_8015CF58[((gameWork.view.viewAngle +
                entity->facing.signedValue + 0x100) >> 9) & 7], 0);
        action->timer.raw = 0;
        motion->velocityX = (-x_step) << 18;
        motion->velocityY = (-y_step) << 18;
        action->phase++;
        return;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocityY = 0;
        motion->velocityX = 0;
        (sprite->frameTable) = D_8015CF00;
        func_80047784(sprite,
            D_8015CF00[((gameWork.view.viewAngle + entity->facing.signedValue + 0x100) >> 9) & 7], 0);
        if (entity->flags & 0x2000) {
            action->timer.raw = 7;
            action->phase = 5;
            return;
        }
        entity->facing.raw &= 0xFFF;
        action->phase++;
        return;

    case 3:
        {
            u16 angle = entity->facing.raw;
            if ((entity->facing.signedValue == 0x400) ||
                (sprite->flags & 0x8000)) {
                func_80047784(sprite, 0x37, 0);
                action->phase++;
                return;
            }
            if ((u32)(angle - 0x401) < 0x800) {
                entity->facing.raw = angle - 0x80;
                return;
            }
            entity->facing.raw = (angle + 0x80) & 0xFFF;
            return;
        }

    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        func_80047784(sprite, 0x38, 0);
        attempts_left = 0x40;
        player_tile = &D_80082E80;
        floor_limits = D_80081468;
        action->timer.raw = 0;
        x_step = sprite->tile.bytes.x;
        y_step = sprite->tile.bytes.y;

        for (;;) {
            if (--attempts_left <= 0) {
                sprite->tile.bytes.x = (u8)x_step;
                sprite->tile.bytes.y = (u8)y_step;
                action->phase++;
                return;
            }
            direction_offset = func_800A4E2C(&sprite->tile.bytes.x, &sprite->tile.bytes.y);
            if (direction_offset < 0) {
                continue;
            }
            if (direction_offset == (s8)((u8)player_tile->unk_026) &&
                floor_limits[3] >= 2) {
                continue;
            }
            direction_offset = func_800BCB04((sprite->tile.bytes.x << 6) | 0x20,
                (sprite->tile.bytes.y << 6) | 0x20,
                (s16)(motion->z.w.i - 0x80));
            direction_or_test = direction_offset < 0x201;
            if (direction_or_test) {
                action->phase++;
                return;
            }
        }

    case 5:
        {
            sprite->scaleX = D_8015CFC4[action->timer.signedValue];
            sprite->scaleY = D_8015CFD4[action->timer.signedValue];
            if (action->timer.signedValue == 4) {
                func_800A56E0(0x705);
            }
            if (!(sprite->flags & 0x8000)) {
                action->timer.raw++;
                if (action->timer.signedValue < 8) {
                    return;
                }
            }
            dungeonStatus.unk_0A--;
            func_800AA53C(entity);
            height = func_800BCB04((sprite->tile.bytes.x << 6) | 0x20,
                (sprite->tile.bytes.y << 6) | 0x20,
                (s16)(motion->z.w.i - 0x80));
            entity->groundHeight = height;
            sprite->frameTable = D_8015CF00;
            func_800AD594(entity, 0x200);
            func_80047784(sprite,
                sprite->frameTable[((gameWork.view.viewAngle + entity->facing.signedValue + 0x100)
                    >> 9) & 7], 0);
            func_8009A21C(sprite->tile.bytes.x, sprite->tile.bytes.y,
                (entity->flags & 0x2000) ? 0x300 : 0x3000);
            func_800A2B04(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
            sprite->scaleY = 0x1000;
            sprite->scaleX = 0x1000;
            action->nextBehavior = func_801590F4;
            func_800A4ACC(entity);
            entity->remainingActions = 0;
            entity->actionFlags &= 0x7FFF;
            return;
        }
    }
}
