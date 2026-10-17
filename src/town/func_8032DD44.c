#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


extern s32 townCheckCallbackRecordBytes(s32, s32);
extern void townSetCurrentEntryScriptFlag(void);
extern void townApplyEntryPosition(void *, void *, s32, s32);
extern void townSetScriptFlagBit(s32);
extern s32 townGetScriptFlagMask(s32);
extern M2C_UNK D_8001BE2C;
extern M2C_UNK D_8001BE44;
extern M2C_UNK D_8001C354;


/* Handles the conditional callback and selects data according to flag 0x1460. */
void townHandleConditionalEventCallback(s32 context, s32 unused, s32 event_code) {
    void *selected_data;

    if ((event_code == 0x1E) && (townCheckCallbackRecordBytes(0xD, 1) != 0)) {
        D_80016000->unk_20->callback_078(0);
        townSetScriptFlagBit(0x1460);
        townSetCurrentEntryScriptFlag();
    }

    if (townGetScriptFlagMask(0x1460) != 0) {
        selected_data = &D_8001BE2C;
    } else {
        selected_data = &D_8001BE44;
    }
    townApplyEntryPosition(selected_data, &D_8001C354, context, event_code);
}
