#include "common.h"

extern s32 cardBootLoadSlotMetadata(s32 slot);
extern s32 cardBootCreateSlotWindow(void *parent_object, s32 object_index);
extern void cardBootShowLoadFailureNotice(void *value);
extern void cardBootReturnFromSlotMenu(void);
extern void cardBootRestoreSavedSelectionCallback(void);
extern void cardBootEnterSlotSelectionInput(void);

/* Processes the current slot and selects callbacks when unavailable or all five are done. */
void func_80025BD4(void *state_arg) {
    void *state;
    s32 slot;

    state = state_arg;
    slot = *(s32 *)((u8 *)state + 0x24);
    if (slot < 5) {
        if (cardBootLoadSlotMetadata(slot) != 0) {
            *(s32 *)((u8 *)state + 4 + slot * 4) = cardBootCreateSlotWindow((u8 *)state - 0x20, slot);
            *(s32 *)((u8 *)state + 0x24) = *(s32 *)((u8 *)state + 0x24) + 1;
        } else {
            *(void (**)(void))((u8 *)state + 0x34) = cardBootReturnFromSlotMenu;
            cardBootShowLoadFailureNotice((u8 *)state - 0x20);
            *(void (**)(void))((u8 *)state - 0x10) = cardBootRestoreSavedSelectionCallback;
        }
    }
    if (slot == 5) {
        *(void (**)(void))((u8 *)state - 0x10) = cardBootEnterSlotSelectionInput;
    }
}
