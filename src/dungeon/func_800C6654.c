#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

extern u8 D_800E1B08[];
extern u8 D_800E1B2E[];

extern void display_formatted_context_message();
extern s32 func_80042900();
extern void func_800419EC();
extern s32 play_sound_if_enabled();

/* Advances a timed Z transition, waits for readiness, and marks completion. */
void advance_timed_z_transition(s16 *transition) {
    GameView *state = &g_game_work.view;
    s16 phase = transition[1];

    switch (phase) {
    case 0:
        state->unk_0A0 = state->unk_0A0 + (0x800 - state->unk_0A0) / transition[2];
        {
            u16 frames_left = (u16)transition[2] - 1;
            transition[2] = frames_left;
            if ((s32)(frames_left << 16) > 0) {
                return;
            }
            {
                DungeonGlobalStatus *settings = &g_dungeon_status;
                transition[1] = (u16)transition[1] + 1;
                state->unk_0A0 = -0x800;
                settings->unk_0A = (u16)((u16)settings->unk_0A) - 1;
                display_formatted_context_message(D_800E1B08, settings, state);
            }
        }
        return;

    case 1:
    {
        DungeonGlobalStatus *settings = &g_dungeon_status;
        if ((settings->flags & 0x10) &&
            ((func_80042900(((u8 *)D_800E3D7C), 0x1C) << 16) == 0)) {
            transition[2] = 0x10;
            transition[1] = (u16)transition[1] + 1;
            settings->unk_0A = (u16)((u16)settings->unk_0A) + 1;
            func_800419EC(0x10, 8);
            play_sound_if_enabled(0x818);
        }
    }
        return;

    case 2:
        state->unk_0A0 = state->unk_0A0 + (0 - state->unk_0A0) / transition[2];
        {
            u16 frames_left = (u16)transition[2] - 1;
            transition[2] = frames_left;
            if ((s32)(frames_left << 16) <= 0) {
                DungeonGlobalStatus *settings = &g_dungeon_status;
                u8 *message = D_800E1B2E;
                settings->unk_0A = (u16)((u16)settings->unk_0A) - 1;
                state->unk_0A0 = 0;
                display_formatted_context_message(message);
                ((u16 *)transition)[-1] = ((u16 *)transition)[-1] | 0x8000;
                object_flag_block.flags = ((u32)object_flag_block.flags) | 0x8000;
            }
        }

        break;
    }
}
