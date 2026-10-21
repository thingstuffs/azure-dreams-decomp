#include "common.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/object_node.h"

#ifndef DUNGEON_ACTOR_ITEM_SLOTS_VIEW
#define DUNGEON_ACTOR_ITEM_SLOTS_VIEW
/* Three adjacent 3-byte action records begin at +0x08. */
typedef struct ActorItemSlotsView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorItemSlotsView;
#endif

#ifndef DUNGEON_PLAYER_ACTION_COUNT_VIEW
#define DUNGEON_PLAYER_ACTION_COUNT_VIEW
typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remainingActions;
} PlayerActionCountView;
#endif

typedef struct AbilityActionState {
    u8 pad_00[0x8C];
    s32 * nextBehavior;
    u8 pad_90[0x6];
    u16 timer;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} AbilityActionState;

s32 get_cd_command_queue_depth(void);
void select_sprite_entry();
s32 func_80069EF8();
void *scan_monster_along_heading();
void set_record_integer_tile_center();
s32 advance_status_timers();
s32 play_sound_if_enabled();
s32 create_actor_spell_effect();
void func_8015F020();
extern s32 D_8015F760;
extern u8 D_80162E88[9];

void advance_ability_action_and_reset_state(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor) {
    s16 next_effect;
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

    phase = ((AbilityActionState *)action)->phase;
    use_player = 0;
    switch (phase) {
    case 0:
        if (actor->flags1C & 0x2000) {
            ability_id = actor->action_flags & 0x3FFF;
            switch (ability_id) {
            case 7:
                use_player = 1;
            case 3:
                ability = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 6:
                use_player = 1;
            case 2:
                ability = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 5:
                use_player = 1;
            case 1:
                ability = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                ability = NULL;
                break;
            }
        } else {
            normal_ability = actor->action_flags & 0x3FFF;
            switch (normal_ability) {
            case 3:
                ability = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 2:
                ability = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 1:
                ability = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                ability = NULL;
                break;
            }
        }
        if (*ability != 0) {
            ((AbilityActionState *)action)->flags &= 0xFF7F;
            {
                s32 player_target = use_player;
                if (player_target) {
                    target = D_800814A8;
                    actor->target = target;
                    {
                        target_sprite =
                            ((ObjectNodeHeader *)((u8 *)target - 0x20))->unk_0C;
                        actor->target_tile_x = ((Rec_D_80082E80 *)target_sprite)->unk_24;
                        actor->target_tile_y = ((Rec_D_80082E80 *)target_sprite)->unk_25;
                    }
                } else {
                    DefEntry *ability_table;
                    u8 ability_kind;
                    DefEntry *ability_entry;

                    ability_kind = *ability;
                    ability_table = D_8006DE24;
                    ability_entry = &ability_table[ability_kind];
                    if (ability_entry->kind == 2) {
                        target = actor->target;
                        if (target != NULL) {
                            {
                                target_sprite =
                                    ((ObjectNodeHeader *)((u8 *)target - 0x20))->unk_0C;
                                actor->target_tile_x = ((Rec_D_80082E80 *)target_sprite)->unk_24;
                                actor->target_tile_y = ((Rec_D_80082E80 *)target_sprite)->unk_25;
                            }
                        }
                    } else {
                        {
                            s32 x = (s32)scan_monster_along_heading(actor, ((SpriteFrameState *)sprite)->unk_24,
                                          ((SpriteFrameState *)sprite)->unk_25,
                                          actor->facing, 0x10);
                            s32 y;

                            actor->target = (void *)x;
                            x = abs(actor->target_tile_x);
                            y = abs(actor->target_tile_y);
                            actor->target_tile_x = x;
                            actor->target_tile_y = y;
                        }
                    }
                }
            }
            if (create_actor_spell_effect(actor, ability, use_player, &((AbilityActionState *)action)->flags) == 0) {
                return;
            }
            ((AbilityActionState *)action)->timer = 0x13U;
            ((AbilityActionState *)action)->phase = (u8) (((AbilityActionState *)action)->phase + 1);
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            g_dungeon_status.active_actor = 0;
            ((PlayerActionCountView *)D_800814A8)->remainingActions = (u16) (((PlayerActionCountView *)D_800814A8)->remainingActions - 1);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            ((AbilityActionState *)action)->nextBehavior = &D_8015F760;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags = (u16) (actor->action_flags & 0x7FFF);
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags
                | 0x800);
            return;
        }
        ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
        ((AbilityActionState *)action)->phase = (u8) (((AbilityActionState *)action)->phase + 1);
        play_sound_if_enabled(0x703);
    case 2:
        effect_ticks = ((AbilityActionState *)action)->timer - 1;
        ((AbilityActionState *)action)->timer = effect_ticks;
        if ((effect_ticks << 0x10) <= 0 || (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((AbilityActionState *)action)->flags = (u16) (((AbilityActionState *)action)->flags | 0x80);
            ((AbilityActionState *)action)->phase = (u8) (((AbilityActionState *)action)->phase + 1);
            ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags
                | 0x800);
            ((AbilityActionState *)action)->timer = 0xFU;
        }
        if ((u32) (((AbilityActionState *)action)->timer - 9) >= 6U) {
            return;
        }
        effect_count = 0;
        do {
            func_8015F020(action - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
            next_effect = effect_count + 1;
            effect_count = next_effect;
        } while (next_effect < 0xA);
        return;
    case 3:
        if (((s32)g_dungeon_status.active_actor) == 0) {
            ((AbilityActionState *)action)->timer = 0U;
        }
        finish_ticks = ((AbilityActionState *)action)->timer - 1;
        ((AbilityActionState *)action)->timer = finish_ticks;
        if ((finish_ticks << 0x10) <= 0) {
            ((AbilityActionState *)action)->timer = 0U;
            ((SpriteFrameState *)sprite)->flags =
                (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
        }
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        if ((*(M2C_UNK * *)&((SpriteFrameState *)sprite)->frameTable) != D_80162E88) {
            ((SpriteFrameState *)sprite)->frameTable = D_80162E88;
            select_sprite_entry(sprite, D_80162E88[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            ((SpriteFrameState *)sprite)->flags =
                (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((AbilityActionState *)action)->nextBehavior = &D_8015F760;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        actor->action_flags = (u16) (actor->action_flags & 0x7FFF);
        play_sound_if_enabled(0xB4);
        return;
    }
}
