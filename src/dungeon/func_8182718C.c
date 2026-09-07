#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8182718C_0_pre {
    u16 unk_00;
} S_8182718C_0_pre;   /* the 0x2 bytes before arg0 in func_8182718C, addressed as arg0[-1] */

typedef struct S_8182718C_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
    u16 unk_4E;
} S_8182718C_0;   /* arg0 in func_8182718C */

typedef struct S_8182718C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8182718C_1;   /* temp_v1 in func_8182718C */



extern int D_800814A0[];
extern u8 D_80045340[];
extern void func_80024A7C(void) __attribute__((noreturn));

void func_8182718C(void *arg0, void *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    S_8182718C_1 *temp_v1;

    temp_v1 = ((S_8182718C_0 *)arg0)->unk_00;
    temp_v1->unk_52 = (s16) (temp_v1->unk_52 | 0x8000);
    temp_v1_2 = ((S_8182718C_0 *)arg0)->unk_4C.s;
    if (temp_v1_2 == 0) {
        goto zero_state;
    }
    if (temp_v1_2 == 1) {
        goto one_state;
    }
    func_80024A7C();

zero_state:
    {
        u16 temp_zero_4c;
        u16 temp_zero_4e;

        temp_v0_2 = ((S_8182718C_0 *)arg0)->unk_48 - 1;
        ((S_8182718C_0 *)arg0)->unk_48 = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            func_8004491C(arg0 - 0x20, D_80045340);
            temp_zero_4c = ((S_8182718C_0 *)arg0)->unk_4C.u;
            temp_zero_4e = ((S_8182718C_0 *)arg0)->unk_4E;
            ((S_8182718C_0 *)arg0)->unk_48 = temp_zero_4e;
            ((S_8182718C_0 *)arg0)->unk_4C.u = (u16) (temp_zero_4c + 1);
            func_80024A7C();
        }
        goto done;
    }

one_state:
    {
        temp_v0 = ((S_8182718C_0 *)arg0)->unk_48;
        ((S_8182718C_0 *)arg0)->unk_48 = (u16) (temp_v0 - 1);
        if ((temp_v0 << 0x10) <= 0) {
            func_800478B8(arg2);
            ((S_8182718C_0 *)arg0)->unk_48 = (u16) ((S_8182718C_0 *)arg0)->unk_4E;
        }
        if (arg2->unk_14.at00_u16.v & 0x6000) {
            ((S_8182718C_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8182718C_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }

done:
    ;
}
