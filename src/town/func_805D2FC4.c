#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_805D2FC4_2 {
    u8 pad_00[0x4];
    union { u8 s; s8 u; } unk_04;   /* accessed as both */
} S_805D2FC4_2;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in func_805D2FC4 */


typedef struct S_805D2FC4_1 {
    s32 unk_00;
} S_805D2FC4_1;   /* &D_80019AFC in func_805D2FC4 */


M2C_UNK func_80017E1C();                            /* extern */
s32 func_80018504();                    /* extern */
s32 func_800194D8();                         /* extern */
extern M2C_UNK D_80019AFC;

s32 func_80016FC4(s32 input_value, M2C_UNK input) {
    s32 result;
    u8 field_value;

    field_value = ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_04.s;
    ((S_805D2FC4_1 *)(&D_80019AFC))->unk_00 = (s32) field_value;
    result = 0;
    if ((field_value != 2) && (func_800194D8(0x639) != 0)) {
        result = func_80018504(input_value, input);
    }
    if (result != 0) {
        ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_04.u = 0;
        D_80019AFC = 0;
        do {
            return result;
        } while (0);
    }
    func_80017E1C();
    if (((S_805D2FC4_1 *)(&D_80019AFC))->unk_00 == 1) {
        ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_04.u = 0;
        D_80019AFC = 0;
    }
    return result;
}

/* MECHANISM: The retail prologue is driven by arg0/arg1 held in s1/s2 and
   the conditional helper result held in s0; the do-while(0) around the early
   `return var_s0;` is the barrier that keeps s0 across the zero-edge. The tail
   pseudo-call func_8001709C (true base +0xD8, this row's own epilogue) was
   replaced by that return 2026-09-22 (byte-exact). */
