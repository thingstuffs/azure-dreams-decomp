#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AFD00_0 {
    u8 pad_00[0xA8];
    void * unk_A8;
} S_800AFD00_0;   /* arg0 in func_800AFD00 */

typedef struct S_800AFD00_1 {
    u8 pad_00[0x98];
    s32 unk_98;
    s32 unk_9C;
} S_800AFD00_1;   /* ((S_800AFD00_0 *)arg0)->unk_A8 in func_800AFD00 */




M2C_UNK func_800497F4();                /* extern */
M2C_UNK func_8004CB2C();                         /* extern */
M2C_UNK func_800AF9C4();                      /* extern */


void func_800AFD00(void *arg0) {
    func_8004CB2C(arg0 + 0x1C);
    func_800497F4(((S_800AFD00_1 *)(((S_800AFD00_0 *)arg0)->unk_A8))->unk_98, 0);
    func_800497F4(((S_800AFD00_1 *)(((S_800AFD00_0 *)arg0)->unk_A8))->unk_9C, 0);
    func_800AF9C4(arg0);
}
