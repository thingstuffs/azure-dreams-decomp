#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024070_0_pre {
    u16 unk_00;
} S_80024070_0_pre;   /* the 0x2 bytes before arg0 in func_80024070, addressed as arg0[-1] */

typedef struct S_80024070_0 {
    u8 pad_00[0xC];
    s16 * unk_0C;
} S_80024070_0;   /* arg0 in func_80024070 */


extern s32 D_800814A0[3];

/* Set record and global flags when the linked value is zero. */
void func_80024070(void *record) {
    if (*((S_80024070_0 *)record)->unk_0C == 0) {
        ((S_80024070_0_pre *)record)[-1].unk_00 = (u16) (((S_80024070_0_pre *)record)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
