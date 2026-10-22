#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8016E3C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_8016E3C4_0;   /* arg0 in advance_the_actor_s_action_animation_triggers_timed_effects */

typedef struct S_8016E3C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016E3C4_1;   /* arg1 in advance_the_actor_s_action_animation_triggers_timed_effects */

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void func_8016B21C(void *, void *, void *, void *);
extern void func_8016B4FC(void *, void *, void *, void *);

extern u8 D_8016C4BC[];
extern u8 D_8016FDDC[8];
extern u8 D_8016FDE4[8];
extern u8 D_8016FDEC[8];

/* Advances the actor's action animation and triggers timed effects. */
void advance_the_actor_s_action_animation_triggers_timed_effects(void *action, void *motion, void *anim, ActorRecord *actor)
{
    s16 timer;
    u8 state;

    state = ((S_8016E3C4_0 *)action)->unk_9B;
    switch (state) {

    case 0:
        ((S_8016E3C4_1 *)motion)->unk_14 = 0;
        ((S_8016E3C4_1 *)motion)->unk_10 = 0;
        ((S_8016E3C4_1 *)motion)->unk_0C = 0;
        ((S_8016E3C4_0 *)action)->unk_96.s = 0;
        ((S_8016E3C4_0 *)action)->unk_9B++;
        if (!(((SpriteFrameState *)anim)->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = ((S_8016E3C4_0 *)action)->unk_96.s + 1;
        ((S_8016E3C4_0 *)action)->unk_96.s = timer;
        if ((timer != 4) && !(((SpriteFrameState *)anim)->flags & 0x8000)) {
            return;
        }
        ((S_8016E3C4_0 *)action)->unk_96.s = 0;
        ((S_8016E3C4_0 *)action)->unk_9B++;
        switch (actor->unk_48) {
        case 13:
            ((SpriteFrameState *)anim)->frameTable = D_8016FDDC;
            select_sprite_entry(anim,
                D_8016FDDC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 14:
            ((SpriteFrameState *)anim)->frameTable = D_8016FDE4;
            select_sprite_entry(anim,
                D_8016FDE4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 15:
            ((SpriteFrameState *)anim)->frameTable = D_8016FDEC;
            select_sprite_entry(anim,
                D_8016FDEC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_8016E3C4_0 *)action)->unk_9B = 5;
            play_sound_if_enabled(0x60C);
            return;
        default:
            return;
        }

    case 2:
        timer = ((S_8016E3C4_0 *)action)->unk_96.s + 1;
        ((S_8016E3C4_0 *)action)->unk_96.s = timer;
        if ((timer == 5) || (((SpriteFrameState *)anim)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
            ((S_8016E3C4_0 *)action)->unk_96.s = 0;
            ((S_8016E3C4_0 *)action)->unk_9B++;
        }
        if (((S_8016E3C4_0 *)action)->unk_96.u == 3) {
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if (((SpriteFrameState *)anim)->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            ((S_8016E3C4_0 *)action)->unk_8C = D_8016C4BC;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;

    case 5:
        timer = ((S_8016E3C4_0 *)action)->unk_96.s + 1;
        ((S_8016E3C4_0 *)action)->unk_96.s = timer;
        if ((timer == 10) || (((SpriteFrameState *)anim)->flags & 0x8000)) {
            ((SpriteFrameState *)anim)->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            func_8016B21C(action, motion, anim, actor);
            func_8016B4FC(action, motion, anim, actor);
        }
        if ((((S_8016E3C4_0 *)action)->unk_96.u == 12) ||
            (((SpriteFrameState *)anim)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim, actor->facing,
                ((S_8016E3C4_0 *)action)->unk_AA);
        }
        if ((((S_8016E3C4_0 *)action)->unk_96.u == 20) ||
            (((SpriteFrameState *)anim)->flags & 0x8000)) {
            ((SpriteFrameState *)anim)->flags &= 0xF7FF;
            ((S_8016E3C4_0 *)action)->unk_96.s = 0;
            ((S_8016E3C4_0 *)action)->unk_9B = 3;
        }
    case 4:
    default:
        return;
    }
}
