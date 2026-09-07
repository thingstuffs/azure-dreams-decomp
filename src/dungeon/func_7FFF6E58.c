#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984(); /* extern */
extern M2C_UNK D_80092CD4;
extern M2C_UNK D_800D0140;

typedef struct S_800945B8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800945B8_0;   /* arg1 in func_800945B8 */

void func_800945B8(M2C_UNK **arg0, S_800945B8_0 *arg1, M2C_UNK arg2) {
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x800948DC` forwards $a0,$a1,$a3 untouched from this row's entry.
     * $a3 is never read here, so m2c gave the row no name for it; the pinned
     * forwarder locals below are that name (section 22).  `need` is a
     * positional SET, so the call carries positions 0..3 (section 21). */
    register M2C_UNK _a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK _a1 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK _a2 ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
    M2C_UNK _a3;
    func_800948DC(_a0, _a1, _a2, _a3);
    arg1->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D0140, arg0, arg2);
    *arg0 = &D_80092CD4;
}
