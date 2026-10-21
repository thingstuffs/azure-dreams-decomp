#include "common.h"

extern u32 func_8001E670(s16 value);
extern u8 D_80017BD0[];
extern u8 town_selection_records[];

/* Counts listed records whose value at offset 4 passes func_8001E670. */
s32 count_listed_enabled_records(void) {
    s32 match_count;
    u8 *record_ids;
    u8 *records;

    match_count = 0;
    if (D_80017BD0[0] == 0) {
        return match_count;
    }
    do {
        records = town_selection_records;
    } while (0);
    record_ids = D_80017BD0;
    do {
        if (func_8001E670(*(s16 *)(records + (*record_ids * 0xC) + 4)) != 0) {
            match_count += 1;
        }
        record_ids += 1;
    } while (*record_ids != 0);
    return match_count;
}
