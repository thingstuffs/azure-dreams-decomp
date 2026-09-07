#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024B48_0_pre {
    u16 unk_00;
} S_80024B48_0_pre;   /* the 0x2 bytes before arg0 in func_80024B48, addressed as arg0[-1] */

typedef struct S_80024B48_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x38];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80024B48_0;   /* arg0 in func_80024B48 */

typedef struct S_80024B48_1 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80024B48_1;   /* D_80080000 in func_80024B48 */

typedef struct S_80024B48_2 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024B48_2;   /* ((S_80024B48_0 *)arg0)->unk_00 in func_80024B48 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80080000[];

void func_80024B48(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v2;
    s32 temp_v3;

    ((S_80024B48_2 *)(((S_80024B48_0 *)arg0)->unk_00))->unk_52 =
        (s16) (((S_80024B48_2 *)(((S_80024B48_0 *)arg0)->unk_00))->unk_52 | 0x8000);
    ((S_80024B48_0 *)arg0)->unk_48 = (u16) (((S_80024B48_0 *)arg0)->unk_48 + 1);
    if (((S_80024B48_0 *)arg0)->unk_4C != 0) {
        if (((S_80024B48_0 *)arg0)->unk_4C != 1) {
            return;
        }
        goto block_5;
    }
    temp_v0 = (s16) ((S_80024B48_0 *)arg0)->unk_0C;
    temp_v1 = (s16) ((S_80024B48_0 *)arg0)->unk_0E;
    ((S_80024B48_0 *)arg0)->unk_48 = 0U;
    ((S_80024B48_0 *)arg0)->unk_04 = (s16) ((temp_v0 << 6) + 0x20);
    ((S_80024B48_0 *)arg0)->unk_06 = (s16) ((temp_v1 << 6) + 0x20);
    temp_v2 = (s16) ((S_80024B48_0 *)arg0)->unk_0C;
    temp_v3 = (s16) ((S_80024B48_0 *)arg0)->unk_0E;
    ((S_80024B48_0 *)arg0)->unk_0C = (s16) ((temp_v2 - 7) << 6);
    ((S_80024B48_0 *)arg0)->unk_0E = (s16) ((temp_v3 - 7) << 6);
    ((S_80024B48_0 *)arg0)->unk_4C = (s16) ((u16) ((S_80024B48_0 *)arg0)->unk_4C + 1);
block_5:
    if ((s16) ((S_80024B48_0 *)arg0)->unk_48 >= 0x20) {
        ((S_80024B48_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80024B48_0_pre *)arg0)[-1].unk_00 | 0x8000);
        (*(s32 *)((u8 *)D_80080000 + 0x14A0)) = (s32) (((S_80024B48_1 *)D_80080000)->unk_14A0 | 0x8000);
    }
}
