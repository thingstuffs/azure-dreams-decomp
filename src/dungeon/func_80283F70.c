#include "modules/dungeon_dungeon_setup.h"

void initialize_dungeon_region_records(void) {
    s16 next_count;
    s16 count;
    dungeon_setup_80283F70_S_80016F70_0 *record;
    s8 *id_ptr;
    s16 record_id;
    s8 record_type;

    record = (dungeon_setup_80283F70_S_80016F70_0 *)&D_800E3DB0;
    count = 0;
    record_id = count;
    record_type = 1;
    do {
        id_ptr = (s8 *)record + 3;
        next_count = count + 1;
        count = next_count;
        record->unk_00 = record_type;
        id_ptr[-2] = 0;
        id_ptr[-1] = 0;
        id_ptr[0] = record_id;
        record_id += 1;
        record++;
    } while (next_count < 4);
    count = 0;
    record_type = 3;
    do {
        id_ptr = (s8 *)record + 3;
        next_count = count + 1;
        count = next_count;
        record->unk_00 = record_type;
        id_ptr[-2] = 0;
        id_ptr[-1] = 0;
        id_ptr[0] = record_id;
        record_id += 1;
        record++;
    } while (next_count < 2);
    record->unk_00 = 2;
    record->unk_01 = 0;
    record->unk_02 = 0;
    record->unk_03 = record_id;
    record->unk_04 = 0;
}
