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

/* Add a directional step to the vector and scale it down if it exceeds the length limit. */
void func_80094F58(s16 angle, s32 max_length, FuncData *vector) {
    s32 first_step;
    s32 second_step;
    s32 over_limit;
    s32 rounded_length;
    register s32 adjusted_length ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 divisor;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 limit_units ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 first_quotient ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 second_quotient;

    first_step = func_800644B8(angle) << 6;
    second_step = func_80064584(angle) << 6;
    vector->first += first_step;
    vector->second += second_step;
    second_quotient = func_8003BD84(vector->first, vector->second);
    over_limit = max_length < second_quotient;
    rounded_length = second_quotient + 0xFFF;
    if (over_limit != 0) {
        adjusted_length = rounded_length;
        if (rounded_length < 0) {
            adjusted_length = second_quotient + 0x1FFE;
        }
        divisor = adjusted_length >> 12;
        first_quotient =
            ((Rec_D_800E3D7C *)vector)->unk_0C.as_vs32 / divisor;
        ASM_KEEP(first_quotient);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        limit_units = max_length;
        if (max_length < 0) {
            limit_units = max_length + 0xFFF;
        }
        limit_units >>= 12;
        ((Rec_D_800E3D7C *)vector)->unk_0C.as_vs32 =
            first_quotient * limit_units;
        second_quotient =
            ((Rec_D_800E3D7C *)vector)->unk_10.at00_vs32.v / divisor;
        ((Rec_D_800E3D7C *)vector)->unk_10.at00_vs32.v =
            second_quotient * limit_units;
    }
}
