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
extern void update_dungeon_action_behavior(void *, void *, void *, void *);
extern u8 D_80150EF8[];
extern u8 D_80150F00[];
extern u8 D_80150F58[];
extern u16 D_80150FC4[];
extern u16 D_80150FD4[];

extern void select_sprite_entry();
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void set_record_integer_tile_center();
extern s32 advance_status_timers(void *);
extern s16 select_dungeon_spawn_tile(u8 *, u8 *);
extern s32 play_sound_if_enabled(s32);
extern void refresh_actor_proximity_state(u8 *context);
extern void spend_actor_mp(void *, s32);
extern s16 sample_terrain_surface_height(s32, s32, s16);

/* Updates movement, destination selection, and recovery animation for the entity. */
void update_actor_movement_recovery(ActorActionView *action, ActorMotionView *motion, ActorSpriteView *sprite, ActorFacingView *entity)
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
    x_step_ptr = (s16 *)((u8 *)dir_step_x);
    direction_or_test = entity->facing.raw;
    direction_offset = direction_or_test >> 8;
    direction_offset &= 0xE;
    state_id = action->phase;
    x_step_ptr = (s16 *)((u8 *)x_step_ptr + direction_offset);
    direction_offset += (u32)((u8 *)dir_step_y);
    direction_or_test = state_id < 6;
    x_step = *x_step_ptr;
    y_step = *(s16 *)direction_offset;
    if (!direction_or_test) {
        return;
    }
    switch (state_id) {
    case 0:
        update_map_cell_flags_with_item_limit(sprite->tile.bytes.x, sprite->tile.bytes.y,
            (entity->flags & 0x2000) ? 0x300 : 0x3000);
        (sprite->frameTable) = D_80150EF8;
        select_sprite_entry(sprite,
            D_80150EF8[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing.signedValue + 0x100) >> 9) & 7], 0);
        motion->velocityX = (x_step << 19) + (x_step << 18);
        motion->velocityY = (y_step << 19) + (y_step << 18);
        action->timer.raw = 4;
        play_sound_if_enabled(0x80E);
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
        (sprite->frameTable) = D_80150F58;
        select_sprite_entry(sprite,
            D_80150F58[((g_game_work.view.camera_rotation.parts.viewAngle +
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
        (sprite->frameTable) = D_80150F00;
        select_sprite_entry(sprite,
            D_80150F00[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing.signedValue + 0x100) >> 9) & 7], 0);
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
                select_sprite_entry(sprite, 0x37, 0);
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
        select_sprite_entry(sprite, 0x38, 0);
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
            direction_offset = select_dungeon_spawn_tile(&sprite->tile.bytes.x, &sprite->tile.bytes.y);
            if (direction_offset < 0) {
                continue;
            }
            if (direction_offset == (s8)((u8)player_tile->room_index) &&
                floor_limits[3] >= 2) {
                continue;
            }
            direction_offset = sample_terrain_surface_height((sprite->tile.bytes.x << 6) | 0x20,
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
            sprite->scaleX = D_80150FC4[action->timer.signedValue];
            sprite->scaleY = D_80150FD4[action->timer.signedValue];
            if (action->timer.signedValue == 4) {
                play_sound_if_enabled(0x705);
            }
            if (!(sprite->flags & 0x8000)) {
                action->timer.raw++;
                if (action->timer.signedValue < 8) {
                    return;
                }
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            refresh_actor_proximity_state(entity);
            height = sample_terrain_surface_height((sprite->tile.bytes.x << 6) | 0x20,
                (sprite->tile.bytes.y << 6) | 0x20,
                (s16)(motion->z.w.i - 0x80));
            entity->groundHeight = height;
            sprite->frameTable = D_80150F00;
            spend_actor_mp(entity, 0x200);
            select_sprite_entry(sprite,
                sprite->frameTable[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing.signedValue + 0x100)
                    >> 9) & 7], 0);
            cycle_map_cell_flags(sprite->tile.bytes.x, sprite->tile.bytes.y,
                (entity->flags & 0x2000) ? 0x300 : 0x3000);
            set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
            sprite->scaleY = 0x1000;
            sprite->scaleX = 0x1000;
            action->nextBehavior = update_dungeon_action_behavior;
            advance_status_timers(entity);
            entity->remainingActions = 0;
            entity->actionFlags &= 0x7FFF;
            return;
        }
    }
}
