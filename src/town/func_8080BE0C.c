#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080BE0C_0_pre {
    u16 unk_00;
} S_8080BE0C_0_pre;   /* the 0x2 bytes before arg0 in func_8080BE0C, addressed as arg0[-1] */

typedef struct S_8080BE0C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    s32 unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_8080BE0C_0;   /* arg0 in func_8080BE0C */

typedef struct S_8080BE0C_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8080BE0C_1;   /* temp_s2 in func_8080BE0C */


M2C_UNK func_80058588();               /* extern */
s32 func_80071424();                             /* extern */
void func_80526AFC() __attribute__((noreturn));  /* extern */
extern s32 D_80084D5C;
extern s16 D_80530000[];

void func_8080BE0C(void *arg0) {
    s16 *var_v1;
    s16 temp_v1;
    s32 var_a0;
    s32 var_s1;
    u16 temp_v0_2;
    u16 state_value;
    u16 flags_value;
    void *temp_s2;

    var_s1 = 0;
    var_a0 = 7;
    var_v1 = &D_80530000[0x333];
    temp_s2 = ((S_8080BE0C_0 *)arg0)->unk_0C;
    do {
        var_s1 += *var_v1;
        var_v1 -= 1;
        var_a0 -= 1;
    } while (var_a0 >= 0);
    temp_v1 = ((S_8080BE0C_0 *)arg0)->unk_00.s;
    if (temp_v1 == 0) {
        goto state_0;
    }
    if (temp_v1 == 1) {
        goto state_1;
    }
    func_80526AFC(var_a0);

state_0:
    temp_v0_2 = ((S_8080BE0C_0 *)arg0)->unk_02 - 1;
    ((S_8080BE0C_0 *)arg0)->unk_02 = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto done;
    }
    state_value = ((S_8080BE0C_0 *)arg0)->unk_00.u;
    flags_value = ((S_8080BE0C_0 *)arg0)->unk_1C;
    state_value += 1;
    flags_value &= 0xFFFD;
    ((S_8080BE0C_0 *)arg0)->unk_1C = flags_value;
    ((S_8080BE0C_0 *)arg0)->unk_00.u = state_value;
    func_80526AFC(var_a0);

state_1:
    func_80058588(var_s1, func_80071424(((S_8080BE0C_0 *)arg0)->unk_04), ((S_8080BE0C_0 *)arg0)->unk_04);
    if (((S_8080BE0C_1 *)temp_s2)->unk_2A & 1) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_8080BE0C_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }

done:
    return;
}
/* MECHANISM: The page-base symbol plus &D_80530000[0x333] emits retail's entry lui/addiu in v1.
   A noreturn tail ABI and explicit label order preserve default/state-0/state-1 CFG and jump slots.
   Split state/flags RMW temporaries establish the retail v1/v0 lifetimes and flags/state store order. */
