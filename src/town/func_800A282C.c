#include "common.h"

typedef struct {
    u8 pad0[6];
    u8 result;
    u8 pad7[9];
    s16 x;
    s16 y;
} TownRecord;

typedef struct {
    u16 x;
    u16 y;
    u8 pad4[8];
    void *recordsOwner;
} TownState;

extern s32 func_8003BD84(s32, s32);
extern s32 D_800D0728[];
extern TownState *D_80100900;

/* Return the nearest unflagged record's result, or -1 if none is available. */
s32 func_8009FF8C(s32 record_set, void *target)
{
    TownRecord *records;
    TownRecord *record;
    u8 *flag_base;
    s32 count;
    s32 best_distance;
    register s32 best_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 record_index;
    s32 base_x;
    s32 base_y;
    s32 distance;
    s32 result;
    u16 raw_x;
    u16 raw_y;

    best_distance = 0x7FFFFFFF;
    record_index = 0;
    count = D_800D0728[record_set];
    records = *(TownRecord **)((u8 *)D_80100900->recordsOwner + 4);
    raw_x = D_80100900->x;
    raw_y = D_80100900->y;
    best_index = record_index;
    if (count > 0) {
        base_x = (s16)raw_x;
        base_y = (s16)raw_y;
        record = records;
        flag_base = (u8 *)0x80010000;
        do {
            if (flag_base[0x981] == 0) {
                distance = func_8003BD84(
                    ((record->x + base_x) - *(s16 *)(target + 2)) << 16,
                    ((record->y + base_y) - *(s16 *)(target + 6)) << 16);
                if (distance < best_distance) {
                    best_distance = distance;
                    best_index = record_index;
                }
                record++;
            } else {
                record++;
            }
            record_index++;
            flag_base += 4;
        } while (record_index < count);
    }
    if (best_distance == 0x7FFFFFFF) {
        goto no_best;
    }
    result = records[best_index].result;
    goto done;
no_best:
    result = -1;
done:
    return result;
}

