#include "common.h"

extern u8 D_80701DFC[];
extern void advance_selected_flag_row(s32 index);
extern s32 test_linked_flag(u16 value);

/* Select the first table entry whose value check returns zero. */
void advance_clear_flag_row(void) {
    s32 index = 0;
    s32 offset = 0;

    while (test_linked_flag(*(u16 *)&D_80701DFC[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    advance_selected_flag_row(index);
}
