#include "common.h"
#include "m2c_compat.h"

extern u8 D_800177AC[];
extern void *D_80017860;
void select_data_by_kind_and_index(void) { D_80017860 = D_800177AC; }
