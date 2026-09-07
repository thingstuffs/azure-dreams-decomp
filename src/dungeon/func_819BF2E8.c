#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800247C0;
extern M2C_UNK D_80045340;

typedef struct S_80024AE8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
} S_80024AE8_0;   /* temp_v0_2 in func_80024AE8 */

typedef struct S_80024AE8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024AE8_1;   /* temp_v0 in func_80024AE8 */

typedef struct S_80024AE8_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024AE8_2;   /* temp_v1 in func_80024AE8 */

typedef struct S_80024AE8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024AE8_3;   /* arg1 in func_80024AE8 */

typedef struct S_80024AE8_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024AE8_4;   /* temp_v1_2 in func_80024AE8 */

void func_80024AE8(s32 arg0, S_80024AE8_3 *arg1) {
    void *temp_v0;
    S_80024AE8_0 *temp_v0_2;
    S_80024AE8_2 *temp_v1;
    S_80024AE8_4 *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v0_2 = temp_v0 + 0x20;
        temp_v0_2->unk_28 = 0x1E;
        temp_v0_2->unk_2A = 0x1E;
        temp_v0_2->unk_20 = arg0;
        ((S_80024AE8_1 *)temp_v0)->unk_10 = &D_800247C0;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = ((S_80024AE8_1 *)temp_v0)->unk_08;
        temp_v1->unk_00 = (s32) arg1->unk_00;
        temp_v1->unk_04 = (s32) arg1->unk_04;
        temp_v1->unk_08 = (s32) arg1->unk_08;
        temp_v1_2 = ((S_80024AE8_1 *)temp_v0)->unk_0C;
        temp_v1_2->unk_14 = (u16) (temp_v1_2->unk_14 | 0x80);
    }
}
