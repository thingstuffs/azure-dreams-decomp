#include "common.h"

extern u32 find_target_byte_index_in_list(void);
extern void load_a_shared_buffer_process_write_back(void *record_ref);
extern void set_resident_bitmap_bit(s32 bit_id);
extern s32 D_800D0728[];
extern s16 D_800D253C[];

/* Processes entries in state 19 and triggers their associated sounds. */
void process_entries_in_state_n_19_triggers_associated_sounds(void) {
    s32 entry_count;
    s32 entry_index;
    s16 *sound_id;
    u8 *entry;
    u8 state;

    entry_count = D_800D0728[find_target_byte_index_in_list()];
    do {
        entry_index = 0;
    } while (0);
    if (entry_count > 0) {
        sound_id = D_800D253C;
        entry = (u8 *)0x80010000;
loop:
        state = entry[0x981];
        if (state != 0) {
            if (state == 19) {
                load_a_shared_buffer_process_write_back((void *)(0x80010A80 + ((entry[0x983] & 0x3F) * 84)));
                set_resident_bitmap_bit(*sound_id);
            }
        }
        sound_id++;
        entry_index++;
        entry += 4;
        if (entry_index < entry_count) {
            goto loop;
        }
    }
}
