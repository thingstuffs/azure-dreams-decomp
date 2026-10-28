#include "common.h"
#include "dungeon/monster/troll.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"

typedef struct S_801623C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_801623C4_0;   /* arg0 in advance_timed_action_and_effects */


extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void func_8015F21C(void *, void *, void *, void *);
extern void func_8015F4FC(ActorRecord *source_object, ObjectPosition *source_pos, SpriteFrameState *sprite_template, ActorRecord *actor);

extern u8 D_801604BC[];
extern u8 D_80163DDC[8];
extern u8 D_80163DE4[8];
extern u8 D_80163DEC[8];

/* Advance the actor's timed action sequence and update its animation and effects. */
void advance_timed_action_and_effects(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor) {
    s16 timer;
    u8 state;

    state = action->action_phase.u;
    switch (state) {

    case 0:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_timer.u = 0;
        action->action_phase.u++;
        if (!(animation->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer != 4) && !(animation->flags & 0x8000)) {
            return;
        }
        action->action_timer.u = 0;
        action->action_phase.u++;
        switch (actor->unk_48) {
        case 13:
            animation->frameTable = D_80163DDC;
            select_sprite_entry(animation,
                D_80163DDC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 14:
            animation->frameTable = D_80163DE4;
            select_sprite_entry(animation,
                D_80163DE4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 15:
            animation->frameTable = D_80163DEC;
            select_sprite_entry(animation,
                D_80163DEC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u = 5;
            play_sound_if_enabled(0x60C);
            return;
        default:
            return;
        }

    case 2:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer == 5) || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            action->action_timer.u = 0;
            action->action_phase.u++;
        }
        if (action->action_timer.s == 3) {
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if (animation->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = D_801604BC;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;

    case 5:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer == 10) || (animation->flags & 0x8000)) {
            animation->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            func_8015F21C(action, motion, animation, actor);
            func_8015F4FC(action, motion, animation, actor);
        }
        if ((action->action_timer.s == 12) ||
            (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing,
                action->unk_AA);
        }
        if ((action->action_timer.s != 20) &&
            !(animation->flags & 0x8000)) {
            break;
        }
        animation->flags &= 0xF7FF;
        action->action_timer.u = 0;
        action->action_phase.u = 3;

    case 4:
    default:
        break;
    }
}
