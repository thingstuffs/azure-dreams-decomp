#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_8009204C;
extern M2C_UNK D_800D00B0;

typedef struct S_800942B0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800942B0_0;   /* arg1 in func_800942B0 */

typedef struct S_800942B0_1 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800942B0_1;   /* arg0 in func_800942B0 */

/* Initializes an object and its associated state, then assigns its data pointer and clears its counter. */
void func_800942B0(S_800942B0_1 *object, S_800942B0_0 *state, M2C_UNK setupArg) {
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x800948DC` forwards $a0,$a1,$a3 untouched from this row's entry.
     * $a3 is never read here, so m2c gave the row no name for it; the pinned
     * forwarder locals below are that name (section 22).  `need` is a
     * positional SET, so the call carries positions 0..3 (section 21). */
    register M2C_UNK forwardedObject ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK forwardedState ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK forwardedSetupArg ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
    M2C_UNK forwardedFourthArg;
    func_800948DC(forwardedObject, forwardedState, forwardedSetupArg, forwardedFourthArg);
    state->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D00B0, object, setupArg);
    object->unk_00 = &D_8009204C;
    object->unk_0A = 0;
}
