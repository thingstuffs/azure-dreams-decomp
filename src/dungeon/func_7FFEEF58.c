#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8008D050();                      /* extern */

typedef struct S_8008C6B8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C6B8_0;   /* arg0 in func_8008C6B8 */

typedef struct S_8008C6B8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C6B8_1;   /* temp_s0 in func_8008C6B8 */

s16 func_8008C6B8(S_8008C6B8_0 *arg0, s32 arg1, s32 arg2) {
    s32 sp10[5];
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0_2;
    s32 component;
    register s32 addend ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_8008C6B8_1 *temp_s0;

    temp_a2 = arg2 * 0x10;
    temp_s0 = temp_a2 + arg1;
    component = arg0->unk_00;
    addend = temp_s0->unk_00;
    component += addend;
    sp10[0] = component;
    component = arg0->unk_04;
    addend = temp_s0->unk_04;
    component += addend;
    sp10[1] = component;
    component = arg0->unk_08;
    addend = temp_s0->unk_08;
    component += addend;
    sp10[2] = component;
    temp_v0 = func_8008D050(sp10);
    if ((temp_v0 << 0x10) == 0) {
        return 0;
    }
    temp_v1 = temp_s0->unk_04;
    var_v0_2 = temp_v1 >> 0x10;
    if (temp_v1 < 0) {
        temp_v1 += 0xFFFF;
        var_v0_2 = temp_v1 >> 0x10;
    }
    return temp_v0 - var_v0_2;
}
