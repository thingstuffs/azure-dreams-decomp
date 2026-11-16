#include "common.h"
#include "m2c_compat.h"

extern u8 D_800176D4[];
extern void *D_8001778C;
/* Stores D_800176D4 in D_8001778C. */
void set_shared_buffer_pointer(void) { D_8001778C = D_800176D4; }
