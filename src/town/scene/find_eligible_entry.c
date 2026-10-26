#include "common.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/script_flags.h"

typedef s32 (*TownEntryPredicate)(void *, s32);

typedef struct S_80019F94_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019F94_1;



typedef struct S_80019F94_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
} S_80019F94_0;   /* held_arg0 in find_eligible_entry */

/* Returns the first eligible entry with a zero callback result, restarting when requested. */
s32 find_eligible_entry(void *context) {
    S_80019F94_0 *scan;
    s32 *flag_page;
    s32 entry_index;

    scan = context;
    process_town_records(scan->unk_14, scan->unk_1A);
    flag_page = (s32 *)0x80020000;
    do {
        flag_page[-3874] = 0;
        entry_index = 0;
        for (;;) {
            if ((get_script_flag_mask(((S_80019F94_1 *)(scan->unk_10 + entry_index * 0x10))->unk_0C) != 0) ||
                (*(TownEntryPredicate *)(scan->unk_10 + entry_index * 0x10))(scan, entry_index) != 0) {
                entry_index++;
                continue;
            }
            break;
        }
    } while (flag_page[-3874] != 0);
    return entry_index;
}
