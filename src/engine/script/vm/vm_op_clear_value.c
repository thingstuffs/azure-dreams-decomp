#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_80039F28_1 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_80039F28_1;   /* ((*temp_v1 * 4) + arg0->unk_80) in vm_op_49_clear_value */


typedef struct S_80039F28_0 {
    u8 pad_00[0x1C];
    u8 * unk_1C;
    u8 pad_20[0x60];
    s32 unk_80;
} S_80039F28_0;   /* arg0 in vm_op_49_clear_value */


/* Clear the script-selected word and advance the script cursor. */
void vm_op_49_clear_value(S_80039F28_0 *vm) {
    u8 *script;

    script = vm->unk_1C;
    ((S_80039F28_1 *)(((*script * 4) + vm->unk_80)))->unk_48 = 0;
    vm->unk_1C = (u8 *) (script + 1);
}
