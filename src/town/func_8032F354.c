#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"


typedef struct S_80019B54_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019B54_1;   /* (arg1 * 0x10) + ((Rec_func_800165F4_arg0 *)arg0)->unk_10 in townApplySelectedEntryValues */


extern s32 townCheckRecordFlagIfUnblocked(Rec_func_800165F4_arg0 *);
extern s32 townSetScriptFlagBit(s16 value);
extern s32 townClearScriptFlagBit(s16 value);

/* Apply the selected entry and record values if the record passes its check. */
s32 townApplySelectedEntryValues(Rec_func_800165F4_arg0 *record, s32 entry_index) {
    if (townCheckRecordFlagIfUnblocked(record) != 0) {
        townSetScriptFlagBit(((S_80019B54_1 *)((entry_index * 0x10) + record->unk_10))->unk_0C);
        townClearScriptFlagBit(record->unk_18);
        return 1;
    }
    return 0;
}
