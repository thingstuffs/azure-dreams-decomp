#include "common.h"
extern u32 D_80700768, D_80700E44;
/* Replaces D_80700768 with its previous value times eight plus D_80700E44. */
void shift_index_and_add_offset(void) { u32 *index = &D_80700768; *index = (*index << 3) + D_80700E44; }
