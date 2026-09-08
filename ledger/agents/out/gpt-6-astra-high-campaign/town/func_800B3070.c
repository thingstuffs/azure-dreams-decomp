#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B07D0_1 {
    u8 pad_00[0xCC];
    void * unk_CC;
} S_800B07D0_1;   /* arg0 in func_800B07D0 */

typedef struct S_800B07D0_2 {
    u8 pad_00[0x74];
    s32 unk_74;
    s32 unk_78;
} S_800B07D0_2;   /* ((S_800B07D0_1 *)arg0)->unk_CC in func_800B07D0 */




M2C_UNK func_800497F4();                    /* extern */
M2C_UNK func_8004CB2C();                         /* extern */

typedef struct S_800B07D0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B07D0_0;   /* arg0 in func_800B07D0 */

/* Process the embedded data and pass the record flag bits to its two linked handles. */
void func_800B07D0(void *record) {
    func_8004CB2C(record + 0x28);
    func_800497F4(((S_800B07D0_2 *)(((S_800B07D0_1 *)record)->unk_CC))->unk_74, ((S_800B07D0_0 *)record)->unk_1C & 2);
    func_800497F4(((S_800B07D0_2 *)(((S_800B07D0_1 *)record)->unk_CC))->unk_78, ((S_800B07D0_0 *)record)->unk_1C & 1);
}
