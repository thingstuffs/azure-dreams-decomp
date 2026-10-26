#include "common.h"
#include "town/player/script_flags.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} TownRecord;

extern s16 scene_dependency_ids[3];

/* Processes town records according to global and per-record conditions. */
void process_town_records(s32 records_addr, s32 record_count)
{
    s32 record_index;
    TownRecord *record;
    s16 *condition_ids;

    if ((records_addr != 0) && (record_index = 0, (record_count > 0))) {
        condition_ids = scene_dependency_ids;
        do {
            record = (TownRecord *)((record_index * 8) + records_addr);
            clear_script_flag_bit(record->unk2);
            if (get_script_flag_mask(condition_ids[1]) == 0) {
                clear_script_flag_bit(record->unk4);
            } else {
                record = (TownRecord *)((record_index * 8) + records_addr);
                if (get_script_flag_mask(record->unk0) != 0) {
                    set_script_flag_bit(record->unk4);
                }
            }
            clear_script_flag_bit(((TownRecord *)((record_index * 8) + records_addr))->unk0);
            record_index++;
            if (record_index >= record_count) {
                break;
            }
        } while (1);
    }
}

/* MECHANISM: A held pointer to D_8001B8A8 supplies retail's long-lived s4 base, while index-derived
   eight-byte record pointers force retail's repeated sll/addu. Pinning only the runtime index to s1
   leaves the record pointer to fall naturally into s0. */
