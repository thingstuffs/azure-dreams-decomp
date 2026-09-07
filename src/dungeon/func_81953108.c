#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void *func_8003FD64();                  /* extern */
extern M2C_UNK D_80024830;

typedef struct S_80024908_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80024908_0;   /* temp_v0 in func_80024908 */

typedef struct S_80024908_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x16];
    s16 unk_26;
    u8 pad_28[0x4];
    s16 unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
} S_80024908_1;   /* temp_v0_2 in func_80024908 */

void func_80024908(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    void *temp_v0;
    S_80024908_1 *temp_v0_2;

    temp_v0 = func_8003FD64(0x200, arg0);
    if (temp_v0 != NULL) {
        ((S_80024908_0 *)temp_v0)->unk_10 = &D_80024830;
        temp_v0_2 = temp_v0 + 0x20;
        temp_v0_2->unk_26 = arg1;
        temp_v0_2->unk_0C = arg3;
        temp_v0_2->unk_30 = arg2;
        temp_v0_2->unk_2C = 0x40;
    }
}
