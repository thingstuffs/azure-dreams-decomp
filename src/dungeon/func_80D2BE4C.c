#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
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

typedef struct ActorSpriteSlot { u8 *sprite; } ActorSpriteSlot;

s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry();
s32 func_80069EF8();
void *scan_monster_along_heading();
extern void set_record_integer_tile_center();
extern s32 advance_status_timers(void *);
extern s32 play_sound_if_enabled(s32);
extern void *create_actor_spell_effect();
void func_80159020();
extern void update_ability_actor_behavior(void *, void *, void *, void *);
extern u8 D_8015CE88[9];

/* Updates an actor's ability action, effects, and completion state. */
void update_ability_actor_action(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor) {
    s16 effect_count;
    s32 ability_id;
    s32 normal_ability;
    s16 use_player;
    u16 effect_ticks;
    u16 finish_ticks;
    u8 *ability;
    s32 phase;
    void *target;
    u8 *target_sprite;

    phase = action->phase;
    use_player = 0;
    switch (phase) {
    case 0:
        if (actor->flags1C & 0x2000) {
            ability_id = actor->unk_46 & 0x3FFF;
            switch (ability_id) {
            case 7:
                use_player = 1;
                /* fallthrough */
            case 3:
                ability = ((ActorAbilityView *)actor)->slots[2];
                break;
            case 6:
                use_player = 1;
                /* fallthrough */
            case 2:
                ability = ((ActorAbilityView *)actor)->slots[1];
                break;
            case 5:
                use_player = 1;
                /* fallthrough */
            case 1:
                ability = ((ActorAbilityView *)actor)->slots[0];
                break;
            default:
                ability = NULL;
                break;
            }
        } else {
            normal_ability = actor->unk_46 & 0x3FFF;
            switch (normal_ability) {
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
                ability = NULL;
                break;
            }
        }
        if (*ability != 0) {
            action->flags &= 0xFF7F;
            {
                s32 player_target = use_player;
                if (player_target) {
                    target = D_800814A8;
                    actor->target = target;
                    {
                        target_sprite =
                            ((ActorSpriteSlot *)((u8 *)target - 0x14))->sprite;
                        actor->unk_72 = ((SpriteFrameState *)target_sprite)->unk_24;
                        actor->unk_73 = ((SpriteFrameState *)target_sprite)->unk_25;
                    }
                } else {
                    u8 ability_kind;

                    ability_kind = *ability;
                    if (D_8006DE24[ability_kind].kind == 2) {
                        target = actor->target;
                        if (target != NULL) {
                            {
                                target_sprite =
                                    ((ActorSpriteSlot *)((u8 *)target - 0x14))->sprite;
                                actor->unk_72 = ((SpriteFrameState *)target_sprite)->unk_24;
                                actor->unk_73 = ((SpriteFrameState *)target_sprite)->unk_25;
                            }
                        }
                    } else {
                        {
                            s32 x = (s32)scan_monster_along_heading(actor, sprite->tile.bytes.x,
                                          sprite->tile.bytes.y,
                                          actor->facing, 0x10);
                            s32 y;

                            *(void * volatile *)&actor->target = (void *)x;
                            x = actor->unk_72;
                            y = actor->unk_73;
                            if (x < 0) {
                                x = -x;
                            }
                            if (y < 0) {
                                y = -y;
                            }
                            actor->unk_72 = x;
                            actor->unk_73 = y;
                        }
                    }
                }
            }
            if (create_actor_spell_effect(actor, ability, use_player, &action->flags) == 0) {
                return;
            }
            action->timer.raw = 0x13U;
            action->phase = (u8) (action->phase + 1);
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
            g_dungeon_status.unk_0C = 0;
            ((PlayerActionCounterView *)D_800814A8)->activeActions = (u16) (((PlayerActionCounterView *)D_800814A8)->activeActions - 1);
            advance_status_timers(actor);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            action->nextBehavior = &update_ability_actor_behavior;
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags = (u16) (sprite->flags
                | 0x800);
            return;
        }
        sprite->flags = (u16) (sprite->flags & 0xF7FF);
        action->phase = (u8) (action->phase + 1);
        play_sound_if_enabled(0x703);
        /* fallthrough */
    case 2:
        effect_ticks = action->timer.raw - 1;
        action->timer.raw = effect_ticks;
        if ((effect_ticks << 0x10) <= 0 || (sprite->flags & 0xE000)) {
            action->flags = (u16) (action->flags | 0x80);
            action->phase = (u8) (action->phase + 1);
            sprite->flags = (u16) (sprite->flags
                | 0x800);
            action->timer.raw = 0xFU;
        }
        if ((u32) (action->timer.raw - 9) >= 6U) {
            return;
        }
        for (effect_count = 0; effect_count < 10; effect_count++) {
            func_80159020((u8 *)(u8 *)action - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
        }
        return;
    case 3:
        if (((s32)g_dungeon_status.unk_0C) == 0) {
            action->timer.raw = 0U;
        }
        finish_ticks = action->timer.raw - 1;
        action->timer.raw = finish_ticks;
        if ((finish_ticks << 0x10) <= 0) {
            action->timer.raw = 0U;
            sprite->flags =
                (u16) (sprite->flags & 0xF7FF);
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile.bytes.x, sprite->tile.bytes.y);
        if (sprite->frameTable != D_8015CE88) {
            (sprite->frameTable) = D_8015CE88;
            select_sprite_entry(sprite, D_8015CE88[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            sprite->flags =
                (u16) (sprite->flags & 0xF7FF);
        }
        if (((s32)g_dungeon_status.unk_0C) != 0) {
            return;
        }
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
        action->nextBehavior = &update_ability_actor_behavior;
        advance_status_timers(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        play_sound_if_enabled(0xB4);
        return;
    }
}
