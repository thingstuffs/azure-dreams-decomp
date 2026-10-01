#include "common.h"
#include "shared/def_table.h"
#include "shared/dungeon_status.h"


s32 func_800A35D8(u8 arg0, u16 arg1);

/* Selects the highest-value nonempty item among three slots, breaking ties by kind score. */
s16 func_800A40AC(s32 records_addr, s32 item_kind)
{
    s16 result;
    s32 best_score;
    s16 best_value;
    s32 count;
    s32 table_or_result;
    s16 index;
    s32 value;
    s32 tripled_index;
    u8 item;
    register s32 item_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 records;
    u8 *record;

    records = records_addr;
    records_addr = item_kind;
    result = -1;
    best_score = -4;
    best_value = 0;
    count = 0;
    tripled_index = dungeonStatus.unk_1E;
    table_or_result = (s32)D_8006DE24;
    index = tripled_index & 3;
    do {
        if (((s16)(index)) == 3) {
            index = 0;
        }
        tripled_index = ((s16)(index)) * 3;
        record = (u8 *)records + tripled_index;
        item = record[8];
        if (item != 0) {
            s32 score;
            s32 prior_value;
            s16 candidate_value;

            value = record[9];
            item_offset = item * 20;
            score = func_800A35D8(((u8 *)table_or_result)[item_offset + 16], (u16)records_addr);
            prior_value = best_value;
            candidate_value = value;
            if (prior_value < candidate_value) {
                best_value = value;
                result = index + 5;
                best_score = score;
            } else if (prior_value == candidate_value) {
                if ((best_score << 16) < (score << 16)) {
                    best_score = score;
                    result = index + 5;
                }
            }
            count++;
        } else {
            count++;
        }
        index++;
        if (count >= 3) {
            break;
        }
    } while (1);
    table_or_result = result;
    return table_or_result;
}
