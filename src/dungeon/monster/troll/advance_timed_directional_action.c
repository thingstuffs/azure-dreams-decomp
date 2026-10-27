#include "common.h"
#include "dungeon/monster/troll.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_8017121C_arg1.h"
#include "dungeon/actor/status.h"

typedef struct S_801743C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_801743C4_0;   /* arg0 in advance_timed_directional_action */

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void create_targeted_motion_effect(void *, void *, void *, void *);
void create_actor_action_effect(ActorRecord *source_object, ObjectPosition *source_pos, SpriteFrameState *sprite_template, ActorRecord *actor);

extern u8 troll_action_dispatch_address[];
extern u8 D_80175DDC[8];
extern u8 D_80175DE4[8];
extern u8 D_80175DEC[8];

/* Advance a timed action sequence with directional animation and sound effects. */
void advance_timed_directional_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
    s16 timer;
    u8 state;

    state = action->action_phase.u;
    switch (state) {

    case 0:
        ((Rec_func_8017121C_arg1 *)motion)->unk_14 = 0;
        ((Rec_func_8017121C_arg1 *)motion)->unk_10 = 0;
        ((Rec_func_8017121C_arg1 *)motion)->unk_0C = 0;
        ((S_801743C4_0 *)action)->unk_96.s = 0;
        action->action_phase.u++;
        if (!(sprite->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = ((S_801743C4_0 *)action)->unk_96.s + 1;
        ((S_801743C4_0 *)action)->unk_96.s = timer;
        if ((timer != 4) && !(sprite->flags & 0x8000)) {
            return;
        }
        ((S_801743C4_0 *)action)->unk_96.s = 0;
        action->action_phase.u++;
        switch (entity->unk_48) {
        case 13:
            sprite->frameTable = D_80175DDC;
            select_sprite_entry(sprite,
                D_80175DDC[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 14:
            sprite->frameTable = D_80175DE4;
            select_sprite_entry(sprite,
                D_80175DE4[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 15:
            sprite->frameTable = D_80175DEC;
            select_sprite_entry(sprite,
                D_80175DEC[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u = 5;
            play_sound_if_enabled(0x60C);
            return;
        default:
            return;
        }

    case 2:
        timer = ((S_801743C4_0 *)action)->unk_96.s + 1;
        ((S_801743C4_0 *)action)->unk_96.s = timer;
        if ((timer == 5) || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(entity, sprite, entity->facing, 1);
            ((S_801743C4_0 *)action)->unk_96.s = 0;
            action->action_phase.u++;
        }
        if (((S_801743C4_0 *)action)->unk_96.u == 3) {
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(entity, 0x100);
            ((S_801743C4_0 *)action)->unk_8C = troll_action_dispatch_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(entity);
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;

    case 5:
        timer = ((S_801743C4_0 *)action)->unk_96.s + 1;
        ((S_801743C4_0 *)action)->unk_96.s = timer;
        if ((timer == 10) || (sprite->flags & 0x8000)) {
            sprite->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            create_targeted_motion_effect(action, motion, sprite, entity);
            create_actor_action_effect(action, motion, sprite, entity);
        }
        if ((((S_801743C4_0 *)action)->unk_96.u == 12) ||
            (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(entity, sprite, entity->facing,
                ((S_801743C4_0 *)action)->unk_AA);
        }
        if ((((S_801743C4_0 *)action)->unk_96.u == 20) ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            ((S_801743C4_0 *)action)->unk_96.s = 0;
            action->action_phase.u = 3;
        }
    case 4:
    default:
        return;
    }
}
