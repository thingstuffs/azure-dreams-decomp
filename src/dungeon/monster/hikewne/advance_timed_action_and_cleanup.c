#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern u8 hikewne_frame_set_16[];

typedef struct S_80172864_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172864_0;   /* s0 in advance_timed_action_and_cleanup */

typedef struct S_80172864_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172864_2;   /* s1 in advance_timed_action_and_cleanup */

/* Advances a timed action through animation setup, execution, and cleanup. */
void advance_timed_action_and_cleanup(void *action_data, void *unused, SpriteFrameState *sprite, void *actor_data)
{
    register S_80172864_0 *action = action_data;
    register S_80172864_2 *actor = actor_data;
    u8 state;
    u16 timer;

    state = action->unk_9B.n;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        timer = action->unk_96.u;
        action->unk_96.u = timer + 1;
        if ((s16)timer < 4 && !(sprite->flags & 0x8000)) {
            return;
        }
        state = action->unk_9B.v;
        action->unk_96.u = 0;
        action->unk_9B.n = state + 1;
        return;

    case 1:
        if (action->unk_A2 != 0 &&
            !(sprite->flags & 0x8000)) {
            return;
        }
        sprite->frameTable = hikewne_frame_set_16;
        select_sprite_entry(
            sprite,
            hikewne_frame_set_16[((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
            0);
        state = action->unk_9B.n;
        action->unk_96.u = 0;
        action->unk_A2 = 0;
        action->unk_9E = 0;
        action->unk_9B.n = state + 1;
        return;

    case 2:
        timer = action->unk_96.u + 1;
        action->unk_96.u = timer;
        if ((s16)timer == 9 || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->unk_2A, 1);
            action->unk_96.u = 0;
            action->unk_9B.n++;
        }
        if (action->unk_96.s != 6) {
            return;
        }
        play_sound_if_enabled(0x808);
        return;

    case 3:
        state = action->unk_9B.n;
        action->unk_96.u = 0;
        action->unk_9B.n = state + 1;
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        action->unk_8C = update_actor_behavior_animation_and_facing;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->unk_46 &= 0x7FFF;

        return;
    }
}
