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

void func_80056654(void *arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    void *temp_a2;
    s32 temp_a1;
    s32 hi;
    s32 *table;
    s32 *tbase;
    temp_a2 = D_80084960 + (M2C_FIELD(arg0, u16 *, 6) * 0x9C);
    if ((M2C_FIELD(arg0, s32 *, 0x4C) != 0) || (M2C_FIELD(arg0, s32 *, 0x30) != 0) ||
        (M2C_FIELD(temp_a2, s32 *, 8) != 0) || (M2C_FIELD(temp_a2, s16 *, 0x50) != 0) ||
        (M2C_FIELD(temp_a2, s32 *, 0x1C) != M2C_FIELD(arg0, s32 *, 0x70)) || (arg1 != 0)) {
        M2C_FIELD(arg0, s32 *, 0x70) = (s32) M2C_FIELD(temp_a2, s32 *, 0x1C);
        temp_s0 = M2C_FIELD(arg0, u16 *, 0x3C) + (M2C_FIELD(temp_a2, u16 *, 0x3A) + M2C_FIELD(temp_a2, u16 *, 0x52));
        temp_v0 = func_800565D8(arg0, M2C_FIELD(temp_a2, s32 *, 0x1C), temp_a2);
        tbase = D_80073740;
        temp_a1 = (M2C_FIELD(arg0, u16 *, 0xC) << 7) + temp_v0;
        D_80084918.field4 = 0x60;
        table = tbase + M2C_FIELD(arg0, u16 *, 0);
        ASM_KEEP_NV(table);
        temp_s0_2 = temp_s0 + temp_a1;
        hi = (s32) (temp_s0_2 << 0x10) >> 0x17;
        temp_s0_2 &= 0x7F;
        D_80084918.field0 = *table;
        hi <<= 8;
        temp_s0_2 |= hi;
        if (M2C_FIELD(arg0, u8 *, 0x23) != 0) {
            D_80084918.field18 = (s16) (((M2C_FIELD(arg0, u8 *, 0x22) - 1) << 8) | (0x7F - M2C_FIELD(arg0, u8 *, 0x23)));
        } else {
            D_80084918.field18 = (s16) (M2C_FIELD(arg0, u8 *, 0x23) | (M2C_FIELD(arg0, u8 *, 0x22) << 8));
        }
        D_80084918.field16 = (s16) temp_s0_2;
        func_8005F134(&D_80084918);
    }
    if ((M2C_FIELD(arg0, s32 *, 0x30) != 0) && (func_8005EB78(D_80073740[M2C_FIELD(arg0, u16 *, 0)]) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x30) = 0;
        M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    }
}
