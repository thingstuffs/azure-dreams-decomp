#include "common.h"
#include "m2c_compat.h"

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern s16 func_800AD568(void *, s32);
extern M2C_UNK func_800B4C7C(s32, void *, s32, s32);

typedef struct S_818B6824_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x3B];
    u16 unk_64;
} S_818B6824_0;   /* arg0 in func_818B6824 */

void func_818B6824(S_818B6824_0 *arg0, s32 arg1) {
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 var_a1;

    if (func_8009D218(arg0, 1) == 0) {
        temp_v1 = func_800A6870(arg1 & 0xFF) + 8;
        var_a1 = temp_v1;
        if (arg0->unk_28 & 1) {
            var_a1 = temp_v1 << 1;
        }
        arg0->unk_64 = (u16) (arg0->unk_64 + var_a1);
        func_800AD568(arg0, var_a1);
        func_800B4C7C(0x8004, arg0, (s16) arg0->unk_64, 1);
        func_800AD4D0(arg0);
    }
}
