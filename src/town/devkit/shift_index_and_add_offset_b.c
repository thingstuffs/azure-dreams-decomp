/* Relinked copy of town/func_808B98AC (func_808B98AC.c); retail differs only at relocation sites. */
#include "common.h"
extern u32 D_00004160, D_00004608;
void shift_index_and_add_offset_b(void) { u32 *index = &D_00004160; *index = (*index << 3) + D_00004608; }
