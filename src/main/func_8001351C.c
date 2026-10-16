#include "common.h"

extern s32 D_80083E98[];
extern s32 D_8002644C[];
extern s32 D_800263C0[];

s32 cardBootGetRemainingBlockSummary(void);
s32 cardBootCountCachedSlots(void);
void func_800264D8(void *context);
void cardBootEnterInsufficientSpaceAdvice(void *record_part);

/* Selects a state table or handler based on the context and current status. */
void mainRouteSaveSlotValidation(void *context) {
    if (D_80083E98[*(s32 *)((s8 *)context + 0x2C) << 5] != 0) {
        *(s32 **)((s8 *)context - 0x10) = D_8002644C;
        return;
    }
    if (cardBootGetRemainingBlockSummary() >= 3) {
        *(s32 **)((s8 *)context - 0x10) = D_800263C0;
        return;
    }
    if (cardBootCountCachedSlots() != 0) {
        cardBootEnterInsufficientSpaceAdvice(context);
        return;
    }
    func_800264D8(context);
}
