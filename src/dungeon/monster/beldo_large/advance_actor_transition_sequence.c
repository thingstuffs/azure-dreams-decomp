#include "shared/audio_commands.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "engine/object.h"
#include "dungeon/effect/screen.h"
#include "dungeon/monster/beldo_large.h"







typedef struct S_8016BE20_6 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_8016BE20_6;   /* header in advance_actor_transition_sequence */

typedef struct ResetFlagWord { u16 flags; } ResetFlagWord;

extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);
extern void func_80164BA4(void *);

extern void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
extern u8 beldo_large_frame_set_3[];
extern u8 beldo_large_frame_set_11[];
extern u8 encounter_transition_pool_script[];
extern u8 D_80175DC0;
extern u8 encounter_recovery_flag;

/* Advances the actor sequence, then resets its state and updates world objects. */
void advance_actor_transition_sequence(ActorRecord *state_arg, ObjectPosition *work_arg, SpriteFrameState *sprite, ActorRecord *ctx_arg)
{
    ActorRecord *state = state_arg;
    ObjectPosition *work = work_arg;
    SpriteFrameState *actor= sprite;
    ActorRecord *ctx = ctx_arg;
    u8 *world;
    u8 *anim_table;
    u8 *object_header;
    void *object;
    void *setup_data;
    s32 object_index;
    u16 timer;
    u16 global_flags;
    u16 control_count;
    u8 state_index;

    state_index = state->action_phase.u;
    switch (state_index) {
    case 0:
        work->velocity_z = 0;
        work->velocity_y = 0;
        work->velocity_x = 0;
        state->action_timer.s = 0;
        state->action_phase.u++;
        encounter_recovery_flag = 0;
        return;

    case 1:
    {
        if (encounter_recovery_flag == 0) {
            state->action_timer.s = 0;
            state->action_phase.u++;
            (actor->frameTable) = beldo_large_frame_set_11;
            select_sprite_entry(actor,
                beldo_large_frame_set_11[((g_game_work.view.camera_rotation.parts.viewAngle + ctx->facing + 0x100) >> 9) & 7],
                0);
        } else {
            if (D_80175DC0 == 0) {
                return;
            }
            state->action_timer.s = 0;
            state->action_phase.u++;
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            (actor->frameTable) = beldo_large_frame_set_11;
            select_sprite_entry(actor,
                beldo_large_frame_set_11[((g_game_work.view.camera_rotation.parts.viewAngle + ctx->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    case 2:
        timer = state->action_timer.u + 1;
        state->action_timer.u = timer;
        if ((s16)timer == 0x11) {
            resolve_attack_damage_and_effects(ctx, actor, ctx->facing, 1);
            state->action_timer.s = 0;
            state->action_phase.u++;
        }
        if (state->action_timer.s != 0xF) {
            return;
        }
        play_sound_if_enabled(0x804);
        return;

    case 3:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        anim_table = beldo_large_frame_set_3;
        if (*(u8 **)&actor->frameTable != anim_table) {
            (actor->frameTable) = anim_table;
            select_sprite_entry(actor,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ctx->facing + 0x100) >> 9) & 7],
                0);
        }
        if (encounter_recovery_flag != 0) {
            state_index = state->action_phase.u;
            state->action_timer.s = 0;
            state->action_phase.u = state_index + 1;
            return;
        }
        state->action_phase.u += 2;
        return;

    case 4:
        timer = state->action_timer.u + 1;
        state->action_timer.u = timer;
        if ((s16)timer < 0x28) {
            return;
        }
        state_index = state->action_phase.u;
        state->action_phase.u = state_index + 1;
        return;

    case 5:
        world = *(u8 **)((u8 *)(&dungeon_actor_ring_anchor));
        if (((ActorRecord *)world)->hp < 2) {
            if (ctx->target == world) {
                setup_data = encounter_transition_pool_script;
                state->unk_8C.byte_ptr = beldo_large_action_resume_address;
                control_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
                g_dungeon_status.active_actor = 0;
                control_count++;
                g_dungeon_status.activity_counts.parts.pending_action_count = control_count;
                ctx->action_flags &= 0x7FFF;
                global_flags = ((ResetFlagWord *)&system_update_flags)->flags;
                ((ResetFlagWord *)&system_update_flags)->flags = global_flags | 8;
                enqueue_runtime_pool_script(setup_data);
                ctx->pending_turn_updates = 0;
                state->action_phase.u = 0;

                for (object_index = 0; object_index < 2; object_index++) {
                    object = (*(void **)((*(u8 **)((u8 *)(&dungeon_actor_ring_anchor))) + 0xAC + object_index * 4));
                    if (object != 0) {
                        func_80164BA4(object);
                        object_header = (u8 *)(*(void **)((*(u8 **)((u8 *)(&dungeon_actor_ring_anchor))) + 0xAC
                            + object_index * 4)) - 0x20;
                        ((S_8016BE20_6 *)object_header)->unk_10 |= 0x80000000;
                    }
                }
                return;
            }
        }
        state->unk_8C.byte_ptr = beldo_large_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(ctx);
        ctx->action_flags &= 0x7FFF;
        return;
    default:
        return;
    }
}
