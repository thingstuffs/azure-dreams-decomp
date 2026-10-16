#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AE494_0 {
    s32 unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} S_800AE494_0;   /* arg0 in townRunItemMenuRecordHandlers; pointer addresses record offset 0x10 */


void townSetItemMenuRecordActive();                         /* extern */
void townScheduleItemMenuChildRelease();                         /* extern */

/* Pass the record handles to their handlers and clear its secondary handle and status. */
void townRunItemMenuRecordHandlers(void *record_payload) {
    townScheduleItemMenuChildRelease(((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_14);
    ((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_14 = 0;
    townSetItemMenuRecordActive(((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_10);
    ((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_00 = 0;
}
