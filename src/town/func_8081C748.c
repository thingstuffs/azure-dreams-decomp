#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026748_0_pre {
    u16 unk_00;
} S_80026748_0_pre;   /* the 0x2 bytes before arg0 in func_80026748, addressed as arg0[-1] */

typedef struct S_80026748_0 {
    void * unk_00;
    s32 unk_04;
} S_80026748_0;   /* arg0 in func_80026748 */

typedef struct S_80026748_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80026748_1;   /* arg1 in func_80026748 */

typedef struct S_80026748_2 {
    u8 pad_00[0x58];
    u16 unk_58;
} S_80026748_2;   /* temp_t0 in func_80026748 */

typedef struct S_80026748_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80026748_3;   /* arg2 in func_80026748 */


extern s32 D_800814A0[3];

void func_80026748(void *arg0, S_80026748_1 *arg1, S_80026748_3 *arg2) {
    u16 temp_v0;
    S_80026748_2 *temp_t0;

    temp_t0 = ((S_80026748_0 *)arg0)->unk_00;
    arg1->unk_00 = (s32) (arg1->unk_00 + ((S_80026748_0 *)arg0)->unk_04);
    arg1->unk_04 = (s32) (arg1->unk_04 + arg1->unk_10);
    temp_t0->unk_58 = (u16) (temp_t0->unk_58 | 1);
    temp_v0 = arg2->unk_1E - 0x100;
    arg2->unk_1E = temp_v0;
    arg2->unk_1C = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) < 0x201U) {
        temp_t0->unk_58 = (u16) (temp_t0->unk_58 & 0xFFFE);
        ((S_80026748_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80026748_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
