#include "common.h"
#include "m2c_compat.h"

typedef struct S_807B0238_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B0238_3;   /* temp_v0 in func_807B0238 */

typedef struct S_807B0238_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B0238_4;   /* arg0 in func_807B0238 */

typedef struct S_807B0238_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807B0238_5;   /* ((S_807B0238_3 *)temp_v0)->unk_08 in func_807B0238 */

typedef struct S_807B0238_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_807B0238_6;   /* ((S_807B0238_4 *)arg0)->unk_08 in func_807B0238 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800F7910;
extern M2C_UNK D_800FBE24;

typedef struct S_807B0238_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_807B0238_0;   /* temp_v0 in func_807B0238 */

typedef struct S_807B0238_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_807B0238_1;   /* temp_v1 in func_807B0238 */

typedef struct S_807B0238_2 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_807B0238_2;   /* temp_s0 in func_807B0238 */

void func_807B0238(S_807B0238_4 *arg0, s16 arg1, s32 arg2) {
    S_807B0238_2 *temp_s0;
    void *temp_v0;
    S_807B0238_1 *temp_v1;

    temp_v0 = func_8003FD64(0x212, arg0);
    if (temp_v0 != NULL) {
        ((S_807B0238_0 *)temp_v0)->unk_10 = &D_800F7910;
        func_8004491C(temp_v0, &D_80045340);
        ((S_807B0238_5 *)(((S_807B0238_3 *)temp_v0)->unk_08))->unk_02 = (s16) ((((S_807B0238_6 *)(arg0->unk_08))->unk_02 + (rand() & 0x3F)) - 0x20);
        ((S_807B0238_5 *)(((S_807B0238_3 *)temp_v0)->unk_08))->unk_06 = (s16) ((((S_807B0238_6 *)(arg0->unk_08))->unk_06 + (rand() & 0x3F)) - 0x20);
        ((S_807B0238_5 *)(((S_807B0238_3 *)temp_v0)->unk_08))->unk_0A = (s16) ((((S_807B0238_6 *)(arg0->unk_08))->unk_0A + (rand() & 0x3F)) - 0x20);
        temp_v1 = ((S_807B0238_0 *)temp_v0)->unk_0C;
        temp_s0 = temp_v0 + 0x20;
        temp_v1->unk_08 = &D_800FBE24;
        temp_v1->unk_1E = 0x1000;
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_0C = arg2;
        temp_v1->unk_06 = 8;
        temp_s0->unk_14 = arg1;
        temp_s0->unk_32 = (s16) ((rand() & 0xFF) | 0x80);
    }
}
