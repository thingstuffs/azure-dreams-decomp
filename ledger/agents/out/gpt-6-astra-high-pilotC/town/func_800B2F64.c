#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B06C4_0_pre {
    u16 unk_00;
} S_800B06C4_0_pre;   /* the 0x2 bytes before arg0 in func_800B06C4, addressed as arg0[-1] */

typedef struct S_800B06C4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800B06C4_0;   /* arg0 in func_800B06C4 */


M2C_UNK func_800AF148();                         /* extern */
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Set the record and global high flags, then process the stored record value. */
void func_800B06C4(void *record) {
    s32 record_value;
    s32 global_flags;

    ((S_800B06C4_0_pre *)record)[-1].unk_00 = (u16) (((S_800B06C4_0_pre *)record)[-1].unk_00 | 0x8000);
    global_flags = D_800814A0.v | 0x8000;
    record_value = ((S_800B06C4_0 *)record)->unk_04;
    D_800814A0.v = global_flags;
    func_800AF148(record_value);
}
