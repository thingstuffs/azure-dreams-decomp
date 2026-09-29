#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

extern u8 D_800E1B08[];
extern u8 D_800E1B2E[];

extern void func_800997FC();
extern s32 func_80042900(void *, s32, void *);
extern void func_800419EC(s32, s32);
extern void func_800A56E0(s32);

/* Advances a timed Z transition, waits for readiness, and marks completion. */
void func_800CBDB4(s16 *transition) {
    GameView *state = &gameWork.view;
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
                DungeonGlobalStatus *settings = &dungeonStatus;
                transition[1] = (u16)transition[1] + 1;
                state->unk_0A0 = -0x800;
                settings->unk_0A = (u16)((u16)settings->unk_0A) - 1;
                func_800997FC(D_800E1B08, settings, state);
            }
        }
        return;

    case 1:
        {
            DungeonGlobalStatus *settings = &dungeonStatus;
            if ((settings->flags & 0x10) &&
                ((func_80042900(((u8 *)D_800E3D7C), 0x1C, state) << 16) == 0)) {
                transition[2] = 0x10;
                transition[1] = (u16)transition[1] + 1;
                settings->unk_0A = (u16)((u16)settings->unk_0A) + 1;
                func_800419EC(0x10, 8);
                func_800A56E0(0x818);
            }
        }
        return;

    case 2:
        state->unk_0A0 = state->unk_0A0 + (0 - state->unk_0A0) / transition[2];
        {
            u16 frames_left = (u16)transition[2] - 1;
            transition[2] = frames_left;
            if ((s32)(frames_left << 16) <= 0) {
                DungeonGlobalStatus *settings = &dungeonStatus;
                u8 *message = D_800E1B2E;
                settings->unk_0A = (u16)((u16)settings->unk_0A) - 1;
                state->unk_0A0 = 0;
                func_800997FC(message);
                ((u16 *)transition)[-1] = ((u16 *)transition)[-1] | 0x8000;
                objectFlagBlock.flags = ((u32)objectFlagBlock.flags) | 0x8000;
            }
        }

        break;
    }
}
