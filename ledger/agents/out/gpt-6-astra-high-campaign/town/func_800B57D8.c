#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B2F38_0 {
    u8 pad_00[0xA8];
    void * unk_A8;
} S_800B2F38_0;   /* arg0 in func_800B2F38 */

typedef struct S_800B2F38_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    M2C_UNK ** unk_14;
} S_800B2F38_1;   /* ((S_800B2F38_0 *)arg0)->unk_A8 in func_800B2F38 */




M2C_UNK func_8004CBFC();      /* extern */
extern M2C_UNK D_80071244;
extern M2C_UNK D_800792DC;


/* Apply D_800792DC using the linked value and set the linked target to D_80071244. */
void func_800B2F38(void *record) {
    func_8004CBFC(record + 0x1C, &D_800792DC, ((S_800B2F38_1 *)(((S_800B2F38_0 *)record)->unk_A8))->unk_10);
    *((S_800B2F38_1 *)(((S_800B2F38_0 *)record)->unk_A8))->unk_14 = &D_80071244;
}
