#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"

typedef struct S_func_801728C4_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_func_801728C4_0;

typedef struct S_func_801728C4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void *unk_2C;
} S_func_801728C4_2;

extern void *actor_update_node_cursor;
#include "dungeon/monster/stealth.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

extern u8 D_80173D58[];

void select_sprite_entry(void *, u8, s32);
void set_record_integer_tile_center(void *, u8, u8);
void play_sound_if_enabled(s32);
void spend_actor_mp(void *, s32);

/*
 * Starts Stealth's directional attack, resolves damage after two ticks, then recenters, spends MP,
 * and updates status.
 */
void update_actor_actions_and_impact_effects(S_func_801728C4_0 *action, ObjectPosition *motion, S_func_801728C4_2 *animation,
    ActorRecord *actor) {
    u16 delay_ticks;
    s32 state;

    state = action->unk_9B;
    switch (state) {
    case 0:
        action->unk_9B = 1;
    case 1:
        if (animation->unk_14 & 0x8000) {
            action->unk_9B = 3;
            animation->unk_14 |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        animation->unk_2C = D_80173D58;
        select_sprite_entry(animation,
            D_80173D58[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->unk_96 = 0;
        action->unk_9B++;
        return;
    case 2:
        delay_ticks = action->unk_96 + 1;
        action->unk_96 = delay_ticks;
        if ((s16)delay_ticks != 2) {
            return;
        }
        play_sound_if_enabled(0x804);
        resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
        action->unk_9B++;
        return;
    case 3:
        if (!(animation->unk_14 & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(motion, animation->unk_24, animation->unk_25);
        spend_actor_mp(actor, 0x100);
        action->unk_8C = stealth_behavior_entry;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
            return;
        }
        actor_update_node_cursor = (u8 *)actor - 0x20;
        return;
    default:
        return;
    }
}
