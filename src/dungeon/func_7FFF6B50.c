#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_8009204C;
extern M2C_UNK D_800D00B0;



/* Initializes an object and its associated state, then assigns its data pointer and clears its counter. */
void func_800942B0(Rec_func_80094268_arg0 *object, Rec_D_800E3D7C *state, M2C_UNK setupArg) {
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x800948DC` forwards $a0,$a1,$a3 untouched from this row's entry.
     * $a3 is never read here, so m2c gave the row no name for it; the pinned
     * forwarder locals below are that name (section 22).  `need` is a
     * positional SET, so the call carries positions 0..3 (section 21). */
    register M2C_UNK forwardedObject ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register M2C_UNK forwardedState ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register M2C_UNK forwardedSetupArg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    M2C_UNK forwardedFourthArg;
    func_800948DC(forwardedObject, forwardedState, forwardedSetupArg, forwardedFourthArg);
    state->unk_14.as_s32 = 0xFFEF0000;
    func_80094984(&D_800D00B0, object, setupArg);
    object->unk_00.as_pm = &D_8009204C;
    object->unk_0A.as_s16 = 0;
}
