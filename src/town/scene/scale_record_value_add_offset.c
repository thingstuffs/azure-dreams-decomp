#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017868;
/* Stores 1 in D_80017868. */
void scale_record_value_and_add_offset(void) { D_80017868 = 1; }
