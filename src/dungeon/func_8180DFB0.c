#include "common.h"

typedef struct S_80026FB0_0 {
    u8 pad_00[0x64];
    union { s16 s; u16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
} S_80026FB0_0;   /* arg0 in func_80026FB0 */

typedef struct S_80026FB0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80026FB0_1;   /* arg2 in func_80026FB0 */



extern s32 D_800814A0;

/* Waits, then fades the color channels toward 0x80 and flags completion. */
void func_80026FB0(void *effect, s32 unused, void *color)
{
    s16 phase;
    s32 frames_left;
    s32 intensity;

    phase = ((S_80026FB0_0 *)effect)->unk_64.s;
    switch (phase) {
    default:
        return;

    case 0:
        frames_left = (u16)((S_80026FB0_0 *)effect)->unk_66 - 1;
        ((S_80026FB0_0 *)effect)->unk_66 = frames_left;
        if ((frames_left << 16) <= 0) {
            ((S_80026FB0_0 *)effect)->unk_66 = 0x10;
            ((S_80026FB0_0 *)effect)->unk_64.u += 1;
        }
        break;

    case 1:
        intensity = ((S_80026FB0_1 *)color)->unk_0C;
        intensity = intensity + ((0x80 - intensity) / ((S_80026FB0_0 *)effect)->unk_66);
        ((S_80026FB0_1 *)color)->unk_0C = intensity;
        ((S_80026FB0_1 *)color)->unk_0E = intensity;
        ((S_80026FB0_1 *)color)->unk_0D = intensity;
        frames_left = (u16)((S_80026FB0_0 *)effect)->unk_66 - 1;
        ((S_80026FB0_0 *)effect)->unk_66 = frames_left;
        if ((frames_left << 16) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    }
}
