#include "common.h"

typedef struct S_80175C60_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175C60_0;   /* arg1_pinned in func_80175C60 */

typedef struct S_80175C60_1 {
    s16 * unk_00;
    u8 pad_04[0x1C];
    u16 unk_20;
} S_80175C60_1;   /* arg0 in func_80175C60 */

typedef struct S_80175C60_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80175C60_2;   /* arg2 in func_80175C60 */


extern s32 D_800814A0;
extern s16 D_80083228;


void func_80175C60(void *arg0, void *arg1, void *arg2)
{
    register void *arg1_pinned ASM_REG("$5") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_v1_wide;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v0_2;
    s32 temp_v1;
    u16 temp_v0;

    ASM_KEEP(arg1_pinned);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_80175C60_0 *)arg1_pinned)->unk_00 += ((S_80175C60_0 *)arg1_pinned)->unk_0C;
    ((S_80175C60_0 *)arg1_pinned)->unk_04 += ((S_80175C60_0 *)arg1_pinned)->unk_10;
    ((S_80175C60_0 *)arg1_pinned)->unk_08 += ((S_80175C60_0 *)arg1_pinned)->unk_14;
    temp_v1 = ((S_80175C60_0 *)arg1_pinned)->unk_0C;
    temp_a0 = temp_v1 >> 5;
    temp_a2 = ((S_80175C60_0 *)arg1_pinned)->unk_10;
    temp_v0_2 = temp_a2;
    ASM_KEEP(temp_v0_2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_80175C60_0 *)arg1_pinned)->unk_0C = temp_v1 + temp_a0;
    ASM_KEEP(temp_v0_2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0_2 += temp_v0_2 >> 5;
    ((S_80175C60_0 *)arg1_pinned)->unk_10 = temp_v0_2;
    temp_v0 = ((S_80175C60_1 *)arg0)->unk_20 - 1;
    ((S_80175C60_1 *)arg0)->unk_20 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    ((S_80175C60_2 *)arg2)->unk_1C += 0x80;
    ((S_80175C60_2 *)arg2)->unk_1E += 0x80;
    ((S_80175C60_2 *)arg2)->unk_1A += 0x40;
    {
        s32 temp_v1_2;

        temp_v1_wide = ((((s32)(D_80083228 + *((S_80175C60_1 *)arg0)->unk_00 + 0x100) >> 9) & 7) + 2) << 9;
        temp_v1_2 = temp_v1_wide;
        ASM_KEEP(temp_v1_2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_80175C60_2 *)arg2)->unk_18 = temp_v1_wide;
        if ((temp_v1_2 == 0x400) || (temp_v1_2 == 0xC00)) {
            ((S_80175C60_2 *)arg2)->unk_18 = temp_v1_wide + 0x100;
        }
    }
}
