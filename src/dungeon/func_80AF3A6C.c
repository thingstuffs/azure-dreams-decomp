#include "modules/dungeon_resource10_slot0.h"

void func_8017526C(u8 *task, void *context, u8 *input)
{
    s16 frames_left;
    GameWork *fade_state = &gameWork;

    if (task[0x9A] == 0) {
        (*(s32 *)D_80175A84) = *(s32 *)(input + 8);
        func_800478B8(input);
        if (*(u16 *)(input + 0x14) & 0xE000) {
            func_80044A50(task - 0x20);
            *(s16 *)(task + 0x96) = 0x10;
            task[0x9A]++;
            return;
        }
    } else {
        fade_state->view.unk_090 = (u8)(fade_state->view.unk_090 +
            ((s32)(0x80 - fade_state->view.unk_090) / *(s16 *)(task + 0x96)));
        fade_state->view.unk_091 = (u8)(fade_state->view.unk_091 +
            ((s32)(0x80 - fade_state->view.unk_091) / *(s16 *)(task + 0x96)));
        fade_state->view.unk_092 = (u8)(fade_state->view.unk_092 +
            ((s32)(0x80 - fade_state->view.unk_092) / *(s16 *)(task + 0x96)));

        frames_left = *(u16 *)(task + 0x96) - 1;
        *(s16 *)(task + 0x96) = frames_left;
        if (frames_left <= 0) {
            *(u16 *)(task - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
