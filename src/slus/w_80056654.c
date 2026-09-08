/* func_80056654 -- BYTE-EXACT, gcc 2.7.2-cdk -O2, aspsx 2.56.
 *
 * The table address is deliberately built in TWO statements.  Spelled as one
 * (`table = &D_80073740[idx];`) the index load and the symbol address are a
 * single statement, so every source permutation moves them together; both are
 * priority-1 fillers in the post-call block, and the LUID tie-break then puts
 * the index load in front of the `D_80084918.field4 = 0x60` store.  Its live
 * range then overlaps the constant's, local-alloc must give them different
 * registers, and the index/base pair comes out as $a0/$v1 instead of retail's
 * $v1/$a0.  Assigning the base first and adding the index AFTER the store gives
 * the two insns separate LUIDs on either side of it: the `lui` schedules early,
 * the index `lhu` schedules after the `sw`, the 0x60 dies there and the index
 * reuses $v1.  ASM_KEEP_NV stays on `table` (not on `tbase`) -- it is what stops
 * cdk folding the pointer back into a %hi + per-access %lo pair; keeping `tbase`
 * as well re-ties the address and costs 9.
 */
#include "common.h"

typedef struct S_80056654_0 {
    u16 unk_00;
    u8 pad_02[0x4];
    u16 unk_06;
    u8 pad_08[0x4];
    u16 unk_0C;
    u8 pad_0E[0x14];
    u8 unk_22;
    u8 unk_23;
    u8 pad_24[0xC];
    s32 unk_30;
    u8 pad_34[0x8];
    union { u16 u16; s32 s32; } unk_3C;   /* accessed as both */
    u8 pad_40[0xC];
    s32 unk_4C;
    u8 pad_50[0x20];
    s32 unk_70;
} S_80056654_0;   /* arg0 in func_80056654 */

typedef struct S_80056654_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
    u8 pad_20[0x1A];
    u16 unk_3A;
    u8 pad_3C[0x14];
    s16 unk_50;
    u16 unk_52;
} S_80056654_1;   /* temp_a2 in func_80056654 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 field0;
    s32 field4;
    u8 pad8[0x16 - 8];
    s16 field16;
    s16 field18;
    u8 pad1A[0x40 - 0x1A];
} S_80084918;

s32 func_800565D8(void *, s32, void *);
s32 func_8005EB78(s32);
void func_8005F134(S_80084918 *);
extern s32 D_80073740[];
extern S_80084918 D_80084918;
extern u8 D_80084960[];

void func_80056654(S_80056654_0 *arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    S_80056654_1 *temp_a2;
    s32 temp_a1;
    s32 hi;
    s32 *table;
    s32 *tbase;
    temp_a2 = D_80084960 + (arg0->unk_06 * 0x9C);
    if ((arg0->unk_4C != 0) || (arg0->unk_30 != 0) ||
        (temp_a2->unk_08 != 0) || (temp_a2->unk_50 != 0) ||
        (temp_a2->unk_1C != arg0->unk_70) || (arg1 != 0)) {
        arg0->unk_70 = (s32) temp_a2->unk_1C;
        temp_s0 = arg0->unk_3C.u16 + (temp_a2->unk_3A + temp_a2->unk_52);
        temp_v0 = func_800565D8(arg0, temp_a2->unk_1C, temp_a2);
        tbase = D_80073740;
        temp_a1 = (arg0->unk_0C << 7) + temp_v0;
        D_80084918.field4 = 0x60;
        table = tbase + arg0->unk_00;
        ASM_KEEP_NV(table);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        temp_s0_2 = temp_s0 + temp_a1;
        hi = (s32) (temp_s0_2 << 0x10) >> 0x17;
        temp_s0_2 &= 0x7F;
        D_80084918.field0 = *table;
        hi <<= 8;
        temp_s0_2 |= hi;
        if (arg0->unk_23 != 0) {
            D_80084918.field18 = (s16) (((arg0->unk_22 - 1) << 8) | (0x7F - arg0->unk_23));
        } else {
            D_80084918.field18 = (s16) (arg0->unk_23 | (arg0->unk_22 << 8));
        }
        D_80084918.field16 = (s16) temp_s0_2;
        func_8005F134(&D_80084918);
    }
    if ((arg0->unk_30 != 0) && (func_8005EB78(D_80073740[arg0->unk_00]) == 0)) {
        arg0->unk_30 = 0;
        arg0->unk_3C.s32 = 0;
    }
}
