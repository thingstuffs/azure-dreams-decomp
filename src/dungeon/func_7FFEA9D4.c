#include "common.h"
#include "m2c_compat.h"

typedef struct S_7FFEA9D4_4 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_7FFEA9D4_4;   /* temp_v0_2 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_7FFEA9D4_5;   /* ((S_7FFEA9D4_4 *)temp_v0_2)->unk_0C in func_7FFEA9D4 */


typedef struct S_7FFEA9D4_0_pre {
    u16 unk_00;
} S_7FFEA9D4_0_pre;   /* the 0x2 bytes before arg0 in func_7FFEA9D4, addressed as arg0[-1] */

typedef struct S_7FFEA9D4_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
} S_7FFEA9D4_0;   /* arg0 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0x2A];
    s16 unk_3E;
    s16 unk_40;
    u8 pad_42[0x1E];
    u16 unk_60;
} S_7FFEA9D4_1;   /* temp_v0_2 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFEA9D4_2;   /* temp_s0 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFEA9D4_3;   /* temp_s1 in func_7FFEA9D4 */


void *func_7003CF18();                       /* extern */
s32 func_700750E0();                                /* extern */
M2C_UNK func_7010CD00(); /* extern */
extern s32 D_80086AD8;
extern u8 D_800E0F20[0x100];
extern u16 D_80094422;
extern M2C_UNK D_8010C994;

void func_7FFEA9D4(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK saved_arg1 = arg1;
    register M2C_UNK saved_arg2 ASM_REG("$23") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 delta ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_s4;
    s32 rand_value;
    s32 current;
    s32 first_current;
    s32 second_current;
    u16 temp_v0;
    u16 temp_v0_3;
    u16 counter_value;
    u16 *counter;
    S_7FFEA9D4_2 *temp_s0;
    S_7FFEA9D4_3 *temp_s1;
    S_7FFEA9D4_1 *temp_v0_2;

    temp_v0 = ((S_7FFEA9D4_0 *)arg0)->unk_16 + 1;
    ((S_7FFEA9D4_0 *)arg0)->unk_16 = temp_v0;
    if ((s16) temp_v0 < 0x28) {
        var_s4 = 0;
        do {
            temp_v0_2 = func_7003CF18(0x212);
            var_s4 += 1;
            if (temp_v0_2 != NULL) {
                func_7010CD00(temp_v0_2, arg0, saved_arg1, saved_arg2);
                temp_s0 = temp_v0_2->unk_08;
                temp_v0_2->unk_3E = 8;
                temp_v0_2->unk_40 = 8;
                temp_v0_2->unk_10 = &D_8010C994;
                rand_value = func_700750E0();
                first_current = temp_s0->unk_02;
                first_current -= 0x1F;
                first_current += rand_value & 0x3F;
                temp_s0->unk_02 = (u16) first_current;
                rand_value = func_700750E0();
                second_current = temp_s0->unk_06;
                second_current -= 0x1F;
                second_current += rand_value & 0x3F;
                temp_s0->unk_06 = (u16) second_current;
                temp_s1 = ((S_7FFEA9D4_0 *)arg0)->unk_00;
                temp_v0_2->unk_60 = (u16) temp_s0->unk_0A;
                rand_value = func_700750E0();
                delta = D_800E0F20[temp_s1->unk_13];
                current = temp_s0->unk_0A;
                delta += 0x20;
                delta -= rand_value & 0xF;
                current -= delta;
                temp_s0->unk_0A = (u16) current;
                ((S_7FFEA9D4_5 *)(((S_7FFEA9D4_4 *)temp_v0_2)->unk_0C))->unk_0C = 0;
            }
        } while (var_s4 < 2);
    }
    temp_v0_3 = ((S_7FFEA9D4_0 *)arg0)->unk_1E - 1;
    ((S_7FFEA9D4_0 *)arg0)->unk_1E = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        temp_v0 = ((S_7FFEA9D4_0_pre *)arg0)[-1].unk_00;
        counter = &D_80094422;
        temp_v0 |= 0x8000;
        ((S_7FFEA9D4_0_pre *)arg0)[-1].unk_00 = temp_v0;
        counter_value = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = counter_value;
    }
}

/* MECHANISM: Dedicated short-lived RNG locals preserve retail's immediate arithmetic order.
   Guarded argument roles and a late $a0 delta keep reproduce the saved and scratch coloring.
   A held counter pointer/value orders the final global RMW and fills both load-delay slots. */
