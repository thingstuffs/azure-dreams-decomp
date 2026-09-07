#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B5AC8();               /* extern */
M2C_UNK func_800B640C();               /* extern */
M2C_UNK func_800B648C();                 /* extern */
M2C_UNK func_800B6564();                            
typedef struct S_800B6508_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0xA];
    s32 unk_14;
    u8 pad_18[0x80];
    s32 unk_98;
} S_800B6508_0;   /* arg0 in func_800B6508 */

/* extern */

void func_800B6508(void *arg0) {
    func_800B648C(arg0 + 0x88, ((S_800B6508_0 *)arg0)->unk_98);
    if (((S_800B6508_0 *)arg0)->unk_08 != 0) {
        func_800B640C(((S_800B6508_0 *)arg0)->unk_04, ((S_800B6508_0 *)arg0)->unk_98, ((S_800B6508_0 *)arg0)->unk_14);
        func_800B6564();
        return;
    }
    func_800B5AC8(((S_800B6508_0 *)arg0)->unk_04, ((S_800B6508_0 *)arg0)->unk_98, ((S_800B6508_0 *)arg0)->unk_14);
}
