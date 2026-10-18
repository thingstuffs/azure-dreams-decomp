#include "common.h"

typedef struct {
    s32 words[4];
} PackedWord;

extern PackedWord D_80016024;
extern s32 get_script_flag_mask(s32);
extern s32 read_script_flag_range(s32, s32);
extern void write_script_flag_range(s32, s32, s32);

/* Returns the selected table value, cycling the selection when the 0xDB0 check fails. */
s32 cycle_d_6_e_selection_if_allowed(void)
{
    PackedWord table;
    s32 selection;

    table = D_80016024;
    selection = read_script_flag_range(0xD6E, 2);
    if (get_script_flag_mask(0xDB0) == 0) {
        selection++;
        if (selection == 4) {
            selection = 0;
        }
        write_script_flag_range(0xD6E, selection, 2);
    }
    return table.words[selection];
}
