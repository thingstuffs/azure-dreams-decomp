#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


/* Pass the two-byte command 0x0A, 0x17 to the state callback. */
void func_806DB134(void) {
    s8 command[2];

    command[1] = 0x17;
    command[0] = 0xA;
    D_80016000->unk_20->callback_050(command);
}
