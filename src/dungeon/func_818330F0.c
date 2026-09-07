#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818330F0_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818330F0_0;   /* arg1 in func_818330F0 */

typedef struct S_818330F0_1_pre {
    u16 unk_00;
} S_818330F0_1_pre;   /* the 0x2 bytes before arg0 in func_818330F0, addressed as arg0[-1] */

typedef struct S_818330F0_1 {
    void * unk_00;
    u8 pad_04[0x8];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} S_818330F0_1;   /* arg0 in func_818330F0 */


typedef struct S_818330F0_3 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818330F0_3;   /* temp_v1 in func_818330F0 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0;
void func_818330F0(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0;
    s16 temp_v0;
    void *temp_v1;

    ((S_818330F0_0 *)arg1)->unk_02 = (s16) ((u16) ((S_818330F0_0 *)arg1)->unk_02 + ((((S_818330F0_1 *)arg0)->unk_0C - ((S_818330F0_0 *)arg1)->unk_02) / 12));
    ((S_818330F0_0 *)arg1)->unk_06 = (s16) ((u16) ((S_818330F0_0 *)arg1)->unk_06 + ((((S_818330F0_1 *)arg0)->unk_0E - ((S_818330F0_0 *)arg1)->unk_06) / 12));
    temp_a0 = ((S_818330F0_1 *)arg0)->unk_10;
    temp_v0 = ((S_818330F0_0 *)arg1)->unk_0A;
    ((S_818330F0_0 *)arg1)->unk_0A = (s16) ((u16) ((S_818330F0_0 *)arg1)->unk_0A + ((temp_a0 - temp_v0) / 10));
    ((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v = (s32) (((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v + 0xC0C0C);
    temp_v1 = ((S_818330F0_1 *)arg0)->unk_00;
    ((S_818330F0_3 *)temp_v1)->unk_52 = (u16) (((S_818330F0_3 *)temp_v1)->unk_52 | 0x8000);
    func_800478B8(arg2);
    if ((u8) ((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v >= 0x91U) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_818330F0_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
