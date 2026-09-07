#include "common.h"
#include "m2c_compat.h"

typedef struct CounterBlock {
    u8 pad[0xA];
    u16 count;
} CounterBlock;

M2C_UNK func_8003DB94();        /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80045C34;
extern CounterBlock D_80083460;
extern M2C_UNK D_800C5D80;

typedef struct S_800C5E5C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800C5E5C_0;   /* temp_v0 in func_800C5E5C */

typedef struct S_800C5E5C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C5E5C_1;   /* temp_v0_2 in func_800C5E5C */

typedef struct S_800C5E5C_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C5E5C_2;   /* temp_s0 in func_800C5E5C */

typedef struct S_800C5E5C_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} S_800C5E5C_3;   /* temp_v0_3 in func_800C5E5C */

void func_800C5E5C(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s16 arg4) {
    M2C_UNK var_a0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    S_800C5E5C_2 *temp_s0;
    CounterBlock *temp_s4;
    void *temp_v0;
    S_800C5E5C_1 *temp_v0_2;
    S_800C5E5C_3 *temp_v0_3;
    u16 temp_flags;

    if (arg4 != 0) {
        func_800A56E0(0x816);
    }
    var_s2 = 0xB;
    var_s5 = 0x20;
    temp_s4 = &D_80083460;
    var_s3 = 0xFFFA0000;
    do {
        var_a0 = 0x12;
        if (var_s2 != 0) {
            var_a0 = 0x212;
        }
        temp_v0 = func_8003FC64(var_a0);
        if (temp_v0 != NULL) {
            ((S_800C5E5C_0 *)temp_v0)->unk_10 = &D_800C5D80;
            func_8004491C(temp_v0, &D_80045C34);
            temp_v0_2 = ((S_800C5E5C_0 *)temp_v0)->unk_08;
            temp_v0_2->unk_02 = arg0;
            temp_v0_2->unk_06 = arg1;
            temp_v0_2->unk_0A = arg2;
            temp_v0_2->unk_14 = var_s3;
            temp_s0 = ((S_800C5E5C_0 *)temp_v0)->unk_0C;
            func_8003DB94(temp_s0, arg3, 0);
            temp_flags = temp_s0->unk_14;
            {
                s32 temp_color;
                temp_color = 0x808080;
                temp_s0->unk_0C = temp_color;
                ASM_KEEP(temp_color);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            }
            {
                s32 temp_1000;
                temp_1000 = 0x1000;
                temp_s0->unk_1E = temp_1000;
                temp_s0->unk_1C = temp_1000;
            }
            temp_v0_3 = temp_v0 + 0x20;
            temp_s0->unk_10 = var_s5;
            temp_flags |= 0xC;
            temp_s0->unk_14 = temp_flags;
            temp_v0_3->unk_10 = var_s5;
            temp_v0_3->unk_0C = var_s2;
            if (var_s2 == 0) {
                temp_s4->count = (u16) (temp_s4->count + 1);
            }
        }
        var_s3 += 0x8000;
        var_s2 -= 1;
    } while (var_s2 >= 0);
}

/* MECHANISM: An s32 loop counter removes the duplicate sign-extension live range and yields the retail 0x38 frame.
   A held CounterBlock base plus scoped v0/v1 locals reproduces the full-address and post-call register roles.
   Updating var_s3 before var_s2 places the 0x8000 materialization before the loop decrement. */
