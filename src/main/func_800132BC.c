#include "common.h"

typedef s32 M2C_UNK;

extern void *cardBootRecheckSelectedChannel(void);
extern s32 cardBootWriteSaveViaTemporaryPath(s32, s32);
extern void cardBootShowOverwriteFailureNotice(void *);
extern void cardBootSetSlotSelectionMarker(s32, s32);
extern void cardBootSetSlotDetailsSelection(s32, s32, s32);
extern void cardBootPrepareSaveBuffer(s32, s32, s32);
extern void cardBootRefreshFiveSlotObjects(void *);
extern M2C_UNK SD_Call(s32);
extern M2C_UNK func_800A6104(void);

extern s16 D_80010208[];
extern M2C_UNK D_800261C0[];
extern M2C_UNK D_80026240[];
extern s32 D_800265B8[];


/* Processes the current selection and stores the next state. */
void *cardBootSaveSelectedSlot(void *context) {
    void *result;

    cardBootPrepareSaveBuffer(0x80010000, *(s32 *)((s8 *)context + 0x2C), *(s32 *)((s8 *)context + 0x24));
    if (cardBootWriteSaveViaTemporaryPath(*(s32 *)((s8 *)context + 0x2C), 0x80010000) == 0) {
        *(u8 **)((s8 *)context + 0x34) = (u8 *)D_800265B8;
        cardBootShowOverwriteFailureNotice((u8 *)context - 0x20);
        *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800261C0;
    } else {
        cardBootSetSlotDetailsSelection(*(s32 *)((s8 *)context + 4), *(s32 *)((s8 *)context + 0x2C), 3);
        cardBootRefreshFiveSlotObjects(context);
        cardBootSetSlotSelectionMarker(*(s32 *)((s8 *)context + *(s32 *)((s8 *)context + 0x2C) * 4 + 0xC), 1);
        if (D_80010208[0] != 0) {
            func_800A6104();
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_80026240;
        } else {
            SD_Call(0x503);
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800265B8;
        }
    }
    result = cardBootRecheckSelectedChannel();
    *(s32 *)((s8 *)context + 0x40) = 0;
    return result;
}
