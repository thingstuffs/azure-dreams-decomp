#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
extern u32 D_80083208[3];
extern u8 D_800DEAE0[];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
void func_8003DB94();                    /* extern */
s32 func_800BCB04();               /* extern */
extern M2C_UNK D_800F6070;

typedef struct S_800F6090_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800F6090_0;   /* temp_v0 in func_800F6090 */

typedef struct S_800F6090_1 {
    u8 pad_00[0xC];
    u32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800F6090_1;   /* temp_s0 in func_800F6090 */

typedef struct S_800F6090_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F6090_2;   /* temp_s0_2 in func_800F6090 */

void func_800F6090(s16 arg0, s16 arg1) {
    S_800F6090_1 *temp_s0;
    S_800F6090_2 *temp_s0_2;
    S_800F6090_0 *temp_v0;
    u32 temp_v1;

    temp_v0 = func_8003FC64(0x16);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800F6070;
        func_8004491C(temp_v0, D_80045340);
        temp_s0 = temp_v0->unk_0C;
        temp_v1 = (u32) *D_80083208;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_0C = temp_v1;
        func_8003DB94(temp_s0, D_800DEAE0, 0);
        temp_s0->unk_10 = 0x20;
        temp_s0->unk_14 = 0xC;
        temp_s0_2 = temp_v0->unk_08;
        temp_s0_2->unk_02 = arg0;
        temp_s0_2->unk_06 = arg1;
        temp_s0_2->unk_0A = (s16) (func_800BCB04(arg0 & 0xFFFF, arg1 & 0xFFFF, -0x400) - 8);
    }
}
