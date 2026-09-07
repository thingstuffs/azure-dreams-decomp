#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002569C_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002569C_6;   /* temp_v0 in func_8002569C */




void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80025160;
extern M2C_UNK D_80025340;
extern u16 D_8002632A;
extern u8 D_80026478[];
extern s16 D_80026878;

typedef struct S_8002569C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_8002569C_0;   /* temp_v0 in func_8002569C */

typedef struct S_8002569C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_8002569C_1;   /* temp_s2 in func_8002569C */

typedef struct S_8002569C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8002569C_2;   /* arg0 in func_8002569C */

typedef struct S_8002569C_3 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u8 pad_1E[0x4];
    u16 unk_22;
} S_8002569C_3;   /* temp_v1 in func_8002569C */

typedef struct S_8002569C_4 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8002569C_4;   /* temp_a0 in func_8002569C */

typedef struct S_8002569C_5 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8002569C_5;   /* temp_v0_3 in func_8002569C */

void *func_8002569C(S_8002569C_2 *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s16 temp_v0_2;
    u16 temp_a3;
    u16 temp_a1;
    u16 temp_a1_2;
    u16 temp_v1_2;
    S_8002569C_4 *temp_a0;
    u8 *temp_base;
    S_8002569C_1 *temp_s2;
    void *temp_v0;
    S_8002569C_5 *temp_v0_3;
    S_8002569C_3 *temp_v1;

    temp_v0 = func_8003FD64(0x202, arg4);
    if (temp_v0 != NULL) {
        ((S_8002569C_0 *)temp_v0)->unk_10 = &D_80025160;
        func_8004491C(temp_v0, &D_80025340);
        temp_s2 = ((S_8002569C_0 *)temp_v0)->unk_08;
        temp_s2->unk_02 = (s16) (arg0->unk_02 + ((s32) (func_80064584(arg1) * arg2) >> 0xF));
        temp_s2->unk_06 = (s16) (arg0->unk_06 + ((s32) (func_800644B8(arg1) * arg2) >> 0xF));
        temp_v0_2 = arg0->unk_0A + ((s32) (arg3 << 0x10) >> 0x13);
        temp_s2->unk_0A = temp_v0_2;
        if (D_80026878 < temp_v0_2) {
            temp_s2->unk_0A = D_80026878;
        }
        temp_s2->unk_0E = (u16) arg0->unk_02;
        temp_s2->unk_12 = (u16) arg0->unk_06;
        temp_s2->unk_16 = (u16) arg0->unk_0A;
        temp_v1 = (void *) 0xE04020;
        (*(s32 *)((u8 *)(((S_8002569C_6 *)temp_v0)->unk_0C) + 0xC)) = (s32) temp_v1;
        temp_a3 = D_8002632A;
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_16 = arg1;
        temp_v1->unk_1C = arg3;
        temp_v1->unk_18 = arg2;
        temp_v1->unk_22 = temp_a3;
        if ((s16) temp_a3 < 0x71) {
            temp_base = D_80026478;
            temp_a0 = &temp_base[(s16) temp_a3 * 8];
            temp_a1 = temp_s2->unk_0E;
            temp_v0_3 = &temp_base[((s16) temp_a3 + 0x10) * 8];
            temp_a0->unk_00 = temp_a1;
            temp_v0_3->unk_00 = temp_a1;
            temp_v1_2 = temp_s2->unk_12;
            temp_a0->unk_02 = temp_v1_2;
            temp_v0_3->unk_02 = temp_v1_2;
            temp_a1_2 = temp_s2->unk_16;
            D_8002632A = temp_a3 + 1;
            temp_a0->unk_04 = temp_a1_2;
            temp_v0_3->unk_04 = temp_a1_2;
        }
    }
    return temp_v0;
}
/* MECHANISM: Natural long-lived arguments/results reproduce the 0x38 frame and nine-register save set.
   Direct scalar globals plus one cached counter remove remats; byte indexing with a held table base fixes scaling.
   One guarded v1 lifetime carries 0xE04020, then object+0x20, keeping the count store branch-slot eligible.
   Relocating ASM_KEEP_NV after the three field stores selects retail's final lhu/addiu ready-list order. */
