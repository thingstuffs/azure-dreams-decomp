#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C9864;
extern M2C_UNK D_800D64DC;

typedef struct S_800C9C54_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800C9C54_0;   /* arg0 in func_800C9C54 */

void func_800C9C54(S_800C9C54_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D64DC);
    arg0->unk_50 = &D_800C9864;
}
