#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800247B8_arg1.h"

typedef struct {
    u8 bytes[12];
} U12;

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
extern M2C_UNK D_800249FC;
extern M2C_UNK D_80025B48;

typedef struct S_80024AEC_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
    u8 pad_5E[0x2A];
    s32 unk_88;
} S_80024AEC_0;   /* temp_v1 in func_80024AEC */

typedef struct S_80024AEC_1 {
    u8 pad_00[0x88];
    s32 unk_88;
} S_80024AEC_1;   /* arg0 in func_80024AEC */

typedef struct S_80024AEC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024AEC_2;   /* temp_v0 in func_80024AEC */

typedef struct S_80024AEC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024AEC_3;   /* temp_a3 in func_80024AEC */

typedef struct S_80024AEC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024AEC_4;   /* temp_v1_2 in func_80024AEC */


void func_80024AEC(S_80024AEC_1 *arg0, Rec_func_800247B8_arg1 *arg1) {
    S_80024AEC_3 *temp_a3;
    void *temp_v0;
    S_80024AEC_0 *temp_v1;
    S_80024AEC_4 *temp_v1_2;

    temp_v0 = func_8003FC64(0x12);
    temp_v1 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        temp_v1->unk_5A = 0x3C;
        temp_v1->unk_5C = 0x3C;
        temp_v1->unk_88 = (s32) arg0->unk_88;
        ((S_80024AEC_2 *)temp_v0)->unk_10 = &D_800249FC;
        func_8004491C(temp_v0, D_80045340);
        temp_a3 = ((S_80024AEC_2 *)temp_v0)->unk_0C;
        temp_a3->unk_10 = 0x40;
        temp_a3->unk_06 = 0xA;
        temp_a3->unk_14 = (u16) (temp_a3->unk_14 | 0xC);
        temp_v1_2 = ((S_80024AEC_2 *)temp_v0)->unk_08;
        temp_v1_2->unk_02 = (u16) arg1->unk_02;
        temp_v1_2->unk_06 = (u16) arg1->unk_06;
        temp_v1_2->unk_0A = (u16) arg1->unk_0A;
        temp_a3 = ((S_80024AEC_2 *)temp_v0)->unk_0C;
        temp_a3->unk_0E = 0x50;
        temp_a3->unk_0D = 0x50;
        temp_a3->unk_0C = 0x50;
        temp_a3->unk_1E = 0;
        temp_a3->unk_1C = 0;
        *(U12 *)((u8 *)temp_v0 + 0x96) = *(U12 *)&D_80025B48;
        temp_a3->unk_08 = (void *) (temp_v0 + 0x96);
    }
}
