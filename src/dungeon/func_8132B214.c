#include "common.h"

typedef struct S_80172A14_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80172A14_0;   /* arg0 in func_80172A14 */

typedef struct S_80172A14_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172A14_1;   /* temp_v0 in func_80172A14 */

typedef struct S_80172A14_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    void * unk_20;
    void * unk_24;
} S_80172A14_2;   /* temp_v0_2 in func_80172A14 */

typedef struct S_80172A14_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80172A14_3;   /* temp_a0 in func_80172A14 */

typedef struct S_80172A14_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172A14_4;   /* temp_v1 in func_80172A14 */

typedef struct S_80172A14_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172A14_5;   /* arg1 in func_80172A14 */

typedef struct S_80172A14_6 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80172A14_6;   /* temp_a0_2 in func_80172A14 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern u8 D_80045C34[];
extern u8 D_80172874[];
extern u8 D_80174ABC[];

void func_80172A14(void *arg0, S_80172A14_5 *arg1) {
    S_80172A14_3 *temp_a0;
    register void *temp_a0_2 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *temp_v0;
    S_80172A14_2 *temp_v0_2;
    S_80172A14_4 *temp_v1;

    temp_v0 = func_8003FD64(0x12, (u8 *)arg0 - 0x20);
    if (temp_v0 != 0) {
        ((S_80172A14_0 *)arg0)->unk_AC = temp_v0;
        ((S_80172A14_1 *)temp_v0)->unk_10 = D_80172874;
        func_8004491C(temp_v0, D_80045C34);
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        temp_v0_2->unk_18 = 5;
        temp_v0_2->unk_20 = arg0;
        temp_v0_2->unk_24 = arg1;
        temp_a0 = ((S_80172A14_1 *)temp_v0)->unk_0C;
        temp_a0->unk_10 = 0x40;
        temp_a0->unk_14 |= 0xC;
        temp_v1 = ((S_80172A14_1 *)temp_v0)->unk_08;
        temp_v1->unk_02 = arg1->unk_02;
        temp_v1->unk_06 = arg1->unk_06;
        temp_v1->unk_0A = arg1->unk_0A;
        temp_a0_2 = ((S_80172A14_1 *)temp_v0)->unk_0C;
        ((S_80172A14_6 *)temp_a0_2)->unk_1E = 0xA00;
        ((S_80172A14_6 *)temp_a0_2)->unk_1C = 0xA00;
        ((S_80172A14_6 *)temp_a0_2)->unk_0E = 0;
        ((S_80172A14_6 *)temp_a0_2)->unk_0D = 0;
        ((S_80172A14_6 *)temp_a0_2)->unk_0C = 0;
        ((S_80172A14_6 *)temp_a0_2)->unk_08 = D_80174ABC;
    }
}
