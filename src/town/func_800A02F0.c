#include "common.h"

typedef struct S_8009DA50_1 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x4];
    u16 unk_18;
    u16 unk_1A;
} S_8009DA50_1;   /* var_s4 in func_8009DA50 */

typedef struct S_8009DA50_2 {
    u8 unk_00;
    u8 unk_01;
    s16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
} S_8009DA50_2;   /* one 0x14-byte entry */


extern s32 func_80033B2C();
extern s32 func_8008CC90();
extern s32 func_8009D424();
extern s16 D_8006ADD4;

/* Process eligible entries and mark those handled successfully as active. */
void func_8009DA50(S_8009DA50_2 *entries, void *bounds, s32 origin_x, s32 origin_y)
{
    s32 test_x;
    s32 test_y;
    s16 entry_x;
    s16 entry_y;
    s32 base_y;
    s32 base_x;
    s32 flags;

    base_x = origin_x;
    base_y = origin_y;
    while (((flags = entries->unk_01) & 0xC0) != 0x80) {
        if (entries->unk_00 == 0) {
            if (!(flags & 1) ? func_80033B2C(entries->unk_02) != 0 : func_80033B2C(entries->unk_02) != 1) {
                test_x = base_x + entries->unk_10;
                test_y = base_y + entries->unk_12;
                entry_x = test_x;
                entry_y = test_y;
                if ((func_8008CC90(
                         (s16)(((S_8009DA50_1 *)bounds)->unk_00 - test_x),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_02 - test_y),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_08 - test_x),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_0A - test_y),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_10 - test_x),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_12 - test_y),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_18 - test_x),
                         (s16)(((S_8009DA50_1 *)bounds)->unk_1A - test_y)) != 0) ||
                    (D_8006ADD4 == 0xC) ||
                    (entries->unk_01 & 0x10)) {
                    if (func_8009D424(entries->unk_0C, entries->unk_04, entries->unk_05, entries->unk_06,
                            entries->unk_07, entries->unk_01 & 0x20, entries->unk_08,
                            (s16)entry_x, (s16)entry_y, entries) != 0) {
                        entries->unk_00 = 1;
                    }
                    while (!(entries->unk_01 & 0xC0)) {
                        entries++;
                    }
                }
            }
        }
        entries++;
    }
}
