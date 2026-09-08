#include "common.h"
#include "m2c_compat.h"

typedef struct S_800ADB8C_0_pre {
    u16 unk_00;
} S_800ADB8C_0_pre;   /* the 0x2 bytes before arg0 in func_800ADB8C, addressed as arg0[-1] */

typedef struct S_800ADB8C_0 {
    u8 * unk_00;
} S_800ADB8C_0;   /* arg0 in func_800ADB8C */


extern s32 D_800814A0[];

/* Sets the record and global 0x8000 flags when the referenced byte is nonzero. */
void func_800ADB8C(void *record) {
    if (*((S_800ADB8C_0 *)record)->unk_00 != 0) {
        ((S_800ADB8C_0_pre *)record)[-1].unk_00 = (u16) (((S_800ADB8C_0_pre *)record)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
