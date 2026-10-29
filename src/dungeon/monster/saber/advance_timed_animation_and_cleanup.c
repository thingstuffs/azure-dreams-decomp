#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);


#include "dungeon/monster/saber.h"
extern u8 D_80174E1C[];

typedef struct S_80172FD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FD8_0;   /* arg0 in advance_timed_animation_and_cleanup */


/* Advances an actor's timed animation sequence and performs its final cleanup. */
void advance_timed_animation_and_cleanup(ActorRecord *sequence, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;

    state = sequence->action_phase.u;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            sequence->action_phase.u = 4;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sequence->action_timer.u = 0;
        sequence->action_phase.u++;
        return;

    case 1:
        if ((s16)++sequence->action_timer.u == 4 ||
            (sprite->flags & 0x8000)) {
            sprite->frameTable = D_80174E1C;
            select_sprite_entry(sprite,
                D_80174E1C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sequence->action_timer.u = 0;
            sequence->action_phase.u++;
            return;
        }
        return;

    case 2:
        if ((s16)++sequence->action_timer.u == 9 ||
            (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            sequence->action_timer.u = 0;
            sequence->action_phase.u++;
        }
        if (sequence->action_timer.s == 6) {
            play_sound_if_enabled(0x808);
            return;
        }
        return;

    case 3:
        if ((s16)++sequence->action_timer.u == 6) {
            sprite->flags |= 0x0800;
        }
        if (sequence->action_timer.s == 15 ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            sequence->action_timer.u = 0;
            sequence->action_phase.u++;
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            sequence->unk_8C.address = &saber_behavior_entry;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    default:
        return;
    }
}
