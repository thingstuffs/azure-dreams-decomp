#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_807B09A0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B09A0_4;   /* temp_v0_2 in func_807B09A0 */

typedef struct S_807B09A0_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_807B09A0_5;   /* ((S_807B09A0_4 *)temp_v0_2)->unk_08 in func_807B09A0 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEED0;
extern M2C_UNK D_800F89B8;

typedef struct S_807B09A0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B09A0_0;   /* arg0 in func_807B09A0 */

typedef struct S_807B09A0_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_807B09A0_1;   /* temp_v0_2 in func_807B09A0 */

typedef struct S_807B09A0_2 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_807B09A0_2;   /* temp_s0 in func_807B09A0 */

typedef struct S_807B09A0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_807B09A0_3;   /* &D_800DEED0 in func_807B09A0 */

void func_807B09A0(S_807B09A0_0 *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0_3;
    u16 temp_v0;
    S_807B09A0_2 *temp_s0;
    S_807B09A0_1 *temp_v0_2;

    temp_v0 = arg0->unk_08 + 1;
    arg0->unk_08 = temp_v0;
    if (temp_v0 & 1) {
        temp_v0_2 = func_8003FD64(0x312, &D_80083498);
        if (temp_v0_2 != NULL) {
            temp_v0_2->unk_10 = &D_800F89B8;
            func_8004491C(temp_v0_2, &D_80045340);
            temp_s0 = temp_v0_2->unk_0C;
            temp_a0 = (arg0->unk_00 + (rand() % 48)) - 0x18;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)temp_v0_2)->unk_08))->unk_02 = temp_a0;
            temp_a0_2 = (arg0->unk_02 + (rand() % 48)) - 0x18;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)temp_v0_2)->unk_08))->unk_06 = temp_a0_2;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)temp_v0_2)->unk_08))->unk_0A = (u16) (arg0->unk_04 - (rand() & 7));
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)temp_v0_2)->unk_08))->unk_0C = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)temp_v0_2)->unk_08))->unk_10 = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            temp_s0->unk_1E = 0xC00;
            temp_s0->unk_1C = 0xC00;
            temp_s0->unk_10 = 0x60;
            temp_s0->unk_00 = &D_800DEED0;
            temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
            temp_v0_3 = ((S_807B09A0_3 *)(&D_800DEED0))->unk_04;
            temp_s0->unk_04 = 0;
            temp_s0->unk_05 = 0;
            temp_s0->unk_0C = 0xA0A0A0;
            temp_s0->unk_08 = temp_v0_3;
        }
    }
}
