/* cfail-repair: unary-star typing only */
#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK func_8003BAF8();
extern M2C_UNK func_800A0BC0();
extern void func_800A0BC8(s32 *arg0);
extern s32 func_800B2834();
extern M2C_UNK func_800B28A0();

void func_800A0B74(void *arg0, s32 *arg1) {
    u8 temp_v1;

    temp_v1 = *((u8 *)((s8 *)arg0 + 0x96));
    if (temp_v1 == 0) {
        func_800A0BC8(arg1);
        return;
    }
    if (temp_v1 == 1) {
        s32 temp_v0;

        temp_v0 = func_800B28A0();
        temp_v0 <<= 2;
        ASM_TAILSLOT_PIN_TIED(temp_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800A0BC0();
        return;
    }
    func_8003BAF8(arg1[func_800B2834()]);
}
