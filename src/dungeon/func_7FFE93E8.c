#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_7FFE93E8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void);
    u8 pad_14[0x18];
    s32 unk_2C;
    u8 pad_30[0xE];
    s16 unk_3E;
    u8 pad_40[0x4];
    void * unk_44;
} S_7FFE93E8_0;   /* temp_v0 in func_7FFE93E8 */

typedef struct S_7FFE93E8_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_7FFE93E8_1;   /* temp_a0 in func_7FFE93E8 */

typedef struct S_7FFE93E8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE93E8_2;   /* temp_v1 in func_7FFE93E8 */

typedef struct S_7FFE93E8_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFE93E8_3;   /* arg0 in func_7FFE93E8 */

typedef struct S_7FFE93E8_4 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE93E8_4;   /* temp_a0_2 in func_7FFE93E8 */

typedef struct S_7FFE93E8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE93E8_5;   /* ((S_7FFE93E8_3 *)arg0)->unk_08 in func_7FFE93E8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003A7C4();
void *func_8003CF18();
void func_8010BB90(void);
extern u16 D_80094422[5];
extern M2C_UNK D_800E2BB8;

void func_7FFE93E8(S_7FFE93E8_3 *arg0, s32 arg1) {
    s32 temp_arg1;
    S_7FFE93E8_1 *temp_a0;
    S_7FFE93E8_4 *temp_a0_2;
    S_7FFE93E8_0 *temp_v0;
    S_7FFE93E8_2 *temp_v1;

    temp_v0 = func_8003CF18(0x12);
    if (temp_v0 != NULL) {
        temp_a0 = temp_v0->unk_0C;
        temp_v0->unk_10 = func_8010BB90;
        temp_v0->unk_44 = arg0;
        temp_v0->unk_3E = 0x50;
        temp_a0->unk_10 = 0x20;
        temp_a0->unk_14 =
            (u16)(temp_a0->unk_14 | 0xC);
        temp_v1 = temp_v0->unk_08;
        temp_v1->unk_02 =
            (u16)((S_7FFE93E8_5 *)(arg0->unk_08))->unk_02;
        temp_v1->unk_06 =
            (u16)((S_7FFE93E8_5 *)(arg0->unk_08))->unk_06;
        temp_v1->unk_0A =
            (u16)((S_7FFE93E8_5 *)(arg0->unk_08))->unk_0A;
        temp_a0_2 = temp_v0->unk_0C;
        temp_a0_2->unk_0C.at02.v = 0x80;
        temp_a0_2->unk_0C.at01.v = 0x80;
        temp_a0_2->unk_0C.at00.v = 0x80;
        temp_arg1 = *(volatile s32 *)&arg1;
        temp_a0_2->unk_1E = 0x1000;
        temp_a0_2->unk_1C = 0x1000;
        temp_a0_2->unk_0C.at00u.v = temp_arg1;
        temp_v0->unk_2C = temp_arg1;
        temp_a0_2->unk_12 = 0x7DCE;
        temp_a0_2->unk_14 =
            (u16)(temp_a0_2->unk_14 | 0x100);
        func_8003A7C4(temp_a0_2, &D_800E2BB8, 0);
        D_80094422[0] += 1;
    }
}
