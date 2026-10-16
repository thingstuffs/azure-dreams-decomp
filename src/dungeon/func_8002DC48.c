/* Relink of matched town/func_8002DC48; every changed retail word is a paired relocation. */
/* Relink of matched town/func_800C90B4; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C4174();    /* extern */
extern void func_800CB028(void *);                            /* extern */


/* Decrement the record's countdown and run its follow-up calls when it expires. */
void func_800CB3A8(Rec_func_80094268_arg0 *record, s32 forward_arg1, s32 forward_arg2) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CB028(record);
        func_800C4174(record, forward_arg1, forward_arg2);
    }
}
