#include "common.h"
#include "m2c_compat.h"

typedef struct S_80170B50_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void ** unk_10;
} S_80170B50_0;   /* temp_v0 in func_80170B50 */

typedef struct S_80170B50_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u8 pad_96[0x16];
    s32 unk_AC;
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    s16 unk_B6;
} S_80170B50_1;   /* temp_s2 in func_80170B50 */

typedef struct S_80170B50_2 {
    void * unk_00;
    u8 pad_04[0x3A];
    u16 unk_3E;
} S_80170B50_2;   /* arg0 in func_80170B50; pointer addresses record offset 0x14 */

typedef struct S_80170B50_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    M2C_UNK * unk_2C;
} S_80170B50_3;   /* temp_s1 in func_80170B50 */

typedef struct S_80170B50_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170B50_4;   /* temp_s0 in func_80170B50 */

typedef struct S_80170B50_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170B50_5;   /* arg1 in func_80170B50 */

typedef struct S_80170B50_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80170B50_6;   /* temp_a1 in func_80170B50 */

typedef struct S_80170B50_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80170B50_7;   /* arg2 in func_80170B50 */


typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Copy4;

extern u8 D_80083498[];
extern void *D_80170898[];
extern u8 D_80045340[];
extern s16 D_80083228[5];
extern M2C_UNK D_80173EB4;
extern s32 func_8003DE58();
extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern M2C_UNK func_80047784();

void func_80170B50(void *arg0, S_80170B50_5 *arg1, void *arg2, s16 arg3) {
    u32 temp_v0_2;
    u16 temp_v1_2;
    s16 temp_s6;
    S_80170B50_6 *temp_a1;
    S_80170B50_4 *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *var_a2;
    void *var_a3;

    temp_s6 = arg3;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 != NULL) {
        temp_s2 = temp_v0 + 0x20;
        ((S_80170B50_0 *)temp_v0)->unk_10 = D_80170898;
        ((S_80170B50_1 *)temp_s2)->unk_B6 = arg3;
        ((S_80170B50_1 *)temp_s2)->unk_AC = (s32) (arg0 - 0x20);
        ((S_80170B50_1 *)temp_s2)->unk_94 = (u16) ((S_80170B50_2 *)((u8 *)arg0 - 0x14))->unk_3E;
        var_a3 = arg2;
        ((S_80170B50_1 *)temp_s2)->unk_2A = (u16) ((S_80170B50_2 *)((u8 *)arg0 - 0x14))->unk_3E;
        temp_s1 = ((S_80170B50_0 *)temp_v0)->unk_0C;
        var_a2 = temp_s1;
        do {
            *(Copy4 *)var_a2 = *(Copy4 *)var_a3;
            var_a3 += 0x10;
            var_a2 += 0x10;
        } while (var_a3 != (arg2 + 0x30));
        func_8004491C(temp_v0, D_80045340, var_a2, var_a3);
        ((S_80170B50_3 *)temp_s1)->unk_2C = &D_80173EB4;
        func_80047784(temp_s1, *((u8 *)&D_80173EB4 + ((((s32) (*D_80083228 + (s16) ((S_80170B50_2 *)((u8 *)arg0 - 0x14))->unk_3E + 0x100) >> 9) & 7))), 0);
        ((S_80170B50_3 *)temp_s1)->unk_10 = 0x20;
        temp_v0_2 = ((S_80170B50_3 *)temp_s1)->unk_14 | 0xC;
        ((S_80170B50_3 *)temp_s1)->unk_14 = temp_v0_2;
        *(volatile u16 *)((s8 *)temp_s1 + 0x14) = temp_v0_2 | 0x80;
        temp_s0 = ((S_80170B50_0 *)temp_v0)->unk_08;
        temp_s0->unk_02 = (u16) arg1->unk_02;
        temp_s0->unk_06 = (u16) arg1->unk_06;
        temp_s0->unk_0A = (u16) arg1->unk_0A;
        temp_a1 = ((S_80170B50_2 *)((u8 *)arg0 - 0x14))->unk_00;
        if (func_8003DE58(temp_a1->unk_08, temp_a1, temp_s2 + 0xB0, temp_s6) != 0) {
            temp_s0->unk_02 = (u16) (temp_s0->unk_02 + ((S_80170B50_1 *)temp_s2)->unk_B0);
            temp_s0->unk_06 = (u16) (temp_s0->unk_06 + ((S_80170B50_1 *)temp_s2)->unk_B2);
            temp_s0->unk_0A = (u16) (temp_s0->unk_0A + ((S_80170B50_1 *)temp_s2)->unk_B4);
        }
        ((S_80170B50_3 *)temp_s1)->unk_1C = (u16) ((S_80170B50_7 *)arg2)->unk_1C;
        temp_v1_2 = (u16) ((S_80170B50_7 *)arg2)->unk_1E;
        ((S_80170B50_3 *)temp_s1)->unk_0E = 0x80;
        ((S_80170B50_3 *)temp_s1)->unk_0D = 0x80;
        ((S_80170B50_3 *)temp_s1)->unk_0C = 0x80;
        ((S_80170B50_3 *)temp_s1)->unk_1E = temp_v1_2;
    }
}
