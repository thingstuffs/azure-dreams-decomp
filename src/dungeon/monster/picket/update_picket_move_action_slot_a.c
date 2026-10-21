#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"

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

/* The sprite pointer is in the object header, 0x14 bytes before its entity record. */




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

/* Three adjacent three-byte ability slots, selected by action kinds 1, 2 and 3. */
typedef struct ActorAbilityView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorAbilityView;
extern int abs(int);

extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void *create_actor_spell_effect();
extern s32 play_sound_if_enabled(s32);
extern void create_two_effect_groups(void *, void *, void *, s32);
extern void set_record_integer_tile_center();
extern s32 advance_status_timers(void *);
extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry();

extern void update_dungeon_action_behavior(void *, void *, void *, void *);
extern u8 D_80150EF8[];
extern u8 D_80150F00[];

/* Updates the actor action sequence, including movement, landing, and recovery. */
void update_picket_move_action_slot_a(ActorActionView *action, ObjectPosition *motion, ActorSpriteView *sprite, ActorRecord *actor)
{
    u32 direction_byte_offset;
    u16 angle;
    u32 action_index;
    s16 *dir_x_table;
    s32 dir_x;
    s32 dir_y;
    u16 timer;
    u32 state;
    u8 *selector;
    s32 special;
    s32 next_phase;
    u16 position[3];

    dir_x_table = dir_step_x;
    angle = ((u16)actor->facing);
    direction_byte_offset = angle >> 8;
    direction_byte_offset &= 0xE;
    dir_x = *(s16 *)((u8 *)dir_x_table + direction_byte_offset);
    direction_byte_offset += (u32)dir_step_y;
    dir_y = *(s16 *)direction_byte_offset;
    timer = action->timer.raw;
    state = action->phase;
    action->timer.raw = timer - 1;
    special = 0;
    switch (state) {

    case 0:
        action->startHeight.raw = ((u16)motion->z.w.i);
        if (((u32)actor->flags1C) & 0x2000) {
            u16 action_kind;

            action_kind = actor->action_flags & 0x3FFF;
            action_index = action_kind - 1;
            switch (action_index) {
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                selector = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                selector = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 4:
                special = 1;
                /* fallthrough */
            case 0:
                selector = ((ActorAbilityView *)actor)->slots[0];
                break;
            case 3:
            default:
                selector = 0;
            }
        } else {
            u16 action_kind;

            action_kind = actor->action_flags & 0x3FFF;
            switch (action_kind) {
            case 3:
                selector = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 2:
                selector = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 1:
                selector = ((ActorAbilityView *)actor)->slots[0];
                break;
            default:
                selector = 0;
            }
        }

        if (*selector != 0) {
            void *owner;
            u16 use_owner;
            s32 target_sprite_or_effect;

            action->flags &= 0xFF7F;
            use_owner = special;
            if (use_owner) {
                owner = primary_actor_record;
                actor->target = owner;
                target_sprite_or_effect = ((SpriteLinkPrefixView *)owner)[-1].unk_00;
                actor->target_tile_x = ((SpriteFrameState *)target_sprite_or_effect)->unk_24;
                actor->target_tile_y = ((SpriteFrameState *)target_sprite_or_effect)->unk_25;
            } else {
                direction_byte_offset = *selector;
                if (item_action_definitions[direction_byte_offset].kind == 2) {
                    owner = actor->target;
                    if (owner != 0) {
                        target_sprite_or_effect = ((SpriteLinkPrefixView *)owner)[-1].unk_00;
                        actor->target_tile_x = ((SpriteFrameState *)target_sprite_or_effect)->unk_24;
                        actor->target_tile_y = ((SpriteFrameState *)target_sprite_or_effect)->unk_25;
                    }
                } else {
                    actor->target = scan_monster_along_heading(actor,
                        sprite->tile.bytes.x,
                        sprite->tile.bytes.y,
                        actor->facing, 16);
                    actor->target_tile_x = abs(actor->target_tile_x);
                    actor->target_tile_y = abs(actor->target_tile_y);
                }
            }

            {
                void *move_actor;

                move_actor = actor;
                position[0] = ((u16)motion->x.w.i);
                position[1] = ((u16)motion->y.w.i);
                position[2] = ((u16)motion->z.w.i);
                target_sprite_or_effect = (s32)create_actor_spell_effect(move_actor, selector, special,
                                            &action->flags);
            }
            if (!target_sprite_or_effect) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_effect_groups(motion, sprite, actor, 10);
            action->scratch = 0;
            action->timer.raw = 2;
            action->flags |= 8;
            {
                s32 back_x;
                s32 back_y;

                back_x = -dir_x;
                back_y = -dir_y;
                motion->velocity_x =
                    (back_x << 18) + (back_x << 19);
                motion->velocity_y =
                    (back_y << 18) + (back_y << 19);
            }
            motion->velocity_z = (s32)0xFFF30000;
            {
                next_phase = action->phase;
                next_phase++;
                action->phase = next_phase;
                return;
            }
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
        {
            void *owner;

            owner = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            ((PlayerRemainingActionsView *)owner)->remaining--;
        }
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        action->nextBehavior = update_dungeon_action_behavior;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (sprite->flags & 0x8000) {
            action->phase = 16;
            action->flags |= 0x80;
            return;
        }
        if (action->timer.signedValue <= 0) {
            motion->velocity_x = 0;
            motion->velocity_y = 0;
            motion->velocity_z = 0;
            motion->velocity_x = dir_x << 18;
            motion->velocity_y = dir_y << 18;
            motion->velocity_z = (s32)0xFFF30000;
            {
                action->phase = action->phase + 1;
                return;
            }
        }
        motion->velocity_x *= 2;
        motion->velocity_y *= 2;
        return;

    case 2:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->phase++;
        /* fallthrough */
    case 3:
        motion->velocity_z += 0x30000;
        if (!((sprite->framePhase == 4 && (sprite->flags & 0x1000)) ||
              (sprite->flags & 0xE000))) {
            return;
        }
        {
            motion->velocity_x = dir_x << 19;
            motion->velocity_y = dir_y << 19;
            action->flags |= 0x80;
            action->phase++;
            return;
        }

    case 4:
        motion->velocity_z += 0x20000;
        if (!((((u32)actor->flags1C) & 0x08000000) && (motion->z.w.i <= action->startHeight.signedValue))) {
            if (motion->z.w.i <= action->startHeight.signedValue) {
                return;
            }
        }
        {
            u8 *effect;

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            action->timer.raw = 4;
            sprite->scaleX = 0x1400;
            sprite->scaleY = 0x0C00;
            effect = D_80150F00;
            sprite->frameTable = effect;
            select_sprite_entry(sprite,
                effect[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->flags &= 0xFFF7;
            action->phase++;
            return;
        }

    case 5:
    {
        s32 ticks;
        s32 ticks_squared;

        ticks = action->timer.signedValue;
        ticks_squared = ticks * ticks;
        ticks = 0x1000 + ticks_squared * 300;
        sprite->scaleX = ticks;
        sprite->scaleY = 0x1000 - ticks_squared * 200;
    }
        if (action->timer.signedValue > 0) {
            return;
        }
        sprite->frameTable = D_80150EF8;
        select_sprite_entry(sprite,
            D_80150EF8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->timer.raw = 10;
        action->phase = action->phase + 1;
        return;

    case 6:
    {
        s32 current_coord;
        {
            s32 tile_coord;

            tile_coord = sprite->tile.bytes.x;
            current_coord = motion->x.w.i;
            tile_coord = tile_coord << 6;
            current_coord -= 0x20;
            motion->velocity_x =
                (tile_coord - current_coord) << 14;
        }
        {
            s32 tile_coord;
            s32 target_coord;

            tile_coord = sprite->tile.bytes.y;
            current_coord = motion->y.w.i;
            tile_coord <<= 6;
            target_coord = tile_coord;
            current_coord -= 0x20;
            motion->velocity_y =
                (target_coord - current_coord) << 14;
        }
    }
        if (action->timer.signedValue > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->flags |= 0x6000;
        action->phase = 16;
        return;

    case 16:
    {

        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
        if (sprite->frameTable != D_80150F00) {
            sprite->frameTable = D_80150F00;
            select_sprite_entry(sprite,
                D_80150F00[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->flags &= 0xF7FF;
        action->nextBehavior = update_dungeon_action_behavior;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            (*(u8 *)&actor->pending_turn_updates)--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(0xB4);
    }
    default:
        return;
    }
}
