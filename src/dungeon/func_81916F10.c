#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

typedef struct S_80024710_0 {
    void * unk_00;
    u8 pad_04[0xA];
    s16 unk_0E;
    s16 unk_10;
} S_80024710_0;   /* arg0 in func_80024710 */

typedef struct S_80024710_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024710_1;   /* temp_v1 in func_80024710 */

typedef struct S_80024710_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024710_2;   /* arg1 in func_80024710 */

void func_80024710(S_80024710_0 *arg0, S_80024710_2 *arg1) {
    s32 temp_s0;
    s32 temp_s0_2;
    S_80024710_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    temp_s0 = func_800644B8(arg0->unk_0E);
    arg1->unk_00 = (s32) (arg1->unk_00 + ((temp_s0 >> 4) * (func_800644B8(arg0->unk_10) >> 4) * 0x1C));
    temp_s0_2 = func_800644B8(arg0->unk_0E);
    arg1->unk_04 = (s32) (arg1->unk_04 + ((temp_s0_2 >> 4) * (func_80064584(arg0->unk_10) >> 4) * 0x1C));
    arg1->unk_08 = (s32) (arg1->unk_08 + ((func_80064584(arg0->unk_0E) >> 4) * 0x1C00));
}
