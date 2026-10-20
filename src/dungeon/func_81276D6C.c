#include "common.h"
#include "shared/entity.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern int abs(int);

extern s32 get_cd_command_queue_depth(void);
extern s32 select_sprite_entry();
extern void *scan_monster_along_heading();
extern void set_record_integer_tile_center();
extern void advance_status_timers();
extern void play_sound_if_enabled();
extern s32 create_actor_spell_effect();
extern void func_8014CE18();

extern s32 D_8014D514;
extern u8 D_8014FE8C[8];
extern u8 D_8014FEDC[8];

typedef struct ActorActionWork {
    u8 pad_00[0x8C];
    void *handler;
    u8 pad_90[2];
    union { s16 signedValue; u16 value; } remainingAmount;
    u8 pad_94[2];
    u16 phaseTicks;
    u16 actionFlags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    u16 adjustment;
    u8 pad_A0[2];
    union { s16 signedValue; u16 value; } pendingAmount;
} ActorActionWork;

/* Three adjacent action records are selected by action kind. */
typedef struct ActorActionSlots {
    u8 pad_00[8];
    u8 first[3];
    u8 second[3];
    u8 third[3];
} ActorActionSlots;

typedef struct ActorCounterView {
    u8 pad_00[0xA6];
    u16 pendingCount;
} ActorCounterView;

typedef struct TargetLinkHeader {
    u8 * positionRecord;
    u8 pad_04[0x10];
} TargetLinkHeader;   /* The position-record link is 0x14 bytes before the actor. */

