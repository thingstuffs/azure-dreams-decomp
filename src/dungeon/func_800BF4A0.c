#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800C4C00_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_800C4C00_0;   /* arg0 in func_800C4C00 */


/* Fades the color toward the target, then back to neutral, and marks completion. */
void func_800C4C00(void *fade)
{
    GameView *color_state;
    u16 frames_left;

    color_state = &gameWork.view;
    if (((S_800C4C00_0 *)fade)->unk_04.s == 0) {
        color_state->unk_090 +=
            (((S_800C4C00_0 *)fade)->unk_00 - color_state->unk_090) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->unk_091 +=
            (((S_800C4C00_0 *)fade)->unk_01 - color_state->unk_091) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->unk_092 +=
            (((S_800C4C00_0 *)fade)->unk_02 - color_state->unk_092) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        frames_left = ((S_800C4C00_0 *)fade)->unk_06.u - 1;
        ((S_800C4C00_0 *)fade)->unk_06.u = frames_left;
        if ((s16)frames_left <= 0) {
            ((S_800C4C00_0 *)fade)->unk_06.s = 0x10;
            ((S_800C4C00_0 *)fade)->unk_04.u++;
        }
    } else {
        color_state->unk_090 +=
            (0x80 - color_state->unk_090) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->unk_091 +=
            (0x80 - color_state->unk_091) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->unk_092 +=
            (0x80 - color_state->unk_092) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        frames_left = ((S_800C4C00_0 *)fade)->unk_06.u - 1;
        ((S_800C4C00_0 *)fade)->unk_06.u = frames_left;
        if ((s16)frames_left <= 0) {
            color_state->unk_090 = 0x80;
            color_state->unk_091 = 0x80;
            color_state->unk_092 = 0x80;
            dungeonStatus.unk_0A--;
            (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
