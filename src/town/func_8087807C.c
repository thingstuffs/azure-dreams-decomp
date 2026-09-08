#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80702670();                         /* extern */
M2C_UNK func_807026C0();                         /* extern */
s32 func_80702714();                             /* extern */
extern u8 D_80700000[];

typedef struct S_8070207C_0 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
    u16 unk_1DCE;
} S_8070207C_0;   /* (D_80700000 + temp_s0) in func_8070207C */

typedef struct S_8070207C_1 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
} S_8070207C_1;   /* (D_80700000 + final_index) in func_8070207C */

void func_8070207C(s32 arg0) {
    register s32 temp_s0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 temp_s1 ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 final_index ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    temp_s1 = arg0;
    ASM_KEEP_NV(temp_s1);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    temp_s0 = arg0 * 4;
    if (func_80702714(((S_8070207C_0 *)((D_80700000 + temp_s0)))->unk_1DCC) != 0) {
        func_80702670(((S_8070207C_0 *)((D_80700000 + temp_s0)))->unk_1DCE);
    } else {
        func_807026C0(((S_8070207C_0 *)((D_80700000 + temp_s0)))->unk_1DCE);
    }
    final_index = temp_s1 * 4;
    func_80702670(((S_8070207C_1 *)((D_80700000 + final_index)))->unk_1DCC);
}
