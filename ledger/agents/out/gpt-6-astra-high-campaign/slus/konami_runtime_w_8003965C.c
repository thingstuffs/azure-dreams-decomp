#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003965C_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8003965C_0;   /* arg0 in func_8003965C */

typedef struct S_8003965C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8003965C_1;   /* temp_a2 in func_8003965C */


/* Sets the event-script instruction pointer to the little-endian address at its current position. */
void func_8003965C(S_8003965C_0 *vm) {
    S_8003965C_1 *jump_address;

    jump_address = vm->unk_1C;
    vm->unk_1C = (void *) (jump_address->unk_00 + (jump_address->unk_01 << 8) + (jump_address->unk_02 << 0x10) + (jump_address->unk_03 << 0x18));
}
