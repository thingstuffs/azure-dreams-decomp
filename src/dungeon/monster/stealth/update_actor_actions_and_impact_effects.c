#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_func_801728C4_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_func_801728C4_0;

typedef struct S_func_801728C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_801728C4_1;

typedef struct S_func_801728C4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void *unk_2C;
} S_func_801728C4_2;

typedef struct S_func_801728C4_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_func_801728C4_3;

extern void *actor_update_node_cursor;
extern u8 D_80170F74[];
extern u8 D_80173D58[];

void select_sprite_entry(void *, u8, s32);
void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
void set_record_integer_tile_center(void *, u8, u8);
void advance_status_timers(void *);
void play_sound_if_enabled(s32);
void spend_actor_mp(void *, s32);

/* Advance the actor action through animation setup, delay, and completion. */
/* Starts Stealth's directional attack, resolves damage after two ticks, then recenters, spends MP, and
 * updates status. */
void update_actor_actions_and_impact_effects(S_func_801728C4_0 *action, S_func_801728C4_1 *motion, S_func_801728C4_2 *animation,
    S_func_801728C4_3 *actor) {
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
            resolve_attack_damage_and_effects(actor, animation, actor->unk_2A, 1);
            return;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        animation->unk_2C = D_80173D58;
        select_sprite_entry(animation,
            D_80173D58[((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
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
        resolve_attack_damage_and_effects(actor, animation, actor->unk_2A, 1);
        action->unk_9B++;
        return;
    case 3:
        if (!(animation->unk_14 & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(motion, animation->unk_24, animation->unk_25);
        spend_actor_mp(actor, 0x100);
        action->unk_8C = D_80170F74;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->unk_6D == 0) {
            actor->unk_46 &= 0x7FFF;
            return;
        }
        actor_update_node_cursor = (u8 *)actor - 0x20;
        return;
    default:
        return;
    }
}
