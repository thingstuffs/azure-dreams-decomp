/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF674_1 {
    void * unk_00;
} S_800AF674_1;   /* arg0 in func_800AF674 */

typedef struct S_800AF674_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    s32 * unk_20;
} S_800AF674_2;   /* ((S_800AF674_1 *)arg0)->unk_00 in func_800AF674 */


typedef struct S_800AF674_0 {
    u8 pad_00[0xA8];
    union { s32 s; s32 * u; } unk_A8;   /* accessed as both */
} S_800AF674_0;   /* arg0 in func_800AF674 */


s32 func_8004AC3C();
s32 func_8004DC14();
M2C_UNK func_800B0318();

void func_800AF674(S_800AF674_0 *arg0) {
    s32 sp10;
    s32 *temp_v1_2;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0x10;
    func_800B0318(arg0->unk_A8.s);
    var_s0 = ((S_800AF674_2 *)(((S_800AF674_1 *)arg0)->unk_00))->unk_10 * 0xA;
loop_1:
    if (var_s0 < ((S_800AF674_2 *)(((S_800AF674_1 *)arg0)->unk_00))->unk_1C) {
        temp_a0 = ((S_800AF674_2 *)(((S_800AF674_1 *)arg0)->unk_00))->unk_20[var_s0];
        temp_v0 = func_8004AC3C(temp_a0, &sp10);
        var_s0 += 1;
        temp_v0 = func_8004DC14(temp_v0, sp10);
        temp_v1_2 = arg0->unk_A8.u[var_s1];
        var_s1 += 1;
        *temp_v1_2 = temp_v0;
        if (var_s1 < 0x1A) {
            goto loop_1;
        }
    }
}
