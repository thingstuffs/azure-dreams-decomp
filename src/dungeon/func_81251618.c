#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern s16 D_80083228[5];
void *func_8003FD64();
M2C_UNK func_8004491C();
void func_80047784();
extern M2C_UNK D_80170D44;
extern u8 D_80173EB4[8];

typedef struct S_80170E18_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
} S_80170E18_0;   /* temp_v1 in func_80170E18 */

typedef struct S_80170E18_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80170E18_1;   /* temp_v0 in func_80170E18 */

typedef struct S_80170E18_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x8];
    M2C_UNK * unk_2C;
} S_80170E18_2;   /* temp_s0 in func_80170E18 */

typedef struct S_80170E18_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170E18_3;   /* arg3 in func_80170E18 */

typedef struct S_80170E18_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170E18_4;   /* temp_v1_2 in func_80170E18 */

typedef struct S_80170E18_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170E18_5;   /* arg1 in func_80170E18 */

void func_80170E18(void *unused, S_80170E18_5 *arg1, void *arg2, S_80170E18_3 *arg3) {
    s32 temp_t0;
    S_80170E18_2 *temp_s0;
    void *temp_v0;
    S_80170E18_0 *temp_v1;
    S_80170E18_4 *temp_v1_2;
    void *var_a2;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    temp_v0 = func_8003FD64(0x112, D_80083498);
    var_a2 = arg2;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_96 = 7;
        temp_v1->unk_A8 = 7;
        ((S_80170E18_1 *)temp_v0)->unk_10 = &D_80170D44;
        temp_v1->unk_AC = arg1;
        temp_s0 = ((S_80170E18_1 *)temp_v0)->unk_0C;
        src = (Block16 *)var_a2;
        dst = (Block16 *)temp_s0;
        end = src + 3;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_0E = 0x50;
        temp_s0->unk_0D = 0x50;
        temp_s0->unk_0C = 0x50;
        temp_s0->unk_10 = 0x20;
        temp_s0->unk_12 = 0xFF80;
        temp_s0->unk_22 = 0xFFF1;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        func_8004491C(temp_v0, D_80045340, src, dst);
        temp_s0->unk_2C = &D_80173EB4;
        func_80047784(temp_s0, *((((s32) (*D_80083228 + arg3->unk_2A + 0x100) >> 9) & 7) + D_80173EB4), 0);
        temp_v1_2 = ((S_80170E18_1 *)temp_v0)->unk_08;
        temp_v1_2->unk_02 = (u16) arg1->unk_02;
        temp_v1_2->unk_06 = (u16) arg1->unk_06;
        temp_v1_2->unk_0A = (u16) arg1->unk_0A;
    }
}
