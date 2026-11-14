#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

typedef struct Func806D835CRoot {
    u8 pad0[0x38];
    u8 *entries;
} Func806D835CRoot;

extern Func806D835CRoot *town_scene_root;

/* Selects IDs 0x9AF-0x9B6 from two entry codes and returns the match count. */
s32 set_event_flags_for_entry_codes(void)
{
    s32 match_count;
    s32 entry_index;
    s32 entry_code;
    s32 selected_id;
    u8 *entry_data;
    match_count = 2;
    clear_script_flag_bit(F_sbs35_pad04);
    clear_script_flag_bit(F_sbs35_pad05);
    clear_script_flag_bit(F_sbs35_pad06);
    clear_script_flag_bit(F_sbs35_pad07);
    clear_script_flag_bit(F_sbs35_pad08);
    clear_script_flag_bit(F_sbs35_pad09);
    clear_script_flag_bit(F_sbs35_pad10);
    clear_script_flag_bit(F_sbs35_pad11);

    entry_index = 1;
    do {
        entry_data = town_scene_root->entries;
        entry_data += entry_index;
        entry_code = entry_data[0x3608];
        switch (entry_code) {
        case 5:
            selected_id = 0x9AF;
            break;
        case 6:
            selected_id = 0x9B0;
            break;
        case 8:
            selected_id = 0x9B1;
            break;
        case 9:
            selected_id = 0x9B2;
            break;
        case 10:
            selected_id = 0x9B3;
            break;
        case 11:
            selected_id = 0x9B4;
            break;
        case 12:
            selected_id = 0x9B5;
            break;
        default:
            match_count -= 1;
            selected_id = 0x9B6;
            if (match_count != 0) {
                continue;
            }
            break;
        }
        set_script_flag_bit(selected_id);
    } while (--entry_index >= 0);

    return match_count;
}
