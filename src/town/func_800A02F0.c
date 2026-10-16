#include "modules/town_town_windows.h"

/* Process eligible entries and mark those handled successfully as active. */
void townProcessEligibleEntries(func_800A02F0_S_8009DA50_2 *entries, void *bounds, s32 origin_x, s32 origin_y)
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
            if (!(flags & 1) ? testResidentBitmapBit(entries->unk_02) != 0 : testResidentBitmapBit(entries->unk_02) != 1) {
                test_x = base_x + entries->unk_10;
                test_y = base_y + entries->unk_12;
                entry_x = test_x;
                entry_y = test_y;
                if ((townCheckFourVectorHalfTurnGaps(
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_00 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_02 - test_y),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_08 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_0A - test_y),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_10 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_12 - test_y),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_18 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_1A - test_y)) != 0) ||
                    (D_8006ADD4 == 0xC) ||
                    (entries->unk_01 & 0x10)) {
                    if (townCreateObjectAndInitializeRenderState(entries->unk_0C, entries->unk_04, entries->unk_05, entries->unk_06,
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
