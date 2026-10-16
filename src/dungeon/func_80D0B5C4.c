/* Relink of matched dungeon/func_80CE75C4; every changed retail word is a paired relocation. */
#define dungeonUpdateNormalizedGrayFade func_8014CDC4
#include "modules/dungeon_ovl_7f469800_p01.h"

/* Decrement the countdown, update three scaled output components, and flag completion. */
void func_8014CDC4(void *countdownState, s32 unused, T_80170DC4_S_80170DC4_1 *output) {
    s32 scaledRemaining;
    u16 remainingCount;

    remainingCount = ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_96 - 1;
    scaledRemaining = (s32) ((s32) (remainingCount << 16) >> 9) / ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_9E;
    ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_96 = remainingCount;
    output->unk_0C = (s8) scaledRemaining;
    output->unk_0E = (s8) scaledRemaining;
    output->unk_0D = (s8) scaledRemaining;
    if ((s16) ((T_80170DC4_S_80170DC4_0 *)countdownState)->unk_96 <= 0) {
        ((T_80170DC4_S_80170DC4_0_pre *)countdownState)[-1].unk_00 = ((T_80170DC4_S_80170DC4_0_pre *)countdownState)[-1].unk_00 | 0x8000;
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
