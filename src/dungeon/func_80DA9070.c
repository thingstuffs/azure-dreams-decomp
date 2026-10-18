#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

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
typedef struct ActorSpriteLink {
    void *sprite;
    u8 pad_04[0x10];
} ActorSpriteLink;

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

typedef struct PlayerActionCounterView {
    u8 pad_00[0xA6];
    u16 activeActions;
} PlayerActionCounterView;
extern int abs(int);

extern s32 get_cd_command_queue_depth(void);
extern void func_80047784();
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center();
extern s32 advance_status_timers(void *);
extern s32 play_sound_if_enabled(s32);
extern void *create_actor_spell_effect();

extern void dispatch_ability_action(void *, void *, void *, void *);
extern u8 D_8015B86C[];

/* Advances actor ability, waits for completion, and resets the action state. */
void advance_ability_action(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
{
    u16 saved_position[3];
    u8 *ability;
    s16 use_player_target;
    void *target;
    s32 wait_frames;
    u8 *target_sprite;
    void *effect;

    use_player_target = 0;
    switch (action->phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_player_target = 1;
                /* fallthrough */
            case 3:
                ability = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 6:
                use_player_target = 1;
                /* fallthrough */
            case 2:
                ability = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 5:
                use_player_target = 1;
                /* fallthrough */
            case 1:
                ability = ((ActorAbilityView *)actor)->slots[0];
                break;
            default:
                ability = (u8 *)0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                ability = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 2:
                ability = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 1:
                ability = ((ActorAbilityView *)actor)->slots[0];
                break;
            default:
                ability = (u8 *)0;
                break;
            }
        }

        if (*ability != 0) {
            action->flags &= 0xFF7F;
            if (use_player_target != 0) {
                target = D_800814A8;
                actor->target = target;
                target_sprite = ((ActorSpriteLink *)target)[-1].sprite;
                actor->unk_72 = ((SpriteFrameState *)target_sprite)->unk_24;
                actor->unk_73 = ((SpriteFrameState *)target_sprite)->unk_25;
            } else if (D_8006DE24[*ability].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    target_sprite = ((ActorSpriteLink *)target)[-1].sprite;
                    actor->unk_72 = ((SpriteFrameState *)target_sprite)->unk_24;
                    actor->unk_73 = ((SpriteFrameState *)target_sprite)->unk_25;
                }
            } else {
                actor->target =
                    scan_monster_along_heading(actor, sprite->tile.bytes.x, sprite->tile.bytes.y,
                                  actor->facing, 0x10);
                actor->unk_72 = abs(actor->unk_72);
                actor->unk_73 = abs(actor->unk_73);
            }
            saved_position[0] = ((u16)motion->x.w.i);
            saved_position[1] = ((u16)motion->y.w.i);
            saved_position[2] = ((u16)motion->z.w.i);
            effect = (void *)create_actor_spell_effect(actor, ability, use_player_target, &action->flags);
            if (effect == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            action->phase = action->phase + 1;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
        g_dungeon_status.unk_0C = 0;
        ((PlayerActionCounterView *)D_800814A8)->activeActions = ((PlayerActionCounterView *)D_800814A8)->activeActions - 1;
        advance_status_timers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        action->nextBehavior = dispatch_ability_action;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->phase = action->phase + 1;
        /* fallthrough */
    case 2:
        if ((sprite->framePhase == 5 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            action->timer.raw = 0x20;
            action->flags |= 0x80;
        }
        wait_frames = action->timer.raw - 1;
        action->timer.raw = wait_frames;
        if ((s16)wait_frames <= 0) {
            action->timer.raw = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
        {
            u8 *direction_anims = D_8015B86C;

            if (sprite->frameTable != direction_anims) {
                (sprite->frameTable) = direction_anims;
                func_80047784(sprite,
                    direction_anims[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        target_sprite = (u8 *)&g_dungeon_status.unk_00;
        if (((DungeonGlobalStatus *)target_sprite)->unk_0C != 0) {
            return;
        }
        ((DungeonGlobalStatus *)target_sprite)->unk_0A = ((DungeonGlobalStatus *)target_sprite)->unk_0A - 1;
        sprite->flags &= 0xF7FF;
        action->nextBehavior = dispatch_ability_action;
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}
