#include "common.h"

#include "engine/entity.h"
#include "dungeon/actor.h"

/* Finds a record slot matching an initial-stat value group, or returns -1. */
s32 find_matching_initial_stat_slot(u8 *record) {
    s32 initial_index;
    s32 initial_value;
    s32 entry_index;
    s32 value_group;
    u8 *initial_entry;
    u8 *entry;
    u8 entry_value;

    initial_index = 0;
    initial_entry = (u8 *)initialStatsTable + (record[0x13] * 24);
    do {
        initial_value = initial_entry[8] & 0x7F;
        if ((initial_value != 0) && (initial_value < 46)) {
            entry_index = 0;
            entry = record;
            value_group = (initial_value - 1) / 3;
            do {
                entry_value = entry[8];
                if ((entry_value != 0) &&
                    (value_group == ((entry_value - 1) / 3))) {
                    return (s16)entry_index;
                }
                entry_index += 1;
                /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_8180E73C). */
                do {
                    entry += 3;
                } while (0);
            } while (entry_index < 3);
        }
        initial_index += 1;
        initial_entry += 3;
    } while (initial_index < 3);
    return -1;
}
