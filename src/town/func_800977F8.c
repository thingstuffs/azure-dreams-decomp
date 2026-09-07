#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"



s32 func_8003BD84();                        /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

typedef struct {
    s32 pad[3];
    s32 first;
    s32 second;
} FuncData;

void func_80094F58(s16 arg0, s32 arg1, FuncData *arg2) {
    s32 first;
    s32 second;
    s32 result;
    s32 condition;
    s32 rounded_result;
    register s32 adjusted_result ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 divisor ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 rounded_arg ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 first_quotient ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 second_quotient ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    first = func_800644B8(arg0) << 6;
    second = func_80064584(arg0) << 6;
    arg2->first += first;
    arg2->second += second;
    result = func_8003BD84(arg2->first, arg2->second);
    condition = arg1 < result;
    rounded_result = result + 0xFFF;
    if (condition != 0) {
        adjusted_result = rounded_result;
        if (rounded_result < 0) {
            adjusted_result = result + 0x1FFE;
        }
        divisor = adjusted_result >> 12;
        first_quotient =
            ((Rec_D_800E3D7C *)arg2)->unk_0C.as_vs32 / divisor;
        ASM_KEEP(first_quotient);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rounded_arg = arg1;
        if (arg1 < 0) {
            rounded_arg = arg1 + 0xFFF;
        }
        rounded_arg >>= 12;
        ((Rec_D_800E3D7C *)arg2)->unk_0C.as_vs32 =
            first_quotient * rounded_arg;
        second_quotient =
            ((Rec_D_800E3D7C *)arg2)->unk_10.at00_vs32.v / divisor;
        ((Rec_D_800E3D7C *)arg2)->unk_10.at00_vs32.v =
            second_quotient * rounded_arg;
    }
}

/* MECHANISM: Typed fields recover the initial v1/a1 update roles.
   A block-local guarded a1 quotient exposes retail's divide/scale live ranges.
   Long-lived args and first shifted result induce the s2/s1/s0 frame contract. */
