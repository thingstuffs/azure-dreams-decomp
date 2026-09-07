#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D2FC4_2 {
    u8 pad_00[0x4];
    union { u8 s; s8 u; } unk_04;   /* accessed as both */
} S_805D2FC4_2;   /* ((D_80016000->unk_08 * 8) + D_80016000->unk_40) in func_805D2FC4 */


typedef struct S_805D2FC4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_805D2FC4_0;   /* D_80016000 in func_805D2FC4 */

typedef struct S_805D2FC4_1 {
    s32 unk_00;
} S_805D2FC4_1;   /* &D_80019AFC in func_805D2FC4 */


s32 func_8001709C();                                /* extern */
M2C_UNK func_80017E1C();                            /* extern */
s32 func_80018504();                    /* extern */
s32 func_800194D8();                         /* extern */
extern S_805D2FC4_0 *D_80016000;
extern M2C_UNK D_80019AFC;

s32 func_805D2FC4(s32 arg0, M2C_UNK arg1) {
    s32 var_s0;
    u8 temp_v1;

    temp_v1 = ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_04.s;
    ((S_805D2FC4_1 *)(&D_80019AFC))->unk_00 = (s32) temp_v1;
    var_s0 = 0;
    if ((temp_v1 != 2) && (func_800194D8(0x639) != 0)) {
        var_s0 = func_80018504(arg0, arg1);
    }
    if (var_s0 != 0) {
        ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_04.u = 0;
        D_80019AFC = 0;
        return func_8001709C();
    }
    func_80017E1C();
    ASM_KEEP(var_s0);   /* MATCH pin: retail register colouring depends on it */
    if (((S_805D2FC4_1 *)(&D_80019AFC))->unk_00 == 1) {
        ((S_805D2FC4_2 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_04.u = 0;
        D_80019AFC = 0;
    }
    return var_s0;
}

/* MECHANISM: The retail prologue is driven by arg0/arg1 held in s1/s2 and
   the conditional helper result held in s0. A post-call read/write liveness
   barrier preserves s0 across the zero-edge; both cleanup arms clear state. */
