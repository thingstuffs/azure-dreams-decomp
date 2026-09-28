#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

extern void func_80044A50(void *arg0);
extern void func_800478B8();

extern s32 D_80175220;

/* Processes input, then blends three state channels toward 0x80 and marks completion. */
void func_801749F4(u8 *task, void *context, u8 *input)
{
    s16 frames_left;
    GameWork *fade_state = &gameWork;

    if (task[0x9A] == 0) {
        D_80175220 = *(s32 *)(input + 8);
        func_800478B8(input, context, fade_state);
        if (*(u16 *)(input + 0x14) & 0xE000) {
            func_80044A50(task - 0x20);
            *(s16 *)(task + 0x96) = 0x10;
            task[0x9A]++;
            return;
        }
    } else {
        fade_state->unk_0A8 = (u8)(fade_state->unk_0A8 +
            ((s32)(0x80 - fade_state->unk_0A8) / *(s16 *)(task + 0x96)));
        fade_state->unk_0A9 = (u8)(fade_state->unk_0A9 +
            ((s32)(0x80 - fade_state->unk_0A9) / *(s16 *)(task + 0x96)));
        fade_state->unk_0AA = (u8)(fade_state->unk_0AA +
            ((s32)(0x80 - fade_state->unk_0AA) / *(s16 *)(task + 0x96)));

        frames_left = *(u16 *)(task + 0x96) - 1;
        *(s16 *)(task + 0x96) = frames_left;
        if (frames_left <= 0) {
            *(u16 *)(task - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
