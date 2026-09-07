#include "common.h"
#include "m2c_compat.h"

typedef struct S_80099E70_1 {
    u8 pad_00[0x44];
    void * unk_44;
} S_80099E70_1;   /* arg0 in func_80099E70 */

typedef struct S_80099E70_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80099E70_2;   /* ((S_80099E70_1 *)arg0)->unk_44 in func_80099E70 */




M2C_UNK func_80094984();                 /* extern */
extern u8 D_80082660;
extern M2C_UNK D_80099874;

typedef struct S_80099E70_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2E];
    s32 unk_40;
} S_80099E70_0;   /* arg0 in func_80099E70 */

void func_80099E70(S_80099E70_0 *arg0) {
    func_80094984(((S_80099E70_2 *)(((S_80099E70_1 *)arg0)->unk_44))->unk_14, arg0);
    *((arg0->unk_40 * 8) + &D_80082660) = 0;
    arg0->unk_04 = &D_80099874;
    arg0->unk_10 = 0;
}
