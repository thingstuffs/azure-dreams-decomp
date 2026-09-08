#include "common.h"
#include "m2c_compat.h"

s32 func_80025530();                             /* extern */
M2C_UNK func_800262EC();                         /* extern */
M2C_UNK func_80028320();                    /* extern */

typedef struct S_800257C0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800257C0_0;   /* arg0 in func_800257C0 */

/* Processes the record header and its resolved value, then returns success. */
s32 func_800257C0(void *record) {
    func_800262EC(record - 0x20);
    func_80028320(func_80025530(((S_800257C0_0 *)record)->unk_14), ((S_800257C0_0 *)record)->unk_08);
    return 1;
}
