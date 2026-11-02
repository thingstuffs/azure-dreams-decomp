#include "common.h"
#include "town/devkit.h"
extern u32 D_A0700A60, D_A0700B48;
/* Replaces D_A0700A60 with its previous value times eight plus D_A0700B48. */
void shift_index_and_add_offset_c(void) { u32 *index = &D_A0700A60; *index = (*index << 3) + D_A0700B48; }
