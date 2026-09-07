#include "common.h"
#include "m2c_compat.h"

typedef struct S_80094F58_0 {
    u8 pad_00[0xC];
    volatile s32 unk_0C;
    volatile s32 unk_10;
} S_80094F58_0;   /* arg2 in func_80094F58 */


s32 func_8003BD84();                        /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

typedef struct {
    s32 pad[3];
    s32 first;
    s32 second;
} FuncData;

/* Add a directional step to the vector and scale it down if it exceeds the length limit. */
void func_80094F58(s16 angle, s32 max_length, FuncData *vector) {
    s32 first_step;
    s32 second_step;
    s32 length;
    s32 over_limit;
    s32 rounded_length;
    register s32 adjusted_length ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 divisor ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 limit_units ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 first_quotient ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 second_quotient ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    first_step = func_800644B8(angle) << 6;
    second_step = func_80064584(angle) << 6;
    vector->first += first_step;
    vector->second += second_step;
    length = func_8003BD84(vector->first, vector->second);
    over_limit = max_length < length;
    rounded_length = length + 0xFFF;
    if (over_limit != 0) {
        adjusted_length = rounded_length;
        if (rounded_length < 0) {
            adjusted_length = length + 0x1FFE;
        }
        divisor = adjusted_length >> 12;
        first_quotient =
            ((S_80094F58_0 *)vector)->unk_0C / divisor;
        ASM_KEEP(first_quotient);   /* MATCH pin: keeps a statement from moving across a call/branch */
        limit_units = max_length;
        if (max_length < 0) {
            limit_units = max_length + 0xFFF;
        }
        limit_units >>= 12;
        ((S_80094F58_0 *)vector)->unk_0C =
            first_quotient * limit_units;
        second_quotient =
            ((S_80094F58_0 *)vector)->unk_10 / divisor;
        ((S_80094F58_0 *)vector)->unk_10 =
            second_quotient * limit_units;
    }
}
