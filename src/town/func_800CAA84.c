#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C81E4_0 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800C81E4_0;   /* arg0 in func_800C81E4 */

typedef struct S_800C81E4_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800C81E4_1;   /* arg1 in func_800C81E4 */


M2C_UNK func_800C8194(S_800C81E4_0 *, S_800C81E4_1 *);
void func_800C81E4(S_800C81E4_0 *arg0, S_800C81E4_1 *arg1) {
    func_800C8194(arg0, arg1);
    if (arg0->unk_6C > 0) {
        do { arg1->unk_06 = (u16) (arg1->unk_06 + 8); } while (0);
        arg0->unk_6C = (s16) ((u16) arg0->unk_6C - 1);
    }
}
