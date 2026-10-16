#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 townGetScriptFlagMask(s32);
extern void townClearScriptFlagBit(s32);

/* Consume condition 0x3EB and invoke the callback when it is active. */
s32 townConsumeCondition3EB(void) {
    if (townGetScriptFlagMask(0x3EB) != 0) {
        townClearScriptFlagBit(0x3EB);
        D_80016000->unk_20->callback_2F8(0xD, 0x200);
        return 1;
    }
    return 0;
}