typedef struct TargetPositionView {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TargetPositionView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 animationKind;
    u8 animationEnabled;
    u8 pad_06[0xE];
    u16 animationFlags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    union { s8 signedValue; u8 value; } roomId;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* Advances an actor's action phase, updating its target, animation, and completion. */
void advance_actor_action_phase(ActorActionWork *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
{
    s32 usePlayerTarget = 0;
    u8 *actionEntry;
    u32 phase;
    u32 priorPhase;
    /* The selector and linked position address share this temporary. */
    s32 actionKindOrTargetAddress;
    u32 actionKind;
    u16 ticks;
    s32 next_ticks;
    u8 *target_link;

    phase = action->phase;
    switch (phase) {
    case 0:
        if (actor->flags1C & 0x2000) {
            actionKind = actor->unk_46 & 0x3FFF;
            switch (actionKind) {
            case 7:
                usePlayerTarget = 1;
                /* fallthrough */
            case 3:
                actionEntry = ((ActorActionSlots *)actor)->third;
                break;
            case 6:
                usePlayerTarget = 1;
                /* fallthrough */
            case 2:
                actionEntry = ((ActorActionSlots *)actor)->second;
                break;
            case 5:
                usePlayerTarget = 1;
                /* fallthrough */
            case 1:
                actionEntry = ((ActorActionSlots *)actor)->first;
                break;
            default:
                actionEntry = 0;
                break;
            }
        } else {
            actionKindOrTargetAddress = actor->unk_46 & 0x3FFF;
            switch (actionKindOrTargetAddress) {
            case 3:
                actionEntry = ((ActorActionSlots *)actor)->third;
                break;
            case 2:
                actionEntry = ((ActorActionSlots *)actor)->second;
                break;
            case 1:
                actionEntry = ((ActorActionSlots *)actor)->first;
                break;
            default:
                actionEntry = 0;
                break;
            }
        }
        if (*actionEntry != 0) {
            action->actionFlags &= 0xFF7F;
            {
                u8 use_player_target = usePlayerTarget;

                if (use_player_target) {
                    target_link = D_800814A8;
                    actor->target = target_link;
                    /* Both target paths read the link in the object prefix. */
                    actionKindOrTargetAddress = (s32)((TargetLinkHeader *)target_link)[-1].positionRecord;

                    actor->unk_72 = ((TargetPositionView *)actionKindOrTargetAddress)->tileX;
                    actor->unk_73 = ((TargetPositionView *)actionKindOrTargetAddress)->tileY;
                } else if (D_8006DE24[*actionEntry].kind == 2) {
                    target_link = actor->target;
                    if (target_link != 0) {
                        /* Both target paths read the link in the object prefix. */
                        actionKindOrTargetAddress = (s32)((TargetLinkHeader *)target_link)[-1].positionRecord;

                        actor->unk_72 = ((TargetPositionView *)actionKindOrTargetAddress)->tileX;
                        actor->unk_73 = ((TargetPositionView *)actionKindOrTargetAddress)->tileY;
                    }
                } else {
                    s32 abs_x;
                    s32 abs_y;

                    actor->target = scan_monster_along_heading(
                        actor,
                        sprite->position.tile.x,
                        sprite->position.tile.y,
                        actor->facing,
                        0x10);
                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }
            if (create_actor_spell_effect(actor, actionEntry, usePlayerTarget, &action->actionFlags) == 0) {
                return;
            }
            action->phaseTicks = 0;
            action->phase++;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->position.tile.x, sprite->position.tile.y);
        g_dungeon_status.active_actor = 0;
        ((ActorCounterView *)D_800814A8)->pendingCount--;
        advance_status_timers(actor);
        actor->unk_6D--;
        action->handler = &D_8014D514;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->animationFlags |= 0x800;
            return;
        }
        sprite->animationFlags &= 0xF7FF;
        action->phase++;
        play_sound_if_enabled(0x703);
        /* fall through */
    case 2:
        ticks = action->phaseTicks;
        next_ticks = ticks + 1;
        action->phaseTicks = next_ticks;
        if ((s16)ticks < 8 && !(sprite->animationFlags & 0x8000)) {
            return;
        }
        priorPhase = action->phase;

        action->phaseTicks = 0;
        action->phase = priorPhase + 1;
        return;

    case 3:
        if (action->pendingAmount.signedValue != 0) {
            ticks = action->phaseTicks;
            next_ticks = ticks + 1;
            action->phaseTicks = next_ticks;
            if ((s16)ticks < 15 && !(sprite->animationFlags & 0x8000)) {
                return;
            }
        }
        action->phaseTicks = 0;
        action->phase++;
        play_sound_if_enabled(0x703);
        sprite->directionFrames = D_8014FEDC;
        select_sprite_entry(
            sprite,
            D_8014FEDC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        return;

    case 4:
        func_8014CE18(action, motion, sprite, actor);
        ticks = action->phaseTicks;
        next_ticks = ticks + 1;
        action->phaseTicks = next_ticks;
        if ((s16)ticks < 3 && !(sprite->animationFlags & 0xE000)) {
            return;
        }
        sprite->animationFlags |= 0x800;
        priorPhase = action->phase;
        action->phase = priorPhase + 1;
        return;

    case 5:
        sprite->animationFlags |= 0x800;
        ticks = action->phaseTicks;
        next_ticks = ticks + 1;
        action->phaseTicks = next_ticks;
        if ((s16)ticks < 10 && !(sprite->animationFlags & 0x8000)) {
            return;
        }
        action->phaseTicks = 0;
        action->phase++;
        sprite->animationFlags &= 0xF7FF;
        return;

    case 6:
        action->actionFlags |= 0x80;
        action->phaseTicks = 0;
        action->phase++;
        return;

    case 7:
        if (!(sprite->animationFlags & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->position.tile.x, sprite->position.tile.y);
        action->phase++;
        if (sprite->directionFrames == D_8014FE8C) {
            return;
        }
        sprite->directionFrames = D_8014FE8C;
        select_sprite_entry(
            sprite,
            D_8014FE8C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->adjustment = 0;
        action->remainingAmount.signedValue = -0x20;
        return;

    case 8:
        {

            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            action->handler = &D_8014D514;
            advance_status_timers(actor);
            actor->unk_6D--;
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }
        return;
    default:
        return;
    }
}
