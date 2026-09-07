#include "common.h"
#include "m2c_compat.h"

extern s32 func_8009D218(void *arg0, s32 arg1);
extern s32 func_800A6870(s32 arg0);
extern void func_800AD4D0(void *arg0);
extern void func_800AD568(void *arg0, s32 arg1);
extern void func_800B4C7C(s32 arg0, void *arg1, s32 arg2, s32 arg3);

typedef struct S_818B0850_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x3B];
    u16 unk_64;
} S_818B0850_0;   /* arg0 in func_818B0850 */

void func_818B0850(void *arg0, s32 arg1) {
    if (func_8009D218(arg0, 4) == 0) {
        register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
        s16 temp_v0;
        s32 var_a1;

        temp_v1 = func_800A6870(arg1 & 0xFF) + 8;
        temp_v0 = ((S_818B0850_0 *)arg0)->unk_28 & 4;
        var_a1 = temp_v1;
        if (temp_v0) {
            temp_v0 = (s32) (temp_v1 << 16) >> 18;
            var_a1 = temp_v1 + temp_v0;
        }
        ((S_818B0850_0 *)arg0)->unk_64 = (u16) (((S_818B0850_0 *)arg0)->unk_64 + var_a1);
        func_800AD568(arg0, var_a1);
        func_800B4C7C(0x8004, arg0, (s16) ((S_818B0850_0 *)arg0)->unk_64, 1);
        func_800AD4D0(arg0);
    }
}
