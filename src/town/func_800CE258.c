#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB9B8_4 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800CB9B8_4;   /* arg0 in func_800CB9B8 */

typedef struct S_800CB9B8_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800CB9B8_5;   /* temp_s3 in func_800CB9B8 */

typedef struct S_800CB9B8_6 {
    u8 pad_00[0x72];
    s16 unk_72;
} S_800CB9B8_6;   /* ((S_800CB9B8_4 *)arg0)->unk_9C in func_800CB9B8 */

typedef struct S_800CB9B8_7 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800CB9B8_7;   /* ((S_800CB9B8_5 *)temp_s3)->unk_08 in func_800CB9B8 */




M2C_UNK func_80033D08();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_800C30A4();                      /* extern */
s32 func_800CB7D0();                          /* extern */
M2C_UNK func_800CBA8C();                            /* extern */

typedef struct S_800CB9B8_0 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800CB9B8_0;   /* arg0 in func_800CB9B8 */

typedef struct S_800CB9B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB9B8_1;   /* temp_v0 in func_800CB9B8 */

typedef struct S_800CB9B8_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800CB9B8_2;   /* arg1 in func_800CB9B8 */

typedef struct S_800CB9B8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800CB9B8_3;   /* temp_s0 in func_800CB9B8 */

void func_800CB9B8(S_800CB9B8_0 *arg0, S_800CB9B8_2 *arg1) {
    void *temp_a0;
    S_800CB9B8_3 *temp_s0;
    S_800CB9B8_5 *temp_s3;
    S_800CB9B8_1 *temp_v0;

    temp_a0 = arg0->unk_9C;
    temp_v0 = temp_a0 - 0x20;
    temp_s0 = temp_v0->unk_08;
    temp_s3 = temp_v0->unk_0C;
    if (func_800CB7D0(temp_a0) == 0) {
        func_80033D08(arg0);
        func_800C30A4(arg0);
        return;
    }
    arg1->unk_00 = (s32) (temp_s0->unk_00 + (func_800644B8(((S_800CB9B8_6 *)(((S_800CB9B8_4 *)arg0)->unk_9C))->unk_72) * 0x140));
    arg1->unk_04 = (s32) (temp_s0->unk_04 + (func_80064584(((S_800CB9B8_6 *)(((S_800CB9B8_4 *)arg0)->unk_9C))->unk_72) * 0x140));
    arg1->unk_08 = (s32) (temp_s0->unk_08 + (((S_800CB9B8_7 *)(temp_s3->unk_08))->unk_03 << 0x11) + 0x100000);
}
