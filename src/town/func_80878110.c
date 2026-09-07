#include "common.h"
#include "m2c_compat.h"

typedef struct S_80702110_0 {
    u8 pad_00[0x1DFE];
    u16 unk_1DFE;
} S_80702110_0;   /* (D_80700000 + (arg0 * 4)) in func_80702110 */




s32 func_80702140(void) __attribute__((noreturn));  /* extern */
s32 func_80702714();                             /* extern */
extern u8 D_80700000[8];


s32 func_80702110(s32 arg0) {
    s16 *temp_s0;

    temp_s0 = (*(s16 **)((u8 *)((D_80700000 + (((S_80702110_0 *)((D_80700000 + (arg0 * 4))))->unk_1DFE * 4))) + 0x1DEC));
    if (func_80702714(*temp_s0) != 0) {
        temp_s0 += 1;
        ASM_TAILSLOT_PIN_TIED(temp_s0);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_80702140();
    }
    return *temp_s0 == 0;
}
