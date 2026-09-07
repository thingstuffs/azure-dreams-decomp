#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024D90();                 /* extern */
void *func_8003FD64();                  /* extern */
extern M2C_UNK D_80024728;

typedef struct S_80024968_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024968_0;   /* temp_v0 in func_80024968 */

typedef struct S_80024968_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024968_1;   /* temp_a0 in func_80024968 */

typedef struct S_80024968_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024968_2;   /* arg1 in func_80024968 */

void *func_80024968(s32 arg0, S_80024968_2 *arg1, s16 arg2, s32 arg3) {
    S_80024968_1 *temp_a0;
    S_80024968_0 *temp_v0;

    temp_v0 = func_8003FD64(2, arg0 - 0x20);
    if (temp_v0 != NULL) {
        temp_a0 = temp_v0->unk_08;
        temp_v0->unk_10 = &D_80024728;
        temp_a0->unk_02 = (u16) arg1->unk_02;
        temp_a0->unk_06 = (u16) arg1->unk_06;
        temp_a0->unk_0A = (u16) arg1->unk_0A;
        temp_v0->unk_20 = arg3;
        func_80024D90(temp_a0, arg2);
    }
    return temp_v0;
}
