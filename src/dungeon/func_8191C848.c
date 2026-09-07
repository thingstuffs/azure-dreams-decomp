#include "common.h"
#include "m2c_compat.h"

typedef struct S_8191C848_0_pre {
    u16 unk_00;
} S_8191C848_0_pre;   /* the 0x2 bytes before arg0 in func_8191C848, addressed as arg0[-1] */

typedef struct S_8191C848_0 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
} S_8191C848_0;   /* arg0 in func_8191C848 */

typedef struct S_8191C848_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8191C848_1;   /* temp_v1 in func_8191C848 */

typedef struct S_8191C848_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8191C848_2;   /* arg2 in func_8191C848 */

typedef struct S_8191C848_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8191C848_3;   /* arg1 in func_8191C848 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

void func_8191C848(void *arg0, S_8191C848_3 *arg1, S_8191C848_2 *arg2) {
    s32 temp_lo;
    S_8191C848_1 *temp_v1;
    temp_v1 = ((S_8191C848_0 *)arg0)->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        ((S_8191C848_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8191C848_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
    arg1->unk_02 = (u16) (arg1->unk_02 + ((s32) ((func_800644B8(((S_8191C848_0 *)arg0)->unk_08) >> 4) * ((S_8191C848_0 *)arg0)->unk_0A) >> 8));
    temp_lo = (func_80064584(((S_8191C848_0 *)arg0)->unk_08) >> 4) * ((S_8191C848_0 *)arg0)->unk_0A;
    arg1->unk_0A = (u16) (arg1->unk_0A - 4);
    arg1->unk_06 = (u16) (arg1->unk_06 + (temp_lo >> 8));
}
