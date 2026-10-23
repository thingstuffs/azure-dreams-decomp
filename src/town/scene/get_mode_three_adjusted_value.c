#include "common.h"

extern s32 scene_captured_value[];
extern s32 D_00003FCC[];
extern s32 D_000045F8[];

extern s32 print_scene_sequence_number_sno(s32 mode);
extern s32 set_flag_entry_has_bit(s32 index, s32 mode);

/* Return the selected table value plus the global offset after mode-three calls. */
s32 get_mode_three_adjusted_value(void) {
    s32 entry_index;
    s32 entry_value;

    entry_index = scene_captured_value[0];
    entry_value = D_00003FCC[entry_index * 8];
    set_flag_entry_has_bit(entry_index, 3);
    print_scene_sequence_number_sno(3);
    return entry_value + D_000045F8[0];
}

/* MECHANISM: Named overlay globals force the retail hi/lo address forms.
   The table is word-indexed by index*8, emitting the byte stride sll 5.
   Holding the table value across both calls naturally allocates only s0. */
