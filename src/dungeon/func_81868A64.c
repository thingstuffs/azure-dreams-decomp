#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_8002418C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEDB0;

typedef struct S_81868A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81868A64_0;   /* temp_v0 in func_81868A64 */

typedef struct S_81868A64_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81868A64_1;   /* temp_s0 in func_81868A64 */

typedef struct S_81868A64_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81868A64_2;   /* temp_s0_2 in func_81868A64 */

typedef struct S_81868A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81868A64_3;   /* arg1 in func_81868A64 */

void func_81868A64(s32 arg0, S_81868A64_3 *arg1, s8 arg2) {
    S_81868A64_1 *temp_s0;
    S_81868A64_2 *temp_s0_2;
    S_81868A64_0 *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0->unk_0C;
        temp_v0->unk_10 = &D_8002418C;
        temp_v0->unk_20 = arg0;
        temp_s0->unk_0E = arg2;
        temp_s0->unk_0D = arg2;
        temp_s0->unk_0C = arg2;
        func_8003DB94(temp_s0, &D_800DEDB0, 0);
        temp_s0->unk_1E = 0x1800;
        temp_s0->unk_1C = 0x1800;
        temp_s0->unk_12 = 0x7E0B;
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x60);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x10C);
        func_8004491C(temp_v0, &D_80045340);
        temp_s0_2 = temp_v0->unk_08;
        temp_s0_2->unk_02 = (u16) arg1->unk_02;
        temp_s0_2->unk_06 = (u16) arg1->unk_06;
        temp_s0_2->unk_0A = (s16) ((arg1->unk_0A + (rand() % 17)) - 8);
    }
}
