#include "common.h"
#include "town/scene.h"

extern u32 func_8001E670(s16 value);
extern u8 town_counted_record_ids[];
extern u8 town_selection_records[];

/* Counts listed records whose value at offset 4 passes func_8001E670. */
s32 count_listed_enabled_records(void) {
    s32 match_count;
    u8 *record_ids;
    u8 *records;

    match_count = 0;
    if (town_counted_record_ids[0] == 0) {
        return match_count;
    }
    /* BYTES: cse block end at the loop note: unwrap lets cse forward/fold a value retail recomputes (ledger/onetrip_loadbearing.jsonl: town/func_804695D0). */
    do {
        records = town_selection_records;
    } while (0);
    record_ids = town_counted_record_ids;
    do {
        if (func_8001E670(*(s16 *)(records + (*record_ids * 0xC) + 4)) != 0) {
            match_count += 1;
        }
        record_ids += 1;
    } while (*record_ids != 0);
    return match_count;
}
