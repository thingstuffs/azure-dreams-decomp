#include "shared/audio_commands.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"

typedef struct S_8016BE20_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
} S_8016BE20_0;   /* state in advance_actor_transition_sequence */

typedef struct S_8016BE20_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016BE20_1;   /* work in advance_actor_transition_sequence */

typedef struct S_8016BE20_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
} S_8016BE20_2;   /* ctx in advance_actor_transition_sequence */

typedef struct S_8016BE20_4 {
    u8 pad_00[0x28];
    u8 unk_28;
} S_8016BE20_4;   /* world in advance_actor_transition_sequence */

typedef struct S_8016BE20_6 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_8016BE20_6;   /* header in advance_actor_transition_sequence */

typedef struct ResetFlagWord { u16 flags; } ResetFlagWord;

extern void enqueue_runtime_pool_script(void *);
extern void select_sprite_entry(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void func_80164BA4(void *);

extern u8 beldo_large_action_resume_address[];
extern u8 beldo_large_frame_set_3[];
extern u8 beldo_large_frame_set_11[];
extern u8 encounter_transition_pool_script[];
extern u8 D_80175DC0;
extern u8 encounter_recovery_flag;

/* Advances the actor sequence, then resets its state and updates world objects. */
void advance_actor_transition_sequence(void *state_arg, void *work_arg, void *actor_arg, void *ctx_arg)
{
    void *state = state_arg;
    void *work = work_arg;
    SpriteFrameState *actor= actor_arg;
    void *ctx = ctx_arg;
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

    state_index = ((S_8016BE20_0 *)state)->unk_9B.n;
    switch (state_index) {
    case 0:
        ((S_8016BE20_1 *)work)->unk_14 = 0;
        ((S_8016BE20_1 *)work)->unk_10 = 0;
        ((S_8016BE20_1 *)work)->unk_0C = 0;
        ((S_8016BE20_0 *)state)->unk_96.s = 0;
        ((S_8016BE20_0 *)state)->unk_9B.n++;
        encounter_recovery_flag = 0;
        return;

    case 1:
    {
        if (encounter_recovery_flag == 0) {
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n++;
            (actor->frameTable) = beldo_large_frame_set_11;
            select_sprite_entry(actor,
                beldo_large_frame_set_11[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016BE20_2 *)ctx)->unk_2A + 0x100) >> 9) & 7],
                0);
        } else {
            if (D_80175DC0 == 0) {
                return;
            }
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n++;
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            (actor->frameTable) = beldo_large_frame_set_11;
            select_sprite_entry(actor,
                beldo_large_frame_set_11[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016BE20_2 *)ctx)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    case 2:
        timer = ((S_8016BE20_0 *)state)->unk_96.u + 1;
        ((S_8016BE20_0 *)state)->unk_96.u = timer;
        if ((s16)timer == 0x11) {
            resolve_attack_damage_and_effects(ctx, actor, ((S_8016BE20_2 *)ctx)->unk_2A, 1);
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n++;
        }
        if (((S_8016BE20_0 *)state)->unk_96.s != 0xF) {
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
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016BE20_2 *)ctx)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        if (encounter_recovery_flag != 0) {
            state_index = ((S_8016BE20_0 *)state)->unk_9B.v;
            ((S_8016BE20_0 *)state)->unk_96.s = 0;
            ((S_8016BE20_0 *)state)->unk_9B.n = state_index + 1;
            return;
        }
        ((S_8016BE20_0 *)state)->unk_9B.n += 2;
        return;

    case 4:
        timer = ((S_8016BE20_0 *)state)->unk_96.u + 1;
        ((S_8016BE20_0 *)state)->unk_96.u = timer;
        if ((s16)timer < 0x28) {
            return;
        }
        state_index = ((S_8016BE20_0 *)state)->unk_9B.n;
        ((S_8016BE20_0 *)state)->unk_9B.n = state_index + 1;
        return;

    case 5:
        world = *(u8 **)((u8 *)(&dungeon_actor_ring_anchor));
        if (((S_8016BE20_4 *)world)->unk_28 < 2) {
            if (((S_8016BE20_2 *)ctx)->unk_60 == world) {
                setup_data = encounter_transition_pool_script;
                ((S_8016BE20_0 *)state)->unk_8C = beldo_large_action_resume_address;
                control_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
                g_dungeon_status.active_actor = 0;
                control_count++;
                g_dungeon_status.activity_counts.parts.pending_action_count = control_count;
                ((S_8016BE20_2 *)ctx)->unk_46 &= 0x7FFF;
                global_flags = ((ResetFlagWord *)&system_update_flags)->flags;
                ((ResetFlagWord *)&system_update_flags)->flags = global_flags | 8;
                enqueue_runtime_pool_script(setup_data);
                ((S_8016BE20_2 *)ctx)->unk_6D = 0;
                ((S_8016BE20_0 *)state)->unk_9B.n = 0;

                for (object_index = 0; object_index < 2; object_index++) {
                    object = (*(void **)((u8 *)(*(u8 **)((u8 *)(&dungeon_actor_ring_anchor))) + 0xAC + object_index * 4));
                    if (object != 0) {
                        func_80164BA4(object);
                        object_header = (u8 *)(*(void **)((u8 *)(*(u8 **)((u8 *)(&dungeon_actor_ring_anchor))) + 0xAC
                            + object_index * 4)) - 0x20;
                        ((S_8016BE20_6 *)object_header)->unk_10 |= 0x80000000;
                    }
                }
                return;
            }
        }
        ((S_8016BE20_0 *)state)->unk_8C = beldo_large_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(ctx);
        ((S_8016BE20_2 *)ctx)->unk_46 &= 0x7FFF;
        return;
    default:
        return;
    }
}
