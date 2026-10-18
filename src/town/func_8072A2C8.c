#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



s32 func_80017684(s32);
extern u8 D_80017AD0;


/* Pass D_80017AD0 to the state callback, then run operation 0xBDB. */
void func_8072A2C8(void) {
    D_80016000->unk_20->callback_270(&D_80017AD0);
    func_80017684(0xBDB);
}
