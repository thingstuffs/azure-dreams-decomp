#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef s32 M2C_UNK;


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


/* Invoke the callback at offset 0x30C with value 0x9000. */
void func_8001AEC8(void) {
    D_80016000->unk_20->callback_30C(0x9000);
}
