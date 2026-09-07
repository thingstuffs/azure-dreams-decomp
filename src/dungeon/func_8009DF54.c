#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A36B4_0 {
    void * unk_00;
    u8 pad_04[0x3A];
    u16 unk_3E;
    u8 pad_40[0x5C];
    u16 unk_9C;
} S_800A36B4_0;   /* arg0 in func_800A36B4; pointer addresses record offset 0x14 */

typedef struct S_800A36B4_1 {
    void * unk_00;
} S_800A36B4_1;   /* arg1 in func_800A36B4; pointer addresses record offset 0x14 */

typedef struct S_800A36B4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A36B4_2;   /* temp_a3 in func_800A36B4 */

typedef struct S_800A36B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A36B4_3;   /* temp_s3 in func_800A36B4 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 func_800A44E0(u16, u16, s16, s16);
extern s32 func_800BCB04(s32, s32, s16);

s32 func_800A36B4(void *arg0, void *arg1) {
    s32 temp_s5;
    s32 temp_s6;
    S_800A36B4_2 *temp_a3;
    S_800A36B4_3 *temp_s3;
    s32 temp_s7;
    s32 temp_s1;
    s32 temp_s0;
    s32 temp_s4;
    s16 temp_s2;

    temp_a3 = ((S_800A36B4_0 *)((u8 *)arg0 - 0x14))->unk_00;
    temp_s3 = ((S_800A36B4_1 *)((u8 *)arg1 - 0x14))->unk_00;
    temp_s6 = temp_a3->unk_24 - temp_s3->unk_24;
    temp_s7 = ((S_800A36B4_0 *)((u8 *)arg0 - 0x14))->unk_3E;
    if (temp_s6 != 0) {
        if (temp_s6 > 0) {
            temp_s6 = 1;
        } else {
            temp_s6 = -1;
        }
    }
    temp_s5 = temp_a3->unk_25 - temp_s3->unk_25;
    if (temp_s5 != 0) {
        if (temp_s5 > 0) {
            temp_s5 = 1;
        } else {
            temp_s5 = -1;
        }
    }
    temp_s1 = temp_a3->unk_24;
    temp_s0 = temp_a3->unk_25;
    temp_s4 = ((S_800A36B4_0 *)((u8 *)arg0 - 0x14))->unk_9C;

    while (temp_s1 != temp_s3->unk_24 ||
           temp_s0 != temp_s3->unk_25) {
        temp_s2 = temp_s4;
        if ((func_800A44E0((temp_s1 << 6) & 0xFFC0,
                           (temp_s0 << 6) & 0xFFC0,
                           temp_s2, temp_s7) << 16) != 0) {
            return 0;
        }
        temp_s1 -= temp_s6;
        temp_s0 -= temp_s5;
        {
            s32 temp_v1;
            temp_v1 = func_800BCB04(((temp_s1 << 6) + 0x20) & 0xFFE0,
                                     ((temp_s0 << 6) + 0x20) & 0xFFE0,
                                     temp_s4 - 0x20);
            if ((s16)temp_v1 < temp_s2) {
                temp_s4 = temp_v1;
            }
        }
    }
    return 1;
}
