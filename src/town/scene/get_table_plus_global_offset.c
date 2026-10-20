/* Relinked copy of town/func_808B81FC (func_808B81FC.c); it uses mode 2 (twin mode 3), otherwise retail differs only at relocation sites. */
#include "common.h"

extern s32 D_00003F50[];
extern s32 D_00003FC4[];
extern s32 D_000045F8[];

extern s32 print_scene_sequence_number_sno(s32 mode);
extern s32 set_flag_entry_has_bit(s32 index, s32 mode);

/* Return the selected table value plus the global offset after mode-two calls. */
s32 get_table_plus_global_offset(void) {
    s32 entry_index;
    s32 entry_value;

    entry_index = D_00003F50[0];
    entry_value = D_00003FC4[entry_index * 8];
    set_flag_entry_has_bit(entry_index, 2);
    print_scene_sequence_number_sno(2);
    return entry_value + D_000045F8[0];
}

/* MECHANISM: Named overlay globals force the retail hi/lo address forms.
   The table is word-indexed by index*8, emitting the byte stride sll 5.
   Holding the table value across both calls naturally allocates only s0. */
