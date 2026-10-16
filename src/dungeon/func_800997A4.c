#include "common.h"

extern s16 D_800E3CD8[8];
extern void dungeonSubmitActivationCommand(void);
extern void dungeonCreateTransformedRenderObject(s16 x, s16 y, s32 color, s32 size, s32 count);

/* Create green markers for up to four leading type-2 entries. */
void dungeonDrawGreenTypeTwoMarkers(void) {
    s16 *record;
    s32 entry_count;
    s32 color;

    dungeonSubmitActivationCommand();
    entry_count = 0;
    record = D_800E3CD8;
loop:
    if (record[0] == 2) {
        color = 0x208020;
        dungeonCreateTransformedRenderObject(record[1], record[2], color, 1, 0);
        record += 4;
        entry_count += 1;
        if (entry_count < 4) {
            goto loop;
        }
    }
}
