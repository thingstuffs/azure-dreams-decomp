#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026920();                         /* extern */
M2C_UNK func_80027AFC();                    /* extern */

typedef struct S_80026784_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_80026784_0;   /* arg0 in func_80026784 */

/* Update the base record and pass its paired fields to the next helper. */
void func_80026784(void *record_part) {
    func_80026920(record_part - 0x20);
    func_80027AFC(((S_80026784_0 *)record_part)->unk_20, ((S_80026784_0 *)record_part)->unk_24);
}
