#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BA8C4_0_pre {
    u16 unk_00;
} S_800BA8C4_0_pre;   /* the 0x2 bytes before arg0 in func_800BA8C4, addressed as arg0[-1] */

typedef struct S_800BA8C4_0 {
    u8 pad_00[0x98];
    u8 * unk_98;
} S_800BA8C4_0;   /* arg0 in func_800BA8C4 */


M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                            /* extern */
extern volatile struct { s32 v; s32 pad[2]; } D_800814A0;

void func_800BA8C4(void *arg0) {
    if (*((S_800BA8C4_0 *)arg0)->unk_98 == 0) {
        func_8008F134();
        func_80033D08(arg0);
        ((S_800BA8C4_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800BA8C4_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0.v |= 0x8000;
    }
}
