#include "common.h"
#include "m2c_compat.h"

extern void func_80021298(void) __attribute__((noreturn));
extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern u8 D_8006CCF8[];
extern s16 D_80083228[];

typedef struct S_800211C4_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800211C4_0;   /* arg0 in func_800211C4 */

typedef struct S_800211C4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    s32 unk_2C;
} S_800211C4_1;   /* arg2 in func_800211C4 */

typedef struct S_800211C4_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800211C4_2;   /* arg1_hold in func_800211C4 */

void func_800211C4(S_800211C4_0 *arg0, void *arg1, S_800211C4_1 *arg2) {
    u8 *var_v0;
    s32 base_v0;
    s32 temp_s0;
    u8 *temp_v0;
    s32 temp_v2;
    u16 temp_v1;
    S_800211C4_2 *arg1_hold = arg1;

    temp_v1 = (arg0->unk_2A + 0x2000) & 0xFFF;
    arg0->unk_2A = temp_v1;
    temp_v2 = (s32)(D_80083228[0] + temp_v1 + 0x100) >> 9;
    temp_s0 = temp_v2 & 7;
    if (arg2->unk_14 & 0x6000) {
        func_80047784(arg2, *((u8 *)arg2->unk_2C + temp_s0), 0);
    }
    if (arg1_hold->unk_20 == temp_s0) {
        var_v0 = (u8 *)0x80070000;
        goto page_check;
    }
    temp_v0 = (u8 *)arg2->unk_2C;
    if (temp_v0 != 0) {
        func_80047738(arg2, temp_v0[temp_s0], arg2->unk_04);
    }
    arg1_hold->unk_20 = temp_s0;
    var_v0 = (u8 *)0x80070000;
page_check:
    base_v0 = (s32)var_v0 - 0x3308;
    ASM_KEEP(base_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_v0 = (u8 *)(temp_s0 + base_v0);
    if (temp_v0[0] != 0) {
        u32 temp_return;
        temp_return = arg2->unk_14 | 1;
        ASM_TAILSLOT_PIN_TIED(temp_return);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80021298();
    }
    arg2->unk_14 = (u16)(arg2->unk_14 & 0xFFFE);
}
