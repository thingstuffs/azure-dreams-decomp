#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

s32 func_8004CAE8();                    /* extern */
M2C_UNK func_8008F9F8();                            /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_8009A350();          /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80081484;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800DD25C;
extern s32 D_800E3540;


typedef struct S_8008F878_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x88];
    void * unk_124;
} S_8008F878_0;   /* arg0 in func_8008F878 */

typedef struct S_8008F878_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008F878_1;   /* arg2 in func_8008F878 */

typedef struct S_8008F878_2 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
} S_8008F878_2;   /* &D_800DD25C in func_8008F878 */

typedef struct S_8008F878_3 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8008F878_3;   /* temp_v0 in func_8008F878 */

typedef struct S_8008F878_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008F878_4;   /* temp_v1_2 in func_8008F878 */

typedef struct S_8008F878_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008F878_5;   /* arg3 in func_8008F878 */


typedef struct S_8008F878_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8008F878_7;   /* temp_s0 in func_8008F878 */

typedef struct S_8008F878_8 {
    u8 pad_00[0x6D];
    s8 unk_6D;
} S_8008F878_8;   /* ((S_8008F878_2 *)(&D_800DD25C))->unk_00.p in func_8008F878 */

void func_8008F878(S_8008F878_0 *arg0, void *arg1, S_8008F878_1 *arg2, S_8008F878_5 *arg3) {
    u16 sp10;
    M2C_UNK var_a0;
    s32 temp_v1;
    s32 temp_saved;
    S_8008F878_3 *temp_v0;
    S_8008F878_4 *temp_v1_2;
    S_8008F878_7 *temp_s0;

    temp_v1 = arg0->unk_9B;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 >= 2) {
        goto done;
    }
    if (temp_v1 != 0) {
        goto done;
    }
    if (func_8004CAE8(arg2->unk_08, 0) == 0) {
        temp_v0 = arg0->unk_124;
        ((S_8008F878_2 *)(&D_800DD25C))->unk_00.p = temp_v0;
        if (temp_v0->unk_13 <= 0) {
            ((S_8008F878_2 *)(&D_800DD25C))->unk_00.i = 0;
        }
        temp_v1_2 = arg0->unk_124;
        temp_v1_2->unk_1C = (s32) (temp_v1_2->unk_1C & 0xFFF7FFFF);
        arg3->unk_1C = (s32) (arg3->unk_1C & 0xFFEFFFFF);
        func_8009A350(arg2->unk_24, arg2->unk_25, ((u16) arg3->unk_2A >> 9) & 7, &sp10);
        var_a0 = 0x50C;
        if (sp10 & 0x400) {
            var_a0 = 0x517;
        }
        func_800A56E0(var_a0);
        temp_saved = ((Rec_D_80016000 *)(&D_80081484))->unk_00.at00_s32.v;
        ((Rec_D_80016000 *)(&D_80081484))->unk_00.at00_s32.v = 0;
        D_800E3540 = temp_saved;
        arg0->unk_9B++;
        func_8008F9F8();
        return;
    }
    return;
state_1:
    if (arg2->unk_14 & 0x6000) {
        arg0->unk_9B = 2U;
        temp_s0 = &D_80083460;
        temp_s0->unk_02 = (u16) (temp_s0->unk_02 | 0x412);
        func_80099F70(arg3->unk_5C);
        func_80099F04(arg3->unk_5C);
        if (((S_8008F878_2 *)(&D_800DD25C))->unk_00.p != NULL) {
            ((S_8008F878_8 *)(((S_8008F878_2 *)(&D_800DD25C))->unk_00.p))->unk_6D = 0;
        }
        arg0->unk_8C = &D_8008ACDC;
        temp_s0->unk_0A = (u16) (temp_s0->unk_0A - 1);
    }
done:
    return;
}
/* MECHANISM: A dead arg1 restores the live arg0/arg2/arg3 ABI roles in s1/s0/s2.
   Signed explicit state dispatch reproduces the CFG and exact save-store ordering.
   Separate old-value transfer plus a held D_80083460 base closes the +1-word cascade. */
