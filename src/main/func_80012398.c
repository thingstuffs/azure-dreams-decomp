#include "common.h"



extern void cardBootRecheckSelectedChannel(void);
extern s32 cardBootWriteSaveViaTemporaryPath(s32, s32);
extern s32 cardBootLoadSaveAndClearMarker(s32, s32, s32);
extern void cardBootRefreshDirectorySummary(void);
extern void cardBootShowCopyFailureNotice(void *);
extern void cardBootRefreshSlotWindow(s32);
extern void cardBootResumeMenuAfterSlotRefresh(void *);
extern void func_8002519C(s32);
extern void func_80025358(s32, s32);

extern u8 D_80024F7C[];

typedef struct S_80025398_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    s32 unk_2C;
    u8 pad_30[0x10];
    s32 unk_40;
} S_80025398_0;   /* arg0 in func_80025398 */

typedef struct S_80025398_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80025398_1;

/* Process five context entries if checks pass, or schedule the fallback callback. */
void func_80025398(void *context) {
    s32 entry_value;
    s32 entry_count;
    void *owner;
    void *entry_cursor;

    if (cardBootLoadSaveAndClearMarker(((S_80025398_0 *)context)->unk_2C, 0x80010000, 0) != 0) {
        func_80025358(0x80010000, ((S_80025398_0 *)context)->unk_28);
        if (cardBootWriteSaveViaTemporaryPath(((S_80025398_0 *)context)->unk_28, 0x80010000) != 0) {
            func_8002519C(0x80010000);
            entry_count = 0;
            cardBootRefreshDirectorySummary();
            entry_cursor = context;
            do {
                entry_value = ((S_80025398_1 *)entry_cursor)->unk_04;
                entry_cursor = (u8 *)entry_cursor + 4;
                entry_count += 1;
                cardBootRefreshSlotWindow(entry_value);
            } while (entry_count < 5);
            cardBootResumeMenuAfterSlotRefresh(context);
            cardBootRecheckSelectedChannel();
            ((S_80025398_0 *)context)->unk_40 = 0;
            return;
        }
    }
    owner = (u8 *)context - 0x20;
    *(void (**)(void))((u8 *)context + 0x34) = (void (*)(void))cardBootResumeMenuAfterSlotRefresh;
    cardBootShowCopyFailureNotice(owner);
    *(void **)((u8 *)context - 0x10) = (void *)D_80024F7C;
    cardBootRecheckSelectedChannel();
    ((S_80025398_0 *)context)->unk_40 = 0;
}
