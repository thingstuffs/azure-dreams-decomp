#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef s32 M2C_UNK;


/* Invoke the callback at offset 0x30C with value 0x9000. */
void invoke_callback_30_c_9000(void) {
    D_80016000->unk_20->callback_30C(0x9000);
}
