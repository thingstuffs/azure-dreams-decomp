#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B3178();            /* extern */
M2C_UNK func_800B39E4();                         /* extern */

typedef struct S_800B32D4_0 {
    void * unk_00;
    u8 pad_04[0xA4];
    s32 unk_A8;
} S_800B32D4_0;   /* arg0 in func_800B32D4 */

typedef struct S_800B32D4_1 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B32D4_1;   /* temp_a1 in func_800B32D4 */

void func_800B32D4(S_800B32D4_0 *arg0) {
    void *temp_a1;

    func_800B39E4(arg0->unk_A8);
    temp_a1 = arg0->unk_00;
    func_800B3178(arg0->unk_A8 + 0x40, temp_a1 + 0x1C, ((S_800B32D4_1 *)temp_a1)->unk_3C);
}
