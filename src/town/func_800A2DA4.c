#include "common.h"
#include "m2c_compat.h"

s32 townCreateAnPositionInitializesGraphicsState();                     /* extern */
void *townGetAddressGlobal80100AA0();                              /* extern */
void townHandleShiftEntriesLeftUntilFreeEntryLimitClearTail();                            /* extern */

typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;   /* temp_v0 in townRunTheFollowUpActionHasEligibleTypePassesCheck */

/* Run the follow-up action when the current record has an eligible type and passes the check. */
void townRunTheFollowUpActionHasEligibleTypePassesCheck(s32 check_value) {
    u8 record_type;
    S_800A0504_0 *record;

    record = townGetAddressGlobal80100AA0();
    record_type = record->unk_01;
    if ((record_type != 0) && (record_type != 0x13) && (townCreateAnPositionInitializesGraphicsState(record, check_value) != 0)) {
        townHandleShiftEntriesLeftUntilFreeEntryLimitClearTail();
    }
}
