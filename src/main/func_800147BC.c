#include "common.h"
#include "shared/game_work.h"

extern void cardBootToggleChannel(void);
extern s32 cardBootGetOperationState(void);
extern s32 cardBootDebounceCardStatusEvents(void);
extern void func_80021904(void);
extern void cardBootShowPleaseWaitNotice(void *input, void *value);

extern u8 D_8002789C[];
extern void *D_8002809C[];

/* Updates the selected callback or triggers a one-time action when no callback is selected. */
void cardBootPollCardChooserStatus(void *state) {
    s32 callback_index;
    void *callback;

    if ((gameWork.buttons != 0) && (((s32)gameWork.unk_010) & 0x20)) {
        cardBootToggleChannel();
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(void **)((u8 *)state - 0x10) = D_8002789C;
        return;
    }

    callback_index = cardBootDebounceCardStatusEvents();
    func_80021904();
    if (callback_index != 0) {
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(s32 *)((u8 *)state + 0x30) = callback_index;
        callback = D_8002809C[callback_index];
        *(s32 *)((u8 *)state + 0x34) = callback_index;
        *(void **)((u8 *)state - 0x10) = callback;
        return;
    }

    if ((cardBootGetOperationState() == 3) && (*(s32 *)((u8 *)state + 0x38) == 0)) {
        cardBootShowPleaseWaitNotice((u8 *)state - 0x20, (u8 *)state + 0x38);
        *(s32 *)((u8 *)state + 0x38) = 1;
    }
}
