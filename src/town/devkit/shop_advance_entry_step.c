#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_80701DCE[];
extern TownPair D_80701DFC[];

extern s32 test_flag_list_terminator(s32 index);
extern void set_entry_bit_flag(s32 index, s32 value);
extern s32 advance_clear_flag_row(void);
extern void set_linked_flag(u16 value);
extern void clear_linked_flag(s32 value);
extern s32 test_linked_flag(u16 value);

/* Advance the selected flag row and process entry zero when required. */
s32 advance_selected_flag_row(s32 index) {
    if (test_linked_flag(D_80701DCE[0]) == 0 &&
        test_linked_flag(0x1F9) != 0) {
        if (test_flag_list_terminator(index) != 0) {
            set_linked_flag(D_80701DFC[index].field_0);
            clear_linked_flag(0x1F9);
            return advance_clear_flag_row();
        }
        set_entry_bit_flag(index, 0);
        return index;
    }
    set_entry_bit_flag(index, 0);
    return index;
}
