#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800C9F34_arg0.h"


/* Initialize the record state fields and update its flags. */
void func_800CAA94(Rec_func_800C9F34_arg0 *record) {
    record->unk_9A.as_s8 = 8;
    record->unk_96 = 0x40;
    record->unk_9B = 0;
    record->unk_8C = 0;
    record->unk_1C = (s32) ((record->unk_1C | 0x04000000) & ~0x1638);
}
