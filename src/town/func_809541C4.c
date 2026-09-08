#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern u8 D_8006CCF8[];
extern s16 D_80083228[];

typedef struct S_800211C4_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800211C4_0;   /* arg0 in func_800211C4 */


typedef struct S_800211C4_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800211C4_2;   /* arg1_hold in func_800211C4 */

void func_800211C4(S_800211C4_0 *arg0, void *arg1, Rec_D_80082E80 *arg2) {
    u8 *var_v0;
    s32 base_v0;
    s32 temp_s0;
    u8 *temp_v0;
    s32 temp_v2;
    u16 temp_v1;
    u16 finalVal;
    S_800211C4_2 *arg1_hold = arg1;

    temp_v1 = (arg0->unk_2A + 0x2000) & 0xFFF;
    arg0->unk_2A = temp_v1;
    temp_v2 = (s32)(D_80083228[0] + temp_v1 + 0x100) >> 9;
    temp_s0 = temp_v2 & 7;
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        func_80047784(arg2, *((u8 *)arg2->unk_2C.as_s32 + temp_s0), 0);
    }
    if (arg1_hold->unk_20 == temp_s0) {
        var_v0 = (u8 *)0x80070000;
        goto page_check;
    }
    temp_v0 = (u8 *)arg2->unk_2C.as_s32;
    if (temp_v0 != 0) {
        func_80047738(arg2, temp_v0[temp_s0], arg2->unk_04.as_s8);
    }
    arg1_hold->unk_20 = temp_s0;
    var_v0 = (u8 *)0x80070000;
page_check:
    base_v0 = (s32)var_v0 - 0x3308;
    ASM_KEEP(base_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_v0 = (u8 *)(temp_s0 + base_v0);
    if (temp_v0[0] != 0) {
        finalVal = arg2->unk_14.at00_u16.v | 1;
    } else {
        finalVal = arg2->unk_14.at00_u16.v & 0xFFFE;
    }
    arg2->unk_14.at00_u16.v = finalVal;
}
