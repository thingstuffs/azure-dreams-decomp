#include "common.h"
extern u32 D_80700A3C, D_807013AC;
/* Replaces D_80700A3C with its previous value times eight plus D_807013AC. */
void advance_table_index_by_eight_byte_stride(void) { u32 *index = &D_80700A3C; *index = (*index << 3) + D_807013AC; }
