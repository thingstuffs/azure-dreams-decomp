#include "common.h"
#include "m2c_compat.h"

typedef struct S_80023EC4_0 {
    s32 unk_00;
} S_80023EC4_0;   /* arg0 in func_80023EC4; pointer addresses record offset 0x10 */


/* Clear the record's first word using a pointer to its offset 0x10. */
void func_80023EC4(void *record_data) {
    ((S_80023EC4_0 *)((u8 *)record_data - 0x10))->unk_00 = 0;
}
