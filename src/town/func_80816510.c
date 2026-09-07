#include "common.h"
#include "m2c_compat.h"

typedef struct S_80020510_0_pre {
    u16 unk_00;
} S_80020510_0_pre;   /* the 0x2 bytes before arg0 in func_80020510, addressed as arg0[-1] */

typedef struct S_80020510_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    s32 unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_80020510_0;   /* arg0 in func_80020510 */

typedef struct S_80020510_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020510_1;   /* temp_s2 in func_80020510 */


M2C_UNK func_800537D0();               /* extern */
s32 strlen();                             /* extern */
extern s16 D_800272A0[];
extern s32 D_800814A0;

void func_80020510(void *arg0) {
    s16 temp_v1;
    s32 var_a0;
    s32 var_s0;
    u16 temp_v0_2;
    void *temp_s2;

    var_s0 = 0;
    var_a0 = 7;
    temp_s2 = ((S_80020510_0 *)arg0)->unk_0C;
    do {
        var_s0 += D_800272A0[var_a0];
        var_a0 -= 1;
    } while (var_a0 >= 0);
    temp_v1 = ((S_80020510_0 *)arg0)->unk_00.s;
    if (temp_v1 == 0) {
        goto state_zero;
    }
    if (temp_v1 == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    temp_v0_2 = ((S_80020510_0 *)arg0)->unk_02 - 1;
    ((S_80020510_0 *)arg0)->unk_02 = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto done;
    }
    ((S_80020510_0 *)arg0)->unk_1C =
        (u16) (((S_80020510_0 *)arg0)->unk_1C & 0xFFFD);
    ((S_80020510_0 *)arg0)->unk_00.u =
        (u16) (((S_80020510_0 *)arg0)->unk_00.u + 1);
    goto done;

state_one:
    func_800537D0(var_s0, strlen(((S_80020510_0 *)arg0)->unk_04),
                  ((S_80020510_0 *)arg0)->unk_04);
    if (((S_80020510_1 *)temp_s2)->unk_2A & 1) {
        (*(u16 *)((u8 *)arg0 + -2)) =
            (u16) (((S_80020510_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: Indexed D_800272A0 access lets loop strength reduction emit the
   held base plus 14-byte induction pointer and direct signed halfword load.
   Explicit default/zero/one label order targets the rowbase-local epilogue;
   direct scalar D_800814A0 access completes the retail CFG and delay slots. */
