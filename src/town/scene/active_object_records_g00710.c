/* Build and submit active object records (G00710). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80470EB8, CL:town/func_80470F3C, PD:town/image_3ef000:8001B318. */
#include "town/scene/active_object_records_g00710.h"
#include "town/scene.h"

/* Checks whether the selected entry is 8 or 9 and get_record_value_tier returns zero. */
s32 check_selected_entry_8(S_80017EB8_0 *position) {
    s32 entry_value;
    u8 column;
    u8 row;

    row = position->unk_01;
    column = position->unk_00;
    entry_value = ((S_80017EB8_4 *)((column * 0x14) + ((S_80017EB8_3 *)(((row * 0x14)
        + ((TownResourceLinks *)town_scene_root->unk_24)->gridRows)))->unk_0C))->unk_00;
    if (get_record_value_tier() == 0) {
        if ((u32)(entry_value - 8) < 2U) {
            return 1;
        }
    }
    return 0;
}

/* Builds a terminated record list with an optional entry and flags checked records. */
u8 *record_check_returned(void *unused)
{
    s32 record_count;
    s32 record_id;
    s32 checked_count;
    s32 plain_count;
    s32 checked_tag;
    u32 plain_tag;
    register u8 *seed_record;
    register u8 *records;
    u8 *optional_record;
    u8 *checked_base;
    u8 *checked_record;
    u8 *plain_base;
    u8 *plain_record;
    u8 *tail_base;
    u32 end_offset;
    u8 *end_record;

    records = town_event_records;
    seed_record = D_8001B1C0;
    *(Copy4 *)records = *(Copy4 *)seed_record;
    record_count = 1;
    if (func_8001A510(F_sbs22_pad36) != 0) {
        record_count = 2;
        optional_record = records + 4;
        optional_record[1] = 0xD;
        records[4] = 4;
        optional_record[3] = 0;
        optional_record[2] = 0;
    }

    record_id = 1;
    checked_base = records;
    checked_tag = 0x18;
    do {
        {
            checked_count = record_count + record_id;
            checked_record = (u8 *)((u32)((checked_count - 1) * 4) + (unsigned long)checked_base);
            checked_record[1] = checked_tag;
            checked_record[0] = record_id;
            if (check_selected_entry_8((S_80017EB8_0 *)checked_record) != 0) {
                checked_record[3] |= 0x80;
            }
            record_id++;
        }
    } while (record_id < 0x20);

    record_count = checked_count;
    record_id = 1;
    plain_base = town_event_records;
    plain_tag = 0xB;
    do {
        {
            plain_count = record_count + record_id;
            plain_record = (u8 *)((u32)((plain_count - 1) * 4) + (unsigned long)plain_base);
            plain_record[0] = record_id;
            record_id++;
            plain_record[1] = plain_tag;
        }
    } while (record_id < 6);

    record_count = plain_count;
    plain_tag = plain_count * 4;
    record_count++;
    tail_base = town_event_records;
    plain_tag += (u32)tail_base;
    end_record = (u8 *)0x18;
    ((u8 *)plain_tag)[1] = (s32)end_record;
    end_record = (u8 *)0x20;
    ((u8 *)plain_tag)[0] = (s32)end_record;
    end_offset = record_count * 4;
    end_record = (u8 *)(end_offset + (unsigned long)tail_base);
    end_record[1] = 0;
    end_record[0] = 0;
    return tail_base;
}

/* Prepares D_8001B218, passes it to the active object's callback, and saves the result. */
S_80018174_0 *prepare_passes_active_object_callback(void) {
    func_80018824((s8 *)town_event_records, 0x100);
    record_check_returned(town_event_records);
    return scene_registered_event_handle = (S_80018174_0 *)town_scene_root->services->callback_068(0, 0, 1, town_event_records);
}

/* Prepares D_8001B218 for the active object's callback and stores its result. */
S_80018174_0 *prepare_active_object_callback(void) {
    func_80018824((s8 *)town_event_records, 0x100);
    func_80018914(town_event_records);
    return scene_registered_event_handle = (S_80018174_0 *)town_scene_root->services->callback_068(0, 1, 1, town_event_records);
}

/* Cache the value at offset 0x24 and return the value at offset 0x20. */
s32 cache_value_at_offset_0x24(void) {
    D_8001B31C = scene_registered_event_handle->unk_24;
    return scene_registered_event_handle->unk_20;
}
