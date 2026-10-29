#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/player/state.h"
#include "town/scene.h"

typedef struct {
    s32 words[4];
} PackedWord;

extern PackedWord D_80016024;

/* Returns the selected table value, cycling the selection when the 0xDB0 check fails. */
s32 cycle_d_6_e_selection_if_allowed(void)
{
    PackedWord table;
    s32 selection;

    table = D_80016024;
    selection = read_script_flag_range(Ftt_pad61, 2);
    if (get_script_flag_mask(Ftt_pad128) == 0) {
        selection++;
        if (selection == 4) {
            selection = 0;
        }
        write_script_flag_range(Ftt_pad61, selection, 2);
    }
    return table.words[selection];
}
